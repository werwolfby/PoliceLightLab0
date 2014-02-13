/*
 * TimerLab.c
 *
 * Created: 13.02.2014 22:25:17
 *  Author: werwo_000
 */ 


#include <avr/io.h>
#include <util/delay.h>

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
	
	OCR0A = 10;
	OCR0B = 10;
	
    while(1)
    {
		OCR0A += 10;
		OCR0B += 10;
		_delay_ms(20);
    }
}