#include <avr/io.h>
#include "./io.h"

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#ifndef BAUD
#define BAUD 9600
#endif
#include <util/setbaud.h>

#include <stdio.h>
#include <stdlib.h>

int uart_putchar(char c, FILE *stream);
char uart_getchar(FILE *stream);

//static const FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

//static const FILE uart_input = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);

void connection_init() {
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;
    
#if USE_2X
    UCSR0A |= _BV(U2X0);
#else
    UCSR0A &= ~(_BV(U2X0));
#endif

    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */ 
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);   /* Enable RX and TX */    
}
int uart_putchar(char c, FILE *stream) {
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
    return 0;
}

char uart_getchar(FILE *stream) {
    loop_until_bit_is_set(UCSR0A, RXC0);
    return UDR0;
}

void *deserialize_package(){
    void *pkg = malloc((sizeof(uint32_t) * 16));
    if(pkg == NULL) return NULL;
    int r_value = fread(pkg, PACKAGE_SIZE, 1, &uart_input);
    if(r_value != 64) return NULL;
    return pkg;
}

int serialize_package(void *pkg){
    if(pkg == NULL) return -1;
    int r_value = fwrite(pkg, PACKAGE_SIZE, 1, &uart_output);
    if(r_value != 1) return -1;
    return 0;
}
