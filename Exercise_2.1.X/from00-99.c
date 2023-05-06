#define _XTAL_FREQ 1000000
// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection Bits (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select (MCLR/VPP pin function is digital input)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover Mode (Internal/External Switchover Mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config STVREN = OFF     // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will not cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF      // Low-Power Brown Out Reset (Low-Power BOR is disabled)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)

#include<xc.h>

// This program is written by Nguyen Hai Dang - ID:20146110
void number_state() {
    // This function is designed for the counting states of the last digit
    // Pins are used from RC0 to RC6
    LATC = 0b0111111;   // The last digit is "0"
        __delay_ms (200);
    LATC = 0b0000110;   // The last digit is "1"
        __delay_ms (200);
    LATC = 0b1011011;   // The last digit is "2"
        __delay_ms (200);
    LATC = 0b1001111;   // The last digit is "3"
        __delay_ms (200);
    LATC = 0b1100110;   // The last digit is "4"
        __delay_ms (200);
    LATC = 0b1101101;   // The last digit is "5"
        __delay_ms (200);
    LATC = 0b1111101;   // The last digit is "6"
        __delay_ms (200);
    LATC = 0b0000111;   // The last digit is "7"
        __delay_ms (200);
    LATC = 0b1111111;   // The last digit is "8"
        __delay_ms (200);
    LATC = 0b1101111;   // The last digit is "9"
        __delay_ms (200);
    return;
}

void main(void) {
    // Initializing pins
    TRISC = 0; // "0" means output mode
    TRISA = 0;
    TRISB = 0;
    
    ANSELC = 0; // "0" means deselecting analog mode
    ANSELB = 0;
    ANSELA = 0;
    
    // Counter operation
while(1) {
    /* Pin-LED relations: RA2-a, RA4-b, RA5-c
                          RB4-d, RB5-e, RB6-f, RB7-g */
    // 00 to 09
    LATA = 0b00110100;
    LATB = 0b01110000;
    number_state();
    
    // 10 to 19
    LATA = 0b00110000;
    LATB = 0b00000000;
    number_state();
    
    // 20 to 29
    LATA = 0b00010100;
    LATB = 0b10110000;
    number_state();
    
    // 30 to 39
    LATA = 0b00110100;
    LATB = 0b10010000;
    number_state();
    
    // 40 to 49
    LATA = 0b00110000;
    LATB = 0b11000000;
    number_state();
    
    // 50 to 59
    LATA = 0b00100100;
    LATB = 0b11010000;
    number_state();
    
    // 60 to 69
    LATA = 0b00100100;
    LATB = 0b11110000;
    number_state();
    
    // 70 to 79
    LATA = 0b00110100;
    LATB = 0b00000000;
    number_state();
    
    // 80 to 89
    LATA = 0b00110100;
    LATB = 0b11110000;
    number_state();
    
    // 90 to 99
    LATA = 0b00110100;
    LATB = 0b11010000;
    number_state();   
}
    return;
}
