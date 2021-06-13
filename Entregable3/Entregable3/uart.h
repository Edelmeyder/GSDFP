/*
 * uart.h
 *
 * Created: 1/6/2021 5:52:25 pm
 *  Author: Edelmiro
 */ 


#ifndef UART_H_
#define UART_H_

#define BR 0x33 //9600 br @ 8MHz
/*---------------------
Buffer sizes, if larger than 255 variable types for indexes on .c file must be changed
------------------------*/
#define TX_BUFFER_LENGTH 250
#define RX_BUFFER_LENGTH 10

#include <stdint.h>

void UART_init();
void UART_sendString(const uint8_t * st);
uint8_t UART_getCharFromBuffer(uint8_t * ch);

#endif /* UART_H_ */