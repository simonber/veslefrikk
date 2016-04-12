#include <dsp.h>
#include <sensor.h>
#include <setup.h>
#include <HardwareLink3.h>
#include <waterlevel.h>

bool new_temp = false;
bool new_power = false;
bool new_battery = false;
bool new_bilge = false;
bool new_level = false; 
bool send_data = false;

unsigned int data_counter = 19;  
unsigned int temp_counter = 0;
unsigned int temp_mean_counter = 0;
unsigned int battery_counter = 0;
unsigned int bilge_counter_1 = 0;
unsigned int bilge_counter_2 = 0;
unsigned int bilge_array_counter = 0;
unsigned int level_counter = 0;
unsigned int level_mean_counter = 0;
unsigned int power_counter = 0;
uint16_t temp_sec = 0;
volatile unsigned long ntp_counter = 0;
volatile unsigned long seconds = 0;

uint8_t bilge_buffer_1 = 0;
uint8_t bilge_buffer_2 = 0;
uint8_t data[1024] = {}; 

uint16_t ts_bilge_1[64] = {};
uint16_t ts_bilge_2[64] = {};

int16_t temp1_raw[61] = {};
int16_t temp2_raw[61] = {};
int16_t temp3_raw[61] = {};
int16_t temp4_raw[61] = {};
uint8_t temp1_mean[3] = {};
uint8_t temp2_mean[3] = {};
uint8_t temp3_mean[3] = {};
uint8_t temp4_mean[3] = {};
uint8_t shorepower_raw = 0;
uint8_t shorepower[256] = {};
uint16_t battery_1[128] = {};
uint16_t battery_2[128] = {};
uint8_t bilge_1[128] = {};
uint8_t bilge_2[128] = {};
float level_1[31] = {};
float level_2[31] = {};
float level_1_mean[3] = {};
float level_2_mean[3] = {};

const uint8_t IMEI[15] = {48,49,51,57,53,48,48,48,55,50,54,49,52,50,52};

typedef union
{
 float fl;
 uint8_t bytes[4];
} FLOATUNION_t;

typedef union
{
 uint16_t uint;
 uint8_t bytes[2];
} INTUNION_t;

void setup()
{ 
  initSystem();
  initModem();
  initSensors();
  initTimer();
  for(int i = 0; i < 15; i++)
  {                   
      data[i] = IMEI[i];
  }
}

