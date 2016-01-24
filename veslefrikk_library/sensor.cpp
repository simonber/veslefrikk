#include <sensor.h>

int readTemp(int sensor_pin)
{
	float temp;
	temp = analogRead(sensor_pin);
	return temp;
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
int readWaterLevel(int sensor_pin)
{
	return 0;
}