#ifndef IO_H_
#define IO_H_
#include <stdio.h>
#include <stddef.h>

#define PACKAGE_SIZE 64


void connection_init();
int uart_putchar(char c, FILE *stream);
//char uart_getchar(FILE *stream);
//int uart_sendstr(const char *str);
//int uart_getstr(char *str, int size);
void *get_package();
int send_package(void *pkg);

/* CARA, EU REALMENTE DEVERIA FAZER TODO O IO AQUI E SOMENTE EXPORTAR UMA INTERFACE DEFINIDA, EM QUE O CARA SÓ PASSA A STRING VELHO, O QUE ESTOU FAZENDO??????? */

#endif 
