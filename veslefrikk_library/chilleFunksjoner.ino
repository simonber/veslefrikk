#include "chilleFunksjoner.h"
#include <iostream>
#include <math.h>
#include <string>
using namespace std;

// Counters og orden til buffere. P står for pump og WL står for water level. 
const int ORDER_P = 4;
int countP = 0;
int countWL = 0;

// Kritiske grenser for pumpe og vannstand
int critPumpOn1 = 6; // Kritisk verdi for hvor lenge pumpa har vært på.
int critPumpOn2 = 3; // Kritisk verdi for hvor lenge pumpa har vært på gitt at vannstanden har steget imellomtiden 
int critPumpOff = 10; // Kritisk verdi for hvor lenge pumpa har vært av.
int critHighWL = 25; // Kritisk vannstandsnivå.
int critCount = 0; // teller hvor mange samples som har ligget over kritisk vannstandsnivå
int riseCount = 0; // teller hvor mange samples som vannstanden har steget.

// Alarm er et flagg som settes dersom noe er galt. En feilmelding blir lagret i msg. 
//Når denne feilmeldingen er sendt settes flagget msgSent slik at meldingen ikke blir sent flere ganger på rad.
bool alarm = 0;
bool msgSent = 0;
string msg;

int takeMeanValue(int sensorVec[], const int length) {
	int tempSum = 0;

	for (int i = 0; i < length; i++) {
		tempSum += sensorVec[i];
	}
	return (int)round(tempSum / (double)length);
}

void swap(int *sensorVec, int p1, int p2) {
	int pitstop = sensorVec[p1];
	sensorVec[p1] = sensorVec[p2];
	sensorVec[p2] = pitstop;
}


void sort(int *sensorVec, const int length) {

	for (int i = 0; i < (length-1); i++) {
		for (int j = i + 1; j < length; j++) {
			if (sensorVec[i] > sensorVec[j]) {
				swap(sensorVec, i, j);
			}
		}
	}
}

int takeMedian(int *sensorVec, const int length) {
	int res = 0;
	sort(sensorVec, length);

	if (length % 2 == 0) {
		res = (int)round((sensorVec[(length/2)-1] + sensorVec[length/2]) / 2.0);
	}
	else {
		res = sensorVec[(length - 1) / 2];
	}
	return res;
}


void tempWarning(int tempMotor, int tempDass, int tempStyr, int tempOut) {

	// skjekker temperaturen i motorrommet, på do og i styrrommet
	if (tempMotor > 20 || tempDass > 20 || tempStyr > 20) {
		msg = "Skipet ditt brenner kaptein! \n Temp motorrommet: " + to_string(tempMotor) + "\n Temp do: " + to_string(tempDass) + "\n Temp Styrrom: " + to_string(tempStyr) + "\n Temp ute: " + to_string(tempOut) + "\n";
	}
	else if (tempMotor < 5 || tempDass < 5 || tempStyr < 5) {
		msg = "Skipet ditt fryser kaptein! \n Temp motorrommet: " + to_string(tempMotor) + "\n Temp do: " + to_string(tempDass) + "\n Temp Styrrom: " + to_string(tempStyr) + "\n Temp ute: " + to_string(tempOut) + "\n";
	}
	else {
		msg = "";
	}
}

void landPowerWarning(bool landPower) {

	if (landPower == true) {
		msg = "";
	}
	else {
		msg = "Skuta er ikke lenger koblet til landstrøm kaptein! \n";
	}
}

void samplePump(int *pumpBuff, int sample) {

	if (sample == 0 || sample == 1) {
		if (countP % 2 == 0) {
			if (sample == 1) {
				countP++;
				pumpBuff[countP] = 1;
			}
			else {
				pumpBuff[countP]++;
			}
		}
		else if (countP % 2 == 1) {

			if (sample == 0 && countP < (ORDER_P - 1)) {
				countP++;
				pumpBuff[countP] = 1;
			}
			else if (sample == 0 && countP == ORDER_P - 1) {
				countP = 0;
				pumpBuff[countP] = 1;
			}
			else {
				pumpBuff[countP]++;
			}
		}
		else {
			cout << "Noe er galt" << endl;
		}
	}
	else {
		cout << "Noe er galt" << endl;
	}
}

void gotThePump(int *pumpBuff, int *waterLevelBuff) {

	if (countP % 2 == 0) {

		if (pumpBuff[countP] > critPumpOff) {
			msg = "Lensepumpa har vaert av i: " + to_string(pumpBuff[countP]) + " sek.\n";
			alarm = 1;
		}
		else {
			msg = "OK";
			alarm = 0;
		}
	}

	else if (countP % 2 == 1) {


		if (pumpBuff[countP] > critPumpOn2) {

			if (riseCount > 2) {
				msg = "Vannstanden har steget de " + to_string(riseCount) + " siste samplene.\n" + "Lensepumpa har vaert paa i " + to_string(pumpBuff[countP]) + " sek.\n" + "Vannstanden er " + to_string(waterLevelBuff[countWL]);
				alarm = 1;
			}
			
			else if (pumpBuff[countP] > critPumpOn1) {
				msg = "Lensepumpa har vaert paa i: " + to_string(pumpBuff[countP]) + " sek.\n";
				alarm = 1;
			}
		}

		else {
			msg = "OK";
			alarm = 0;
		}
	}
}

void waterLevelCheck(int *waterLevelBuff) {

	//for (int i = 0; i < 30; i++) {
	//	if (waterLevelBuff[i] > critHighWL) {
	//		critCount++;
	//	}
	//}

	if (waterLevelBuff[countWL] > critHighWL) {
		critCount++;
	}
	else {
		critCount = 0;
	}

	if (critCount > 2) {
		msg = "Vannstanden er over kritisk verdi.\n";
		msg += "Naavaerende vannstand er " + to_string(waterLevelBuff[countWL]);
		alarm = 1;
	}

	if (countWL > 0 && countWL < 30 && (waterLevelBuff[countWL] - waterLevelBuff[countWL - 1]) > 0) {
		riseCount++;
	}
	else {
		riseCount = 0;
	}
}
