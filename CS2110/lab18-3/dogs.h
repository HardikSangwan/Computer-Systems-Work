#define UNUSED(param) ((void)((param)))

typedef struct {
    char *name;
    int age;
} Dog;

Dog *createDogArray(int numDogs);
void setDogAtIndex(Dog *dogArray, int index, char *name, int age);
void printDogs(Dog *dogArray, int numDogs);