void loop()
{ 
  if(new_temp == true)
  { 
    sampleTemperatures();
    new_temp = false;
  }
  if(new_power == true)
  {
    readShorePower();
    new_power = false;
  }
  if(new_battery == true)
  {
    readBattery();
    new_battery = false;
  }
  if(new_bilge == true)
  {
    readBilge();
    new_bilge = false;
  }
  if(new_level == true)
  {
    readLevel();
    new_level = false;
  }
  if(send_data == true)
  {
    disableTimer();
    packData();
    send_Package(data, data_counter);
    send_data=false;
    ntp_counter = 0;

    /*
    if(ntp_counter == 2);
    {
      Serial.print("Syncing time to NTP server... ");
      NTP_sync();
      Serial.println("  -   Time synced successfully!");
      ntp_counter = 0;
    }*/
    
    resetTimer();
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
  if(seconds > SEND_INTERVAL)
  {
    send_data = true;
  }
}

void sampleTemperatures()
{
  sensors.requestTemperatures(); 
  temp1_raw[temp_counter] = sensors.getTempC(Probe1);
  temp2_raw[temp_counter] = sensors.getTempC(Probe2);
  temp3_raw[temp_counter] = sensors.getTempC(Probe3);
  temp4_raw[temp_counter] = sensors.getTempC(Probe4);
  
  Serial.println("");
  Serial.print("Temperature 1: ");
  Serial.println(temp1_raw[temp_counter]);
  Serial.print("Temperature 2: ");
  Serial.println(temp2_raw[temp_counter]); 
  Serial.print("Temperature 3: ");
  Serial.println(temp3_raw[temp_counter]);
  Serial.print("Temperature 4: ");
  Serial.println(temp4_raw[temp_counter]);  
  temp_counter++;
  
  if(temp_counter >= TEMP_MEAN_COUNT)
  {
    Serial.println("Calculating mean temperatures... ");
    temp1_mean[temp_mean_counter] = takeMeanValue(temp1_raw, temp_counter);
    temp2_mean[temp_mean_counter] = takeMeanValue(temp2_raw, temp_counter);
    temp3_mean[temp_mean_counter] = takeMeanValue(temp3_raw, temp_counter);
    temp4_mean[temp_mean_counter] = takeMeanValue(temp4_raw, temp_counter);
    Serial.print("Mean value of Temperature 1: ");
    Serial.println(temp1_mean[temp_mean_counter]);
    Serial.print("Mean value of Temperature 2: ");
    Serial.println(temp2_mean[temp_mean_counter]);
    Serial.print("Mean value of Temperature 3: ");
    Serial.println(temp3_mean[temp_mean_counter]);
    Serial.print("Mean value of Temperature 4: ");
    Serial.println(temp4_mean[temp_mean_counter]);
    temp_mean_counter++;
    temp_counter = 0;
  }
}

void readShorePower()
{
    if(battery_1[battery_counter] > 14)
    {
      shorepower_raw = 1;
    }
    if(battery_1[battery_counter] < 14)
    {
      shorepower_raw = 1;
    }
}

void readBattery()
{ 
    battery_1[battery_counter] = analogRead(BATTERY_1);
    battery_2[battery_counter] = analogRead(BATTERY_2);
    Serial.print("Battery 1: ");
    Serial.println(battery_1[battery_counter]);
    Serial.print("Battery 2: ");
    Serial.println(battery_2[battery_counter]);
    battery_counter++;
}

void readBilge()
{
    bilge_1_raw = analogRead(BILGE_1);
    bilge_2_raw = analogRead(BILGE_2);
  
    if(bilge_1_raw > 512)
    {
       
       bilge_buffer_1 = 1;
    }
    else
    {
       bilge_buffer_1 = 0;  
    }

    if(bilge_state_1 != bilge_buffer_1)
    {
          
          bilge_state_1 = bilge_buffer_1;
          if(bilge_state_1)
          {
                temp_sec = seconds;
                temp_sec |= ( 1 << 15);
          }
          else
          {
                temp_sec = seconds;
                temp_sec &= ~(1 << 15);
          }
          ts_bilge_1[bilge_counter_1] = temp_sec;
          if(bilge_buffer_1 == 1)
          {
          Serial.print("Bilge 1 turned on after: ");
          Serial.println(seconds); 
          }
          if(bilge_buffer_1 == 0)
          {
          Serial.print("Bilge 1 turned off after: ");
          Serial.println(seconds); 
          }
          bilge_counter_1++;
    }

    if(bilge_2_raw > 512)
    {
       bilge_buffer_2 = 1;
    }
    else
    {
       bilge_buffer_2 = 0;  
    }

    if(bilge_state_2 != bilge_buffer_2)
    {
          bilge_state_2 = bilge_buffer_2;

          if(bilge_state_2)
          {
                temp_sec = seconds;
                temp_sec |= ( 1 << 15);
          }
          else
          {
                temp_sec = seconds;
                temp_sec &= ~(1 << 15);  
          }
          ts_bilge_2[bilge_counter_2] = temp_sec;
          if(bilge_buffer_2 == 1)
          {
          Serial.print("Bilge 2 turned on after: ");
          Serial.println(seconds); 
          }
          if(bilge_buffer_2 == 0)
          {
          Serial.print("Bilge 2 turned off after: ");
          Serial.println(seconds); 
          }
          bilge_counter_2++;
    }
}

void readLevel()
{
     level_1[level_counter] = readLevel_1();
     Serial.print("Water Level 1: ");
     Serial.println(level_1[level_counter]);
      
     level_2[level_counter] = readLevel_2();
     Serial.print("Water Level 2: ");
     Serial.println(level_2[level_counter]);
     
     level_counter++;

     if(level_counter >= LEVEL_MEAN_COUNT)
     {
        level_1_mean[level_mean_counter] = average(level_1, level_counter);
        Serial.print("Water Level 1 mean: ");
        Serial.println(level_1_mean[level_mean_counter]);
      
        level_2_mean[level_mean_counter] = average(level_2, level_counter);
        Serial.print("Water Level 2 mean: ");
        Serial.println(level_2_mean[level_mean_counter]);
        level_mean_counter++;
        level_counter=0;
     }
}

void packData()
{
  Serial.println("Packing Data... ");
  
  for(int i=0; i<temp_mean_counter; i++)
  {
    data[data_counter] = TEMP_1_CODE;
    data_counter++;
    data[data_counter] = temp1_mean[i];
    data_counter++;

    data[data_counter] = TEMP_2_CODE;
    data_counter++;
    data[data_counter] = temp2_mean[i];
    data_counter++;

    data[data_counter] = TEMP_3_CODE;
    data_counter++;
    data[data_counter] = temp3_mean[i];
    data_counter++;

    data[data_counter] = TEMP_4_CODE;
    data_counter++;
    data[data_counter] = temp4_mean[i];
    data_counter++;
  }

  for(int i=0; i<battery_counter; i++)
  {
    data[data_counter] = BATTERY_1_CODE;
    data_counter++;
    data[data_counter] = (battery_1[i] >> 8) & 0xFF;
    data_counter++;
    data[data_counter] = battery_1[i] & 0xFF;
    data_counter++;

    data[data_counter] = BATTERY_2_CODE;
    data_counter++;
    data[data_counter] = (battery_2[i] >> 8) & 0xFF;
    data_counter++;
    data[data_counter] = battery_2[i] & 0xFF;
    data_counter++;
  }

  INTUNION_t bilge_1;
  INTUNION_t bilge_2;

  for(int i=0; i<bilge_counter_1; i++)
  {
    data[data_counter] = BILGE_1_CODE;
    data_counter++;

    bilge_1.uint = ts_bilge_1[i];
    
    data[data_counter] = bilge_1.bytes[1];
    data_counter++;

    data[data_counter] = bilge_1.bytes[0];
    data_counter++;
  }
  
  for(int i=0; i<bilge_counter_2; i++)
  {
    data[data_counter] = BILGE_2_CODE;
    data_counter++;

    bilge_2.uint = ts_bilge_2[i];
    
    data[data_counter] = bilge_2.bytes[1];
    data_counter++;

    data[data_counter] = bilge_2.bytes[0];
    data_counter++;
  }

  FLOATUNION_t waterlevel_1;
  FLOATUNION_t waterlevel_2;
  
  for(int i=0; i<level_mean_counter; i++)
  {
    data[data_counter] = LEVEL_1_CODE;
    data_counter++;
    waterlevel_1.fl = level_1_mean[i]; 
    data[data_counter] = waterlevel_1.bytes[0];
    data_counter++;
    data[data_counter] = waterlevel_1.bytes[1];
    data_counter++;
    data[data_counter] = waterlevel_1.bytes[2];
    data_counter++;
    data[data_counter] = waterlevel_1.bytes[3];
    data_counter++;
    
    data[data_counter] = LEVEL_2_CODE;
    data_counter++;
    waterlevel_2.fl = level_2_mean[i]; 
    data[data_counter] = waterlevel_2.bytes[0];
    data_counter++;
    data[data_counter] = waterlevel_2.bytes[1];
    data_counter++;
    data[data_counter] = waterlevel_2.bytes[2];
    data_counter++;
    data[data_counter] = waterlevel_2.bytes[3];
    data_counter++;
  }

  for(int i=0; i<power_counter; i++)
  {
    data[data_counter] = POWER_CODE;
    data_counter++;
    data[data_counter] = shorepower[i];
    data_counter++;
  }
}

void resetTimer()
{
  data_counter = 19;
  temp_counter=0;
  temp_mean_counter = 0;
  battery_counter = 0;
  bilge_counter_1 = 0;
  bilge_counter_2 = 0;
  bilge_array_counter = 0;
  level_counter = 0;
  level_mean_counter = 0;
  power_counter = 0;
  seconds=0;
}
