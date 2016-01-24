#include <dsp.h>
#include <sensor.h>
#include <setup.h>
#include "Arduino.h"
#include <communication.h>

volatile unsigned long seconds = 0;
unsigned long elapsed_time = 0;

bool new_temp = false;
bool new_power = false;
bool new_battery = false;
bool new_bilge = false;
bool new_level = false;

float temp_sample[3];

void setup()
{
  Serial.begin(9600);
  initTimer();
}

void loop()
{
  if(new_temp == true)
  {
    temp_sample[0] = readTemp(TEMP_1);
    temp_sample[1] = readTemp(TEMP_2);
    temp_sample[2] = readTemp(TEMP_3);
    temp_sample[3] = readTemp(TEMP_4);
    Serial.println(temp_sample[0]);
    Serial.println(temp_sample[1]);
    new_temp = false;
  }
  if(new_power == true)
  {
    readShorePower(POWER);
    new_power = false;
  }
  if(new_battery == true)
  {
    readBattery(BATTERY_1);
    readBattery(BATTERY_2);
    new_battery = false;
  }
  if(new_bilge == true)
  {
    readBilge(BILGE_1);
    readBilge(BILGE_2);
    new_bilge = false;
  }
  if(new_level == true)
  {
    readBilge(LEVEL_1);
    readBilge(LEVEL_2);
    new_level = false;
  }
}

ISR(TIMER1_COMPA_vect)
{
  seconds++;
  elapsed_time = seconds;
  
  if(elapsed_time%TEMP_INTERVAL == 0)
  {
    new_temp = true;
  }
  if(elapsed_time%POWER_INTERVAL == 0)
  {
    new_power = true;
  }
  if(elapsed_time%BATTERY_INTERVAL == 0)
  {
    new_battery = true;
  }
  if(elapsed_time%BILGE_INTERVAL == 0)
  {
    new_bilge = true;
  }
  if(elapsed_time%LEVEL_INTERVAL == 0)
  {
    new_level = true;
  }
    
  if(seconds == RESET_INTERVAL)
  {
    seconds = 0;
  }
}

