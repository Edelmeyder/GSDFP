/*
 * menu.c
 *
 * Created: 8/6/2021 4:02:33 pm
 *  Author: Edelmiro
 */ 

#include "menu.h"
#include "uart.h"
#include "gsdfp.h"
#include <string.h>

uint8_t command[6];
uint16_t freq = 0;

uint8_t isnum(uint8_t c);
uint16_t pow10(uint8_t a);

void MENU_welcome() {
	UART_sendString((uint8_t *) "Generador de señales digitales de frecuencia programable");
	UART_sendString((uint8_t *) "Ingrese una frecuencia entre 100 y 10000HZ");
	UART_sendString((uint8_t *) "ON - Encender generador");
	UART_sendString((uint8_t *) "OFF - Apagar generador");
	UART_sendString((uint8_t *) "RST - Reiniciar");
}

void MENU_update() {
	uint8_t i = 0;
	while (UART_getCharFromBuffer(&command[i++]) && command[i - 1] != '\0') {
		if (i == 6){
			UART_sendString((uint8_t *) "Comando no válido");
			return;
		}
	}
	if (strcmp(command, "ON") == 0) {
		GSDFP_on();
	} else if (strcmp(command, "OFF") == 0) {
		GSDFP_off();
	} else if (strcmp(command, "RST") == 0) {
		GSDFP_init();
		MENU_welcome();
	} else if (strlen(command) > 2) {
		for (i = 0; i<strlen(command); i++) {
			if (!isnum(command[i])){
				UART_sendString((uint8_t *) "Comando no válido");
				return;
			} else {
				freq += (command[i] - '0') * (pow10(strlen(command) - i));
			}
		}
		if (freq <= 10000 && freq >= 100) {
			GSDFP_setFreq(freq);
		} else {
			 UART_sendString((uint8_t *) "Comando no válido");
		}
		freq = 0;
	} else {
		UART_sendString((uint8_t *) "Comando no válido");
	}
}

uint8_t isnum(uint8_t c) {
	if (c >= '0' && c <= '9') 
		return 1;
	else
		return 0;
}

uint16_t pow10(uint8_t a) {
	uint16_t res = 1;
	for (int i = 1; i < a; i++)
		res *= 10;
	return res;
}