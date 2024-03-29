#ifndef IO_H_
#define IO_H_
#include <stdio.h>

#define PACKAGE_SIZE 512
int uart_putchar(char c, FILE *stream);
char uart_getchar(FILE *stream);
static const FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
static const FILE uart_input = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);

void connection_init();
int serialize_package(void *pkg);
void *deserialize_package();

#endif 
