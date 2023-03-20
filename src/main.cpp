//
// Created by Waffles on 3/20/23.
//
#include "../include/udpBeacon/udpBeacon.h"
#include "../include/DHT20-Pico/DHT20.h"

#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"



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
        printf("tempature: %f , humidity: %f\n", data.tempature, data.humidity);
        sleep_ms(1000);
    }


}


int main(){

    stdio_init_all();
    printf("start\n");


    i2c_init(i2c_default, 100000);

    multicore_launch_core1(data_core1);
    int counter = 0;
    while(true) {
        printf("core %d \n", counter);
        sleep_ms(1000);
        counter++;
    }


    return 0;
}