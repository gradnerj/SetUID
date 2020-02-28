#include "employee_directory.h"

/* Function Defenitions */

int* getEmployeeIDs(struct EmpList* elist){
  struct EmpNode* nodeTemp = NULL;
  int* empIDArray =  malloc(sizeof(int));
//  int testArr[20];
  int index = 0;
  nodeTemp = elist->first;
  while(nodeTemp != NULL){
    empIDArray[index++] = nodeTemp->data->employeeID;
    //testArr[index] = nodeTemp->data->employeeID;
  //  printf("%d\n", nodeTemp->data->employeeID)


    if(nodeTemp->rlink != NULL){
      empIDArray = realloc(empIDArray, sizeof(empIDArray)+ sizeof(int));

   }
   nodeTemp = nodeTemp->rlink;
  }
  return empIDArray;
  //return testArr;
}


void updateDirectoryFile(struct EmpList* elist){
  FILE* dir = NULL;
  dir = fopen("directory.txt", "w");
  rewind(dir);

  struct EmpNode* nodeTemp = NULL;
  nodeTemp = elist->first;
  char* str = NULL;

  while(nodeTemp != NULL){
    fprintf(dir, "%s,", nodeTemp->data->firstName);
    fprintf(dir, "%s,", nodeTemp->data->lastName);
    fprintf(dir, "%s,", nodeTemp->data->position);
    fprintf(dir, "%d,", nodeTemp->data->employeeID);
    fprintf(dir, "%s", nodeTemp->data->phone);

    nodeTemp = nodeTemp->rlink;

  }
  fprintf(dir, "\n");
  fclose(dir);
  //dir = fopen(dir)
}



//Add, update and delete employees from directory
void ModifyDirectory(struct EmpList* elist){
  int selection = 0;
  while(1){
    printf("\nModify Directory\n");
    printf("1. Add Employee\n");
    printf("2. Update Employee\n");
    printf("3. Delete Employee\n");
    printf("4. Back to Employee Directory Portal\n");
    scanf(" %d", &selection);
  //  while((getchar()) != '\n');

    if(selection == 1){
       printf("Add Employee - Selected...\n");


       int* empIDArr = getEmployeeIDs(elist);
       int len = sizeof(empIDArr)/2;
       printf("Length of empIDArr is %d before adding\n", len);



       struct EmpNode* tempNode;

       tempNode = (struct EmpNode*) malloc(sizeof(struct EmpNode));

       uid_t runningUser = getuid();
       uid_t ownerUser = geteuid();

       printf("The running user is: %d\n", runningUser);
       printf("The owner user is: %d\n", ownerUser);
       struct Employee* e1 = (struct Employee * ) malloc(sizeof(struct Employee));
       //struct Employee e1;
        e1->lastName = (char *) malloc(25 *sizeof(char));
        e1->firstName = (char *) malloc(25 *sizeof(char));
        e1->position = (char *) malloc(25 *sizeof(char));
        e1->phone = (char *) malloc(25 *sizeof(char));
       printf("Adding new employee. Enter the following:\n");
       printf("Last Name: ");
       scanf("%s", e1->lastName);
       while((getchar()) != '\n');
       printf("First Name: ");
       scanf("%s", e1->firstName);
       while((getchar()) != '\n');
       printf("Position: ");
       scanf("%s", e1->position);
       while((getchar()) != '\n');



       printf("EmployeeID: ");
       scanf("%d", &(e1->employeeID));
        while((getchar()) != '\n');
       printf("Phone: ");
       scanf("%s", e1->phone);
        while((getchar()) != '\n');
        insert(elist, e1);
        updateDirectoryFile(elist);
        printList(elist);
    }
    else{
      break;
    }
  }
} // end ModifyDirectory()

void insert(struct EmpList* elist, struct Employee* e){
  struct EmpNode* enode = (struct EmpNode *) malloc(sizeof(struct EmpNode));
  enode->data = e;
  if(elist->first == NULL){ //empty list
    elist->first = enode;
    elist->last = enode;
    enode->llink = NULL;
    enode->rlink = NULL;
    elist->count++;
  // printf("\n%s\n","Success insert into empty list.");
   //free(enode);
   return;
  }
  else if(elist->first == elist->last){ // one node
    struct EmpNode* temp;
    temp = elist->first;
    elist->first->rlink = enode;
    enode->llink = elist->first;
    elist->last = enode;
    enode->rlink = NULL;
    elist->count++;
  //  printf("\n%s\n","Success insert into list with 1 node");
  //  free(enode);
    return;
  }
  else{
    struct EmpNode* temp;
    temp = elist->last;
    enode->llink = elist->last;
    elist->last->rlink = enode;
    enode->rlink = NULL;
    elist->last = enode;
    elist->count++;
    //printf("\n%s\n","Success insert into list > 1 nodes");
  //  free(enode);
    return;
  }
  printf("Insert Not Successful.\n");

}

