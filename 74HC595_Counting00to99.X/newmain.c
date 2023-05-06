/*
 * Author: NGUYEN HAI DANG
 *
 * Created on March 7, 2022, 12:21 AM
 */
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
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

//-- My Idea --//
/* My idea is to create 10 function relating to 10 states from 0 to 9, a pulse generating function and a latching function*/
#include <xc.h>

// Pulse generator
void pulse_gen(int n){
    for(int i=0;i<=(n-1);i++){
        LATCbits.LATC0 = 0;     // Negative edge triggering
        LATCbits.LATC0 = 1;     // Positive edge triggering
    }
    return;
}
// Latching generator
void latch_gen(){
    LATCbits.LATC2 = 1;     // Positive edge triggering
    LATCbits.LATC2 = 0;     // Negative edge triggering
    return;
}
// A slight look before getting deeply in
/* Below functions will generate 7 pulse enough for 7 latches integrated in 74HC595
I use the common Anode 7-segment LEDs for the counter, so to light up a LED I must apply LOW voltage to the pin
Due to the working principle of the 74HC595 which is the first data comes in will be shifted to the last pin, so
input signals must stand in a sequence from "g" to "a" */

// Number states for both digits
// Pin RC1 on the 16F1509 is responsible for sending signals to the 74HC595
void state_0(){
    LATCbits.LATC1 = 1; pulse_gen(1);    
    LATCbits.LATC1 = 0; pulse_gen(6); return;
}
void state_1(){
    LATCbits.LATC1 = 1; pulse_gen(4);    
    LATCbits.LATC1 = 0; pulse_gen(2);    
    LATCbits.LATC1 = 1; pulse_gen(1); return;
}
void state_2(){
    LATCbits.LATC1 = 0; pulse_gen(1);    
    LATCbits.LATC1 = 1; pulse_gen(1);    
    LATCbits.LATC1 = 0; pulse_gen(2);    
    LATCbits.LATC1 = 1; pulse_gen(1);
    LATCbits.LATC1 = 0; pulse_gen(2); return;
}
void state_3(){
    LATCbits.LATC1 = 0; pulse_gen(1);    
    LATCbits.LATC1 = 1; pulse_gen(2);    
    LATCbits.LATC1 = 0; pulse_gen(4); return;    
}
void state_4(){
    LATCbits.LATC1 = 0; pulse_gen(2);    
    LATCbits.LATC1 = 1; pulse_gen(2);    
    LATCbits.LATC1 = 0; pulse_gen(2);    
    LATCbits.LATC1 = 1; pulse_gen(1); return;
}
void state_5(){
    LATCbits.LATC1 = 0; pulse_gen(2);    
    LATCbits.LATC1 = 1; pulse_gen(1);    
    LATCbits.LATC1 = 0; pulse_gen(2);    
    LATCbits.LATC1 = 1; pulse_gen(1);
    LATCbits.LATC1 = 0; pulse_gen(1); return;
}
void state_6(){
    LATCbits.LATC1 = 0; pulse_gen(5);    
    LATCbits.LATC1 = 1; pulse_gen(1);    
    LATCbits.LATC1 = 0; pulse_gen(1); return;
}
void state_7(){
    LATCbits.LATC1 = 1; pulse_gen(4);    
    LATCbits.LATC1 = 0; pulse_gen(3); return;   
}
void state_8(){
    LATCbits.LATC1 = 0; pulse_gen(7); return;
}
void state_9(){
    LATCbits.LATC1 = 0; pulse_gen(2);    
    LATCbits.LATC1 = 1; pulse_gen(1);    
    LATCbits.LATC1 = 0; pulse_gen(4); return;   
}
void main(void) {
    TRISC = 0; // "0" means output
    ANSELC = 0; // Deselect analog mode
    
    /* How it counts: 
    We can't hold the first digit and increase the second one until it has reached "9" since the shifting principles
    of the two 74HC595 ICs (I use two ICs). That is why we must send both digits for every count, even if the first digit
    hasn't changed its state yet*/
    while(1){
        // 00 to 09
        state_0(); pulse_gen(1); state_0(); latch_gen();__delay_ms(200); // Sending "00" and latching
        state_0(); pulse_gen(1); state_1(); latch_gen();__delay_ms(200); // Sending "01" and latching
        state_0(); pulse_gen(1); state_2(); latch_gen();__delay_ms(200); // Sending "02" and latching
        state_0(); pulse_gen(1); state_3(); latch_gen();__delay_ms(200); // Sending "03" and latching
        state_0(); pulse_gen(1); state_4(); latch_gen();__delay_ms(200); // Sending "04" and latching
        state_0(); pulse_gen(1); state_5(); latch_gen();__delay_ms(200); // Sending "05" and latching
        state_0(); pulse_gen(1); state_6(); latch_gen();__delay_ms(200); // Sending "06" and latching
        state_0(); pulse_gen(1); state_7(); latch_gen();__delay_ms(200); // Sending "07" and latching
        state_0(); pulse_gen(1); state_8(); latch_gen();__delay_ms(200); // Sending "08" and latching
        state_0(); pulse_gen(1); state_9(); latch_gen();__delay_ms(200); // Sending "09" and latching        
        // 10 to 19
        state_1(); pulse_gen(1); state_0(); latch_gen();__delay_ms(200); // Sending "1x" and latching
        state_1(); pulse_gen(1); state_1(); latch_gen();__delay_ms(200);
        state_1(); pulse_gen(1); state_2(); latch_gen();__delay_ms(200);
        state_1(); pulse_gen(1); state_3(); latch_gen();__delay_ms(200);
        state_1(); pulse_gen(1); state_4(); latch_gen();__delay_ms(200);
        state_1(); pulse_gen(1); state_5(); latch_gen();__delay_ms(200);
        state_1(); pulse_gen(1); state_6(); latch_gen();__delay_ms(200);
        state_1(); pulse_gen(1); state_7(); latch_gen();__delay_ms(200);
        state_1(); pulse_gen(1); state_8(); latch_gen();__delay_ms(200);
        state_1(); pulse_gen(1); state_9(); latch_gen();__delay_ms(200);       
        // 20 to 29
        state_2(); pulse_gen(1); state_0(); latch_gen();__delay_ms(200); // Sending "2x" and latching
        state_2(); pulse_gen(1); state_1(); latch_gen();__delay_ms(200);
        state_2(); pulse_gen(1); state_2(); latch_gen();__delay_ms(200);
        state_2(); pulse_gen(1); state_3(); latch_gen();__delay_ms(200);
        state_2(); pulse_gen(1); state_4(); latch_gen();__delay_ms(200);
        state_2(); pulse_gen(1); state_5(); latch_gen();__delay_ms(200);
        state_2(); pulse_gen(1); state_6(); latch_gen();__delay_ms(200);
        state_2(); pulse_gen(1); state_7(); latch_gen();__delay_ms(200);
        state_2(); pulse_gen(1); state_8(); latch_gen();__delay_ms(200);
        state_2(); pulse_gen(1); state_9(); latch_gen();__delay_ms(200);       
        // 30 to 39
        state_3(); pulse_gen(1); state_0(); latch_gen();__delay_ms(200); // Sending "3x" and latching
        state_3(); pulse_gen(1); state_1(); latch_gen();__delay_ms(200);
        state_3(); pulse_gen(1); state_2(); latch_gen();__delay_ms(200);
        state_3(); pulse_gen(1); state_3(); latch_gen();__delay_ms(200);
        state_3(); pulse_gen(1); state_4(); latch_gen();__delay_ms(200);
        state_3(); pulse_gen(1); state_5(); latch_gen();__delay_ms(200);
        state_3(); pulse_gen(1); state_6(); latch_gen();__delay_ms(200);
        state_3(); pulse_gen(1); state_7(); latch_gen();__delay_ms(200);
        state_3(); pulse_gen(1); state_8(); latch_gen();__delay_ms(200);
        state_3(); pulse_gen(1); state_9(); latch_gen();__delay_ms(200);       
        // 40 to 49
        state_4(); pulse_gen(1); state_0(); latch_gen();__delay_ms(200); // Sending "4x" and latching
        state_4(); pulse_gen(1); state_1(); latch_gen();__delay_ms(200);
        state_4(); pulse_gen(1); state_2(); latch_gen();__delay_ms(200);
        state_4(); pulse_gen(1); state_3(); latch_gen();__delay_ms(200);
        state_4(); pulse_gen(1); state_4(); latch_gen();__delay_ms(200);
        state_4(); pulse_gen(1); state_5(); latch_gen();__delay_ms(200);
        state_4(); pulse_gen(1); state_6(); latch_gen();__delay_ms(200);
        state_4(); pulse_gen(1); state_7(); latch_gen();__delay_ms(200);
        state_4(); pulse_gen(1); state_8(); latch_gen();__delay_ms(200);
        state_4(); pulse_gen(1); state_9(); latch_gen();__delay_ms(200);
        // 50 to 59
        state_5(); pulse_gen(1); state_0(); latch_gen();__delay_ms(200); // Sending "5x" and latching
        state_5(); pulse_gen(1); state_1(); latch_gen();__delay_ms(200);
        state_5(); pulse_gen(1); state_2(); latch_gen();__delay_ms(200);
        state_5(); pulse_gen(1); state_3(); latch_gen();__delay_ms(200);
        state_5(); pulse_gen(1); state_4(); latch_gen();__delay_ms(200);
        state_5(); pulse_gen(1); state_5(); latch_gen();__delay_ms(200);
        state_5(); pulse_gen(1); state_6(); latch_gen();__delay_ms(200);
        state_5(); pulse_gen(1); state_7(); latch_gen();__delay_ms(200);
        state_5(); pulse_gen(1); state_8(); latch_gen();__delay_ms(200);
        state_5(); pulse_gen(1); state_9(); latch_gen();__delay_ms(200);
        // 60 to 69
        state_6(); pulse_gen(1); state_0(); latch_gen();__delay_ms(200); // Sending "6x" and latching
        state_6(); pulse_gen(1); state_1(); latch_gen();__delay_ms(200);
        state_6(); pulse_gen(1); state_2(); latch_gen();__delay_ms(200);
        state_6(); pulse_gen(1); state_3(); latch_gen();__delay_ms(200);
        state_6(); pulse_gen(1); state_4(); latch_gen();__delay_ms(200);
        state_6(); pulse_gen(1); state_5(); latch_gen();__delay_ms(200);
        state_6(); pulse_gen(1); state_6(); latch_gen();__delay_ms(200);
        state_6(); pulse_gen(1); state_7(); latch_gen();__delay_ms(200);
        state_6(); pulse_gen(1); state_8(); latch_gen();__delay_ms(200);
        state_6(); pulse_gen(1); state_9(); latch_gen();__delay_ms(200);
        // 70 to 79
        state_7(); pulse_gen(1); state_0(); latch_gen();__delay_ms(200); // Sending "7x" and latching
        state_7(); pulse_gen(1); state_1(); latch_gen();__delay_ms(200);
        state_7(); pulse_gen(1); state_2(); latch_gen();__delay_ms(200);
        state_7(); pulse_gen(1); state_3(); latch_gen();__delay_ms(200);
        state_7(); pulse_gen(1); state_4(); latch_gen();__delay_ms(200);
        state_7(); pulse_gen(1); state_5(); latch_gen();__delay_ms(200);
        state_7(); pulse_gen(1); state_6(); latch_gen();__delay_ms(200);
        state_7(); pulse_gen(1); state_7(); latch_gen();__delay_ms(200);
        state_7(); pulse_gen(1); state_8(); latch_gen();__delay_ms(200);
        state_7(); pulse_gen(1); state_9(); latch_gen();__delay_ms(200);
        // 80 to 89
        state_8(); pulse_gen(1); state_0(); latch_gen();__delay_ms(200); // Sending "8x" and latching
        state_8(); pulse_gen(1); state_1(); latch_gen();__delay_ms(200);
        state_8(); pulse_gen(1); state_2(); latch_gen();__delay_ms(200);
        state_8(); pulse_gen(1); state_3(); latch_gen();__delay_ms(200);
        state_8(); pulse_gen(1); state_4(); latch_gen();__delay_ms(200);
        state_8(); pulse_gen(1); state_5(); latch_gen();__delay_ms(200);
        state_8(); pulse_gen(1); state_6(); latch_gen();__delay_ms(200);
        state_8(); pulse_gen(1); state_7(); latch_gen();__delay_ms(200);
        state_8(); pulse_gen(1); state_8(); latch_gen();__delay_ms(200);
        state_8(); pulse_gen(1); state_9(); latch_gen();__delay_ms(200);
        // 90 to 99
        state_9(); pulse_gen(1); state_0(); latch_gen();__delay_ms(200); // Sending "9x" and latching
        state_9(); pulse_gen(1); state_1(); latch_gen();__delay_ms(200);
        state_9(); pulse_gen(1); state_2(); latch_gen();__delay_ms(200);
        state_9(); pulse_gen(1); state_3(); latch_gen();__delay_ms(200);
        state_9(); pulse_gen(1); state_4(); latch_gen();__delay_ms(200);
        state_9(); pulse_gen(1); state_5(); latch_gen();__delay_ms(200);
        state_9(); pulse_gen(1); state_6(); latch_gen();__delay_ms(200);
        state_9(); pulse_gen(1); state_7(); latch_gen();__delay_ms(200);
        state_9(); pulse_gen(1); state_8(); latch_gen();__delay_ms(200);
        state_9(); pulse_gen(1); state_9(); latch_gen();__delay_ms(200);
    } 
    return;
}
