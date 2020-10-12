/*
 * ping.c
 *
 *  Created on: Mar 7, 2018
 *      Author: cdishman
 */
#include <ping.h>
#include "driverlib/interrupt.h"

#define BIT0        0x01
#define BIT1        0x02
#define BIT2        0x04
#define BIT3        0x08
#define BIT4        0x10
#define BIT5        0x20
#define BIT6        0x40
#define BIT7        0x80
#define BIT8        0x80
#define BIT9        0x80
#define BIT10        0b10000000000
#define BIT11        0b100000000000
#define BIT12        0b1000000000000
#define BIT13        0b10000000000000
#define BIT14        0b100000000000000
#define BIT15        0b1000000000000000

volatile enum {LOW, HIGH, DONE} state;
volatile unsigned rising_time;
volatile unsigned falling_time;

void sonar_init(void){
    SYSCTL_RCGCGPIO_R |= BIT1; //Turn on PORT B

    //Set port to output
    GPIO_PORTB_DEN_R |= BIT3;
}

void timer_init(void){
    SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R3;
    //Set gpio alternate function on
    //GPIO_PORTB_AFSEL_R |= BIT3;
    GPIO_PORTB_DEN_R |= BIT3;
    GPIO_PORTB_PCTL_R |= GPIO_PCTL_PB3_T3CCP1;

    TIMER3_CTL_R &= ~TIMER_CTL_TBEN;

    TIMER3_CFG_R |= BIT2;
    //TIMER3_CFG_R &= BIT1|BIT0;
    TIMER3_TBMR_R |= TIMER_TBMR_TBCMR |TIMER_TBMR_TBMR_CAP| TIMER_TBMR_TBCDIR;
    TIMER3_CTL_R |= (BIT10 | BIT11);
    TIMER3_TBILR_R |=  0xFFFF;
    //TIMER3_TBPR_R |=  0xFF;
    TIMER3_ICR_R |= TIMER_ICR_CBECINT;
    TIMER3_IMR_R |= TIMER_IMR_CBEIM;


	NVIC_PRI9_R |= 0x20;
	NVIC_EN1_R |= 0x10;

    IntRegister(INT_TIMER3B, TIMER3B_Handler);

	TIMER3_CTL_R |= TIMER_CTL_TBEN | TIMER_CTL_TBEVENT_BOTH;

    IntMasterEnable();
}



void send_pulse(void){
    //DISABLE TIMER

    TIMER3_CTL_R &= ~TIMER_CTL_TBEN;
    GPIO_PORTB_PCTL_R &= ~GPIO_PCTL_PB3_T3CCP1;

    //set output
    GPIO_PORTB_AFSEL_R &= ~BIT3;
    GPIO_PORTB_DIR_R |= BIT3;

    //set PB3 high
    GPIO_PORTB_DATA_R |= BIT3;

    //have ping high for 5 microSeconds
    timer_waitMicros(5);

    //Set PB3 low
    GPIO_PORTB_DATA_R &= ~BIT3;

    //reset to input for listening
    GPIO_PORTB_DIR_R &= ~BIT3;
    GPIO_PORTB_AFSEL_R |= BIT3;


    GPIO_PORTB_PCTL_R |= GPIO_PCTL_PB3_T3CCP1;
    TIMER3_CTL_R |= TIMER_CTL_TBEN;

    state = LOW;
}


unsigned read_pulse(void){
	unsigned int MAXSENSORVALUE = 4294967295;

    send_pulse();
    while(state != DONE){
    }

    if(rising_time > falling_time){
        return rising_time + (MAXSENSORVALUE - falling_time);
    }
    return falling_time - rising_time;
}

unsigned time2dist(unsigned time){
    const double CLOCK = 16000000;
	const double SPEEDOFSOUND = 34000;

    return (time/CLOCK) * (SPEEDOFSOUND /2);
}


void TIMER3B_Handler(void){
	if (TIMER3_MIS_R & BIT10) {
		switch (state) {
		case LOW :
			rising_time = TIMER3_TBR_R;
			state = HIGH;
			break;
		case HIGH :
			falling_time = TIMER3_TBR_R;
			state = DONE;
			break;
		case DONE:
			//MAYBE todo:
			break;

		}

        TIMER3_ICR_R |= BIT10;
	}

}





