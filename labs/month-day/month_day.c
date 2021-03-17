#include <stdio.h>
#include <stdlib.h>

/* month_day function's prototype*/
static int days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static char month_name[13][20] = {"None","Jan","Feb","Mar","Apr","May","June","July","Aug","Sept","Oct","Nov","Dec"};

void is_leap(int y) {
    if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0){
        days_in_month[2] = 29;
    }
    else {
        days_in_month[2] = 28;
    }
}


void month_day(int year, int yearday, int *pmonth, int *pday){

    int i = 1;
    int j = 0;
    int n = 0;
    int y = 0;

    is_leap(year);

    while(j < yearday) {
        if( i == 13) {
            i = 1;
            y++;
            n = n + days_in_month[12];
            is_leap(year + y);
        }
        else {
            j = j + days_in_month[i];
            n = n + days_in_month[i - 1];
            i++;
        }
    }

    j = yearday - n;
    
    printf("%s %d, %d\n", month_name[i-1], j, (year+y));
    

};

int main(int argc, char **argv) {

    month_day(atoi(argv[1]),atoi(argv[2]),0,0);

    return 0;
}