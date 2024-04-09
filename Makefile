CC=avr-gcc
HEXDUMP=avr-objcopy
UPLOADER=avrdude

SRC_FILE=main.c
CFLAGS=-mmcu=atmega328p -O1
INCLUDES=./includes/*.c
OBJFLAGS=-j .text -j .data -O ihex
UPLOADERFLAGS=-F -V -c arduino -p ATMEGA328P -P /dev/ttyUSB0 -b 115200 -U flash:w:

all: compile hexdump upload clean

compile: $(SRC_FILE)
	$(CC) $(CFLAGS) $(INCLUDES) main.c -o main.elf

hexdump: main.elf
	$(HEXDUMP) $(OBJFLAGS) main.elf main.hex

upload: main.hex
	$(UPLOADER) $(UPLOADERFLAGS)main.hex

clean: main.elf
	rm -f *.elf *.hex

