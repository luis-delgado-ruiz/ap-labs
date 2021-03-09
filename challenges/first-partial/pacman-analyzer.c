#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define SIZE 260
#define REPORT_FILE "packages_report.txt"

struct Timestamp {
    int year;
    int month;
    int day;
    int hour;
    int minute;
};

struct Package {
    char name[25];
    char status[15];
    char type[20];
    int c_upgrades;
    struct Timestamp install_date;
    struct Timestamp last_upgrade;
    struct Timestamp removal_date;
};

void removeChar(char* s, char c) {
 
    int j, n = strlen(s);
    for (int i = j = 0; i < n; i++)
        if (s[i] != c)
            s[j++] = s[i];
 
    s[j] = '\0';
}

struct Timestamp zerot(){
    struct Timestamp t = {.year = 0, .month = 0, .day = 0,
    0, .minute = 0};
    return t;
}

struct Package install(char * l){
    char newString[30][30]; 
    struct Package p1;
    int i,j,ctr;
    int tflag = 0;
    int oflag = 0;
    j=0; ctr=0;
    for(i=0; i<=(strlen(l)); i++) {
        if(tflag >= 0 && tflag < 2){
            if(l[i] == '[' || l[i] == ']')
                tflag++;
            if(l[i] == 'T')
                oflag++;
            if(l[i]==' ' || l[i]=='-' || l[i]==':' || l[i] == 'T' || l[i] == '+' || l[i]=='\0') {
                newString[ctr][j]='\0';
                ctr++;  
                j=0;   
            } else {
                newString[ctr][j]=l[i];
                j++;
            }
        }
        else if(l[i]==' ' || l[i]==':' || l[i]=='\0') {
            newString[ctr][j]='\0';
            ctr++;  
            j=0;   
        }
        else {
            newString[ctr][j]=l[i];
            j++;
        }
    }
    
    if(oflag != 0){
        removeChar(newString[0], '[');
        removeChar(newString[6], ']');

        struct Timestamp t1 = {.year = atoi(newString[0]), .month = atoi(newString[1]), .day = atoi(newString[2]),
        .hour = atoi(newString[3]), .minute = atoi(newString[4])};

        strcpy(p1.name, newString[9]);
        strcpy(p1.status, newString[8]);
        strcpy(p1.type, newString[7]);
        p1.c_upgrades = 0;
        p1.install_date = t1;
        p1.last_upgrade = zerot();
        p1.removal_date = zerot();
    }
    else{
        removeChar(newString[0], '[');
        removeChar(newString[4], ']');

        struct Timestamp t1 = {.year = atoi(newString[0]), .month = atoi(newString[1]), .day = atoi(newString[2]),
        .hour = atoi(newString[3]), .minute = atoi(newString[4])};

        strcpy(p1.name, newString[7]);
        strcpy(p1.status, newString[6]);
        strcpy(p1.type, newString[5]);
        p1.c_upgrades = 0;
        p1.install_date = t1;
        p1.last_upgrade = zerot();
        p1.removal_date = zerot();
    }
    return p1;
}

struct Package upgrade(char * l){
    char newString[30][30];
    struct Package p2; 
    int i,j,ctr;
    int tflag = 0;
    int oflag = 0;
    j=0; ctr=0;
    for(i=0; i<=(strlen(l)); i++) {
        if(tflag >= 0 && tflag < 2){
            if(l[i] == '[' || l[i] == ']')
                tflag++;
            if(l[i] == 'T')
                oflag++;
            if(l[i]==' ' || l[i]=='-' || l[i]==':' || l[i] == 'T' || l[i] == '+' || l[i]=='\0') {
                newString[ctr][j]='\0';
                ctr++;  
                j=0;   
            } else {
                newString[ctr][j]=l[i];
                j++;
            }
        }
        else if(l[i]==' ' || l[i]==':' || l[i]=='\0') {
            newString[ctr][j]='\0';
            ctr++;  
            j=0;   
        }
        else {
            newString[ctr][j]=l[i];
            j++;
        }
    }
    if(oflag != 0){
        removeChar(newString[0], '[');
        removeChar(newString[6], ']');

        struct Timestamp t1 = {.year = atoi(newString[0]), .month = atoi(newString[1]), .day = atoi(newString[2]),
        .hour = atoi(newString[3]), .minute = atoi(newString[4])};

        strcpy(p2.name, newString[9]);
        strcpy(p2.status, newString[8]);
        strcpy(p2.type, newString[7]);
        p2.install_date = zerot();
        p2.last_upgrade = t1;
        p2.removal_date = zerot();
    }
    else{
        removeChar(newString[0], '[');
        removeChar(newString[4], ']');

        struct Timestamp t1 = {.year = atoi(newString[0]), .month = atoi(newString[1]), .day = atoi(newString[2]),
        .hour = atoi(newString[3]), .minute = atoi(newString[4])};

        strcpy(p2.name, newString[7]);
        strcpy(p2.status, newString[6]);
        strcpy(p2.type, newString[5]);
        p2.install_date = zerot();
        p2.last_upgrade = t1;
        p2.removal_date = zerot();
    }
    return p2;
}

