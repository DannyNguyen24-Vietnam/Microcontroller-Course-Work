/*
 * File:   LEDbar16.c
 * Author: NGUYEN HAI DANG
 * Field of Study: Mechatronics Engineering
 * Created on March 24, 2022, 10:08 PM
 */
// CONFIG
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define _XTAL_FREQ 1000000
#include <xc.h>

void main(void) {
    TRISB = 0; //Set all ports B to "Output" mode 
    TRISC = 0; //Set all ports C to "Output" mode
    TRISD = 0; //Set all ports D to "Output" mode
    PORTB = 0; // All LEDs must be off
    PORTC = 0; // All LEDs must be off
    PORTD = 0; // All LEDs must be off
    unsigned char bar_2_state = 0b00000000; //LED bar lighting state connected to PORTB
    unsigned char bar_1_state = 0b00000000; //LED bar lighting state connected to PORTC
    unsigned char bar_3_state = 0b00000000; //LED bar lighting state connected to PORTD
    int n_3=7; // Counter for LEDs connected to PORTD
    int n_2=8; // Counter for LEDs connected to PORTB
    int n_1=4; // Counter for LEDs connected to PORTC
    unsigned char i=0; // "i" is used for loops
    int mask_2 = 0b00000001; // The mask "mask_2" represents for the sliding motion of LEDs connected to Port B
    int mask_1 = 0b00000001; // The mask "mask_1" represents for the sliding motion of LEDs connected to Port C
    int mask_3 = 0b00000001; // The mask "mask_3" represents for the sliding motion of LEDs connected to Port D
    
    // The working of LEDs bar will re-run after all bits in each "bar_x_state" are filled with bit 1
    while(1){      
        while((bar_3_state!=0b11111111)||(bar_2_state!=0b11111111)||(bar_1_state!=0b00011111)){
            // Condition used  to update "n_2" 
            if (n_3==-1&&n_2>0)
                n_2-=1;
            // Condition used  to update "n_1"
            if(n_2==-1)
                n_1-=1;
    // LEDs connected to Port C      
           /* The re-updating of "i" and "mask_x" is for the sliding motion of LEDs on every new LED's stacking */
            /* Below condition makes sure the re-updating of "i" and "mask_1" only work when
               the "bar_1_state" hasn't been fully filled up with bit 1 */
            if(bar_1_state!=0b00001111){
                i=0;
                mask_1 = 0b00000001;
            }
        // Sliding motion of LEDs connected to Port C
            while(i<n_1){
                PORTC =  bar_1_state|mask_1;
                __delay_ms(100);
                mask_1 = mask_1<<1;
                i+=1;
            }
        // Displaying when bar_1_state is partially filled
            bar_1_state =  bar_1_state|mask_1;
            PORTC = bar_1_state;

    // LEDs connected to Port B     
            /* Below condition makes sure the re-updating of "i" and "mask_2" only work when
               the "bar_2_state" hasn't been fully filled up with bit 1 */
            if(bar_2_state!=0b11111111){
                i=0;
                mask_2 = 0b00000001;
            } else {mask_2 = 0b00000000;}
        // Sliding motion of LEDs connected to Port B
            while(i<n_2){
                PORTB =  bar_2_state|mask_2;
                __delay_ms(100);
                mask_2 = mask_2<<1;
                i+=1;
            }
        // When n_2=0, the previous loop doesn't work, so it will lost the last LED's state
            if(n_2==0){
                PORTB =  bar_2_state|mask_2;
                __delay_ms(100);
                n_2-=1;
            }
            // Displaying when bar_2_state is partially filled
            bar_2_state =  bar_2_state|mask_2;
            PORTB = bar_2_state;

    // LEDs connected to Port D
            /* Below condition makes sure the re-updating of "i" and "mask_3" only work when
               the "bar_3_state" hasn't been fully filled up with bit 1 */
            if (bar_3_state!=0b11111111){
                i=0;        
                mask_3 = 0b00000001;
            } else {
                mask_3 = 0b00000000;
            }
        // Sliding motion of LEDs connected to Port D
            while(i<n_3&&n_3>0){
                PORTD =  bar_3_state|mask_3;
                __delay_ms(100);
                mask_3 = mask_3<<1;     
                i+=1;
            }
            // When n_3=0, the previous loop doesn't work, so it will lost the last LED's state
            if(n_3==0){
                PORTD =  bar_3_state|mask_3;
                __delay_ms(100);
                n_3-=1;
            }
            // Displaying when bar_3_state is partially filled
            bar_3_state = bar_3_state|mask_3;
            PORTD =  bar_3_state;
            if(n_3>0)
                n_3-=1;
        }
        __delay_ms(200); 
        PORTB = 0;
        PORTC = 0;
        PORTD = 0;
        // Re-Initialize
            // Masks resetting
        mask_1 = 0b00000001;
        mask_2 = 0b00000001;
        mask_3 = 0b00000001;
            // Counter resetting
        n_3=7;
        n_2=8;
        n_1=4;
            // Bars state resetting
        bar_1_state = 0b00000000;
        bar_2_state = 0b00000000;
        bar_3_state = 0b00000000;
    }
    return;
}