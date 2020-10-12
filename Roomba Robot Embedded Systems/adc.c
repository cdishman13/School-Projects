/*
 * adc.c
 *
 *  Created on: Feb 28, 2018
 *      Author: cdishman
 */

#include "adc.h"

void adc_init(void){
    //initialize
    //GPIO port b clock
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
    //adc clock
    SYSCTL_RCGCADC_R |= 0x1;
    //alternate function enable
    GPIO_PORTB_AFSEL_R |= 0x01;
    //disable digital gpio on PB0
    GPIO_PORTB_DEN_R &= 0b11111110;
    //set as input on PB0
    GPIO_PORTB_DIR_R &= 0b11111110;
    //disable analog isolation(?)
    GPIO_PORTB_AMSEL_R |= 0x01;
    //trigger by processor
    GPIO_PORTB_ADCCTL_R = 0x00;
    //SS0 diable for config
    ADC0_ACTSS_R &= ~ADC_ACTSS_ASEN0;
    //set SS0 to processs adc trigger
    ADC0_EMUX_R = ADC_EMUX_EM0_PROCESSOR;
    //set what AIN pin to use
    ADC0_SSMUX0_R |= 0x000A;
    //enable raw interrupt
    ADC0_SSCTL0_R |= (ADC_SSCTL0_IE0 | ADC_SSCTL0_END0);
    //Oversample to reduce jitter
    ADC0_SAC_R |= ADC_SAC_AVG_64X;
    //reenable SS0 after config
    ADC0_ACTSS_R |= ADC_ACTSS_ASEN0;
}


int adc_read(void){
    //take a selfie
   ADC0_PSSI_R=ADC_PSSI_SS0;

   while((ADC0_RIS_R & ADC_RIS_INR0) == 0){
       // wait until snapshot returns result
   }

   return ADC0_SSFIFO0_R;
}

