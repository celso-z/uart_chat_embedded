#include "./protocol.h"
#include "./time.h"
#include <stdlib.h>
#include <inttypes.h>
#define F_CPU 16000000
#include <util/delay.h>

int main(void) {    
    char *msg = malloc(49);
    msg = "Lorem ipsum dolor sit amet, consectetur laoreet. ";
    while(1) {
        send_message(msg, 1, 0);
        
        _delay_ms(3500);
    }
        
    return 0;
}
