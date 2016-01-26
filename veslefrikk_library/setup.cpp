#include "setup.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <HardwareLink3.h>

long int pincode = 0000; 
char* ip_addr;
char ping_addr[32] = "www.google.com"; 

void initTimer()
{
	cli();            			//Disable Global Interrupts
	TCCR1A = 0;
	TCCR1B = 0;
	OCR1A = 15624;
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << CS10);
	TCCR1B |= (1 << CS12);
	TIMSK1 |= (1 << OCIE1A);
	sei();            			//Enable Global Interrupts
}

void initModem()
{
	Serial.println(F("Modem booting"));
  	modemStart(pincode);                            
  	Serial.println(F("Modem boot completed"));
  	Serial.println(F("Entering modem setup"));
  	if(GPRS_setup())
  	{                               
    	Serial.println(F("Modem setup completed"));   
  	}
  	else
  	{
    Serial.println(F("Modem setup failed"));
	}
	
	ip_addr = get_IP();                             
  	Serial.print("IP address: ");
  	Serial.println(ip_addr);
}

void ping()
{
	Serial.print("Signal strenght: ");
  	Serial.println(getSignalStrength());
  	
  	if(GPRS_ping(ping_addr))
  	{                       
    	Serial.print("Pinged "); 
    	Serial.print(ping_addr); 
    	Serial.println(" successfully");
  	}
  	else
  	{
    	Serial.print("ERROR: Could not ping ");
    	Serial.println(ping_addr);
  	}
}
  	
  	
	