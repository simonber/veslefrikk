#ifndef SENSOR_H
#define SENSOR_H

//SENSOR PINOUT
#define TEMP_1 0
#define TEMP_2 1
#define TEMP_3 2
#define TEMP_4 3
#define POWER 4
#define BATTERY_1 5
#define BATTERY_2 6
#define BILGE_1 7
#define BILGE_2 8
#define LEVEL_1 9
#define LEVEL_2 10

//Sampling period defined in seconds
#define TEMP_INTERVAL 	1
#define POWER_INTERVAL	2
#define BATTERY_INTERVAL 3
#define BILGE_INTERVAL 4
#define LEVEL_INTERVAL 5

//Define the total sampling period here in seconds
#define RESET_INTERVAL 10

#include "Arduino.h"

int readTemp(int sensor_pin);
int readShorePower(int sensor_pin);
int readBattery(int sensor_pin);
int readBilge(int sensor_pin);
int readWaterLevel(int sensor_pin);

#endif