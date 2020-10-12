/*
 * servo.h
 *
 *  Created on: Mar 21, 2018
 *      Author: cdishman
 */

#ifndef SERVO_H_
#define SERVO_H_


#include <inc/tm4c123gh6pm.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <timer.h>


void servo_init(void);
unsigned int set_angle(int);

#endif /* SERVO_H_ */
