#ifndef DSP_H
#define DSP_H

double takeMeanValue(int sensorVec[], const int length);
void swap(int *sensorVec, int p1, int p2);
void sort(int *sensorVec, const int length);
double takeMedian(int *sensorVec, const int length);
void tempWarning(int indoorTemp, int outdoorTemp);

#endif 