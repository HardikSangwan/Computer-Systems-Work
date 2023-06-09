/*
 * student.c
 * Multithreaded OS Simulation for CS 2200
 *
 * This file contains the CPU scheduler for the simulation.
 */

#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "os-sim.h"

/** Function prototypes **/
extern void idle(unsigned int cpu_id);
extern void preempt(unsigned int cpu_id);
extern void yield(unsigned int cpu_id);
extern void terminate(unsigned int cpu_id);
extern void wake_up(pcb_t *process);


/*
 * current[] is an array of pointers to the currently running processes.
 * There is one array element corresponding to each CPU in the simulation.
 *
 * current[] should be updated by schedule() each timeslice a process is scheduled
 * on a CPU.  Since the current[] array is accessed by multiple threads, you
 * will need to use a mutex to protect it.  current_mutex has been provided
 * for your use.
 */
static pcb_t **current;
static pthread_mutex_t current_mutex;
static pthread_cond_t not_idle;
static pcb_t *head;
static pcb_t *tail;
unsigned int cpu_count;
//static int num_proc;
//static int scheduler;
static pthread_mutex_t ready_q_mutex;
static int timeslice;
static int srtf = 0;

static void readyqadd(pcb_t *process) {
    pcb_t *temp = head;
    pthread_mutex_lock(&ready_q_mutex);
    if (head == NULL) {
        head = process;
    } else {
        while (temp -> next != NULL) {
            temp = temp -> next;
        }
        temp -> next = process;
    }
    process -> next = NULL;

    pthread_cond_signal(&not_idle);
    pthread_mutex_unlock(&ready_q_mutex);
} 

static pcb_t* readyqremove(void) {
    pcb_t *remove = head;
    pcb_t *previous = head;
    pthread_mutex_lock(&ready_q_mutex);
    if (head == NULL) {
        pthread_mutex_unlock(&ready_q_mutex);
        return NULL;
    } else {
        if(!srtf) {
            if(!(head -> next)) {
                tail = NULL;
            }
            head = head -> next;
        } else {
            unsigned int shortest = UINT_MAX;
            while(remove) {
                if(remove -> time_remaining < shortest) {
                    shortest = remove -> time_remaining;
                }
                remove = remove -> next;
            }
            remove = head;
            while (remove -> time_remaining != shortest) {
                previous = remove;
                remove = remove -> next;
            }
            if (remove == head) {
                if(!(head -> next)) {
                    tail = NULL;
                }
                head = head -> next;
            } else {
                if (remove == tail) {
                    tail = previous;
                }
                previous -> next = remove -> next;
            }
        }
        pthread_mutex_unlock(&ready_q_mutex);
        return remove;
    }
    return remove;
}
/*
 * schedule() is your CPU scheduler.  It should perform the following tasks:
 *
 *   1. Select and remove a runnable process from your ready queue which 
 *	you will have to implement with a linked list or something of the sort.
 *
 *   2. Set the process state to RUNNING
 *
 *   3. Call context_switch(), to tell the simulator which process to execute
 *      next on the CPU.  If no process is runnable, call context_switch()
 *      with a pointer to NULL to select the idle process.
 *	The current array (see above) is how you access the currently running process indexed by the cpu id. 
 *	See above for full description.
 *	context_switch() is prototyped in os-sim.h. Look there for more information 
 *	about it and its parameters.
 */
static void schedule(unsigned int cpu_id)
{
    /* FIX ME */
    pcb_t *rem = readyqremove();
    if (rem != NULL) {
        rem -> state = PROCESS_RUNNING;
    }
    pthread_mutex_lock(&current_mutex);
    current[cpu_id] = rem;
    pthread_mutex_unlock(&current_mutex);
    context_switch(cpu_id, rem, timeslice);
}


/*
 * idle() is your idle process.  It is called by the simulator when the idle
 * process is scheduled.
 *
 * This function should block until a process is added to your ready queue.
 * It should then call schedule() to select the process to run on the CPU.
 */
extern void idle(unsigned int cpu_id)
{
    /* FIX ME */
    pthread_mutex_lock(&ready_q_mutex);
    while (head == NULL) {
        pthread_cond_wait(&not_idle, &ready_q_mutex);
    }
    pthread_mutex_unlock(&ready_q_mutex);
    schedule(cpu_id);

    /*
     * REMOVE THE LINE BELOW AFTER IMPLEMENTING IDLE()
     *
     * idle() must block when the ready queue is empty, or else the CPU threads
     * will spin in a loop.  Until a ready queue is implemented, we'll put the
     * thread to sleep to keep it from consuming 100% of the CPU time.  Once
     * you implement a proper idle() function using a condition variable,
     * remove the call to mt_safe_usleep() below.
     */
    //mt_safe_usleep(1000000);
}


