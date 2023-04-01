#include "todo.h"
#include "useful_strings.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void print_menu(void);
void print_todo_list(void);
void add_to_todo_list(void);
void mark_completed(void);
void remove_completed(void);
void save_todo_array(char *);
void save_todo_file(void);

int main(int argc, char* argv[]) {
       	if (argc == 1) {
        	print_menu();
        }
        else if (argc == 2) {
       		save_todo_array(argv[1]);
       	}
       	else {
          printf("%s", ERROR_USAGE);
       		exit(1);
       	}

}

void print_menu(void) {
    printf("%s%s%s%s", MAIN_MENU_HEADER, QUERY, OPTIONS_LIST, GRAB_INPUT);
    char buffer[1280];
    char *input = fgets(buffer, 1280, stdin);
        if (*input == '1') {
          print_todo_list();
        }
        else if (*input == '2') {
          add_to_todo_list();
        }
        else if (*input == '3'){
          mark_completed();
        }
        else if (*input == '4') {
          remove_completed();
        }
        else if (*input == '5') {
          save_todo_file();
        }
        else if (*input == '6') {
          exit(0);
        }
        else {
          printf("%s", INVALID_CHOICE);
          print_menu();
        }
}

void print_todo_list(void) {
  printf("%s", TODO_LIST_HEADER);
  for(int i=0; i<Todo_list_length; i++)  
    {  
        printf("%s\n\n", Todo_list[i].title);
        if (Todo_list[i].is_done == 1) {
          printf("%s", COMPLETED);
        } 
        else{
          printf("Due: %02d/%02d/%04d\n", Todo_list[i].due_month, Todo_list[i].due_day, Todo_list[i].due_year);
        }
        printf("Description: %s\n", Todo_list[i].description);
        printf("%s", LINE_BREAK);
    }
    print_menu();
}

void add_to_todo_list(void) {
  printf("%s", ADD_TO_LIST_HEADER);
  if (Todo_list_length >= TODO_LIST_MAX) {
      printf("%s", LIST_MAX);
      print_menu();
  } else {
      printf("%s", ADD_TO_LIST);
      read_todo_list_item(stdin);
      print_menu();
  }
  
}

void mark_completed(void) {
  printf("%s%s%s", MARK_ITEM_COMPLETED_HEADER, MARK_ITEM_USER_INPUT, GRAB_INPUT);
  char buffer[128];
  char *input = fgets_no_newline(buffer, 128, stdin);
  int index = *input - 48;
  Todo_list[index].is_done = 1;
  print_menu();
}

void remove_completed(void) {
  printf("%s", REMOVE_ITEM_HEADER);
  int removed_count = 0;
  for(int i=0; i<Todo_list_length; i++)  {
      if (Todo_list[i].is_done == 1){
        removed_count += 1;
        if (i == Todo_list_length - 1) {
        }
          else {
            for(int j=i; j<Todo_list_length-1; j++){
              Todo_list[j] = Todo_list[j+1];
            }
          }
      Todo_list_length -=1;
      i--;
    }
  }
  printf("Success! %d items removed!\n", removed_count);
  print_menu();  
}

void save_todo_array(char *arg) {
  FILE *in_file = fopen(arg, "r");
  if (in_file == NULL) {
    printf("ERROR: File, %s, does not exist!\n", arg);
    exit(1);
  }
  while (feof(in_file) != 1 && read_todo_list_item(in_file) !=0){
  read_todo_list_item(in_file);
  }
  fclose(in_file);
  print_menu();
}

void save_todo_file(void){
  printf("%s", SAVE_FILE_HEADER);
  printf("%s", INPUT_FILE_NAME);
  printf("%s", GRAB_INPUT);
  char buffer[128];
  char *input = fgets_no_newline(buffer, 128, stdin);
  FILE *out_file = fopen(input, "w");
  if (out_file == NULL) {
    printf("ERROR");
    exit(1);
  }
  for (int i = 0; i < Todo_list_length; i++) {
    fprintf(out_file, "%s\n%s\n%d\n%d\n%d\n%d\n", Todo_list[i].title, Todo_list[i].description, Todo_list[i].is_done, Todo_list[i].due_day, Todo_list[i].due_month, Todo_list[i].due_year);
  }
  fclose(out_file);
  print_menu();
}
