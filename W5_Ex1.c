/*
 * File:   baitap1.c
 * Author: Admin
 *
 * Created on September 19, 2022, 7:33 AM
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
#pragma config LVP = OFF         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#define _XTAL_FREQ 4000000
#include <xc.h>
#include "lcd.h"
#include <stdlib.h>
#include <stdio.h>

char str[50];
char str1[50];
int sec_count  = 0;
int min_count  = 0;
int hour_count = 0;
int sec_str  = 0;
int min_str  = 0;
int hour_str = 0;
int count_str = 0;
int counter    = 0;
char state = 0;

void stopMode(){
    
    sprintf(str1, "%02d : %02d : %02d", hour_str, min_str, sec_str);
    LCDGoto(2, 1);
    LCDPutStr(str1);
    
    return;
}
void main(void) {
    
    // Initialize
        // Oscillation
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 0;
    OSCCONbits.SCS   = 1;
    
        // LCD
    LCD_Initialize();
    
        // Timer 1
    T1CONbits.TMR1CS = 0;
    T1CONbits.T1CKPS = 0b00;    // PSA: 1:1
    T1CONbits.TMR1GE = 0;
    T1CONbits.TMR1ON = 0;       // Turn on Timer 1
    
        // Interrrupt
    PIR1bits.TMR1IF = 0;    // Clear Flag
    PIE1bits.TMR1IE = 1;    // Enable TMR1 InterrupT
    IOCBbits.IOCB1  = 1;
    IOCBbits.IOCB2  = 1;
    IOCBbits.IOCB4  = 1;
    INTCONbits.RBIF = 0;
    INTCONbits.RBIE = 1;
    INTCONbits.PEIE = 1;    // Peripheral Interrupt Enable
    INTCONbits.GIE  = 1;    // Global Interrupt Enable
    
        // Ports
    OPTION_REGbits.nRBPU = 0;
    ANSELHbits.ANS10 = 0;
    TRISBbits.TRISB1 = 1;   // Input
    WPUBbits.WPUB1   = 1;   // Weak Pull-up Enable
    
    ANSELHbits.ANS8  = 0;
    TRISBbits.TRISB2 = 1;   // Input
    WPUBbits.WPUB2   = 1;   // Weak Pull-up Enable
    
    ANSELHbits.ANS11  = 0;
    TRISBbits.TRISB4 = 1;   // Input
    WPUBbits.WPUB4   = 1;   // Weak Pull-up Enable
    
    while(1){
        
            stopMode();
            
            if(sec_count == 60){

                min_count += 1;
                sec_count = 0;
            }

            if(min_count == 60){

                hour_count += 1;
                min_count = 0;
            }

            sprintf(str, "%02d : %02d : %02d", hour_count, min_count, sec_count);
            LCDGoto(2, 0);
            LCDPutStr(str);
    }
    
    return;
}

void __interrupt() ISR(void){
    
    if(PIR1bits.TMR1IF == 1){
        counter += 1;
        
        if(counter == 20){
            
            sec_count += 1;
            counter = 0;    // Re-update
        }
        
        TMR1H = 60;
        TMR1L = 175;
        PIR1bits.TMR1IF = 0;    // Clear Flag
    }
    
    if(INTCONbits.RBIF == 1){
        
        // Reset
        if(PORTBbits.RB1 == 0){
            
            T1CONbits.TMR1ON = 0;       // Turn off Timer 1
            counter    = 0;
            sec_count  = 0;
            min_count  = 0;
            hour_count = 0;

        }
        
        // Start
        if(PORTBbits.RB2 == 0){
            
            T1CONbits.TMR1ON = 1;       // Turn on Timer 1
            
            TMR1H = 60;
            TMR1L = 175;
        }
        
        // Stop
        if(PORTBbits.RB4 == 0){
             
            sec_str  = sec_count;
            min_str  = min_count;
            hour_str = hour_count;
        }
        
        INTCONbits.RBIF = 0;
    }
    
}
