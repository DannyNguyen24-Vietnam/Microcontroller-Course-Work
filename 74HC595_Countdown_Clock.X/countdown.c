/*
 * File:   countdown.c
 * Author: Nguyen Hai Dang
 *
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

// My Idea //
/* The original idea comes from the previous exercise of counting from 00 to 99
 I will create 10 functions for number states of RC1 and another 10 for RC4*/

#include <xc.h>
// Pulse generator for RC0
void pulse_gen(int n){
    for(int i=0;i<=(n-1);i++){
        LATCbits.LATC0 = 0;
        LATCbits.LATC0 = 1;
    }
    return;
}
// Latching generator for RC2
void latch_gen(){
    LATCbits.LATC2 = 1;
    LATCbits.LATC2 = 0;
    return;
}
// Number states for LATC1
// The functions will generate 7 pulses enough for 7 latches integrated in the 74HC595
void state_0_C1(){
    LATCbits.LATC1 = 1; pulse_gen(1);    
    LATCbits.LATC1 = 0; pulse_gen(6); return;
}
void state_1_C1(){
    LATCbits.LATC1 = 1; pulse_gen(4);    
    LATCbits.LATC1 = 0; pulse_gen(2);    
    LATCbits.LATC1 = 1; pulse_gen(1); return;
}
void state_2_C1(){
    LATCbits.LATC1 = 0; pulse_gen(1);    
    LATCbits.LATC1 = 1; pulse_gen(1);    
    LATCbits.LATC1 = 0; pulse_gen(2);    
    LATCbits.LATC1 = 1; pulse_gen(1);
    LATCbits.LATC1 = 0; pulse_gen(2); return;
}
void state_3_C1(){
    LATCbits.LATC1 = 0; pulse_gen(1);    
    LATCbits.LATC1 = 1; pulse_gen(2);    
    LATCbits.LATC1 = 0; pulse_gen(4); return;    
}
void state_4_C1(){
    LATCbits.LATC1 = 0; pulse_gen(2);    
    LATCbits.LATC1 = 1; pulse_gen(2);    
    LATCbits.LATC1 = 0; pulse_gen(2);    
    LATCbits.LATC1 = 1; pulse_gen(1); return;
}
void state_5_C1(){
    LATCbits.LATC1 = 0; pulse_gen(2);    
    LATCbits.LATC1 = 1; pulse_gen(1);    
    LATCbits.LATC1 = 0; pulse_gen(2);    
    LATCbits.LATC1 = 1; pulse_gen(1);
    LATCbits.LATC1 = 0; pulse_gen(1); return;
}
void state_6_C1(){
    LATCbits.LATC1 = 0; pulse_gen(5);    
    LATCbits.LATC1 = 1; pulse_gen(1);    
    LATCbits.LATC1 = 0; pulse_gen(1); return;
}
void state_7_C1(){
    LATCbits.LATC1 = 1; pulse_gen(4);    
    LATCbits.LATC1 = 0; pulse_gen(3); return;   
}
void state_8_C1(){
    LATCbits.LATC1 = 0; pulse_gen(7); return;
}
void state_9_C1(){
    LATCbits.LATC1 = 0; pulse_gen(2);    
    LATCbits.LATC1 = 1; pulse_gen(1);    
    LATCbits.LATC1 = 0; pulse_gen(4); return;   
}
/*Since the shifting principles of the two 74HC595 ICs (I use two ICs) used for the two second (time meaning) digits
 We must send both digits for every count, even if the first digit hasn't changed its state yet*/
