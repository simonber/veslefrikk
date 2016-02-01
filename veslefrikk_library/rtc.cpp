#include <rtc.h>

RTC_DS1307 rtc;

uint8_t dec2bcd(uint8_t num)
{
  return ((num/10 * 16) + (num % 10));
}

uint8_t bcd2dec(uint8_t num)
{
  return ((num/16 * 10) + (num % 16));
}

void initRTC () 
{
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) 
  {
    Serial.println("RTC is NOT running!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

uint32_t get_Time()
{
    DateTime now = rtc.now();
    
   	return now.unixtime();
    
    delay(3000);
}