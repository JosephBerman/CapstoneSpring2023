//
// Created by Waffles on 3/11/23.
//

#ifndef CAPSTONESPRING2023_UDPBEACON_H
#define CAPSTONESPRING2023_UDPBEACON_H


#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"

#define DEFAULT_UDP_PORT 4444

typedef struct Server Server;
Server * create_server(const char *address, void * run_function);
void cleanup_server(Server* server);

void  run_server(Server* server);


#endif //CAPSTONESPRING2023_UDPBEACON_H
