/*
*
*   uart.h
*
*   Used to set up the RS232 connector and WIFI module
*   uses UART1 at 115200
*
*
*   @author Dane Larson
*   @date 07/18/2016
*/

#ifndef UART_H_
#define UART_H_

#include "Timer.h"
#include "WiFi.h"
#include <inc/tm4c123gh6pm.h>

void uart_init(void);

void uart_sendChar(char data);

int fancy_uart_receive(int* gimme);

int uart_receive(void);

void uart_sendStr(const char *data);


#endif /* UART_H_ */
