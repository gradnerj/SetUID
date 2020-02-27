
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

//#include "employee.h"
/* Function Prototypes */

void EmployeeDirectory(void);
void ModifyDirectory(void);


struct Employee{

  char* lastName;
  char* firstName;
  char* position;
  int employeeID;
  char* phone;
};

struct EmpNode{
  struct EmpNode* llink;
  struct EmpNode* rlink;
  struct Employee* data;
};

struct EmpList{
  struct EmpNode* first;
  struct EmpNode* last;
  int count;
};

//List functions
void insert(struct EmpList* elist, struct EmpNode* enode);