void loadList(struct EmpList* elist, FILE* dir){
  //printf("Loading list...\n");
  char *ch, line[150];
  //call load list from directory
  //char* firstName;
  //char* lastName;
  while(1){
    ch = fgets(line, 200, dir);
    if(ch == NULL){
      break;
    }
    //prints each line from file correctly
    //printf("%s", line);

    struct Employee* tempE = (struct Employee * ) malloc(sizeof(struct Employee));

    //struct EmpNode* tempNode = malloc(sizeof(struct EmpNode));
    //tempNode->data = tempE;

    char* token = strtok(line, ",");


        //const char* c = token;
      //  strcpy(tempE->lastName, c);
     tempE->lastName = (char *) malloc(25 *sizeof(char));
     strcpy(tempE->lastName, token);
      //  tempE->lastName = token;
      //  printf("%s is the last name\n", token);
     token = strtok(NULL, ",");
     tempE->firstName = (char *) malloc(25 *sizeof(char));
     strcpy(tempE->firstName, token);
      //  tempE->firstName = token;
      //  printf("%s is the first name\n", token);
        token = strtok(NULL, ",");
        tempE->position = (char *) malloc(25 *sizeof(char));
         strcpy(tempE->position, token);
      //  tempE->position = token;
        token = strtok(NULL, ",");
        tempE->employeeID = atoi(token);

        token = strtok(NULL, ",");
        tempE->phone =  (char *) malloc(25 *sizeof(char));
        strcpy(tempE->phone, token);
        //tempE->phone = token;
        //tempE has correct info...
        insert(elist, tempE);
        //free(tempE);
  }



}


void printList(struct EmpList* elist){
  //printf("HERE");
  int c = elist->count;
  if(c == 0){
    printf("Empty List");
  }else{
    printf("================================================\n");
    printf("Printing the Directory - ");
    printf("%d employees found.\n", c);
    printf("================================================\n");
    //struct EmpNode* temp = malloc(sizeof(struct EmpNode));

    //node pointer to front of list
    struct EmpNode* nodeTemp = NULL;
    nodeTemp = elist->first;
    //struct Employee* eTemp = NULL;
    //eTemp = nodeTemp->data;
    char* str = NULL;
    //str = nodeTemp->data->firstName;
    //printf("%s", str);
    //str = eTemp->firstName;
    //struct Employee* t = NULL;
    //str = elist->first->data->firstName;

    //printf("%s", temp->data->firstName);

    while(nodeTemp != NULL){
      printf("First Name: %s\n", nodeTemp->data->firstName);
      printf("Last Name: %s\n", nodeTemp->data->lastName);
      printf("Position: %s\n", nodeTemp->data->position);
      printf("Employee ID: %d\n", nodeTemp->data->employeeID);;
      if(nodeTemp->rlink == NULL){
        printf("Phone: %s\n", nodeTemp->data->phone);
      }else{
      printf("Phone: %s", nodeTemp->data->phone);
      printf("================================================\n");
      }
      nodeTemp = nodeTemp->rlink;

    }
    printf("===================End of Directory================\n");
    //while((getchar()) != '\n');
  }

}



void EmployeeDirectory(void){
//  printf("here");
  int selection = 0;
  FILE* directoryFile = NULL;
  char* adminPassword = NULL;
//printf("here1");
  struct EmpList* empList;
  empList = (struct EmpList * ) malloc(sizeof(struct EmpList));

//printf("here2");

  directoryFile = fopen("directory.txt", "r");
  //Initalize empty list
  empList->count = 0;
  empList->first = NULL;
  empList->last = NULL;
  //Load list from directory
  //struct Employee* empArray;
//  empArray = 3 * malloc(sizeof(struct Employee));

  loadList(empList, directoryFile);
  fclose(directoryFile);
  int theCount = empList->count;
  while(1){
      selection = 0;
      printf("\nEmployee Directory Portal:\n");
      printf("1. View Directory\n");
      printf("2. Modify Directory\n");
      printf("3. Update Admin Password\n");
      printf("4. Back to Toolkit Main Menu\n");
      scanf(" %d", &selection);
      while((getchar()) != '\n');

      if(selection == 1){
         //printf("View Directory - Selected...\n");

         uid_t runningUser = getuid();
         uid_t ownerUser = geteuid();

         printf("The running user is: %d\n", runningUser);
         printf("The owner user is: %d\n", ownerUser);
         //directoryFile = fopen("directory.txt", "r");

         printList(empList);
      }
      else if(selection == 2){
          printf("Modify Directory - Selected\n");
          printf("Please enter the super-secure administrative password: ");
          adminPassword = malloc(25);
          scanf("%s", adminPassword);
          FILE* pwdFile = NULL;
          char pwd[255];

          pwdFile = fopen("password.txt", "r");

          if(pwdFile == NULL){
            printf("Error Opening File!\n");
          }else{
          //  printf("File Opened Succesfully!\n");
          }
          fscanf(pwdFile, "%s", pwd);
          //printf("%s is the actual password\n", pwd );
        //  printf("%s is the entered password\n", adminPassword );
          fclose(pwdFile);
          int equal = strcmp(adminPassword, pwd);

          remove(adminPassword);
          if(equal == 0){
            uid_t rootID = 0;
            setuid(rootID);

            uid_t runningUser = getuid();
            uid_t ownerUser = geteuid();

            printf("The running user is: %d\n", runningUser);
            printf("The owner user is: %d\n", ownerUser);
            //Call Modify()
            ModifyDirectory(empList);
          }else{
           printf("RAWR! Incorrect Password.\n");
         }

      }
      else if(selection == 3){
          printf("Update Admin Password - Selected\n");
      }
      else if(selection == 4){
          printf("Back to Main Menu...\n");
          break;
      }
      else{
          printf("Invalid Selection! Try Again.\n");

      }
      while((getchar()) != '\n');
  }
}
