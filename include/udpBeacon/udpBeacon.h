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

struct Server{
    struct udp_pcb* pcb;
    ip_addr_t addr;
    void (*run_server)(Server* srv);
};


//Created and binds pi pico to port (default 4444) and inits the struct
Server *create_server(const char *address, void * run_function){

    Server* srv =(Server*)malloc(sizeof(*srv));

    srv->run_server = (void (*)(Server*))run_function;
    srv->pcb = udp_new();
//    ipaddr_aton(address,&srv->addr);
//
//    ip_addr_t broadcastNetwork;
//    ipaddr_aton("255.255.255.255", &broadcastNetwork);
//
//    if(ERR_OK != udp_bind(srv->pcb,&srv->addr, DEFAULT_UDP_PORT)){
//        printf("Error binding to port");
//        sleep_ms(1000);
//
//    }
//    udp_connect(srv->pcb,  &broadcastNetwork, DEFAULT_UDP_PORT);
//
//    printf("Starting server at %s on port %u\n", ip4addr_ntoa(netif_ip4_addr(netif_list)), DEFAULT_UDP_PORT);
//    sleep_ms(1000);

    return srv;
}

void cleanup_server(Server* server){
    free(server);
}





void cleanup_server(Server* server);

void  run_server(Server* server);


#endif //CAPSTONESPRING2023_UDPBEACON_H
