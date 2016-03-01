#include "setup.h"

char ping_addr[32] = "www.google.com"; 
long int pincode = 1234;

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

void enableTimer()
{
	TIMSK1 |= (1 << OCIE1A);
}

void disableTimer()
{
	TIMSK1 &= ~(1 << OCIE1A);
}

void initModem(byte* data)
{	
	//Modem Boot
	Serial.println(F("Trying to boot modem..."));  
	modemStart(pincode);                       
  	Serial.println(F("Modem boot completed."));
  	Serial.println(F("Entering modem setup..."));
  	
  	//Modem Setup
  	if(GPRS_setup())
  	{                               //Configures the modem so that it is able to send data and SMS.
    	Serial.println(F("Modem setup completed"));   
  	}
  	else
  	{
    	Serial.println(F("Modem setup failed"));
  	}
  	
  	//Signal Strength
  	Serial.print("Signal strenght: ");
  	Serial.println(getSignalStrength());
  	
  	//Ping
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
  	 
    Serial.println("");
    Serial.println("Startup Complete.");
    Serial.println("");
}

  	
  	
	