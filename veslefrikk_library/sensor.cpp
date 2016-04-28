#include <sensor.h>
/*
OneWire oneWire(TEMP_BUS);
DallasTemperature sensors(&oneWire);

<<<<<<< HEAD
DeviceAddress Probe1 = { 0x28, 0x0A, 0xC5, 0x4F, 0x07, 0x00, 0x00, 0x21 }; 
DeviceAddress Probe2 = { 0x28, 0x91, 0xCF, 0x50, 0x07, 0x00, 0x00, 0x77 };
DeviceAddress Probe3 = { 0x28, 0xA2, 0x2B, 0x4B, 0x07, 0x00, 0x00, 0xAA }; 
DeviceAddress Probe4 = { 0x28, 0x57, 0x5A, 0x50, 0x07, 0x00, 0x00, 0x3F };

OneWire oneWire(TEMP_BUS);
DallasTemperature sensors(&oneWire);

int ipow(int base, int exp)
=======


DeviceAddress Probe01 = { 0x28, 0xFF, 0x82, 0xA0, 0x07, 0x00, 0x00, 0xD3 }; 
DeviceAddress Probe02 = { 0x28, 0xFF, 0x57, 0x59, 0x69, 0x14, 0x04, 0x5A };

float temp[3] = {};

void initSensors()
{
	sensors.begin();
	sensors.setResolution(Probe01, 9);
  	sensors.setResolution(Probe02, 9);
}

int readTemperatures(byte* data, int data_counter)
{
	sensors.requestTemperatures(); 
	data[data_counter] = TEMP_1;
	data_counter++;
	
	temp[0] = sensors.getTempC(Probe01);
	data[data_counter] = temp[0];
	data_counter++;
	return 0;
}
*/
int readShorePower(int sensor_pin)
{
	return 0;
}
int readBattery(int sensor_pin)
{
	return 0;
}
int readBilge(int sensor_pin)
{
	return 0;
}
int readLevel(int sensor_pin)
>>>>>>> b27cf5da3cb83a4036f743b9c641f5c54083e605
{
    int result = 1;
    while (exp)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        base *= base;
    }
    return result;
}	

