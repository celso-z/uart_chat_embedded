# UART_CHAT embedded

## BUILDING

### COMPILING
make compile (inside project main directory)

### OBTAINING .HEX FILE
make hexdump (will generate an main.hex file if succesful)

### UPLOADING TO MICROCONTROLLER
make upload (takes main.hex file and upload to microcontroller (by default using avrdude with default uploader flags and to the port /dev/ttyUSB0, for another set of configurations set the UPLOADER AND UPLOADERFLAGS via command line for now))


## BUILDING TESTS
Run make compile and change SRC_FILE to the test file containing a main function. Follow the rest of the instructions above as normal
