
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
