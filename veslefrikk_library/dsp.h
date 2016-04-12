#ifndef DSP_H
#define DSP_H

#include <Arduino.h>
#include <math.h>

int takeMeanValue(int sensorVec[], const int length);
void swap(int *sensorVec, int p1, int p2);
void sort(int *sensorVec, const int length);
double takeMedian(int *sensorVec, const int length);
void tempWarning(int indoorTemp, int outdoorTemp);
float average(float numbers[], int size);
const char *byte_to_binary(int x);

#endif 