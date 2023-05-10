/*
 * File:   baitap2.c
 * Author: Admin
 *
 * Created on August 29, 2022, 9:12 AM
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

#define _XTAL_FREQ 1000000
#include <xc.h>
#include <stdio.h>

int counter = 0;
int digit1  = 0;
int digit2  = 0;
int digit3  = 0;

char Com_Cathode[10] = {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 
                        0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111};

void LEDdisplay(int dig1, int dig2, int dig3){
    // Led 1 
    PORTC = Com_Cathode[dig1];
    PORTDbits.RD0 = 0; PORTDbits.RD1 = 1; PORTDbits.RD2 = 1;
    __delay_ms(60);
    
    // Led 2
    PORTC = Com_Cathode[dig2];
    PORTDbits.RD1 = 0; PORTDbits.RD0 = 1; PORTDbits.RD2 = 1;
    __delay_ms(60);
    
    // Led 3
    PORTC = Com_Cathode[dig3];
    PORTDbits.RD2 = 0; PORTDbits.RD0 = 1; PORTDbits.RD1 = 1;
    __delay_ms(60);
    
    return;    
}

void main(void) {
    // Initialize
        // Oscillation
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 0;
    OSCCONbits.IRCF0 = 0;
    OSCCONbits.SCS   = 1;
    
        // Port
    TRISBbits.TRISB0 = 1;   // Input on RB0 pin
    TRISDbits.TRISD0 = 0;   // Output on RD0 pin
    TRISDbits.TRISD1 = 0;   // Output on RD1 pin
    TRISDbits.TRISD2 = 0;   // Output on RD2 pin
    ANSEL = ANSELH = 0;
    TRISC = 0;              // Output on Port C
    
    PORTC = 0;
    PORTD = 1;
    
        // Interrupt
    INTCONbits.INTE = 1;    // Enable Ex-Interrupt
    INTCONbits.INTF = 0;    // Clear Interrupt Flag
    INTCONbits.GIE  = 1;    // Enable Global Interrupt
    
    OPTION_REGbits.INTEDG = 0;  // Falling-Edge Interrupt
    
    while(1){
        if(counter>999){
            // Re-update
            counter = 0;
            
            digit1 = 0;
            digit2 = 0;
            digit3 = 0;

        }
        else{
            digit1 = counter/100;
            digit2 = (counter/10)%10;
            digit3 = counter%10;
            
            LEDdisplay(digit1, digit2, digit3);
            
        }
    }
    
    return;
}

void __interrupt() ISR(void){
    __delay_ms(80);     // Debounce
    
    if(INTCONbits.INTF == 1){
        counter += 1;
        INTCONbits.INTF = 0;
        
    }
       
}
