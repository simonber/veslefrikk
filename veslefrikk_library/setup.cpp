#include "setup.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Arduino.h"

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