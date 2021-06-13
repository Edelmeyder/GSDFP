/*
 * gsdfp.c
 *
 * Created: 1/6/2021 5:52:30 pm
 *  Author: Edelmiro
 */ 

#include "gsdfp.h"
#include <avr/io.h>

void GSDFP_init(){
	DDRB |= (1<<PORTB1); // sets OC1A as output
	TCCR1A = 0x00; // OC1A disconected
	TCCR1B = (1<<WGM12) | (1<<CS10); //CTC mode - No prescaling
	GSDFP_setFreq(100);
}

void GSDFP_on(){
	TCCR1A = (1<<COM1A0); // toggle OC1A on campare match
}

void GSDFP_off(){
	TCCR1A = 0x00; // OC1A disconected
}

void GSDFP_setFreq(uint16_t f) {
	OCR1A = (F_CPU/(2*f)) - 1;
}