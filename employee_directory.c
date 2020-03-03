#include "employee_directory.h"

/* Function Defenitions */


void deleteEmployee(struct EmpList* elist){
  if(elist->count == 0){
    printf("There are no employees to delete.\n");
    return;
  }
  //int empid;
  printList(elist);
   int* idArr = getEmployeeIDs(elist);
   printf("Please enter the ID of the employee you would like to update: ");
   int IDtemp = 0;
   scanf("%d", &IDtemp);

   struct EmpNode* temp;
   temp = elist->first;
   if(elist->count == 1){
     elist->first = NULL;
     elist->last = NULL;
     elist->count--;
     free(temp);
     return;
   }else{
     while(temp != NULL){
       if(temp->data->employeeID == IDtemp){
         if(temp == elist->first){
           elist->first = temp->rlink;
           elist->first->llink = NULL;
           temp->rlink = NULL;
           elist->count--;
           printf("Successfully Deleted\n");
           free(temp);
           return;
         }else if(temp == elist->last){
           elist->last = temp->llink;
           elist->last->rlink = NULL;
           temp->llink = NULL;
           elist->count--;
           printf("Successfully Deleted\n");
           free(temp);
           return;
         }else{
          temp->llink->rlink = temp->rlink;
          temp->rlink->llink = temp->llink;
          temp->llink = NULL;
          temp->rlink = NULL;
          elist->count--;
          printf("Successfully Deleted\n");
          free(temp);
          return;
         }
       }
       temp = temp->rlink;
     }
     printf("No employee deleted.\n");
   }




}


int* getEmployeeIDs(struct EmpList* elist){
  struct EmpNode* nodeTemp = NULL;
  int listSize = elist->count;
  int* empIDArray =  malloc(sizeof(int) * listSize);

  int index = 0;
  nodeTemp = elist->first;
  while(nodeTemp != NULL){
   empIDArray[index++] = nodeTemp->data->employeeID;
   //printf("empid%d : %d\n",index, nodeTemp->data->employeeID);
   nodeTemp = nodeTemp->rlink;
  }
  return empIDArray;
  //return testArr;
}
//updates text file from list object
void updateDirectoryFile(struct EmpList* elist){
  FILE* dir = NULL;
  dir = fopen("directory.txt", "w");
  //rewind(dir);

  struct EmpNode* nodeTemp = NULL;
  nodeTemp = elist->first;
  char* str = NULL;

  while(nodeTemp != NULL){


    fprintf(dir, "%s,", nodeTemp->data->firstName);
    fprintf(dir, "%s,", nodeTemp->data->lastName);
    fprintf(dir, "%s,", nodeTemp->data->position);
    fprintf(dir, "%d,", nodeTemp->data->employeeID);
    int len;

    len = strlen(nodeTemp->data->phone);
    if( nodeTemp->data->phone[len-1] == '\n' ){
        nodeTemp->data->phone[len-1] = 0;
      }
    fprintf(dir, "%s\n", nodeTemp->data->phone);



    nodeTemp = nodeTemp->rlink;

  }
  //fprintf(dir, "\n");
  fclose(dir);
  //dir = fopen(dir)
}

bool id_exists(int id, int* idArr, int count){
  for(int i =0; i< count; i++){
    if(id == idArr[i]){
      printf("Error: that Employee ID already exists in the directory.\nPlease update that entry or enter a new Employee ID.\n");
      return true;
    }
  }
  return false;
}
//Get employee by ID
struct Employee* getEmployeeByID(struct EmpList* elist, int empID){
  struct EmpNode* nodeTemp = NULL;
  nodeTemp = elist->first;
  while(nodeTemp != NULL){
   if(nodeTemp->data->employeeID == empID){
     return nodeTemp->data;
   }
   //printf("empid%d : %d\n",index, nodeTemp->data->employeeID);
   nodeTemp = nodeTemp->rlink;
  }
  printf("Employee Not Found.\n");
  return NULL;
}

