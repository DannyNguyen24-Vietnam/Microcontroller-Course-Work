/*
 * File:   baitap4.c
 * Author: Admin
 *
 * Created on September 19, 2022, 11:23 AM
 */
// PIC16F887 Configuration Bit Settings
// 'C' source line config statements
// CONFIG1
#pragma config FOSC = HS
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
#include <stdio.h>

int counter = 0;

void main(void) {
    
    // Initialize
        // Oscillation
    OSCCONbits.SCS = 0;
    
        // Ports
    TRISDbits.TRISD1 = 0;   // Output mode
    PORTDbits.RD1    = 0;
    
        // Timer 2
    T2CONbits.T2CKPS1 = 1;
    T2CONbits.T2CKPS0 = 1;
    T2CONbits.TMR2ON  = 1;  // Turn on Timer 2
    TMR2 = 0;
    PR2  = 250;
    
        // Interrupt
    PIR1bits.TMR2IF = 0;    // Clear Flag
    PIE1bits.TMR2IE = 1;    // Enable Timer 2 Interrupt
    INTCONbits.PEIE = 1;    // Peripheral Interrupt Enable
    INTCONbits.GIE  = 1;    // Global Interrupt Enable
            
    while(1){
        
    }
    
    return;
}

void __interrupt() ISR(void){
    
    if(PIR1bits.TMR2IF == 1){
        
        counter += 1;
        
        if(counter == 87){
            
            PORTDbits.RD1 = ~PORTDbits.RD1;
        }
        
        if(counter == 125){
            
            PORTDbits.RD1 = ~PORTDbits.RD1;
            counter = 0;
        }
        
        //TMR2 = 0;
    }
    
    PIR1bits.TMR2IF = 0;    // Clear Flag
}
