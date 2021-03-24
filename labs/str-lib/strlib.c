

int mystrlen(char *str){

    int i = 0;

     while (str[i] != '\0'){
        i++;
     }

    return i;
}

char *mystradd(char *origin, char *addition){

    while(*origin) {
        origin++;
    }
    
    while(*addition){
        *origin = *addition;
        origin++;
        addition++;
    }
    *origin = '\0';

    return origin;
}

int mystrfind(char *origin, char *substr){
    int i = 0;
    int j = 0;
    int k = 0;

    while (origin[i] != '\0') {
        while (origin[i] != substr[0] && origin[i] == substr[j]) {
            i++;
            j++;
        }
        k = i;
        if (substr[j] == '\0') {
            return k;
        } 
        else if (origin[i] == '\0') {
            return 0;
        }
        }
        i = k++;
        j = 0;
    return -1;
}
