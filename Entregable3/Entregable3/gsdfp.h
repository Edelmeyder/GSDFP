/*
 * gsdfp.h
 *
 * Created: 1/6/2021 5:53:31 pm
 *  Author: Edelmiro
 */ 


#ifndef GSDFP_H_
#define GSDFP_H_

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

void GSDFP_init();
void GSDFP_setFreq(uint16_t);
void GSDFP_on();
void GSDFP_off();

#endif /* GSDFP_H_ */