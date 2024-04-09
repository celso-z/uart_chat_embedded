CC=avr-gcc
CFLAGS=-mmcu=atmega328p -O1
INCLUDES=./includes/*.c

compile: main.c
	$(CC) $(CFLAGS) $(INCLUDES) main.c -o main.elf