void updateEmployee(struct EmpList* elist){

 printList(elist);
 if(elist->count == 0){
   return;
 }
  int* idArr = getEmployeeIDs(elist);
  printf("Please enter the ID of the employee you would like to update: ");
  int IDtemp = 0;
  scanf("%d", &IDtemp);
  //while((getchar()) != '\n');
  struct Employee* emp = NULL;
  emp = getEmployeeByID(elist, IDtemp);
  if(emp == NULL){
    return;
  }
  while(1){
    int s = 0;
    printf("Which field would you like to update?\n");
    //while((getchar()) != '\n');
    printf("1. First Name: %s\n", emp->firstName);
    printf("2. Last Name: %s\n", emp->lastName);
    printf("3. Position: %s\n", emp->position);
    printf("4. Employee ID %d\n", emp->employeeID);


    int len;

    len = strlen(emp->phone);
    if( emp->phone[len-1] == '\n' ){
        emp->phone[len-1] = 0;
      }
    printf("5. Phone %s", emp->phone);
    printf("\n6. To Finish\n");
    scanf("%d", &s);
  //  printf("Selection contains: %d\n", s);
    if(s == 1){
        printf("New First Name: ");
        scanf("%s", emp->firstName);
        while((getchar()) != '\n');
        //scanf("New First Name: %s", emp->firstName);
      }else if(s == 2){
        printf("New Last Name: ");
        scanf("%s", emp->lastName);
        while((getchar()) != '\n');
      }else if(s == 3){
        printf("New Position: ");
        scanf("%s", emp->position);
        while((getchar()) != '\n');
      }else if(s == 4){
        int IDtemp;
        int* empIDArr = getEmployeeIDs(elist);
        do{
        printf("New EmployeeID: ");
        scanf("%d", &(IDtemp));
        while((getchar()) != '\n');

       }while(id_exists(IDtemp, empIDArr, elist->count));
       emp->employeeID = IDtemp;
      }else if(s == 5){
        printf("New Phone: ");
        scanf("%s", emp->phone);
        while((getchar()) != '\n');
      }else if(s == 6){
        break;
      }else{
        printf("That is an invalid selection. Please try again.\n");
      }
  }//end while
  //updateDirectoryFile(elist);
}

void addEmployee(struct EmpList* elist){
  int* empIDArr = getEmployeeIDs(elist);

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


  int IDtemp;

  do{
  printf("EmployeeID: ");
  scanf("%d", &(IDtemp));
  while((getchar()) != '\n');

 }while(id_exists(IDtemp, empIDArr, elist->count));

 e1->employeeID = IDtemp;


  printf("Phone: ");
  scanf("%s", e1->phone);
   while((getchar()) != '\n');
   insert(elist, e1);
   //updateDirectoryFile(elist);
   printList(elist);
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
       addEmployee(elist);
    }
    else if(selection == 2){
      printf("Update Employee - Selected...\n");
      updateEmployee(elist);
    }
    else if(selection == 3){
      printf("Delete Employee - Selected\n");
      deleteEmployee(elist);
    }
    else{
      updateDirectoryFile(elist);
      break;
    }
  }

}

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

  while(1){
    ch = fgets(line, 200, dir);
    if(ch == NULL|| ch == ""){
      break;
    }
    //prints each line from file correctly
    //printf("%s", line);

    struct Employee* tempE = (struct Employee * ) malloc(sizeof(struct Employee));

    //struct EmpNode* tempNode = malloc(sizeof(struct EmpNode));
    //tempNode->data = tempE;

    char* token = strtok(line, ",");
    tempE->firstName = (char *) malloc(25 *sizeof(char));
    strcpy(tempE->firstName, token);


     token = strtok(NULL, ",");
     tempE->lastName = (char *) malloc(25 *sizeof(char));
     strcpy(tempE->lastName, token);
      //  tempE->firstName = token;
      //  printf("%s is the first name\n", token);
        token = strtok(NULL, ",");
        tempE->position = (char *) malloc(25 *sizeof(char));
         strcpy(tempE->position, token);
      //  tempE->position = token;
        token = strtok(NULL, ",");
        tempE->employeeID = atoi(token);

        token = strtok(NULL, "\n");
        tempE->phone =  (char *) malloc(25 *sizeof(char));

        /*int len;

        len = strlen(nodeTemp->data->phone);
        if( nodeTemp->data->phone[len-1] == '\n' ){
            nodeTemp->data->phone[len-1] = 0;
          }*/
        //printf("Phone token in loadList %s\n", token);
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
        printf("Phone: %s", nodeTemp->data->phone);
      }else{
      printf("Phone: %s", nodeTemp->data->phone);
      printf("\n================================================\n");
      }
      nodeTemp = nodeTemp->rlink;

    }
    printf("\n===================End of Directory================\n");
    //while((getchar()) != '\n');
  }

}

