
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
 #include <sys/stat.h>
//#include "employee.h"
/* Function Prototypes */

void EmployeeDirectory(uid_t startID);



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
void ModifyDirectory(struct EmpList* elist);
//List functions
void insert(struct EmpList* elist, struct Employee* e);
void deleteEmployee(struct EmpList* elist);
void updateEmployee(struct EmpList* elist);
void addEmployee(struct EmpList* elist);
struct Employee* getEmployeeByID(struct EmpList* elist, int empID);

void loadList(struct EmpList* elist, FILE* dir);
void printList(struct EmpList* elist);
void updateDirectoryFile(struct EmpList* elist);
int* getEmployeeIDs(struct EmpList* elist);
bool id_exists(int id, int* idArr, int count);
