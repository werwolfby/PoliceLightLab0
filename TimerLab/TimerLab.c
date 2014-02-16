/*
 * TimerLab.c
 *
 * Created: 13.02.2014 22:25:17
 *  Author: werwo_000
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>

#define FAST_PWM0 (_BV(WGM01) | _BV(WGM00))
#define FAST_PWM1 (_BV(WGM11) | _BV(WGM10))
#define CTCA 0
#define CTCB (_BV(WGM12))
#define COM0A_SET (_BV(COM0A0) | _BV(COM0A1))
#define COM1A_SET (_BV(COM1A0) | _BV(COM1A1))
#define COM1A_TOGGLE (_BV(COM1A0))
#define COM0B_SET (_BV(COM0B0) | _BV(COM0B1))
#define COM0B_CLEAR (_BV(COM0B1))
#define PRESCALE_0_1 (_BV(CS00))
#define PRESCALE_0_8 (_BV(CS01))
#define PRESCALE_0_64 (_BV(CS00) | _BV(CS01))
#define PRESCALE_0_256 (_BV(CS02))
#define PRESCALE_1_1 (_BV(CS10))
#define PRESCALE_1_8 (_BV(CS11))
#define PRESCALE_1_64 (_BV(CS10) | _BV(CS11))
#define PRESCALE_1_256 (_BV(CS12))

uint8_t mode = 0;
uint8_t value = 128;
	
ISR(TIMER0_OVF_vect)
{
	if (mode == 0) value++;
	else value--;
	if (value == 0 || value == 255) 
	{
		mode ^= 1;
	}
	OCR0A = value;
	OCR0B = value;
}

ISR(TIMER1_COMPA_vect)
{
	OCR1A = 400 + value * 2;
}

int main(void)
{
	DDRB |= _BV(DDB2) | _BV(DDB3);
	DDRD |= _BV(DDD5);
	
	TCCR0A |= FAST_PWM0 | COM0A_SET | COM0B_CLEAR;
	
	TCCR1A |= CTCA | COM1A_TOGGLE;
	TCCR1B |= CTCB;
	
	TCCR0B |= PRESCALE_0_8;
	TCCR1B |= PRESCALE_1_1;
	
	OCR1A = 400;
	
	TIMSK |= _BV(TOIE0) | _BV(OCIE1A);
	
	sei();
	
    while(1)
    {
    }
}