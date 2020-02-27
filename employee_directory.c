#include "employee_directory.h"

/* Function Defenitions */

//Add, update and delete employees from directory
void ModifyDirectory(){
  int selection = 0;
  while(1){
    printf("\nModify Directory\n");
    printf("1. Add Employee\n");
    printf("2. Update Employee\n");
    printf("3. Delete Employee\n");
    printf("4. Back to Employee Directory Portal\n");
    scanf(" %d", &selection);
    while((getchar()) != '\n');

    if(selection == 1){
       printf("Add Employee - Selected...\n");

       struct EmpNode* tempNode;

       tempNode = malloc(sizeof(struct EmpNode));

       uid_t runningUser = getuid();
       uid_t ownerUser = geteuid();

       printf("The running user is: %d\n", runningUser);
       printf("The owner user is: %d\n", ownerUser);
       struct Employee e1;

       printf("Adding new employee. Enter the following:\n");
       printf("Last Name: ");
       scanf("%s", e1.lastName);
       while((getchar()) != '\n');
       printf("First Name: ");
       scanf("%s", e1.firstName);
       while((getchar()) != '\n');
       printf("Position: ");
       scanf("%s", e1.position);
       while((getchar()) != '\n');
       printf("EmployeeID: ");
       scanf("%d", &(e1.employeeID));
        while((getchar()) != '\n');
       printf("Phone: ");
       scanf("%s", e1.phone);
        while((getchar()) != '\n');

      (*tempNode).data = &e1;
      //insert(elist, tempNode);
       //create  an employee struct instance
       //load information from ownerUser
       //write out in CSV format

      // directoryFile = fopen("directory.txt", "ab+");

    }
    else{
      break;
    }
  }
} // end ModifyDirectory()

void insert(struct EmpList* elist, struct Employee* e){
  struct EmpNode* enode = (struct EmpNode *) malloc(sizeof(struct EmpNode));
  enode->data = e;

  /*char* testName = NULL;
  testName = enode->data->firstName;
  printf("The first name inside insert function is: %s\n", testName);*/



//printf("inserting now...\n");
  if(elist->first == NULL){ //empty list
    elist->first = enode;
    elist->last = enode;
    enode->llink = NULL;
    enode->rlink = NULL;
    elist->count++;
  // printf("\n%s\n","Success insert into empty list.");
  // free(enode);
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


void EmployeeDirectory(void){
  int selection = 0;
  FILE* directoryFile = NULL;
  char* adminPassword = NULL;

  struct EmpList* empList;
  empList = (struct EmpList * ) malloc(sizeof(struct EmpList));



  directoryFile = fopen("directory.txt", "r");
  //Initalize empty list
  empList->count = 0;
  empList->first = NULL;
  empList->last = NULL;
  //Load list from directory
  //struct Employee* empArray;
//  empArray = 3 * malloc(sizeof(struct Employee));

  loadList(empList, directoryFile);

  int theCount = empList->count;
//  printf("Load finished. The count is: %d\n", theCount);



/*  struct EmpNode* tnode;
  tnode = empList->first;
  while(tnode->rlink != NULL){
    printf("Moved a link\n");
    tnode = tnode->rlink;
  }
  tnode = empList->first;
  char* str = NULL;
  str = tnode->data->firstName;


  //works?!?!?
  int x = tnode->data->employeeID;
//  printf("The empID is %d", x);

  char pleaseWork[15];
  strcpy(pleaseWork, tnode->data->lastName); */
//  pleaseWork = tnode->data->firstName;
//  printf("The name is %s", pleaseWork);


  printf("Printing the list\n");
  printList(empList);

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
         printf("View Directory - Selected...\n");
         uid_t runningUser = getuid();
         uid_t ownerUser = geteuid();

         printf("The running user is: %d\n", runningUser);
         printf("The owner user is: %d\n", ownerUser);
         //directoryFile = fopen("directory.txt", "r");

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
            printf("File Opened Succesfully!\n");
          }
          fscanf(pwdFile, "%s", pwd);
          printf("%s is the actual password\n", pwd );
          printf("%s is the entered password\n", adminPassword );
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
            ModifyDirectory();
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





void printList(struct EmpList* elist){
  //printf("HERE");
  int c = elist->count;
  if(c == 0){
    printf("Empty List");
  }else{
    printf("%d employees in the list.\n", c);
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
      printf("Phone: %s\n\n", nodeTemp->data->phone);
      nodeTemp = nodeTemp->rlink;
    }
  }
  /*if(elist.count == 0){
    printf("The list is empty.\n");
  }else{
    struct EmpNode* temp;
    temp = elist.first;
    while(temp != NULL){
      printf("%s\n", temp->data->firstName);
      printf("%s\n", temp->data->lastName);
      printf("%s\n", temp->data->position);
      printf("%d\n", temp->data->employeeID);;
      printf("%s\n\n", temp->data->phone);
      temp = temp->rlink;
    }
  }*/
}
