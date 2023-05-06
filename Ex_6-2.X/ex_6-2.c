/*
 * File:   ex_6-2
 * Author: NGUYEN HAI DANG
 * Field of Study: Mechatronics Engineering
 * This program displays my name and a clock on an HDD44780 LCD
 */
#define _XTAL_FREQ 1000000
#include"16F1509_config.h"
#include <xc.h>
#include <stdio.h>
#include"lcd.h"

void main(void) {
    // Time counter variables
    unsigned char hour_counter   = 0;
    unsigned char minute_counter = 0;
    unsigned char second_counter = 0;
    char time_string[9];
    
    // These variables are used to convert to a string
    // x_counter = x_digit1 X 10 + x_digit2
    unsigned char hour_digit1   = 0, hour_digit2   = 0; // Two digits of the Hour
    unsigned char minute_digit1 = 0, minute_digit2 = 0;
    unsigned char second_digit1 = 0, second_digit2 = 0;
    
    // LCD initialization
    LCD_Initialize();
    
    // Aligning and displaying my name closely to the center
    LCDPutStr2("NGUYEN HAI DANG",1,0);
    
    // Aligning and displaying a clock closely to the center
    LCDPutStr2("00:00:00",4,1);
    
    while(1){
        // Loop will continue until it has reached the hour value of 24
        for(hour_counter=0;hour_counter<=23;hour_counter+=1){
            // Loop will continue until it has reached the minute value of 59
            for(minute_counter=-0;minute_counter<=59;minute_counter+=1){
                // Loop will continue until it has reached the second value of 59
                for(second_counter=0;second_counter<=59;second_counter+=1){
                    // For hour display
                    hour_digit1 = hour_counter/10;
                    hour_digit2 = hour_counter%10;
                    
                    // For minute display
                    minute_digit1 = minute_counter/10;
                    minute_digit2 = minute_counter%10;
                    
                    // For second display
                    second_digit1 = second_counter/10;
                    second_digit2 = second_counter%10;
                    
                    // Put all digits into a string
                    sprintf(time_string,"%d%d:%d%d:%d%d",hour_digit1,hour_digit2
                                                        ,minute_digit1,minute_digit2
                                                        ,second_digit1, second_digit2);
                    // Display
                    LCDPutStr2(time_string, 4, 1);
                    __delay_ms(50);
                }
            }
        }
        hour_counter   = 0;
        minute_counter = 0;
        second_counter = 0;
    }
    return;
}