void EmployeeDirectory(uid_t startID){

  int selection = 0;
  FILE* directoryFile = NULL;
  char* adminPassword = NULL;

  struct EmpList* empList;
  empList = (struct EmpList * ) malloc(sizeof(struct EmpList));

if(fopen("directory.txt", "r") == NULL){
  directoryFile = fopen("directory.txt", "w");
}
else{
  directoryFile = fopen("directory.txt", "r");
}
  //directoryFile = fopen("directory.txt", "ab+");
  uid_t rootid = 0;
  gid_t gid = 0;
  seteuid(rootid);

  //mode_t m = 644;
  chown("./directory.txt", rootid, gid);
  //int success = chmod("./directory.txt", m);
  //printf("%d is the success\n", success);
  seteuid(startID);
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

    printf("The running user in EmpDir() is: %d\n", getuid());
    printf("The owner user in EmpDir() is: %d\n", geteuid());
      selection = 0;
      printf("\nEmployee Directory Portal:\n");
      printf("1. View Directory\n");
      printf("2. Modify Directory\n");
      printf("3. Update Admin Password\n");
      printf("4. Back to Toolkit Main Menu\n");
      scanf(" %d", &selection);
      while((getchar()) != '\n');

      if(selection == 1){
         printf("The running user is: %d\n", getuid());
         printf("The owner user is: %d\n", geteuid());
         printList(empList);
      }
      else if(selection == 2){
          printf("Modify Directory - Selected\n");
          printf("Please enter the super-secure administrative password: ");
          adminPassword = malloc(25);
          scanf("%s", adminPassword);
          FILE* pwdFile = NULL;
          char pwd[255];
          uid_t rootID = 0;
          seteuid(rootID);
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
          seteuid(startID);
          int equal = strcmp(adminPassword, pwd);

          remove(adminPassword);
          if(equal == 0){
            uid_t rootID = 0;
            seteuid(rootID);

            printf("The running user right before modify is: %d\n", getuid());
            printf("The owner user right before modify is: %d\n", geteuid());

            ModifyDirectory(empList);
            seteuid(startID);

          }else{
           printf("RAWR! Incorrect Password.\n");
         }

      }
      else if(selection == 3){
          printf("Update Admin Password - Selected\n");
          printf("Please enter the super-secure administrative password: ");
          adminPassword = malloc(25);
          scanf("%s", adminPassword);
          FILE* pwdFile = NULL;
          char pwd[255];

          uid_t rootID = 0;
          seteuid(rootID);

          printf("The running user in update password is: %d\n", getuid());
          printf("The owner user in update password is: %d\n", geteuid());

          pwdFile = fopen("password.txt", "r");

          if(pwdFile == NULL){
            printf("Error Opening File!\n");
          }

          fscanf(pwdFile, "%s", pwd);
          //printf("%s is the actual password\n", pwd );
        //  printf("%s is the entered password\n", adminPassword );
          fclose(pwdFile);
          seteuid(startID);
          int equal = strcmp(adminPassword, pwd);

          remove(adminPassword);
          if(equal == 0){
            printf("Please enter a new password: ");
            char newPassword[255];
            scanf("%s", newPassword);
            seteuid(rootID);
              pwdFile = fopen("password.txt", "w");
              fprintf(pwdFile, "%s", newPassword);
              fclose(pwdFile);
            seteuid(startID);
          }
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
