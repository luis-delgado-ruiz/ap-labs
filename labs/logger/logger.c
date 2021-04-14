#include <stdio.h>
#include <signal.h>
#include <stdarg.h>

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

void colorText(int attr, int bc) {
    char command[13];
	sprintf(command, "%c[%d;%d;%dm", 0x1B, attr + 30, bc + 40);
	printf("%s", command);
}

int infof(const char *format, ...) {
	textcolor(BRIGHT, GREEN, BLACK);
	va_list input;
	va_start(input, format);
    vprintf(format, input);
	va_end(input);
    textcolor(RESET, WHITE, BLACK);
	return 0;
}

int warnf(const char *format, ...) {
	colorText(BRIGHT, YELLOW, BLACK);
    va_list input;
    va_start(input, format);
    vprintf(format, input);
    va_end(input);
	colorText(RESET, WHITE, BLACK);
	return 0;
}

int errorf(const char *format, ...) {
	colorText(BRIGHT, RED, BLACK);
    va_list input;
    va_start(input, format);
    vprintf(format, input);
    va_end(input);
    colorText(RESET, WHITE, BLACK);
    return 0;
}

int panicf(const char *format, ...) {
    colorText(BRIGHT, MAGENTA, BLACK);
    va_list input;
    va_start(input, format);
    vprintf(format, input);
    va_end(input);
    colorText(RESET, WHITE, BLACK);
	raise(SIGABRT);
    return 0;
}