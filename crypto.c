/*!
 *    \file  crypto.c
 *   \brief
 *
 *  \author  Jeff Gradner, jeffreygradner@mail.weber.edu
 *  \internal
 *       Created:  01/14/2020
 *      Revision:  none
 *      Compiler:  gcc
 *  Organization:
 *     Copyright:  Copyright (c) 2020, Jeff Gradner
 */

#include "crypto.h"
//void Encrypt(void);
//void Decrypt(void);
int getSize(char* s);
extern int errno;

void Encrypt(void){

    char key;
    long size = 0;
    int i = 0;
    int errnum = 0;
    FILE* file = NULL;
    char* inFile = NULL;
    char* outFile = NULL;
    char* pText = NULL;
    char* eText = NULL;



    char *line = NULL;
    size_t len = 0;
    size_t read;

    while(1){
        printf("Please enter an encryption key (1 letter will be used): ");
        //while((getchar()) != '\n');
        scanf(" %c", &key);
        //key = getchar();
        while((getchar()) != '\n');
        //printf("%c is the key.......", key);
        if (key  >= 'a' && key <= 'z'){ //Might be uppercase
            key = key - 32;
            break;
        }
        if(key >= 'A' && key <= 'Z'){
            break;
               // printf("Sorry that is an invalid key...try again.\n");
                //continue;
        }else{
               printf("Sorry that is an invalid key...try again.\n");
               continue;
            }
        }




    //printf("\nThe key you've entered is: %c\n", key);
    key = key - 'A';
    //while((getchar()) != '\n');
    while(true){
        //while((getchar()) != '\n');
        printf("Please enter the file you'd like to encrypt: ");

        inFile = malloc(25);
        scanf("%24s", inFile);
        //printf("The file you've selected is: %s\n", inFile);


        file = fopen(inFile, "r");
        if(file == NULL){
            errnum = errno;
            //fprintf(stderr, "Value of error: %d\n", errno);
            //perror("Error printed by perror");
            fprintf(stderr, "Error opening file: %s\n", strerror(errnum));
            while((getchar()) != '\n');
            continue;
        }
        else{
            //Seek the position of END from file <file> with 0L (0) byte offset from position
            fseek(file, 0L, SEEK_END);
            //ftell returns position of file pointer with respect to starting position file
            size = ftell(file);
            //sets file position to beginning of file
            rewind(file);

            pText = malloc(size);
            eText = malloc(size);
            if( !pText ) fclose(file),fputs("memory alloc fails",stderr),exit(1);

            /* copy the file into the buffer */
            //if( 1!=fread( pText , size, 1 , file) ){
             //   fclose(file),free(pText),fputs("entire read fails",stderr),exit(1);
            //}
            while((read = getline(&line, &len, file)) != -1){
               // printf("%s", line);
                strcat(pText, line);

            }
            //pText[strcspn(pText, "\n")] = 0;
            //printf("%s is the contents of the file...", pText);
            //fclose(file);
            remove(inFile);
            fclose(file);
            //free(pText);
            break;
        }
    }
    //size = getSize(pText);
   // eText = malloc(size);

    //printf("\nSize of pText = %d\n", size);
   // printf("pText value = %s\n", pText);

    //Convert plain text to UPPERCASE
    for (i = 0; pText[i]!='\0'; i++) {
      if(pText[i] >= 'a' && pText[i] <= 'z') {
         pText[i] = pText[i] -32;
      }
    }

    for(i = 0; i < (size -1); i++){
        if(pText[i] >= 'A' && pText[i] <= 'Z'){
            eText[i] = pText[i] + key;
            if(eText[i] > 90){
                eText[i] -= 26;
            }
        }
        else {
            eText[i] = pText[i];
        }
    }

    //printf("eText value = %s\n", eText);
    printf("Please enter an output file name: ");
    outFile = malloc(25);
    scanf("%24s", outFile);
   // printf("The file you've selected is: %s\n", outFile);
    file = fopen(outFile, "w");
    fprintf(file, "%s", eText);
    fclose(file);
    //free(eText);
   // while((getchar()) != '\n');
    getchar();
    free(inFile);
    free(eText);
    free(pText);
    free(outFile);
    //free(file);
    free(line);
    exit(0);
    }

