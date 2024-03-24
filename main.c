#include "./protocol.h"
#include <stdlib.h>

int main(void) {    

    connection_init();
    int result = send_signal(START);
    char *str = (char *)malloc(50 * sizeof(char));
                
    while(1) {
        result = uart_getstr(str, 50);
        result = uart_sendstr(str);
    }
        
    return 0;
}
