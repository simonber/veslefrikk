#include <sensor.h>

int readTemp(int sensor_pin)
{
	//Eksempelkode for prototype 26.01.16
	int sensor_val = analogRead(sensor_pin);
	return sensor_val;
}
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
{
	return 0;
}