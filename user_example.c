
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
/* Function Prototypes */

/* Main Function */
int main()
{
    uid_t runningUser = getuid();
    uid_t ownerUser = geteuid();

    printf("The running user is: %d\n", runningUser);
    printf("The owner user is: %d\n", ownerUser);

}
/* Function Defenitions */

