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
#pragma config LVP = ON         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

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
unsigned int counter0 = 0;
unsigned int freq = 0;
unsigned int temp_freq = 0;

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
    T1CONbits.TMR1CS  = 1;
    T1CONbits.T1CKPS  = 0b00;    // PSA: 1:1
    T1CONbits.TMR1GE  = 0;
    T1CONbits.T1SYNC  = 1;
    CM2CON1bits.T1GSS = 1;
    T1CONbits.TMR1ON  = 1;       // Turn on Timer 1
    
        // Timer 0
    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.PSA  = 0;
    OPTION_REGbits.PS2  = 1;
    OPTION_REGbits.PS1  = 0;
    OPTION_REGbits.PS0  = 1;
    TMR0 = 0;
    
        // Interrrupt
    INTCONbits.T0IE = 1;    // TMR0 Interr. Enable
    INTCONbits.T0IF = 0;    // Clear Flag
    INTCONbits.PEIE = 0;    // Peripheral Interrupt Enable
    INTCONbits.GIE  = 1;    // Global Interrupt Enable
    
        // Ports
    ANSELHbits.ANS13 = 0;
    TRISCbits.TRISC0 = 1;   // Input mode
    
    while(1){
        
        if(temp_freq != freq){
            
            sprintf(str, "Freq: %02d     ", freq);
            LCDGoto(0, 0);
            LCDPutStr(str);
            temp_freq = freq;
        }
        else{
            
            sprintf(str, "Freq: ");
            LCDGoto(0, 0);
            LCDPutStr(str);
        }
    }
    
    return;
}

void __interrupt() ISR(void){
    
    if(INTCONbits.T0IF == 1){
        counter0 += 1;
        
        if(counter0 == 61){
            
            counter0 = 0;
            freq = (TMR1H*256 + TMR1L)/1;
            TMR1H = 0;
            TMR1L = 0;
        }
        
        INTCONbits.T0IF = 0;    // Clear Flag
    }
    
}
