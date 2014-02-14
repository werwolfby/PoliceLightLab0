/*
 * TimerLab.c
 *
 * Created: 13.02.2014 22:25:17
 *  Author: werwo_000
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>

#define E1 12134
#define G1 10204
#define A1 9090
#define A1d 8580
#define H1 8099
#define C2 7648
#define C2d 7220
#define D2 6814
#define D2d 6430
#define E2 6069
#define F2 5730
#define G2 5102
#define A2 4545
#define G2d 4815
#define A2d 4291
#define C3 3822
#define P 0
#define End 1

int tanki[31]={C2,D2,D2d,C2,D2,D2d,D2d,F2,G2,D2d,F2,G2,F2,G2,A2,F2,G2,A2,G2d,A2d,C3,G2d,A2d,C3,C3,P,C3,C3,C3,C3,End}; //мелодия танчиков

int mario[45]= {E2,E2,P,E2,P,C2,E2,P,
	G2,P,P,G1,P,P,
	C2,P,P,G1,P,P,E1,P,
	P,A1,P,H1,P,A1d,A1,P,
	G1,E2,G2,A2,P,F2,G2,
	P,E2,P,C2,D2,H1,End};  //мелодия марио


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
		//if (TCNT1 > newValue - 8)
		//{
			//TCNT1 = 0;
		//}
		//OCR1A = newValue;
		////TCNT1 = 0;
		OCR0A = value;
		OCR0B = value;
		prescaler = 0;
	}
}

#include <util/delay.h>

int main(void)
{
	//DDRA |= 
	//
	DDRB |= _BV(DDB2) | _BV(DDB3);
	DDRD |= _BV(DDD5);
	
	TCCR0A |= FAST_PWM0 | COM0A_SET | COM0B_CLEAR;
	
	TCCR1A |= CTCA | COM1A_TOGGLE;
	TCCR1B |= CTCB;
	
	TCCR0B |= PRESCALE_0_1;
	TCCR1B |= PRESCALE_1_1;
	
	TIMSK |= _BV(TOIE0);
	
	sei();
	
	uint8_t current = 0;
	
    while(1)
    {
		uint16_t value = mario[current];
		
		if (value == End)
		{
			current = 0;
			continue;				
		}
		
		OCR1A = value;
		
		_delay_ms(130);
		
		current++;
    }
}