// The seconds counting states from 59th second to 00th second
void second_counting(){
    // 59 to 50
    state_5_C1(); pulse_gen(1); state_9_C1(); latch_gen();__delay_ms(200); // Sending "5x" and latching
    state_5_C1(); pulse_gen(1); state_8_C1(); latch_gen();__delay_ms(200);
    state_5_C1(); pulse_gen(1); state_7_C1(); latch_gen();__delay_ms(200);
    state_5_C1(); pulse_gen(1); state_6_C1(); latch_gen();__delay_ms(200);
    state_5_C1(); pulse_gen(1); state_5_C1(); latch_gen();__delay_ms(200);   
    state_5_C1(); pulse_gen(1); state_4_C1(); latch_gen();__delay_ms(200);   
    state_5_C1(); pulse_gen(1); state_3_C1(); latch_gen();__delay_ms(200);
    state_5_C1(); pulse_gen(1); state_2_C1(); latch_gen();__delay_ms(200);
    state_5_C1(); pulse_gen(1); state_1_C1(); latch_gen();__delay_ms(200);
    state_5_C1(); pulse_gen(1); state_0_C1(); latch_gen();__delay_ms(200);
    // 49 to 40
    state_4_C1(); pulse_gen(1); state_9_C1(); latch_gen();__delay_ms(200); // Sending "4x" and latching
    state_4_C1(); pulse_gen(1); state_8_C1(); latch_gen();__delay_ms(200);
    state_4_C1(); pulse_gen(1); state_7_C1(); latch_gen();__delay_ms(200);
    state_4_C1(); pulse_gen(1); state_6_C1(); latch_gen();__delay_ms(200);
    state_4_C1(); pulse_gen(1); state_5_C1(); latch_gen();__delay_ms(200);
    state_4_C1(); pulse_gen(1); state_4_C1(); latch_gen();__delay_ms(200);
    state_4_C1(); pulse_gen(1); state_3_C1(); latch_gen();__delay_ms(200);
    state_4_C1(); pulse_gen(1); state_2_C1(); latch_gen();__delay_ms(200);
    state_4_C1(); pulse_gen(1); state_1_C1(); latch_gen();__delay_ms(200);
    state_4_C1(); pulse_gen(1); state_0_C1(); latch_gen();__delay_ms(200);     
    // 39 to 30
    state_3_C1(); pulse_gen(1); state_9_C1(); latch_gen();__delay_ms(200); // Sending "3x" and latching
    state_3_C1(); pulse_gen(1); state_8_C1(); latch_gen();__delay_ms(200);
    state_3_C1(); pulse_gen(1); state_7_C1(); latch_gen();__delay_ms(200);
    state_3_C1(); pulse_gen(1); state_6_C1(); latch_gen();__delay_ms(200);
    state_3_C1(); pulse_gen(1); state_5_C1(); latch_gen();__delay_ms(200);
    state_3_C1(); pulse_gen(1); state_4_C1(); latch_gen();__delay_ms(200);
    state_3_C1(); pulse_gen(1); state_3_C1(); latch_gen();__delay_ms(200);
    state_3_C1(); pulse_gen(1); state_2_C1(); latch_gen();__delay_ms(200);
    state_3_C1(); pulse_gen(1); state_1_C1(); latch_gen();__delay_ms(200);
    state_3_C1(); pulse_gen(1); state_0_C1(); latch_gen();__delay_ms(200);      
    // 29 to 20
    state_2_C1(); pulse_gen(1); state_9_C1(); latch_gen();__delay_ms(200); // Sending "2x" and latching
    state_2_C1(); pulse_gen(1); state_8_C1(); latch_gen();__delay_ms(200);
    state_2_C1(); pulse_gen(1); state_7_C1(); latch_gen();__delay_ms(200);
    state_2_C1(); pulse_gen(1); state_6_C1(); latch_gen();__delay_ms(200);
    state_2_C1(); pulse_gen(1); state_5_C1(); latch_gen();__delay_ms(200);
    state_2_C1(); pulse_gen(1); state_4_C1(); latch_gen();__delay_ms(200);
    state_2_C1(); pulse_gen(1); state_3_C1(); latch_gen();__delay_ms(200);
    state_2_C1(); pulse_gen(1); state_2_C1(); latch_gen();__delay_ms(200);
    state_2_C1(); pulse_gen(1); state_1_C1(); latch_gen();__delay_ms(200);
    state_2_C1(); pulse_gen(1); state_0_C1(); latch_gen();__delay_ms(200);
    // 19 t0 10
    state_1_C1(); pulse_gen(1); state_9_C1(); latch_gen();__delay_ms(200); // Sending "1x" and latching
    state_1_C1(); pulse_gen(1); state_8_C1(); latch_gen();__delay_ms(200);
    state_1_C1(); pulse_gen(1); state_7_C1(); latch_gen();__delay_ms(200);
    state_1_C1(); pulse_gen(1); state_6_C1(); latch_gen();__delay_ms(200);
    state_1_C1(); pulse_gen(1); state_5_C1(); latch_gen();__delay_ms(200);
    state_1_C1(); pulse_gen(1); state_4_C1(); latch_gen();__delay_ms(200);
    state_1_C1(); pulse_gen(1); state_3_C1(); latch_gen();__delay_ms(200);
    state_1_C1(); pulse_gen(1); state_2_C1(); latch_gen();__delay_ms(200);
    state_1_C1(); pulse_gen(1); state_1_C1(); latch_gen();__delay_ms(200);
    state_1_C1(); pulse_gen(1); state_0_C1(); latch_gen();__delay_ms(200); 
    // 09 to 00
    state_0_C1(); pulse_gen(1); state_9_C1(); latch_gen();__delay_ms(200); // Sending "0x" and latching
    state_0_C1(); pulse_gen(1); state_8_C1(); latch_gen();__delay_ms(200);
    state_0_C1(); pulse_gen(1); state_7_C1(); latch_gen();__delay_ms(200);
    state_0_C1(); pulse_gen(1); state_6_C1(); latch_gen();__delay_ms(200);
    state_0_C1(); pulse_gen(1); state_5_C1(); latch_gen();__delay_ms(200);
    state_0_C1(); pulse_gen(1); state_4_C1(); latch_gen();__delay_ms(200);
    state_0_C1(); pulse_gen(1); state_3_C1(); latch_gen();__delay_ms(200);
    state_0_C1(); pulse_gen(1); state_2_C1(); latch_gen();__delay_ms(200);
    state_0_C1(); pulse_gen(1); state_1_C1(); latch_gen();__delay_ms(200);
    state_0_C1(); pulse_gen(1); state_0_C1(); latch_gen();__delay_ms(200);        
    return;
}

