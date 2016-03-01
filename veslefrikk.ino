#include <dsp.h>
#include <sensor.h>
#include <setup.h>
#include <HardwareLink3.h>
#include <OneWire.h>
#include <DallasTemperature.h>

bool new_temp = false;
bool new_power = false;
bool new_battery = false;
bool new_bilge = false;
bool new_level = false; 
bool send_data = false;

long int data_counter = 19;  
int temp_counter = 0;
byte temp_code = 2;

byte data[1024] = {}; 
byte temp_samples[255] = {};
byte IMEI[15] = {48,49,51,57,53,48,48,48,55,50,54,49,52,50,52};

volatile unsigned long seconds = 0;

OneWire oneWire(TEMP_BUS);
DallasTemperature sensors(&oneWire);

void setup()
{ 
  Serial.begin(57600);
  Serial3.begin(4800);
  //initModem(data);
  initTimer();
  for(int i = 0; i < 15; i++)
  {                   
      data[i] = IMEI[i];
  }
  sensors.requestTemperatures();
}

void loop()
{ 
  if(new_temp == true)
  { 
    data[data_counter] = temp_code;
    data_counter++;
    
    temp_samples[temp_counter] = sensors.getTempCByIndex(0)-1;
    
    Serial.print("Temperature Sample: ");
    Serial.println(temp_samples[temp_counter]);

    data[data_counter] = temp_samples[temp_counter];

    temp_counter++;
    data_counter++;
    new_temp = false;
  }
  if(new_power == true)
  {
    //Sampler Landtrøm
    readShorePower(POWER);
    new_power = false;
  }
  if(new_battery == true)
  {
    //Sampler batterispenning
    readBattery(BATTERY_1);
    readBattery(BATTERY_2);
    new_battery = false;
  }
  if(new_bilge == true)
  {
    //Sampler Lensepumpe
    readBilge(BILGE_1);
    readBilge(BILGE_2);
    new_bilge = false;
  }
  if(new_level == true)
  {
    //Sampler Vann nivå
    readLevel(LEVEL_1);
    readLevel(LEVEL_2);
    new_level = false;
  }

  //SEND FUNCTION
  if(send_data == true)
  {
    disableTimer();
    Serial.println("");
    send_Package(data, data_counter);
    
    send_data=false;
    data_counter = 19;
    temp_counter=0;
    seconds=0;
    enableTimer();
  }
}

ISR(TIMER1_COMPA_vect)
{
  seconds++;
  
  if(seconds%TEMP_INTERVAL == 0)
  {
    new_temp = true;
  }
  if(seconds%POWER_INTERVAL == 0)
  {
    new_power = true;
  }
  if(seconds%BATTERY_INTERVAL == 0)
  {
    new_battery = true;
  }
  if(seconds%BILGE_INTERVAL == 0)
  {
    new_bilge = true;
  }
  if(seconds%LEVEL_INTERVAL == 0)
  {
    new_level = true;
  }
  if(seconds == CLOCK_RESET)
  {
    seconds = 0;
  }
  if(seconds%SEND_INTERVAL == 0)
  {
    send_data = true;
  }
}

