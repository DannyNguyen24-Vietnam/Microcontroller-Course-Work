/*
 * File:   baitap3.c
 * Author: Admin
 *
 * Created on August 29, 2022, 10:42 AM
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
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#define _XTAL_FREQ 1000000
#include <xc.h>
#include <stdio.h>

int counter = 0;
char Com_Cathode[10] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111};

void main(void) {
    // Initialize
        // Oscillation
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 0;
    OSCCONbits.IRCF0 = 0;  
    OSCCONbits.SCS   = 1;
    
        // Port
    TRISC = 0;  // Output on port C
    ANSEL = ANSELH = 0;
    TRISBbits.TRISB1 = 1;   // Input on RB1 pin
    TRISBbits.TRISB2 = 1;   // Input on RB2 pin
    
    PORTC = 0;
    
    IOCBbits.IOCB1  = 1;
    IOCBbits.IOCB2  = 1;
    INTCONbits.RBIE = 1;   // Enable Interrupt on change
    INTCONbits.RBIF = 0;   // Clear Interrupt flag
    INTCONbits.GIE  = 1;   // Enable Global Interrupt
    
    while(1){
        if(counter>9||counter<0){
            counter = 0;
            
        }
        else{
            PORTC = Com_Cathode[counter];
     
        }    
    }
    return;
}

void __interrupt() ISR(void){
    __delay_ms(80);
    
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