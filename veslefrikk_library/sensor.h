#ifndef SENSOR_H
#define SENSOR_H

//SENSOR PINOUT
#define TEMP_1 12
#define TEMP_2 A1
#define TEMP_3 A2
#define TEMP_4 A3
#define POWER A4
#define BATTERY_1 A5
#define BATTERY_2 A6
#define BILGE_1 A7
#define BILGE_2 A8
#define LEVEL_1 A9
#define LEVEL_2 A10

//Sampling period defined in seconds
#define TEMP_INTERVAL 	5
#define POWER_INTERVAL	2
#define BATTERY_INTERVAL 3
#define BILGE_INTERVAL 4
#define LEVEL_INTERVAL 5

//Define how often we will send data to server in seconds
#define SEND_INTERVAL 900

//Define the total sampling period here in seconds
#define CLOCK_RESET 100

#include "Arduino.h"

int readTemp(int sensor_pin);
int readShorePower(int sensor_pin);
int readBattery(int sensor_pin);
int readBilge(int sensor_pin);
int readLevel(int sensor_pin);

#endif