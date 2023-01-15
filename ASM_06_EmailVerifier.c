// Program    : ASM_06_EmailConfirm.c
// Created by : Peter Oo
// Created on : 1/13/2023 (5:18 PM).
// About      : Incoming string will be analysed an email domain name containing or not.

#include <stdio.h>
#include <stdlib.h>
#include "include/myLibrary.h"
#define file_size 20
#define mail_size 30

void operationMode();
int mailVerify(char *email, char *r_pattern);

int FILE_MODE = false;

int main(){
    FILE *fp = NULL;
    char filename[file_size] = {'\0'};
    char userMail[mail_size] = {'\0'};
    operationMode();
    if(FILE_MODE){
        printf("Submit the File:  ");
        scanf(" %s", filename);
        fp = fopen(filename, "r");
        if(fp == NULL){
            printf("[%s] not FOUND!..\n", filename);
            return -1;
        }
        while(fscanf(fp, "%s", userMail) != EOF){
            int email_length = stringLen(userMail);
            char *userName = subString(userMail, 0, indexOf(userMail, "@"));
            char *domainName = subString(userMail, indexOf(userMail, "@")+1,
                                         indexOf(userMail, ".com"));
            if(mailVerify(userMail, "a-zA-Z0-9")){
                printf("%s is an email.\nMail Length: %d.\nUser Name: %s\n", userMail, email_length, userName);
                printf("Domain Name: %s\n\n", domainName);
            }
            else{
                printf("%s isn't an email.\n\n", userMail);
            }
        }
        if(fp != NULL)
            fclose(fp);
    }
    else{
        while(1){
            printf("Enter an Email or [Quit] to terminate the program:  ");
            scanf(" %s", userMail);
            char temp[mail_size] = {'\0'};
            stringCopy(userMail, temp);
            wordUpper(temp);
            if(stringCmp(temp, "QUIT") != -1)
                break;
            else{
                int email_length = stringLen(userMail);
                char *userName = subString(userMail, 0, indexOf(userMail, "@"));
                char *domainName = subString(userMail, indexOf(userMail, "@")+1,
                                             indexOf(userMail, ".com"));
                if(mailVerify(userMail, "a-zA-Z0-9")){
                    printf("%s is an email.\nMail Length: %d.\nUser Name: %s\n", userMail, email_length, userName);
                    printf("Domain Name: %s\n\n", domainName);
                }
                else{
                    printf("%s isn't an email.\n\n", userMail);
                }
            }
        }
    }

    return 0;
}
/*
 * Handle that the mode is whether FILE or user input mode.
 * */
void operationMode(){
    char *userInput = (char*)(malloc(10*sizeof(char)));
    recall: // to recall back to operation_MODE
    printf("[Yes] for file read mode Or [No] for user input mode:  ");
    scanf(" %s", userInput);
    wordUpper(userInput); // Change userInput to all upper case not to be case-sensitive
    if(stringCmp(userInput, "YES") != -1)
        FILE_MODE = true;       // file read mode
    else if(stringCmp(userInput, "NO") != -1)
        FILE_MODE = false;      // user input mode
    else
        goto recall;            // bring user back to mode selection if answer format not valid.
    free(userInput);
}

/*
 * RETURN: 0 if not email format 1 if it is an email.
 * */
int mailVerify(char *email, char *r_pattern){ // Format: xxxx@[A-Za-z0-9].com
    int indexA = indexOf(email, "@");
    int indexB = indexOf(email, ".com");
    if(indexA == -1 || indexB == -1){
        return 0;
    }
    char *domain = subString(email, indexA+1,indexB);
    if(regExpress(domain, r_pattern))
        return 1;
    else
        return 0;
}
