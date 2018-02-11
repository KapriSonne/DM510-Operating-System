#include <stdio.h>
#include <stdlib.h>

// Structs is usefull for when we need a single name to refer to a
// group of related values. In structs we can store values in variables
// of different types. e.g:
struct database {
  int id;
  int age;
  float salary;
  int *size;
};

int main(){
  
  // now we have created an variable named 'employee' which
  // has modifiable variables inside it
  struct database employee;

  // here we assign values to that explicit variable's variables.
  // This is done by e.g 'employee.age'
  employee.age = 33;
  employee.id = 42;
  employee.salary = 120.00;

  int someRandomVariable = 20;
  employee.size = &someRandomVariable;

  // lets print stuff
  printf("%s\n","employee:" );
  printf("ID: %d\n",employee.id);
  printf("Age: %d\n",employee.age);
  printf("Salary: %f\n",employee.salary);
  printf("Size: %d\n",*employee.size);
  printf("%s\n","");

  // If we allocate a variable 'house' on the heap, based on the sizeof
  // our database struct, we would do like this:
  struct database *house = malloc(sizeof(struct database));

  // we could assign a value to house id like this:
  (*house).id = 22;

  // however this is more readable and do the same:
  house->id = 10;
  house->size = &someRandomVariable;

  // lets print some stuff again
  printf("%s\n","Some house:" );
  printf("ID: %d\n",house->id);
  printf("Size: %d\n",*house->size);

  // lets clean up our heap
  free(house);

  return 0;
}
