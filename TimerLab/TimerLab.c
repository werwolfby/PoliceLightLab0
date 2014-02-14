/*
 * TimerLab.c
 *
 * Created: 13.02.2014 22:25:17
 *  Author: werwo_000
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#define C1 15288
#define C1d 14431
#define D1 13621
#define D1d 12856
#define E1 12134
#define F1 11453
#define F1d 10811
#define G1 10204
#define G1d 9631
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
#define G2d 4815
#define A2 4545
#define A2d 4291
#define H2 4049
#define C3 3822
#define P 0
#define End 1
#define N16 250.000
#define N8 500.000
#define N4 1000.000
#define N2 2000.000
#define N1 4000.000

uint16_t const tanki[] PROGMEM ={160.000,P,N16,C2,N16,D2,N16,D2d,N16,C2,N16,D2,N16,D2d,N16,D2d,N16,F2,N16,G2,N16,D2d,N16,F2,N16,G2,N16,
F2,N16,G2,N16,A2,N16,F2,N16,G2,N16,A2,N16,G2d,N16,A2d,N16,C3,N16,G2d,N16,A2d,N16,C3,N16,C3,N16,P,N16,C3,N16,C3,N16,C3,N16,C3,N16,End}; //мелодия танчиков

uint16_t const mario[] PROGMEM = {100.000,P,N8,E2,N16,E2,N16,P,N16,E2,N8,P,N16,C2,N16,E2,N16,P,N16,
	G2,N16,P,N16,P,N8,G1,N16,P,N8,P,N8,
	C2,N16,P,N8,G1,N16,P,N8,E1,N8,P,N8,
	P,N16,A1,N16,P,N16,H1,N16,P,N16,A1d,N16,A1,N16,P,N16,
	G1,N16,E2,N16,G2,N16,A2,N16,P,N16,F2,N16,G2,N16,
P,N16,E2,N16,P,N16,C2,N16,D2,N16,H1,N16,End};   //мелодия марио

uint16_t const miniPolka[] PROGMEM ={120.000,P,N8,C2,N8,E2,N8,G2,N8,E2,N8,G2,N8,F2,N8,D2,N4,G2,N8,F2,N8,D2,N4,G2,N8,E2,N8,C2,N4,
C2,N8,E2,N8,G2,N8,E2,N8,A2,N8,G2,N8,F2,N4,G2,N8,F2,N8,E2,N8,D2,N8,C2,N4,End};
uint16_t const bumer[] PROGMEM ={170.000,P,N8,E2,N8,G2,N4,P,N4,P,N4,
	G2,N8,E2,N4,P,N4,P,N4,
	A2,N8,G2,N8,A2,N8,G2,
N8,A2,N8,G2,N8,A2,N8,G2,N8,A2,N8,H2,N4,P,N4,End};
uint16_t const nokia[] PROGMEM ={120.000,P,N8,E2,N8,D2,N8,
	F1d,N4,G1d,N4,C2d,N8,H1,N8,
	D1,N4,E1,N4,H1,N8,A1,N8,
C1d,N4,E1,N4,A1,N4,End};
uint16_t const mortal[] PROGMEM ={140.000,A1,N8,A1,N8,C2,N8,A1,N8,D2,N8,A1,N8,E2,N8,D2,N8,
	C2,N8,C2,N8,E2,N8,C2,N8,G2,N8,C2,N8,E2,N8,C2,N8,
	G1,N8,G1,N8,H1,N8,G1,N8,C2,N8,G1,N8,D2,N8,C2,N8,
F1,N8,F1,N8,A1,N8,F1,N8,C2,N8,F1,N8,C2,N8,H1,N8,End};

//int *playlist[]={mortal,
	//nokia,
	//miniPolka,
	//bumer,
	//mario,
	//tanki
//};
//
//int trackN=0;
//

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
	
	#define SONG miniPolka
	
    while(1)
    {
		uint16_t pause = pgm_read_word(SONG + current*2 + 0);
		uint16_t value = pgm_read_word(SONG + current*2 + 1);
		
		if (value == End)
		{
			current = 0;
			continue;				
		}
		
		OCR1A = value;
		
		for (int i = 0; i < pause; i++)
			_delay_us(370);
		
		current++;
    }
}