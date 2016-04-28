#ifndef DSP_H
#define DSP_H

<<<<<<< HEAD
#include <Arduino.h>
#include <math.h>

int takeMeanValue(int sensorVec[], const int length);
=======
double takeMeanValue(int sensorVec[], const int length);
>>>>>>> b27cf5da3cb83a4036f743b9c641f5c54083e605
void swap(int *sensorVec, int p1, int p2);
void sort(int *sensorVec, const int length);
double takeMedian(int *sensorVec, const int length);
void tempWarning(int indoorTemp, int outdoorTemp);
<<<<<<< HEAD
float average(float numbers[], int size);
const char *byte_to_binary(int x);
=======
>>>>>>> b27cf5da3cb83a4036f743b9c641f5c54083e605

#endif 