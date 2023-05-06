/*
 * File:   blinking.c
 * Author: Admin
 *
 * Created on February 24, 2022, 6:20 PM
 */
// PIC16F1823 Configuration Bit Settings
// 'C' source line config statements
#define _XTAL_FREQ 1000000
// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select (MCLR/VPP pin function is digital input)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = OFF      // PLL Enable (4x PLL disabled)
#pragma config STVREN = OFF     // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will not cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

void main(void) {
    TRISCbits.TRISC0 = 0 ;  // "0" means output mode
    TRISCbits.TRISC1 = 0 ;
    TRISCbits.TRISC2 = 0 ;
    
    ANSELA = 0x00;
    ANSELC = 0x00;
    
    while(1){
        LATCbits.LATC0 = 1; // "1" means HIGH state
        LATCbits.LATC1 = 0;
        LATCbits.LATC2 = 0;
        __delay_ms (500);
        
        LATCbits.LATC0 = 0; // "1" means HIGH state
        LATCbits.LATC1 = 1;
        LATCbits.LATC2 = 0;
        __delay_ms (500);
        
        LATCbits.LATC0 = 0; // "1" means HIGH state
        LATCbits.LATC1 = 0;
        LATCbits.LATC2 = 1;
        __delay_ms (500);
 
    }
    
    
    return;
}