void Decrypt(void){
    char key;
    long size = 0;
    int i = 0;
    int errnum;
    FILE* file = NULL;
    char* inFile = NULL;
    char* outFile = NULL;
    char* eText = NULL;
    char* dText = NULL;

    char* line = NULL;
    size_t len = 0;
    size_t read;
     while(1){
        printf("Please enter a decryption key (1 letter will be used): ");
        //while((getchar()) != '\n');
        scanf(" %c", &key);
        //key = getchar();
        while((getchar()) != '\n');
        //printf("%c is the key.......", key);
         if (key  >= 'a' && key <= 'z'){ //Might be uppercase
            key = key - 32;
            break;
        }
        if(key >= 'A' && key <= 'Z'){
            break;
               // printf("Sorry that is an invalid key...try again.\n");
                //continue;
        }else{
               printf("Sorry that is an invalid key...try again.\n");
               continue;
            }

     }
    //printf("\nThe key you've entered is: %c\n", key);
    key = key - 'A';
    while(true){
        printf("Please enter the file you'd like to decrypt: ");

        inFile = malloc(25);
        scanf("%24s", inFile);
        //printf("The file you've selected is: %s\n", inFile);
        //eText = malloc(255);
        file = fopen(inFile, "r");
        if(file == NULL){
            errnum = errno;
            fprintf(stderr, "Error opening file: %s\n", strerror(errnum));
            while((getchar()) != '\n');
            continue;
        }
        else{
            //Seek the position of END from file <file> with 0L (0) byte offset from position
            fseek(file, 0L, SEEK_END);
            //ftell returns position of file pointer with respect to starting position file
            size = ftell(file);
            //sets file position to beginning of file
            rewind(file);

            eText = malloc(size+1);
            dText = malloc(size+1);
            if( !eText ) fclose(file),fputs("memory alloc fails",stderr),exit(1);

            /* copy the file into the buffer */
            //if( 1!=fread( eText , size, 1 , file) ){
             //   fclose(file),free(eText),fputs("entire read fails",stderr),exit(1);
            //}
            while((read = getline(&line, &len, file)) != -1){
                //printf("%s", line);
                strcat(eText, line);
            }

       // eText[strcspn(eText, "\n")] = 0;
       //fscanf(file, "%s", eText);
        //printf("%s Is the contents of the encrypted file...\n", eText);
        fclose(file);
        //free(eText);
        break;
        }
    }
    //size = getSize(eText);
    //dText = malloc(size);
     for (i = 0; eText[i]!='\0'; i++) {
      if(eText[i] >= 'a' && eText[i] <= 'z') {
         eText[i] = eText[i] -32;
      }
   }
    for(i = 0; i < (size); i++){
        if(eText[i] >= 'A' && eText[i] <= 'Z'){
            dText[i] = eText[i] - key;
            if(dText[i] < 65){
                dText[i] += 26;
            }
        }
        else{
            dText[i] = eText[i];
        }
    }

    printf("Please enter an output file name: ");
    outFile = malloc(25);
    scanf("%24s", outFile);
    //printf("The file you've selected is: %s\n", outFile);
    file = fopen(outFile, "w");
    fprintf(file, "%s", dText);
    fclose(file);

   // while((getchar()) != '\n');
    getchar();
    free(dText);
    free(eText);
    free(inFile);
    free(outFile);
    //free(file);
    free(line);
    exit(0);
}

void CryptoMenu(void){
  uid_t runningUser = getuid();
  uid_t ownerUser = geteuid();

  printf("The running user in CryptoMenu() is: %d\n", runningUser);
  printf("The owner user in CryptoMenu() is: %d\n", ownerUser);
    while(true){
        printf("\nCrypto Toolkit\n1. Encrypt\n2. Decrypt\n3. Main Menu\n");
        int input = 0;
        scanf(" %d", &input);
        while((getchar()) != '\n');
	    //while((getchar()) != '\n');
        //input = getchar();

        if(input == 1){
            //return 1;
            Encrypt();
            //return;
        }
        else if(input == 2){
            //printf("Decrypt Selected...\n");
            Decrypt();
           // return;
        }
        else if(input == 3){
           break;
        }
        else{
            printf("Invalid selection, please try again\n");
            continue;
        }
    }

}

int getSize(char* s){
    char* t;
    for(t = s; *t != '\0'; t++);
    return t - s;

}
