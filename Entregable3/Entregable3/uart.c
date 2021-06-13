/*
 * uart.c
 *
 * Created: 1/6/2021 5:52:14 pm
 *  Author: Edelmiro
 */ 

#include "uart.h"
#include <avr/io.h>
#include <avr/interrupt.h>

static uint8_t TX_readIndex = 0, TX_writeIndex = 0, RX_readIndex = 0 , RX_writeIndex = 0;
static uint8_t TX_Buffer[TX_BUFFER_LENGTH], RX_Buffer[RX_BUFFER_LENGTH];

volatile uint8_t UART_flag;

void UART_init() {
	UBRR0H = (uint8_t) (BR>>8);
	UBRR0L = (uint8_t) BR;
	UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0); // enable RX and TX USART modules and RX interrupt
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00); // 8 bit - 1 stop bit - no parity - asynchronous mode
}

void UART_sendString(const uint8_t * st){
	uint8_t i = 0;
	while (st[i] != '\0') {
		if ((TX_writeIndex + 1) % TX_BUFFER_LENGTH == TX_readIndex) {
			//Error_code= ERROR_UART_FULL_BUFF;
			break;
		} else {
			TX_Buffer[TX_writeIndex] = st[i++];
			TX_writeIndex = (TX_writeIndex + 1) % TX_BUFFER_LENGTH;
		}
	}
	if (st[i] == '\0') {
		if ((TX_writeIndex + 1) % TX_BUFFER_LENGTH == TX_readIndex) {
			//Error_code= ERROR_UART_FULL_BUFF;
		} else {
			TX_Buffer[TX_writeIndex] = '\r';
			TX_writeIndex = (TX_writeIndex + 1) % TX_BUFFER_LENGTH;
			UCSR0B |= (1<<UDRIE0); //enable TX interrupt
		}
	}
}
uint8_t UART_getCharFromBuffer(uint8_t * ch) {
	if (RX_readIndex != RX_writeIndex) {
		*ch = RX_Buffer[RX_readIndex];
		RX_readIndex = (RX_readIndex + 1) % RX_BUFFER_LENGTH;
		return 1;
	} else 
		return 0;
}

ISR(USART_RX_vect) {
	if ((RX_writeIndex + 1) % RX_BUFFER_LENGTH == RX_readIndex) {
		//error buffer is full
		RX_writeIndex = RX_readIndex;
		UART_flag;
	} else {
		RX_Buffer[RX_writeIndex] = UDR0;
		if (RX_Buffer[RX_writeIndex] == '\r') {
			RX_Buffer[RX_writeIndex] = '\0';
			UART_flag = 1;
		}
		RX_writeIndex = (RX_writeIndex + 1) % RX_BUFFER_LENGTH;
	}
}

ISR(USART_UDRE_vect) {
	if (TX_readIndex != TX_writeIndex) { //there is data in buffer
		UDR0 = TX_Buffer[TX_readIndex];
		TX_readIndex = (TX_readIndex + 1) % TX_BUFFER_LENGTH;
	} else {
		UCSR0B &= ~(1<<UDRIE0); //disable interrupt
	}
}