/*
 * preempt() is the handler called by the simulator when a process is
 * preempted due to its timeslice expiring.
 *
 * This function should place the currently running process back in the
 * ready queue, and call schedule() to select a new runnable process.
 */
extern void preempt(unsigned int cpu_id)
{
    /* FIX ME */
    pthread_mutex_lock(&current_mutex);
    current[cpu_id] -> state = PROCESS_READY;
    readyqadd(current[cpu_id]);
    pthread_mutex_unlock(&current_mutex);
    schedule(cpu_id);
}


/*
 * yield() is the handler called by the simulator when a process yields the
 * CPU to perform an I/O request.
 *
 * It should mark the process as WAITING, then call schedule() to select
 * a new process for the CPU.
 */
extern void yield(unsigned int cpu_id)
{
    /* FIX ME */
    pthread_mutex_lock(&current_mutex);
    current[cpu_id] -> state = PROCESS_WAITING;
    pthread_mutex_unlock(&current_mutex);
    schedule(cpu_id);
}


/*
 * terminate() is the handler called by the simulator when a process completes.
 * It should mark the process as terminated, then call schedule() to select
 * a new process for the CPU.
 */
extern void terminate(unsigned int cpu_id)
{
    /* FIX ME */
    pthread_mutex_lock(&current_mutex); 
    current[cpu_id] -> state = PROCESS_TERMINATED;
    pthread_mutex_unlock(&current_mutex);   
    schedule(cpu_id);
}


/*
 * wake_up() is the handler called by the simulator when a process's I/O
 * request completes.  It should perform the following tasks:
 *
 *   1. Mark the process as READY, and insert it into the ready queue.
 *
 *   2. If the scheduling algorithm is SRTF, wake_up() may need
 *      to preempt the CPU with the highest remaining timeslice left to allow it to
 *      execute the process which just woke up.  However, if any CPU is
 *      currently running idle, or all of the CPUs are running processes
 *      with a lower remaining timeslice left than the one which just woke up, wake_up()
 *      should not preempt any CPUs.
 *	To preempt a process, use force_preempt(). Look in os-sim.h for 
 * 	its prototype and the parameters it takes in.
 */
extern void wake_up(pcb_t *process)
{
    /* FIX ME */
    unsigned int i = 0;
    unsigned int id = UINT_MAX;
    unsigned int longest = id;
    process -> state = PROCESS_READY;
    readyqadd(process);

    if(srtf) {
        pthread_mutex_lock(&current_mutex);
        while (i < cpu_count) {
            if(current[i] == NULL) {
                id = UINT_MAX;
                break;
            }
            if(current[i] -> time_remaining > longest) {
                longest = current[i] -> time_remaining;
                id = i;
            }
            i++;
        }
        pthread_mutex_unlock(&current_mutex);
        if(id != UINT_MAX && longest > process -> time_remaining) {
            force_preempt(id);
        }
    }

}


/*
 * main() simply parses command line arguments, then calls start_simulator().
 * You will need to modify it to support the -r and -s command-line parameters.
 */
int main(int argc, char *argv[])
{
    /* Parse command-line arguments */
    if (argc < 2 || argc > 4)
    {
        fprintf(stderr, "CS 2200 OS Sim -- Multithreaded OS Simulator\n"
            "Usage: ./os-sim <# CPUs> [ -r <timeslice slice> | -s ]\n"
            "    Default : FIFO Scheduler\n"
            "         -r : Round-Robin Scheduler\n"
            "         -s : Shortest Remaining timeslice First Scheduler\n\n");
        return -1;
    } 

    cpu_count = strtoul(argv[1], NULL, 0);

    /* FIX ME - Add support for -r and -s parameters*/
    if (argc > 2 ) {
        if(!(strcmp(argv[2], "-s"))) {
            printf("Shortest Remaining timeslice First Scheduler\n");
            timeslice = -1;
            srtf = 1;
        } else if(!(strcmp(argv[2], "-r"))) {
            printf("Round-Robin Scheduler\n");
            timeslice = atoi(argv[3]);
        } else {
            printf("FIFO Scheduler\n");
            timeslice = -1;
        }
    }

    /* Allocate the current[] array and its mutex */
    current = malloc(sizeof(pcb_t*) * cpu_count);
    assert(current != NULL);
    head = NULL;
    tail = NULL;
    pthread_mutex_init(&current_mutex, NULL);
    pthread_mutex_init(&ready_q_mutex, NULL);
    pthread_cond_init(&not_idle, NULL);

    /* Start the simulator in the library */
    start_simulator(cpu_count);

    return 0;
}


