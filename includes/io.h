#ifndef IO_H_
#define IO_H_
#include <stdio.h>
#define PACKET_SIZE 64 //TAMANHO DO PACOTE EM BYTES

void connection_init();
int serialize_package(void *pkg);
void *deserialize_package();

#endif 
