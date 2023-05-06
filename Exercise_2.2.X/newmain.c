#define _XTAL_FREQ 1000000
// PIC16F886 Configuration Bit Settings
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// This program is written by Nguyen Hai Dang - ID: 20146110
#include <xc.h>

void num_state_0to9(){
    // This function is used for the counting states of the last second digit
    /* Pins are used from RC0 to RC6 relating to from "a" to "g", 
       Managing the __delay_ms () function will make the clock more accurate */  
    PORTC = 0b00111111; // The last second digit is "0"
        __delay_ms (90);
    PORTC = 0b00000110; // The last second digit is "1"
        __delay_ms (90);
    PORTC = 0b01011011; // The last second digit is "2"
        __delay_ms (90);
    PORTC = 0b01001111; // The last second digit is "3"
        __delay_ms (90);
    PORTC = 0b01100110; // The last second digit is "4"
        __delay_ms (90);
    PORTC = 0b01101101; // The last second digit is "5"
        __delay_ms (90);
    PORTC = 0b01111101; // The last second digit is "6"
        __delay_ms (90);
    PORTC = 0b00000111; // The last second digit is "7"
        __delay_ms (90);
    PORTC = 0b01111111; // The last second digit is "8"
        __delay_ms (90);
    PORTC = 0b01101111; // The last second digit is "9"
        __delay_ms (90);
        return;
}
void num_state_00to59(){
    // This function is used for the counting states of the second
    /* How it works: Hold the first digit of the second until
       the last digit counting has reached 9 */
    /* Pins are used from RB0 to RB6 relating to from "a" to "g" */
    // 00 to 09th second
    PORTB = 0b00111111;
    num_state_0to9();
    // 10 to 19th second
    PORTB = 0b00000110;
    num_state_0to9();
    // 20 to 29th second
    PORTB = 0b01011011;
    num_state_0to9();
    // 30 to 39th second
    PORTB = 0b01001111;
    num_state_0to9();
    // 40 to 49th second
    PORTB = 0b01100110;
    num_state_0to9();
    // 50 to 59th second
    PORTB = 0b01101101;
    num_state_0to9();
    return;
}
void main(void) {
    int minute_var = 0; // Minute tracking value
    int digit_1 = 0, digit_2 = 0; // Displaying digits of the minute
    
    // Setting up pins
    TRISA = 0; // 0 means output mode
    TRISB = 0;
    TRISC = 0;
    ANSEL = 0; // Deselecting the Analog mode
    
    // Initial states: "00:00"
    PORTA = 0b00000000;
    PORTB = 0b00111111;
    PORTC = 0b00111111;
    
    // Clock operation
    while(1){
        while(minute_var<=59){
            /* How it works: A minute will count after the second has reached 59 */
            num_state_00to59();            
            minute_var+=1; // Updating for the next stage
            
            // Breaking the 60th minute
            if (minute_var == 60){
                break;
            }
                              
            // Separating digits from the minuting tracking value
            digit_1 = (minute_var-minute_var%10)/10;
            digit_2 = minute_var%10;
            
            // Lighting up LED after defining digits of the minute
            /* How it works: Using the 7 segments LED having the BCD to 7 segments
                             decoder IC in it which minimizes the need of pins*/
            // The first digit of the minute: RA0 to RA3
            switch(digit_1){
                case 0: RA0=0; RA1=0; RA2=0; RA3=0; break; // BCD: 0000 = DEC: 0
                case 1: RA0=0; RA1=0; RA2=0; RA3=1; break; // BCD: 0001 = DEC: 1
                case 2: RA0=0; RA1=0; RA2=1; RA3=0; break; // BCD: 0010 = DEC: 2
                case 3: RA0=0; RA1=0; RA2=1; RA3=1; break; // BCD: 0011 = DEC: 3
                case 4: RA0=0; RA1=1; RA2=0; RA3=0; break; // BCD: 0100 = DEC: 4
                case 5: RA0=0; RA1=1; RA2=0; RA3=1; break; // BCD: 0101 = DEC: 5
                case 6: RA0=0; RA1=1; RA2=1; RA3=0; break; // BCD: 0110 = DEC: 6
                case 7: RA0=0; RA1=1; RA2=1; RA3=1; break; // BCD: 0111 = DEC: 7
                case 8: RA0=1; RA1=0; RA2=0; RA3=0; break; // BCD: 1000 = DEC: 8
                default: RA0=1; RA1=0; RA2=0; RA3=1;       // BCD: 1001 = DEC: 9          
            }
            // The last digit of the minute: RA4 to RA7 (the same properties as digit_1)
            switch(digit_2){
                case 0: RA4=0; RA5=0; RA6=0; RA7=0; break;
                case 1: RA4=0; RA5=0; RA6=0; RA7=1; break;
                case 2: RA4=0; RA5=0; RA6=1; RA7=0; break;
                case 3: RA4=0; RA5=0; RA6=1; RA7=1; break;
                case 4: RA4=0; RA5=1; RA6=0; RA7=0; break;
                case 5: RA4=0; RA5=1; RA6=0; RA7=1; break;
                case 6: RA4=0; RA5=1; RA6=1; RA7=0; break;
                case 7: RA4=0; RA5=1; RA6=1; RA7=1; break;
                case 8: RA4=1; RA5=0; RA6=0; RA7=0; break;
                default: RA4=1; RA5=0; RA6=0; RA7=1;
            }
        }
    // Re-update before another loop starts
    minute_var = 0;
    PORTA = 0b00000000;
    PORTB = 0b00111111;
    PORTC = 0b00111111;
    }
    return;
}


