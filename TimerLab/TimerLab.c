/*
 * TimerLab.c
 *
 * Created: 13.02.2014 22:25:17
 *  Author: werwo_000
 */ 


#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	PORTB |= _BV(PINB2);
	PORTD |= _BV(PIND5);
	
	DDRD ^= _BV(PIND5);
	
    while(1)
    {
		DDRB ^= _BV(PINB2);
		DDRD ^= _BV(PIND5);
		_delay_ms(250);
    }
}