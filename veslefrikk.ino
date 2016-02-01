#include <dsp.h>
#include <sensor.h>
#include <setup.h>
#include <HardwareLink3.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <rtc.h>

volatile unsigned long seconds = 0;
unsigned long elapsed_time = 0;

bool new_temp = false;
bool new_power = false;
bool new_battery = false;
bool new_bilge = false;
bool new_level = false; 
bool send_data = false;

byte* IMEI_nr = {};  

byte data[2048] = {}; 
long int data_counter = 15;    

byte temp_sample[255] = {};
int temp_counter = 0;
byte temp_code = 2;

OneWire oneWire(TEMP_1);
DallasTemperature sensors(&oneWire);

void setup()
{
  Serial.begin(9600);
  Serial2.begin(4800);
  initRTC();
  initModem();
  IMEI_nr = get_IMEI_nr(); 
  for(int i = 0; i < 15; i++)
  {                        
    data[i] = IMEI_nr[i];
  }
  ping();
  initTimer();
}

void loop()
{ 
  //Prototyp for Unix timestamp, er ikke synket mot NTP, 02.02.16
  Serial.println(get_Time());
  
  if(new_temp == true)
  {
    //Eksempelkode for prototype 26.01.16
    /////////////////////////////////////
    data[data_counter] = temp_code;
    data_counter++;
    sensors.requestTemperatures();
    temp_sample[temp_counter] = sensors.getTempCByIndex(0)-1;
    Serial.print("Temperature Sample: ");
    Serial.println(temp_sample[temp_counter]);

    //Signalbehandling kommer her og leses inn i data buffer, eksempel:
    //data[data_counter] = processTemp(temp_sample, temp_counter);

    //Laster inn rådata istedenfor foreløpig:
    data[data_counter] = temp_sample[temp_counter];

    temp_counter++;
    data_counter++;
    
    //Dirty fix for å hindre overflyt
    if(temp_counter==255)
    {
      temp_counter=0;
      data_counter=0;
    }
    /////////////////////////////////////
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
  if(send_data == true)
  {
    data[data_counter] = 99;
    data_counter++;
    
    //Sender Data til server
    Serial.print("Sending Data: ");
    for(int i = 0; i < data_counter; i++)
    {
      Serial.print((int)data[i]);     //Typecast virker ikke som forventet.
      Serial.print(" ");
    }

    if(GPRS_send(data, data_counter))
    {                    
      Serial.println("Data was successfully sent!");
    }
    else
    {
      Serial.println("ERROR: Failed to send data");
    }
    temp_counter=0;
    data_counter=15;
    send_data=false;
  }
}

//Timer Interrupt som teller sekunder og setter flag når det skal samples eller sendes
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
  if(seconds == CLOCK_RESET)
  {
    seconds = 0;
  }
  if(elapsed_time%SEND_INTERVAL == 0)
  {
    send_data = true;
  }
}

