#include "./protocol.h"
#include "./time.h"
#include <stdlib.h>
#include <inttypes.h>
#define F_CPU 16000000
#include <util/delay.h>

int main(void) {    
    package_t *pkg = malloc(64);
    pkg->msg = malloc(49);
    pkg->msg[48] = '\0';
    pkg->orig_addr = 1;
    pkg->dest_addr = 0;
    pkg->checksum = malloc(9);
    pkg->checksum[8] = '\0';

    while(1) {
        pkg->timestamp = get_timestamp();
        get_checksum(NULL, pkg->checksum, pkg, 64);
        connection_init();
        serialize_package(pkg->checksum);
        
        
        _delay_ms(3500);
    }
        
    return 0;
}
