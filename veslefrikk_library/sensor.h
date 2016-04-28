#ifndef SENSOR_H
#define SENSOR_H

<<<<<<< HEAD
#define TEMP_1_CODE 2
#define TEMP_2_CODE 3
#define TEMP_3_CODE 4
#define TEMP_4_CODE 5
#define POWER_CODE 6
#define BATTERY_1_CODE 7
#define BATTERY_2_CODE 8
#define BILGE_1_CODE 9
#define BILGE_2_CODE 10
#define LEVEL_1_CODE 11
#define LEVEL_2_CODE 12

//SENSOR PINOUT
#define TEMP_BUS 13
#define BATTERY_1 8
#define BATTERY_2 9
#define BILGE_1 12
#define BILGE_2 13
#define POWER 14
=======
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
>>>>>>> b27cf5da3cb83a4036f743b9c641f5c54083e605

//Sampling period defined in seconds
#define TEMP_INTERVAL 	10	
#define POWER_INTERVAL	10000
#define BATTERY_INTERVAL 300
#define BILGE_INTERVAL 1
#define LEVEL_INTERVAL 10

#define TEMP_MEAN_COUNT 30
#define LEVEL_MEAN_COUNT 30

//Define how often we will send data to server in seconds
<<<<<<< HEAD
#define SEND_INTERVAL 900

#include <OneWire.h>
#include <DallasTemperature.h>

int ipow(int base, int exp);

extern DeviceAddress Probe1; 
extern DeviceAddress Probe2;
extern DeviceAddress Probe3; 
extern DeviceAddress Probe4;
=======
#define SEND_INTERVAL 20000
>>>>>>> b27cf5da3cb83a4036f743b9c641f5c54083e605

extern OneWire oneWire;
extern DallasTemperature sensors;

<<<<<<< HEAD

=======
#include <OneWire.h>
#include <DallasTemperature.h>


void initSensors();
int readTemperatures(byte* data, int data_counter);
int readShorePower(int sensor_pin);
int readBattery(int sensor_pin);
int readBilge(int sensor_pin);
int readLevel(int sensor_pin);
>>>>>>> b27cf5da3cb83a4036f743b9c641f5c54083e605

#endif