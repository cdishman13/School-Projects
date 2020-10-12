/*
 * servo.c
 *
 *  Created on: Mar 21, 2018
 *      Author: cdishman
 */
#include "servo.h"
#define PWM_PERIOD_LOW 320000


void servo_init(){
    //start clock for port b
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
    //start clock for timer1
    SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R1;
    //ENABLE PORTB5 AS GPIO OUTPUT
    GPIO_PORTB_DEN_R |= BIT5;
    GPIO_PORTB_DIR_R |= BIT5;
    //SELECT ALTERNATE FUNCTION T1CCP1
    GPIO_PORTB_AFSEL_R |= BIT5;
    GPIO_PORTB_PCTL_R |= GPIO_PCTL_PB5_T1CCP1;
    //DISABLE TIMER FOR CONFIG
    TIMER1_CTL_R &= ~TIMER_CTL_TBEN;

    TIMER1_CFG_R |= TIMER_CFG_16_BIT;
    TIMER1_CTL_R &= ~TIMER_CTL_TBPWML;

    TIMER1_TBMR_R &= ~TIMER_TBMR_TBCMR;
    TIMER1_TBMR_R |=  TIMER_TBMR_TBAMS | TIMER_TBMR_TBMR_PERIOD;

    //set pulse width to 20ms
    unsigned int period_high = 16000;
    unsigned int period_total = (PWM_PERIOD_LOW + period_high);
    TIMER1_TBILR_R =  period_total & 0xFFFF;
    TIMER1_TBPR_R =  (period_total >> 16) & 0xFF;

    //set match point
    TIMER1_TBMATCHR_R = (period_total - period_high) & 0xFFFFFFFF;
    TIMER1_TBPMR_R = ((period_total - period_high) >> 16) & 0xFF;

    //re-enable timer
    TIMER1_CTL_R |= TIMER_CTL_TBEN;
}

//sets the angle and returns the calibrated tick value that it was set to
unsigned int set_angle(int degrees){
    //bot 3 calibration settings
    float calibration_offset = 92.828;
    float calibration_multiplier = 1.7372;
    //Takes in expected angle and converts it to the actual ticks required to acheive that angle
    unsigned int period_high = (((calibration_multiplier*degrees - calibration_offset)/180)+1)*16000;

    //disable timer for config
    TIMER1_CTL_R &= ~TIMER_CTL_TBEN;

    unsigned int period_total = (PWM_PERIOD_LOW + period_high);
    //set pulse width to 20ms
    TIMER1_TBILR_R =  period_total & 0xFFFF;
    TIMER1_TBPR_R =  (period_total >> 16) & 0xFF;

    //set match point
    TIMER1_TBMATCHR_R = (period_total - period_high) & 0xFFFFFFFF;
    TIMER1_TBPMR_R = ((period_total - period_high) >> 16) & 0xFF;

    //re-enable timer
    TIMER1_CTL_R |= TIMER_CTL_TBEN;
    return period_high;
}




