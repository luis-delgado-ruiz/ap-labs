#include <stdio.h>
#include <string.h>

int mystrlen(char *);
char *mystradd(char *, char *);
int mystrfind(char *, char *);

int main(int argc, char *argv[]) {
    
    if (strcmp(argv[1], "-add") == 0) {
        printf("Initial Lenght : %d \n", mystrlen(argv[2]));
        char *new_string = mystradd(argv[2],argv[3]);
        printf("New String     : %s \n", new_string);
        printf("New length     : %d \n", mystrlen(new_string));
        return 0;
    }

    if (strcmp(argv[1], "-find") == 0) {
        int find = mystrfind(argv[2], argv[3]);
        if (find > -1) {
            printf("['%s'] string was found at [%d] position \n", argv[3], find);
        } 
        else {
            printf("The strinfg [%s] was not found \n", argv[3]);
        }
        return 0;
    } 
    else {
        printf("Action not valid \n");
    }
    return 0;
}
