#ifndef DSP_H
#define DSP_H

int processTemp(int* samples, int length);
int processPower(int* samples, int length);
int processBattery(int* samples, int length);
int processBilge(int* samples, int length);
int processLevel(int* samples, int length);

#endif 