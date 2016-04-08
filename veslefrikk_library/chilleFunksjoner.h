#pragma once
#include <string>

int takeMeanValue(int sensorVec[], const int length);
void swap(int *sensorVec, int p1, int p2);
void sort(int *sensorVec, const int length);
int takeMedian(int *sensorVec, const int length);
void tempWarning(int tempMotor, int tempDass, int tempStyr, int tempOut);
void landPowerWarning(bool landPower);
void samplePump(int *buff, int sample);
void gotThePump(int *pumpBuff, int *waterLevelBuff);
void waterLevelCheck(int *waterLevelBuff);

// Counters og orden til buffere. P står for pump og WL står for water level.
extern const int ORDER_P;
extern const int ORDER_WL;
extern int countP;
extern int countWL;

extern int critPumpOn1;
extern int critPumpOn2;
extern int critPumpOff;
extern int critCount;
extern int riseCount;
// Alarm er et flagg som settes dersom noe er galt. En feilmelding blir lagret i msg. 
//Når denne feilmeldingen er sendt settes flagget msgSent slik at meldingen ikke blir sent flere ganger på rad.
extern bool alarm;
extern bool msgSent;
extern std::string msg;
