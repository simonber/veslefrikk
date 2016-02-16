#include <rtc.h>

RTC_DS1307 rtc;
DateTime now;

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
	Serial.println("Init RTC");
	
	if (! rtc.begin()) 
	{
    	Serial.println("Couldn't find RTC");
    	while (1);
  	}

  	if (! rtc.isrunning()) 
  	{
    	Serial.println("RTC is NOT running!");
  	}
  	
  	
  	Serial.println("RTC init successfull!");
    Serial.print("Current Unix Time is: ");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    now = rtc.now();
    Serial.println(now.unixtime());
}

uint32_t get_Time()
{
	now = rtc.now();
	return now.unixtime();
}


