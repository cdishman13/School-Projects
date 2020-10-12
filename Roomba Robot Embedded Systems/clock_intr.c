/**
 * clock-intr.c: timer- and interrupt-based clock program
 * This is skeleton code. You need to make it complete.
 *
 * @author Zach Glanz, Zhao Zhang
 * @date 08/07/2016
 */

#include "timer.h"
#include "lcd.h"
#include "servo.h"
#include "button.h"
#include <stdbool.h>
#include "driverlib/interrupt.h"
#include "stdio.h"
//
int main(void){

    lcd_init();
    button_init();
    servo_init();

    unsigned int angle=90;
    unsigned int ticks = 24000;
    unsigned int pulse_len = 0;
    unsigned int last_angle=0;
    signed char dir=1;
    while(1){
        switch(button_getButton()){
        case 0:
            break;
        case 1:
            angle += 1*dir;
            ticks += 89 * dir;
            break;
        case 2:
            angle += 2.5*dir;
            ticks += 222 * dir;
           break;
        case 3:
            angle += 5*dir;
            ticks += 444 * dir;
          break;
        case 4:
            dir *= -1;
            break;

        }
        //we overflowed
        if (angle > 60000) angle = 0;
        // dont go beyond 180
        if (angle > 180) angle = 180;

        //get rid of that stupid twitching
        if (angle!=last_angle) {
            pulse_len = set_angle(angle);
        }
        //if (angle!=last_angle) set_angle_ticks(ticks);

        lcd_printf("Angle: %d\nPulse length: %d\nDirection: %d", angle, pulse_len, dir);
        last_angle = angle;
        timer_waitMillis(300);
    }

}



