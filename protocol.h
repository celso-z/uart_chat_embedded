#ifndef PROTOCOL_H_
#define PROTOCOL_H_
#include <inttypes.h>

typedef enum {
    START = 0x01,
    WAIT = 0x02,
    END = 0x04
} ProtocolSignal;

int send_message(char *msg);

int get_message(char* msg, uint8_t msg_size);
#endif
