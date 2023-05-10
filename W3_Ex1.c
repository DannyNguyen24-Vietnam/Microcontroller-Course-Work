/*
 * File:   baitap1.c
 * Author: Admin
 *
 * Created on September 5, 2022, 8:49 AM
 */

// PIC16F887 Configuration Bit Settings
// 'C' source line config statements
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#define _XTAL_FREQ 4000000
#include <xc.h>
#include <stdio.h>
#include "lcd.h"
#include <stdlib.h>

// Note that: This code you are running is for the exercise 2 using two buttons, one for
// increment and the other for decrement. You must uncomment necessary stuff for the exercise 1
// which uses only one button and implements the external interrupt of RB0

int counter    = 0;
int temp_value = 0;
char numstr[30];

void main(void) {
    
    // Intialize
        // Oscillation
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 0;
    OSCCONbits.SCS   = 1;

        // LCD
    LCD_Initialize();
    
        // Interrupt
    //INTCONbits.INTE = 1;    // Ex-Interrupt Enable
    //INTCONbits.INTF = 0;    // Clear Interrupt flag
    IOCBbits.IOCB1  = 1;
    IOCBbits.IOCB2  = 1;
    INTCONbits.RBIE = 1;    // Interrup On Change Enable
    INTCONbits.RBIF = 0;    // Clear Interrup On Change Flag
    INTCONbits.GIE  = 1;    // Enable Global Interrupt
    //OPTION_REGbits.INTEDG = 0;   // LOW Trigger Edge
    
        // Display title
    LCDGoto(0,0);
    LCDPutStr("Gia tri hien tai la:");
    
    while(1){
        if(counter>9||counter<0){
            counter = 0;
            
        }
        
        // Display value
        if(temp_value != counter){
            LCDGoto(0,1);
            LCDPutStr("             ");  // Clear old value
            
            sprintf(numstr, "%01d", counter);
            LCDGoto(0,1);
            LCDPutStr(numstr);
            
            temp_value = counter;   // Update temp value
        
        }
        else{
            continue;
            
        }
    }
    
    return;
}

void __interrupt() ISR(void){
//    if(INTCONbits.INTF == 1){
//        __delay_ms(90);
//        counter += 1;
//        
//        INTCONbits.INTF = 0;    // Clear Interrupt Flag
//
//    }
    
    if(INTCONbits.RBIF == 1){
        if(PORTBbits.RB1 != 1){
            counter++;
            
        }
        if(PORTBbits.RB2 != 1){
            counter--;
            
        }
    
        INTCONbits.RBIF = 0;
    }
}
