#include <stdio.h>
#include <signal.h>
#include <stdarg.h>
#include "logger.h"

#define RESET		0
#define BRIGHT 		1
#define DIM		    2
#define UNDERLINE 	3
#define BLINK		4
#define BLACK 		0
#define RED		    1
#define GREEN		2
#define YELLOW		3
#define BLUE		4
#define MAGENTA		5
#define CYAN		6
#define	WHITE		7

int sysFlag;

void colorText(int attr, int bc) {
    char command[13];
	sprintf(command, "%c[%d;%d;%dm", 0x1B, attr + 30, bc + 40);
	printf("%s", command);
}

int initLogger(char *logType) {
    printf("Initializing Logger on: %s\n", logType);
    if (strcmp(logType, "syslog") == 0){
        sysFlag = 1;
    }
    else if (strcmp(logType, "stdout") == 0 || strcmp(logType, "") == 0){
        isSyslog = 0;
    }
    else{
        isSyslog = 0;
        printf("Error [%s] \n", logType);
    }
    return 0;
}

int infof(const char *format, ...) {
	textcolor(GREEN, BLACK);
	va_list input;
	va_start(input, format);
    vprintf(format, input);
	va_end(input);
    textcolor(WHITE, RESET);
	return 0;
}

int warnf(const char *format, ...) {
	colorText(YELLOW, BLACK);
    va_list input;
    va_start(input, format);
    vprintf(format, input);
    va_end(input);
	textcolor(WHITE, RESET);
	return 0;
}

int errorf(const char *format, ...) {
	colorText(RED, BLACK);
    va_list input;
    va_start(input, format);
    vprintf(format, input);
    va_end(input);
    textcolor(WHITE, RESET);
    return 0;
}

int panicf(const char *format, ...) {
    colorText(MAGENTA, BLACK);
    va_list input;
    va_start(input, format);
    vprintf(format, input);
    va_end(input);
    textcolor(WHITE, RESET);
    return 0;
}
