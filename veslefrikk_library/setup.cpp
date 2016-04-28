#include "setup.h"
#include "waterlevel.h"

<<<<<<< HEAD
uint16_t bilge_1_raw;
uint16_t bilge_2_raw; 

uint8_t bilge_state_1;
uint8_t bilge_state_2;
=======
char ping_addr[32] = "www.google.com"; 
long int pincode = 1234;
>>>>>>> b27cf5da3cb83a4036f743b9c641f5c54083e605

void initTimer()
{
	Serial.println("Startup Complete. Starting timer...");
    Serial.println("");    
	cli();            			
	TCCR1A = 0;
	TCCR1B = 0;
	OCR1A = 15624;
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << CS10);
	TCCR1B |= (1 << CS12);
	TIMSK1 |= (1 << OCIE1A);
	sei();        				
}

void initSystem()
{
	pinMode(8, OUTPUT); //Pin 8 - PWRKEY
	pinMode(9, OUTPUT); //Pin 9 - RESTART
	Serial.begin(57600);
  	Serial1.begin(9600);
  	Serial2.begin(9600);
  	Serial3.begin(4800);
  	Serial.println("Starting Veslefrikk 1.0... ");
}

void enableTimer()
{
	TIMSK1 |= (1 << OCIE1A);
}

void disableTimer()
{
	TIMSK1 &= ~(1 << OCIE1A);
}

<<<<<<< HEAD
void initModem()
{		
	Serial.print("Booting Modem..."); 
	digitalWrite(8, HIGH);
	delay(1000);
	digitalWrite(8, LOW);
    delay(18000);

  	Serial.println("	-	Modem boot completed.");
  	Serial.print("Entering modem setup...");
  	
  	if(GPRS_setup())
  	{                              
    	Serial.println("	-	Modem setup completed");   
=======
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
>>>>>>> b27cf5da3cb83a4036f743b9c641f5c54083e605
  	}
  	else
  	{
    	Serial.println(F("Modem setup failed"));
  	}
  	
<<<<<<< HEAD
  	Serial.print("Signal strenght: ");
  	Serial.println(getSignalStrength());  	 
}

void initSensors()
{
	sensors.begin();
 	sensors.setResolution(Probe1, 9);
  	sensors.setResolution(Probe2, 9);
  	sensors.setResolution(Probe3, 9);
  	sensors.setResolution(Probe4, 9);
  	
  	bilge_1_raw = analogRead(BILGE_1);
    bilge_2_raw = analogRead(BILGE_2);
    
    if(bilge_1_raw > 512)
    {
    	bilge_state_1 = 1;
    }
    else
    {
    	bilge_state_1 = 0;
    }
    
    if(bilge_2_raw > 512)
    {
    	bilge_state_2 = 1;
    }
    else
    {
    	bilge_state_2 = 0;
    }
  	//setBaseCapacitance();
=======
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
>>>>>>> b27cf5da3cb83a4036f743b9c641f5c54083e605
}

  	
  	
	