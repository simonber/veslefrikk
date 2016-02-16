#ifndef SETUP_H
#define SETUP_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <HardwareLink3.h>
#include "arduino.h"

void initTimer();
void disableTimer();
void enableTimer();
void initModem();
void ping();

#endif