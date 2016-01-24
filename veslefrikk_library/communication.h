#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#define PINCODE 1234
#define SEND_INTERVAL 3000

#include <Arduino.h>
#include <HardwareLink3.h>

byte data[2048] = {};
long data_counter = 15;

char* ip_addr;
char ping_addr[32] = "google.com";

void initModem();

#endif