struct Package reinstall(char * l){
    char newString[30][30];
    struct Package p4; 
    int i,j,ctr;
    int tflag = 0;
    int oflag = 0;
    j=0; ctr=0;
    for(i=0; i<=(strlen(l)); i++) {
        if(tflag >= 0 && tflag < 2){
            if(l[i] == '[' || l[i] == ']')
                tflag++;
            if(l[i] == 'T')
                oflag++;
            if(l[i]==' ' || l[i]=='-' || l[i]==':' || l[i] == 'T' || l[i] == '+' || l[i]=='\0') {
                newString[ctr][j]='\0';
                ctr++;  
                j=0;   
            } else {
                newString[ctr][j]=l[i];
                j++;
            }
        }
        else if(l[i]==' ' || l[i]==':' || l[i]=='\0') {
            newString[ctr][j]='\0';
            ctr++;  
            j=0;   
        }
        else {
            newString[ctr][j]=l[i];
            j++;
        }
    }
    if(oflag != 0){
        removeChar(newString[0], '[');
        removeChar(newString[6], ']');

        struct Timestamp t1 = {.year = atoi(newString[0]), .month = atoi(newString[1]), .day = atoi(newString[2]),
        .hour = atoi(newString[3]), .minute = atoi(newString[4])};

        strcpy(p4.name, newString[9]);
        strcpy(p4.status, newString[8]);
        strcpy(p4.type, newString[7]);
        p4.c_upgrades = 0;
        p4.install_date = t1;
        p4.last_upgrade = zerot();
        p4.removal_date = zerot();
    }
    else{
        removeChar(newString[0], '[');
        removeChar(newString[4], ']');

        struct Timestamp t1 = {.year = atoi(newString[0]), .month = atoi(newString[1]), .day = atoi(newString[2]),
        .hour = atoi(newString[3]), .minute = atoi(newString[4])};

        strcpy(p4.name, newString[7]);
        strcpy(p4.status, newString[6]);
        strcpy(p4.type, newString[5]);
        p4.c_upgrades = 0;
        p4.install_date = t1;
        p4.last_upgrade = zerot();
        p4.removal_date = zerot();
    }
    return p4;
}

struct Package rem(char * l){
    char newString[30][30]; 
    struct Package p3;
    int tflag = 0;
    int oflag = 0;
    int i,j,ctr;
    j=0; ctr=0;
    for(i=0; i<=(strlen(l)); i++) {
        if(tflag >= 0 && tflag < 2){
            if(l[i] == '[' || l[i] == ']')
                tflag++;
            if(l[i] == 'T')
                oflag++;
            if(l[i]==' ' || l[i]=='-' || l[i]==':' || l[i] == 'T' || l[i] == '+' || l[i]=='\0') {
                newString[ctr][j]='\0';
                ctr++;  
                j=0;   
            } else {
                newString[ctr][j]=l[i];
                j++;
            }
        }
        else if(l[i]==' ' || l[i]==':' || l[i]=='\0') {
            newString[ctr][j]='\0';
            ctr++;  
            j=0;   
        }
        else {
            newString[ctr][j]=l[i];
            j++;
        }
    }
    if(oflag != 0){
        removeChar(newString[0], '[');
        removeChar(newString[6], ']');

        struct Timestamp t1 = {.year = atoi(newString[0]), .month = atoi(newString[1]), .day = atoi(newString[2]),
        .hour = atoi(newString[3]), .minute = atoi(newString[4])};

        strcpy(p3.name, newString[9]);
        strcpy(p3.status, newString[8]);
        strcpy(p3.type, newString[7]);
        p3.c_upgrades = 0;
        p3.install_date = zerot();
        p3.last_upgrade = zerot();
        p3.removal_date = t1;
    }
    else{
        removeChar(newString[0], '[');
        removeChar(newString[4], ']');

        struct Timestamp t1 = {.year = atoi(newString[0]), .month = atoi(newString[1]), .day = atoi(newString[2]),
        .hour = atoi(newString[3]), .minute = atoi(newString[4])};

        strcpy(p3.name, newString[7]);
        strcpy(p3.status, newString[6]);
        strcpy(p3.type, newString[5]);
        p3.install_date = zerot();
        p3.last_upgrade = zerot();
        p3.removal_date = t1;
    }
    return p3;
}

