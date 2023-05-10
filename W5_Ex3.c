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
#include <stdlib.h>
#include <stdio.h>

char str[50];
int count = 0;

void main(void) {
    
    // Initialize
        // Oscillation
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 0;
    OSCCONbits.SCS   = 1;
    
        // Timer 1
    T1CONbits.TMR1CS = 0;
    T1CONbits.TMR1GE = 0;
    T1CONbits.T1INSYNC = 1;
    T1CONbits.T1CKPS = 0b01;    // PSA: 1:1
    T1CONbits.TMR1ON = 1;       // Turn ON Timer 1
    TMR1H = 254;
    TMR1L = 112;
    
        // Interrrupt
    PIE1bits.TMR1IE = 1;    // Enable TMR1 Interrupt
    PIR1bits.TMR1IF = 0;    // Clear Flag
    INTCONbits.PEIE = 1;    // Peripheral Interrupt Enable
    INTCONbits.GIE  = 1;    // Global Interrupt Enable
    
        // Ports
    TRISDbits.TRISD0 = 0;   // Output mode
    PORTDbits.RD0    = 1;
    
    while(1){
    }
    
    return;
}

void __interrupt() ISR(void){
    
    if(PIR1bits.TMR1IF == 1){
        
        count += 1;
        
        if(count == 50){
            
            PORTDbits.RD0 = ~PORTDbits.RD0;
        }
        
        if(count == 250){
            
            PORTDbits.RD0 = ~PORTDbits.RD0;
            count = 0;
        }
        
        TMR1H = 254;
        TMR1L = 112;
        
        PIR1bits.TMR1IF = 0;
    }
    
}
