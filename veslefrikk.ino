#include <dsp.h>
#include <sensor.h>
#include <setup.h>
#include <HardwareLink3.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <rtc.h>


volatile unsigned long seconds = 0;

bool new_temp = false;
bool new_power = false;
bool new_battery = false;
bool new_bilge = false;
bool new_level = false; 
bool send_data = false;

byte data[2048] = {}; 

long int data_counter = 19;    
byte* IMEI_nr = {};  

byte temp_sample[255] = {};
int temp_counter = 0;
byte temp_code = 2;

uint32_t unix_time = 0;

OneWire oneWire(TEMP_1);
DallasTemperature sensors(&oneWire);

void setup()
{ 
  for(int j=19; j<256; j++)
  {
    data[j] = random(0,255);
  }
  
  Serial.begin(9600);
  Serial2.begin(2400);
  initModem();
  
  IMEI_nr = get_IMEI_nr(); 
    
    for(int i = 0; i < 15; i++)
    {                        
      data[i] = IMEI_nr[i];
    }
  
  //ping();
  initTimer();
  initRTC();
  Serial.println("Booting Successful, starting to sample:");
}

void loop()
{ 
  if(new_temp == true)
  { 
    data[data_counter] = temp_code;
    data_counter++;
    sensors.requestTemperatures();
    data[data_counter] = 0;
    data_counter++;
    temp_sample[temp_counter] = sensors.getTempCByIndex(0)-1;
    
    Serial.print("Temperature Sample: ");
    Serial.println(temp_sample[temp_counter]);

    data[data_counter] = temp_sample[temp_counter];

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
  if(send_data == true)
  {
    disableTimer();

    data[data_counter] = 99;    

    unix_time = get_Time();

    Serial.print("Unix Time: ");
    Serial.println(unix_time);
    
    data[15] = (unix_time >> 24) & 0xFF;
    data[16] = (unix_time >> 16) & 0xFF;
    data[17] = (unix_time >> 8) & 0xFF;
    data[18] = unix_time & 0xFF;

    unix_time = 0;
    unix_time = (data[15] << 24 )| (data[16] << 16 )| (data[17] << 8 )| data[18];
    Serial.print("Unix Time converted back is: ");
    Serial.println(unix_time);
    data_counter++;
    
    //Sender Data til server
    Serial.print("Sending Data: ");
    for(int i = 0; i < data_counter; i++)
    {
      Serial.print((int)data[i]);     //Typecast virker ikke som forventet.
      Serial.print(" ");
    }
    
    if(GPRS_send(data, 128))
    {                    
      Serial.println("Data was successfully sent!");
    }
    else
    {
      Serial.println("ERROR: Failed to send data");
    }
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

