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
uint8_t prescaler = 0;
	
ISR(TIMER0_OVF_vect)
{
	//if (TIFR & _BV(TOV1)) return;
	
	prescaler++;
	if (prescaler == 1)
	{
		if (mode == 0) value++;
		else value--;
		if (value == 0 || value == 255) 
		{
			mode ^= 1;
		}
		uint16_t newValue = 400 + value * 2;
		if (TCNT1 > newValue - 8)
		{
			TCNT1 = 0;
		}
		OCR1A = newValue;
		//TCNT1 = 0;
		OCR0A = value;
		OCR0B = value;
		prescaler = 0;
	}
}

int main(void)
{
	DDRA |= 
	
	DDRB |= _BV(DDB2) | _BV(DDB3);
	DDRD |= _BV(DDD5);
	
	TCCR0A |= FAST_PWM0 | COM0A_SET | COM0B_CLEAR;
	
	TCCR1A |= CTCA | COM1A_TOGGLE;
	TCCR1B |= CTCB;
	
	TCCR0B |= PRESCALE_0_1;
	TCCR1B |= PRESCALE_1_1;
	
	TIMSK |= _BV(TOIE0);
	
	sei();
	
    while(1)
    {
    }
}