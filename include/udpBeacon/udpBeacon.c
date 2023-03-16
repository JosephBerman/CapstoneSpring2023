//
// Created by Waffles on 3/11/23.
//
#include "udpBeacon.h"

struct Server{
    struct udp_pcb* pcb;
    ip_addr_t addr;
    void (*run_server)();
};

//Created and binds pi pico to port (default 4444) and inits the struct
Server *create_server(const char *address, void * run_function){



    Server* srv = malloc(sizeof(*srv));

    srv->run_server = run_function;
    srv->pcb = udp_new();
    ipaddr_aton(address,&srv->addr);


    if(ERR_OK != udp_bind(srv->pcb, &srv->addr, DEFAULT_UDP_PORT)){
        printf("Error binding to port");
        sleep_ms(1000);
        return -1;
    }
    udp_connect(srv->pcb, &srv->addr, DEFAULT_UDP_PORT);

    printf("Starting server at %s on port %u\n", ip4addr_ntoa(netif_ip4_addr(netif_list)), DEFAULT_UDP_PORT);
        sleep_ms(1000);

    return srv;
}

void cleanup_server(Server* server){
    free(server);
}


void run_server(Server* srv){
    unsigned char counter[] = "UDP signal";

    while(true){
        struct pbuf *dataBuf = pbuf_alloc(PBUF_TRANSPORT, 16, PBUF_RAM);

        memcpy(dataBuf->payload, counter, sizeof(counter));
        printf("buffer %s\n", dataBuf->payload);
        err_t error = udp_send(srv->pcb, dataBuf);
        pbuf_free(dataBuf);

        if (error != ERR_OK) {
            printf("error=%d\n", error);
        } else {
            printf("sent: %s\n", counter);
            counter[0] = counter[0] + 1;

        }


        sleep_ms(1000);


    }
    return;
}

int main(){

    stdio_init_all();
    if (cyw43_arch_init()) {
        return -1;
    }
    cyw43_arch_enable_sta_mode();

    uint8_t counter = 0;
    while(cyw43_arch_wifi_connect_timeout_ms(SSID, PASS, CYW43_AUTH_WPA2_AES_PSK, 30000)) {

        if(counter >= 10){
            printf("tried 10+ times, failed");
            sleep_ms(200);
        }
        printf("Failed to connect, retrying %d\n", counter);

        sleep_ms(500);
        counter++;

    }

    Server *udpServer  = create_server("0.0.0.0", run_server);


    udpServer->run_server(udpServer);
    cyw43_arch_deinit();
    return 0;
}