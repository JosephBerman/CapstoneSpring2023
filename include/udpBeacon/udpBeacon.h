//
// Created by Waffles on 3/11/23.
//

#ifndef CAPSTONESPRING2023_UDPBEACON_H
#define CAPSTONESPRING2023_UDPBEACON_H


#include <stdio.h>
#include <stdlib.h>
#include "lwip/pbuf.h"
#include "lwip/udp.h"


typedef struct Server Server;
Server * create_server(const char *address, void * run_function);
void * run_server();


#endif //CAPSTONESPRING2023_UDPBEACON_H
