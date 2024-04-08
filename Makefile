CC=avr-gcc
SRC=io.c rtc.c time.c checksum.c protocol.c main.c
CFLAGS=-mmcu=atmega328p -O1

compile: main.c
	$(CC) $(CFLAGS) $(SRC) -o main.elf
