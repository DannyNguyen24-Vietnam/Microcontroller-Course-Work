/*
 * File:   baitap2.c
 * Author: Admin
 *
 * Created on September 12, 2022, 7:26 AM
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
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>


int   ADC_val    = 0;
float result_out = 0;
float temp_value = 0;
int   digit1 = 0;
int   digit2 = 0;
char  numstr[30];

char Com_Cathode[10] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 
                        0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111};

void LEDdisplay(int dig1, int dig2){
    // Led 1 
    PORTC = Com_Cathode[dig1];
    PORTDbits.RD0 = 0; PORTDbits.RD1 = 1;
    __delay_ms(60);
    
    // Led 2
    PORTC = Com_Cathode[dig2];
    PORTDbits.RD1 = 0; PORTDbits.RD0 = 1;
    __delay_ms(60);
    
    return;    
}


void main(void) {
    // Initialize
        // Oscillation
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 0;
    OSCCONbits.SCS   = 1;
    
        // Ports
    TRISAbits.TRISA1 = 1;   // Input
    ANSELbits.ANS1   = 1;   // Analog use on pin RA1
    TRISC            = 0;   // Output
    TRISDbits.TRISD0 = 0;   // Output on RD0 pin
    TRISDbits.TRISD1 = 0;   // Output on RD1 pin

        // ADC Converter
    ADCON0bits.ADCS1 = 1;
    ADCON0bits.ADCS0 = 0;
    ADCON1bits.VCFG0 = 0;   // Internal Vdd Reference
    ADCON1bits.VCFG1 = 0;   // Vss = GND
    ADCON0bits.CHS3  = 0;
    ADCON0bits.CHS2  = 0;
    ADCON0bits.CHS1  = 0;
    ADCON0bits.CHS0  = 1;
    ADCON1bits.ADFM  = 1;   // Right Justified Result
    ADCON0bits.ADON  = 1;   // Enable ADC module
 
    ADCON0bits.GO_DONE = 1; // Start Converting
    
    while(1){
        // Wait for calculation
        __delay_ms(5);
     
		while(ADCON0bits.GO_DONE==1){
            // Wait
            
        }
        
        // Read Data value
        ADC_val     = ADRESH*256 + ADRESL;	
        result_out  = (float)(ADC_val/1023.0)*5.0;
        
        digit1 = result_out;
        digit2 = (result_out - (int)result_out)*10;
        
        LEDdisplay(digit1, digit2);

        ADCON0bits.GO_DONE=1;
 
    }
    return;
}