// Pulse generator for RC3
void pulse_gen_1(int n_1){
    for(int i_1=0;i_1<=(n_1-1);i_1++){
        LATCbits.LATC3 = 0;
        LATCbits.LATC3 = 1;
    }
    return;
}
// Latching generator for RC3
void latch_gen_1(){
    LATCbits.LATC5 = 1;
    LATCbits.LATC5 = 0;
    return;
}
// Number states for LATC4
// The functions will generate 7 pulses enough for 7 latches integrated in the 74HC595
void state_0_C4(){
    LATCbits.LATC4 = 1; pulse_gen_1(1);    
    LATCbits.LATC4 = 0; pulse_gen_1(6); return;
}
void state_1_C4(){
    LATCbits.LATC4 = 1; pulse_gen_1(4);    
    LATCbits.LATC4 = 0; pulse_gen_1(2);    
    LATCbits.LATC4 = 1; pulse_gen_1(1); return;
}
void state_2_C4(){
    LATCbits.LATC4 = 0; pulse_gen_1(1);    
    LATCbits.LATC4 = 1; pulse_gen_1(1);    
    LATCbits.LATC4 = 0; pulse_gen_1(2);    
    LATCbits.LATC4 = 1; pulse_gen_1(1);
    LATCbits.LATC4 = 0; pulse_gen_1(2); return;
}
void state_3_C4(){
    LATCbits.LATC4 = 0; pulse_gen_1(1);    
    LATCbits.LATC4 = 1; pulse_gen_1(2);    
    LATCbits.LATC4 = 0; pulse_gen_1(4); return;    
}
void state_4_C4(){
    LATCbits.LATC4 = 0; pulse_gen_1(2);    
    LATCbits.LATC4 = 1; pulse_gen_1(2);    
    LATCbits.LATC4 = 0; pulse_gen_1(2);    
    LATCbits.LATC4 = 1; pulse_gen_1(1); return;
}
void state_5_C4(){
    LATCbits.LATC4 = 0; pulse_gen_1(2);    
    LATCbits.LATC4 = 1; pulse_gen_1(1);    
    LATCbits.LATC4 = 0; pulse_gen_1(2);    
    LATCbits.LATC4 = 1; pulse_gen_1(1);
    LATCbits.LATC4 = 0; pulse_gen_1(1); return;
}
void state_6_C4(){
    LATCbits.LATC4 = 0; pulse_gen_1(5);    
    LATCbits.LATC4 = 1; pulse_gen_1(1);    
    LATCbits.LATC4 = 0; pulse_gen_1(1); return;
}
void state_7_C4(){
    LATCbits.LATC4 = 1; pulse_gen_1(4);    
    LATCbits.LATC4 = 0; pulse_gen_1(3); return;   
}
void state_8_C4(){
    LATCbits.LATC4 = 0; pulse_gen_1(7); return;
}
void state_9_C4(){
    LATCbits.LATC4 = 0; pulse_gen_1(2);    
    LATCbits.LATC4 = 1; pulse_gen_1(1);    
    LATCbits.LATC4 = 0; pulse_gen_1(4); return;
}