struct Package addas(){

    struct Package p4;
    strcpy(p4.name, "[ALPM-SCRIPTLET]");
    strcpy(p4.status, "-");
    strcpy(p4.type, "[ALPM-SCRIPTLET]");
    p4.c_upgrades = 1;
    p4.install_date = zerot();
    p4.last_upgrade = zerot();
    p4.removal_date = zerot();

    return p4;
}

struct Package addpac(){

    struct Package p5;
    strcpy(p5.name, "[PACMAN]");
    strcpy(p5.status, "-");
    strcpy(p5.type, "[PACMAN]");
    p5.c_upgrades = 1;
    p5.install_date = zerot();
    p5.last_upgrade = zerot();
    p5.removal_date = zerot();

    return p5;
}

void aw(char* file, struct Package arr[], size_t a_size){
    int num;
    FILE *fptr;
    const char* mode  = "w";

    fptr = fopen(file, mode);

    if(fptr == NULL){
        printf("Error");
        exit(1);
    }

    int inst = 0;
    int rem = 0;
    int upgraded = 0;
    struct Package oldest = arr[6];
    struct Package newest = arr[6];
    char nu [2][5000];
    int nctr = 0;
    int j=0; 
    int nui = 0;
    int alpms = 0;
    int alpm = 0;
    int pcmn = 0;
    int cc = 0;

    
    for(int i = 0; i < a_size; i++) {
        if((strcmp(arr[i].status, "installed") == 0) || (strcmp(arr[i].status, "reinstalled") == 0)){
            inst++;
        }
        else if(strcmp(arr[i].status, "upgraded") == 0){
            upgraded++;
        }
        else if(strcmp(arr[i].status, "removed") == 0){
            rem++;
        }

        if( (strcmp(arr[i].name, oldest.name) != 0) && (strcmp(arr[i].type, "[ALPM-SCRIPTLET]") != 0) && (strcmp(arr[i].type, "[PACMAN]") != 0) && 
            arr[i].install_date.year > 1999 && arr[i].install_date.year != 0){
            if(arr[i].install_date.year > 1999 && arr[i].install_date.year < oldest.install_date.year){
                oldest = arr[i];
            } else if (arr[i].install_date.year == oldest.install_date.year && arr[i].install_date.month < oldest.install_date.month){
                oldest = arr[i];
            } else if (arr[i].install_date.year == oldest.install_date.year && arr[i].install_date.month == oldest.install_date.month && 
                    arr[i].install_date.day < oldest.install_date.day) {
                oldest = arr[i];
            } else if (arr[i].install_date.year == oldest.install_date.year && arr[i].install_date.month == oldest.install_date.month && 
                    arr[i].install_date.day == oldest.install_date.day && arr[i].install_date.hour < oldest.install_date.hour) {
                oldest = arr[i];
            } else if (arr[i].install_date.year == oldest.install_date.year && arr[i].install_date.month == oldest.install_date.month && 
                    arr[i].install_date.day == oldest.install_date.day && arr[i].install_date.hour == oldest.install_date.hour && 
                    arr[i].install_date.minute < oldest.install_date.minute){
                oldest = arr[i];
            }
        }

        if( (strcmp(arr[i].name, newest.name) != 0) && (strcmp(arr[i].type, "[ALPM-SCRIPTLET]") != 0) && (strcmp(arr[i].type, "[PACMAN]") != 0) && 
            arr[i].install_date.year > 1999 && arr[i].install_date.year < 2021) {
            if(arr[i].install_date.year > newest.install_date.year){
                newest = arr[i];
            } else if (arr[i].install_date.year == newest.install_date.year && arr[i].install_date.month > newest.install_date.month){
                newest = arr[i];
            } else if (arr[i].install_date.year == newest.install_date.year && arr[i].install_date.month == newest.install_date.month && 
                    arr[i].install_date.day > newest.install_date.day) {
                newest = arr[i];
            } else if (arr[i].install_date.year == newest.install_date.year && arr[i].install_date.month == newest.install_date.month && 
                    arr[i].install_date.day == newest.install_date.day && arr[i].install_date.hour > newest.install_date.hour) {
                newest = arr[i];
            } else if (arr[i].install_date.year == newest.install_date.year && arr[i].install_date.month == newest.install_date.month && 
                    arr[i].install_date.day == newest.install_date.day && arr[i].install_date.hour == newest.install_date.hour && 
                    arr[i].install_date.minute > newest.install_date.minute){
                newest = arr[i];
            }	
        }
        
        if(arr[i].c_upgrades == 0){
            for(nui=0; nui <= (strlen(arr[i].name)); nui++) {
                if(arr[i].name[nui] == '\0') {
                    nu[nctr][j] = ' ';
                    j++;
                }
                else {
                    nu[nctr][j]=arr[i].name[nui];
                    j++;
                }
            }
        }

        if(strcmp(arr[i].type, "[ALPM-SCRIPTLET]") == 0){
            alpms++;
        } else if(strcmp(arr[i].type, "[ALPM]") == 0){
            alpm++;
        } else if(strcmp(arr[i].type, "[PACMAN]") == 0){
            pcmn++;
        }
    }
    
    fprintf(fptr,"Pacman Packages Report \n");
    fprintf(fptr,"---------------------- \n");
    fprintf(fptr,"- Installed packages : %d \n", (inst+upgraded));
    fprintf(fptr,"- Removed packages   : %d \n", rem);
    fprintf(fptr,"- Upgraded packages  : %d \n", upgraded);
    fprintf(fptr,"- Current installed  : %d \n", ((inst+upgraded) - rem));
    fprintf(fptr,"-------------- \n");
    fprintf(fptr,"General Stats \n");
    fprintf(fptr,"-------------- \n");
    fprintf(fptr,"- Oldest package           : %s \n", oldest.name);
    fprintf(fptr,"- Newest package           : %s \n", newest.name);
    fprintf(fptr,"- Package with no upgrades : %s \n", nu[0]);
    fprintf(fptr,"- [ALPM-SCRPLET] count     : %d \n", alpms);
    fprintf(fptr,"- [ALPM] count             : %d \n", alpm);
    fprintf(fptr,"- [PACMAN] count           : %d \n", pcmn);
    fprintf(fptr,"-------------- \n");
    fprintf(fptr,"List of Packages \n");
    fprintf(fptr,"-------------- \n");
    for(int i = 0; i < a_size; i++) {
        if((strcmp(arr[i].name, "[ALPM-SCRIPTLET]") != 0) && (arr[i].install_date.year > 1999) && (arr[i].install_date.year < 2021) ) {
            fprintf(fptr,"- Package Name         : %s \n", arr[i].name);
            if(arr[i].install_date.minute <= 9){
                fprintf(fptr,"   - Install date      : %d-%d-%d %d:0%d \n", arr[i].install_date.year, arr[i].install_date.month,
                                                                arr[i].install_date.day, arr[i].install_date.hour, arr[i].install_date.minute);
            } else {
                fprintf(fptr,"   - Install date      : %d-%d-%d %d:%d \n", arr[i].install_date.year, arr[i].install_date.month,
                                                                arr[i].install_date.day, arr[i].install_date.hour, arr[i].install_date.minute);
            }
            if(arr[i].last_upgrade.year == 0){
                fprintf(fptr,"   - Last update       : - \n");
            } else if (arr[i].last_upgrade.minute <= 9){
                fprintf(fptr,"   - Last update       : %d-%d-%d %d:0%d \n", arr[i].last_upgrade.year, arr[i].last_upgrade.month,
                                                                arr[i].last_upgrade.day, arr[i].last_upgrade.hour, arr[i].last_upgrade.minute);
            } else {
                fprintf(fptr,"   - Last update       : %d-%d-%d %d:%d \n", arr[i].last_upgrade.year, arr[i].last_upgrade.month,
                                                                arr[i].last_upgrade.day, arr[i].last_upgrade.hour, arr[i].last_upgrade.minute);
            }
            fprintf(fptr,"   - How many upgrades : %d \n", arr[i].c_upgrades);
            if(arr[i].removal_date.year == 0){
                fprintf(fptr,"   - Removal date      : - \n");
            } else if (arr[i].removal_date.minute <= 9){
                fprintf(fptr,"   - Removal date      : %d-%d-%d %d:0%d \n", arr[i].removal_date.year, arr[i].removal_date.month,
                                                                arr[i].removal_date.day, arr[i].removal_date.hour, arr[i].removal_date.minute);
            } else {
                fprintf(fptr,"   - Removal date      : %d-%d-%d %d:%d \n", arr[i].removal_date.year, arr[i].removal_date.month,
                                                                arr[i].removal_date.day, arr[i].removal_date.hour, arr[i].removal_date.minute); 
            }
            fprintf(fptr,"\n");
        }
    }
    fclose(fptr);
}

