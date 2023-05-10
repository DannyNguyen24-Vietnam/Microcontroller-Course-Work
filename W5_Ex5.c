/*
 * File:   baitap5.c
 * Author: Admin
 *
 * Created on September 19, 2022, 9:58 PM
 */
// PIC16F887 Configuration Bit Settings
// 'C' source line config statements
// CONFIG1
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
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
#define _XTAL_FREQ 20000000
#include <xc.h>
#include "lcd.h"
#include <stdlib.h>
#include <stdio.h>

char str1[40];
char str2[50];

unsigned int hour_count = 0;
unsigned int min_count  = 0;
unsigned int sec_count  = 0;
unsigned int hour_str   = 0;
unsigned int min_str    = 0;
unsigned int sec_str    = 0;
unsigned int counter    = 0;

void stopMode(){
    
    sprintf(str2, "%02d : %02d : %02d", hour_str, min_str, sec_str);
    LCDGoto(2,1);
    LCDPutStr(str2);
}

void main(void) {
    
    // Initialize
        // Oscillation
    OSCCONbits.SCS = 0;
    
        // LCD
    LCD_Initialize();
    
        // Timer 2
    T2CONbits.T2CKPS1 = 1;
    T2CONbits.T2CKPS0 = 0;
    T2CONbits.TMR2ON  = 0;  // Turn OFF Timer 2
    PR2 = 250;
    
        // Ports
    ANSELHbits.ANS10 = 0;
    ANSELHbits.ANS9  = 0;
    ANSELHbits.ANS8  = 0;
    TRISBbits.TRISB1 = 1;   // Input
    TRISBbits.TRISB2 = 1;
    TRISBbits.TRISB3 = 1;
    
    OPTION_REGbits.nRBPU = 0;
    WPUBbits.WPUB1 = 1;
    WPUBbits.WPUB2 = 1;
    WPUBbits.WPUB3 = 1;
    
        // Interrupt
    // Timer 2
    PIR1bits.TMR2IF = 0;    // Clear flag
    PIE1bits.TMR2IE = 1;
    INTCONbits.PEIE = 1;
    
    // Interrupt on Change
    IOCBbits.IOCB1 = 1;
    IOCBbits.IOCB2 = 1;
    IOCBbits.IOCB3 = 1;
    INTCONbits.RBIF = 0;    // Clear Flag
    INTCONbits.RBIE = 1;
    
    INTCONbits.GIE = 1;     // Global Interrupt Enable
    
    while(1){
        
        stopMode();
        
        // Time calculate
        if(sec_count == 60){
            
            min_count += 1;
            sec_count =  0;
        }
        
        if(min_count == 60){
            
            hour_count += 1;
            min_count =  0;
        }
        
        // Display
        sprintf(str1, "%02d : %02d : %02d", hour_count, min_count, sec_count);
        LCDGoto(2,0);
        LCDPutStr(str1);
    }
    
    return;
}

void __interrupt() ISR(void){
    
    if(INTCONbits.RBIF == 1){
        
        // Start
        if(PORTBbits.RB1 == 0){
            
            TMR2 = 0;
            T2CONbits.TMR2ON = 1;   // Start Counting
        }
        
        // Stop
        if(PORTBbits.RB2 == 0){
            
            hour_str = hour_count;
            min_str  = min_count;
            sec_str  = sec_count;
        }
        
        // Reset and Stop
        if(PORTBbits.RB3 == 0){
            
            // Store elasped time
            hour_str = hour_count;
            min_str  = min_count;
            sec_str  = sec_count;
            
            hour_count = 0;
            min_count  = 0;
            sec_count  = 0;
            
            counter = 0;
            
            T2CONbits.TMR2ON = 0;   // Turn OFF Timer 2 
            
        }
        INTCONbits.RBIF = 0;    // Clear Flag
    }
    
    if(PIR1bits.TMR2IF == 1){
        
        counter += 1;
        
        if(counter == 1250){
            
            sec_count += 1;
            counter = 0;
        }
        
        PIR1bits.TMR2IF = 0;    // Clear Flag
    }
}
