#ifndef SENSOR_H
#define SENSOR_H

#define TEMP_1 2
#define TEMP_2 3
#define TEMP_3 4
#define TEMP_4 5

//SENSOR PINOUT
#define TEMP_BUS 42

#define POWER A4
#define BATTERY_1 5
#define BATTERY_2 6
#define BILGE_1 7
#define BILGE_2 8
#define LEVEL_1 9
#define LEVEL_2 0

//Sampling period defined in seconds
#define TEMP_INTERVAL 	2
#define POWER_INTERVAL	100
#define BATTERY_INTERVAL 100
#define BILGE_INTERVAL 100
#define LEVEL_INTERVAL 100

//Define how often we will send data to server in seconds
#define SEND_INTERVAL 20000

//Define the total sampling period here in seconds
#define CLOCK_RESET 1000

#include <OneWire.h>
#include <DallasTemperature.h>


void initSensors();
int readTemperatures(byte* data, int data_counter);
int readShorePower(int sensor_pin);
int readBattery(int sensor_pin);
int readBilge(int sensor_pin);
int readLevel(int sensor_pin);

#endif