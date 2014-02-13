/*
 * TimerLab.c
 *
 * Created: 13.02.2014 22:25:17
 *  Author: werwo_000
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t mode = 0;
uint8_t value = 0;
uint8_t prescaler = 0;
	
ISR(TIMER0_OVF_vect)
{
	prescaler++;
	if (prescaler == 5)
	{
		switch (mode)
		{
			case 0:
				value += 1;
				break;
			case 1:
				value -= 1;
				break;
		}
		if (value == 0 || value == 255) mode ^= 1;
		OCR0A = value;
		OCR0B = value;
		prescaler = 0;
	}
}

#define FAST_PWM (_BV(WGM01) | _BV(WGM00))
#define COM0A_SET (_BV(COM0A0) | _BV(COM0A1))
#define COM0B_SET (_BV(COM0B0) | _BV(COM0B1))
#define COM0B_CLEAR (_BV(COM0B1))
#define PRESCALE_1 (_BV(CS00))
#define PRESCALE_8 (_BV(CS01))
#define PRESCALE_64 (_BV(CS00) | _BV(CS01))
#define PRESCALE_256 (_BV(CS02))

int main(void)
{
	DDRB |= _BV(DDB2);
	DDRD |= _BV(DDD5);
	
	TCCR0A |= FAST_PWM | COM0A_SET | COM0B_CLEAR;
	TCCR0B |= PRESCALE_1;
	
	TIMSK |= _BV(TOIE0);
	
	sei();
	
    while(1)
    {
    }
}