void main(void){
    TRISC = 0; // "0" means output mode
    ANSELC = 0; // Deselecting analog mode
    // Make sure all used pins are in initial state
    LATCbits.LATC0 = 0; 
    LATCbits.LATC1 = 0; 
    LATCbits.LATC2 = 0; 
    LATCbits.LATC3 = 0; 
    LATCbits.LATC4 = 0;
    LATCbits.LATC5 = 0;
    
    // Clock operation: 15 minutes count down clock
    while(1){
        // 14:59 to 14:00
        state_1_C4(); pulse_gen_1(1); state_4_C4(); latch_gen_1();
        second_counting();
        // 13:59 to 13:00
        state_1_C4(); pulse_gen_1(1); state_3_C4(); latch_gen_1();
        second_counting();
        // 12:59 to 11:00
        state_1_C4(); pulse_gen_1(1); state_2_C4(); latch_gen_1();
        second_counting();
        // 11:59 to 11:00
        state_1_C4(); pulse_gen_1(1); state_1_C4(); latch_gen_1();
        second_counting();
        // 10:59 to 10:00
        state_1_C4(); pulse_gen_1(1); state_0_C4(); latch_gen_1();
        second_counting();
        // 09:59 to 09:00
        state_0_C4(); pulse_gen_1(1); state_9_C4(); latch_gen_1();
        second_counting();
        // 08:59 to 08:00
        state_0_C4(); pulse_gen_1(1); state_8_C4(); latch_gen_1();
        second_counting();
        // 07:59 to 07:00
        state_0_C4(); pulse_gen_1(1); state_7_C4(); latch_gen_1();
        second_counting();
        // 06:59 to 06:00
        state_0_C4(); pulse_gen_1(1); state_6_C4(); latch_gen_1();
        second_counting();
        // 05:59 to 05:00
        state_0_C4(); pulse_gen_1(1); state_5_C4(); latch_gen_1();
        second_counting();
        // 04:59 to 04:00
        state_0_C4(); pulse_gen_1(1); state_4_C4(); latch_gen_1();
        second_counting();
        // 03:59 to 03:00
        state_0_C4(); pulse_gen_1(1); state_3_C4(); latch_gen_1();
        second_counting();
        // 02:59 to 02:00
        state_0_C4(); pulse_gen_1(1); state_2_C4(); latch_gen_1();
        second_counting();
        // 01:59 to 01:00
        state_0_C4(); pulse_gen_1(1); state_1_C4(); latch_gen_1();
        second_counting();
        // 00:59 to 00:00
        state_0_C4(); pulse_gen_1(1); state_0_C4(); latch_gen_1();
        second_counting();
    }
    return;
}