void analizeLog(char* file, char* report) {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    const char* mode  = "r";

    fp = fopen(file, mode);
    if(fp == NULL){
        printf(" ERROR: FILE NOT FOUND");
        exit(EXIT_FAILURE);
    }

    struct Package par[2500];
    int z = 0;
    int k = 0;
    int tflag = 0;
    int i,j,ctr;
    j=0; ctr=0;
    while((read = getline(&line, &len, fp)) != -1) { 
        char * l = line;
        char newString[100][100]; 
        for(i = 0; i <= (strlen(l)); i++) {
            if(tflag >= 0 && tflag < 2){
                if(l[i] == '[' || l[i] == ']'){
                    tflag++;
                }
                if(l[i]==' ' || l[i]=='-' || l[i]==':' || l[i] == 'T' || l[i] == '+' || l[i]=='\0') {
                    newString[ctr][j] = '\0';
                    ctr++;  
                    j=0;   
                } else {
                    newString[ctr][j]=l[i];
                    j++;
                }
            }
            else if(l[i]==' ' || l[i]==':' || l[i]=='\0') {
                newString[ctr][j] = '\0';
                ctr++;  
                j=0;   
            }
            else {
                newString[ctr][j] = l[i];
                j++;
            }
        }
        if ((strcmp(newString[6], "installed") == 0) || (strcmp(newString[8], "installed") == 0)){
            struct Package p1 = install(l);
            par[z] = p1;
            z++;
        }
        else if ((strcmp(newString[8], "reinstalled") == 0) || (strcmp(newString[8], "reinstalled") == 0)){
            for(int i = 0; i < (sizeof(par)/sizeof(par[0])); i++) {
                if ((strcmp(newString[7], par[i].name) == 0) || (strcmp(newString[9], par[i].name) == 0)){
                    struct Package p1 = reinstall(l);
                    par[i] = p1;
                    break;
                }
                if(i >= (sizeof(par)/sizeof(par[0]))){
                    struct Package p1 = install(l);
                    break;
                }
            }
        }
        else if ((strcmp(newString[5], "[ALPM-SCRIPTLET]") == 0) || (strcmp(newString[7], "[ALPM-SCRIPTLET]") == 0)){
            struct Package p1 = addas();
            par[z] = p1;
            z++;
        }
        else if ((strcmp(newString[5], "[PACMAN]") == 0) || (strcmp(newString[7], "[PACMAN]") == 0)){
            struct Package p1 = addpac();
            par[z] = p1;
            z++;
        }
        else if ((strcmp(newString[6], "upgraded") == 0) || (strcmp(newString[8], "upgraded") == 0)){
            for(int i = 0; i < (sizeof(par)/sizeof(par[0])); i++) {
                if ((strcmp(newString[7], par[i].name) == 0) || (strcmp(newString[9], par[i].name) == 0)){
                    struct Timestamp temp = par[i].install_date;
                    struct Package p1 = upgrade(l);
                    int cu = par[i].c_upgrades;
                    par[i] = p1;
                    par[i].install_date = temp;
                    par[i].c_upgrades = cu + 1;
                    break;
                }
                if(i >= (sizeof(par)/sizeof(par[0]))){
                    break;
                }
            }
        }
        else if((strcmp(newString[6], "removed") == 0) || (strcmp(newString[8], "removed") == 0)){
            int flag = 0;
            struct Timestamp tempu;
            int cu = 0;
            for(int i = 0; i < (sizeof(par)/sizeof(par[0])); i++){
                if((strcmp(newString[7], par[i].name) == 0) || (strcmp(newString[9], par[i].name) == 0)){
                    struct Timestamp tempi = par[i].install_date;
                    if(par[i].last_upgrade.hour != 0){
                        tempu = par[i].last_upgrade;
                        cu = par[i].c_upgrades;
                        flag = 1;
                    }
                    struct Package p1 = rem(l);
                    par[i] = p1;
                    par[i].install_date = tempi;
                    if(flag != 0){
                        par[i].last_upgrade = tempu;
                        par[i].c_upgrades = cu;
                    }
                    break;
                }
            }
        } 

        tflag = 0;
        ctr=0;
    }

    aw(report, par, (sizeof(par)/sizeof(par[0])));

    fclose(fp);
    if(line)
        free(line);
    exit(EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
    char input[20]; 
    char report[20]; 

    for(int i = 1; i < argc; i++) {
        if(!strcmp(argv[i],"-input"))
            strcpy(input, argv[i+1]);
        else if(!strcmp(argv[i],"-report"))
            strcpy(report, argv[i+1]);
    }

    printf("Generating Report from: [%s] log file\n", input);
    analizeLog(input, report);
    printf("Report is generated at: [%s]\n", report);

    return 0;
}