#ifndef IO_H_
#define IO_H_

#define PACKAGE_SIZE 512

void connection_init();
int serialize_package(void *pkg);
void *deserialize_package();

#endif 
