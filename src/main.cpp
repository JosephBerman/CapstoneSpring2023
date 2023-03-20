//
// Created by Waffles on 3/20/23.
//
#include "../include/udpBeacon/udpBeacon.h"
#include "../include/DHT20-Pico/DHT20.h"

#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "pico/util/queue.h"
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"


queue_t dht_queue;

void data_core1(){



    DHT20 sensor = DHT20(8,9);
    printf("created sensor\n");

    sensor.intializeRegisters();
    printf("init registers\n");
    sleep_ms(100);
    while(!sensor.isReady()){

        printf("sensor is not ready waiting 50ms");
        sleep_ms(50);
    }

    DHT_Data data;

    while(true) {

        sensor.getData(data);
        printf("getting data\n");
        sleep_ms(1000);
        queue_add_blocking(&dht_queue, &data);
        printf("added data to queue\n");
        sleep_ms(1000);
    }


}


void run_server(Server* srv){

    DHT_Data core1Data;


    while(true){


        char udpMessage[50];

        queue_remove_blocking(&dht_queue, &core1Data);

        sprintf(udpMessage, "t: %.4f, h: %.4f", core1Data.tempature, core1Data.humidity);

        struct pbuf *dataBuf = pbuf_alloc(PBUF_TRANSPORT, sizeof(udpMessage), PBUF_RAM);


        memcpy(dataBuf->payload, udpMessage, sizeof(udpMessage));

        err_t error = udp_send(srv->pcb, dataBuf);
        pbuf_free(dataBuf);
        if (error != ERR_OK) {
            if(error == ERR_USE){
                printf("Port alraedy in use");
            }else{
                printf("error=%d\n", error);
            }
        } else {
            printf(udpMessage);
        }
        sleep_ms(1000);
    }
}

int main(){

    stdio_init_all();
    printf("start\n");

    if (cyw43_arch_init()) {
        return -1;
    }
    cyw43_arch_enable_sta_mode();

    i2c_init(i2c_default, 100000);
    queue_init(&dht_queue, sizeof(DHT_Data), 1);



    uint8_t retries = 0;
    while(cyw43_arch_wifi_connect_timeout_ms(SSID, PASS, CYW43_AUTH_WPA2_AES_PSK, 30000)) {
        if(retries >= 3){
            printf("tried 3 times, failed\n");
            sleep_ms(200);
            return -2;
        }
        printf("Failed to connect, retrying %d\n", retries);

        sleep_ms(500);
        retries++;
    }



    Server *udpServer  = create_server("192.168.69.246", (void*) run_server);

    multicore_launch_core1(data_core1);

    udpServer->run_server(udpServer);







    cyw43_arch_deinit();

    return 0;
}