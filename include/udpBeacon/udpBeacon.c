//
// Created by Waffles on 3/11/23.
//
#include "udpBeacon.h"

struct Server{
    struct udp_pcb* pcb;
    ip_addr_t addr;
    void *run_server;
} ;

Server *create_server(const char *address, void * run_function){

    Server* srv = malloc(sizeof(*srv));
    srv->run_server = run_function;
    ipaddr_aton(address,&srv->addr);

}

int main(){
    return 0;

}