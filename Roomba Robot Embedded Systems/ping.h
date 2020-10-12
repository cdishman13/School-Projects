/*
 * ping.h
 *
 *  Created on: Mar 7, 2018
 *      Author: cdishman
 */

#ifndef PING_H_
#define PING_H_

#include <inc/tm4c123gh6pm.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <timer.h>

void sonar_init(void);
void timer_init(void);
void send_pulse(void);
unsigned read_pulse(void);
unsigned time2dist(unsigned time);
void TIMER3B_Handler(void);
#endif /* PING_H_ */
