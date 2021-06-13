/*
 * Entregable3.c
 *
 * Created: 1/6/2021 5:51:29 pm
 * Author : Edelmiro
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "gsdfp.h"
#include "menu.h"

extern volatile uint8_t UART_flag;

int main(void) {
	UART_init();
	GSDFP_init();
	sei();
	MENU_welcome();
	while (1) {
		if (UART_flag) {
			UART_flag = 0;
			MENU_update();
		}
	}
}



