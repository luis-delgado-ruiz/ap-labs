#include <stdio.h>

int main(){
    int i = 0;
    int len = 0;
    char ch;
    char string[100];
    printf("\nPlease enter the first string\n");
    while((ch = getchar()) != EOF){
        if (ch == '\n') {
            int l = len - 1;
            for (int j = 0; j < len; j++) { 
                printf("%c", string[l-j]);
            }
            i = 0;
            len = 0;
            printf("\n");
        } 
        else {
            string[i] = ch;
            i++;
            len++;
        }
    }
    string[i] = '\0';
    return 0;
}