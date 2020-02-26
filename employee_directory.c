#include "employee_directory.h"



/* Function Defenitions */
void EmployeeDirectory(void){
  int selection = 0;
  FILE* directoryFile = NULL;

  while(1){

      selection = 0;
      printf("\nEmployee Directory Portal:\n");
      printf("1. View Directory\n");
      printf("2. Modify Directory\n");
      printf("3. Update Admin Password\n");
      printf("4. Exit\n");
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
          uid_t rootID = 0;
          setuid(rootID);

          uid_t runningUser = getuid();
          uid_t ownerUser = geteuid();

          printf("The running user is: %d\n", runningUser);
          printf("The owner user is: %d\n", ownerUser);

      }
      else if(selection == 3){
          printf("Update Admin Password - Selected\n");
      }
      else if(selection == 4){
          printf("Goodbye...\n");
          break;
      }
      else{
          printf("Invalid Selection! Try Again.\n");

      }
  }
}
