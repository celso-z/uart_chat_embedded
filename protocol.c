#include "./io.h"
#include "./protocol.h"

int send_signal(ProtocolSignal sig){
    switch(sig){
        case START:{
            //TODO send start package
            break;
        }
        case WAIT:{
            //TODO: send wait package
            break;
        }
        case END:{
            //TODO: send end package
            break;
        }
    }
    
    return 0;
}

ProtocolSignal get_signal(){
    ProtocolSignal sig = START;
    
    return sig;
}
int send_message(char* msg){
    
    return 0;
}
int get_message(char* msg, uint8_t msg_size){
    
    return 0;
}
