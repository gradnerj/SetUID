#include "employee_directory.h"

/* Function Defenitions */

//Add, update and delete employees from directory
void ModifyDirectory(){
  int selection = 0;
  while(1){
    printf("Modify Directory\n");
    printf("1. Add Employee\n");
    printf("2. Update Employee\n");
    printf("3. Delete Employee\n");
    printf("4. Back to Employee Directory Portal\n");
    scanf(" %d", &selection);
    while((getchar()) != '\n');

    if(selection == 1){
       printf("Add Employee - Selected...\n");
       uid_t runningUser = getuid();
       uid_t ownerUser = geteuid();

       printf("The running user is: %d\n", runningUser);
       printf("The owner user is: %d\n", ownerUser);
       struct Employee e1;

       printf("Adding new employee. Enter the following:\n");
       printf("Last Name: ");
       scanf("%s", e1.lastName);
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





void EmployeeDirectory(void){
  int selection = 0;
  FILE* directoryFile = NULL;
  char* adminPassword = NULL;

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
         directoryFile = fopen("directory.txt", "ab+");

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
