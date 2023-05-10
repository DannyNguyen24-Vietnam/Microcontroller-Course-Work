/*
 * File:   baitap1.c
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
#include "lcd.h"
#include <stdio.h>
#include <stdlib.h>

int ADC_val    = 0;
float result_out = 0;
float temp_value = 0;
char numstr[30];

void main(void) {
    // Initialize
        // Oscillation
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 0;
    OSCCONbits.SCS   = 1;
    
        // LCD
    LCD_Initialize();
    
        // Ports
    TRISAbits.TRISA1 = 1;   // Input
    ANSELbits.ANS1   = 1;   // Analog use on pin RA1
    
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
    
        // Display title
    LCDGoto(0,0);
    LCDPutStr("Gia tri bien tro:");
    
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
        
        //if(temp_value != result_out){
            //LCDGoto(5,1);
            //LCDPutStr("             ");
            
            sprintf(numstr, "%3.2f", result_out);
            LCDGoto(5,1);
            LCDPutStr(numstr);
            
            temp_value = result_out;
        //}

        ADCON0bits.GO_DONE=1;
 
    }
    
    return;
}
