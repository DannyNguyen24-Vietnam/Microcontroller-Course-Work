/*
 * File:   prset_clock.c
 * Author: NGUYEN HAI DANG - ID: 20146110
 *
 * Created on March 10, 2022, 1:04 AM
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

//
#include <xc.h>
// Second Digits //
void pulse_gen_C0(int n){
    for(int i=0;i<=(n-1);i++){
        LATCbits.LATC0=1;     // Positive Edge Triggering
        LATCbits.LATC0=0;     // Negative Edge Triggering
    }
    return;
}
// Latching Pulses Generator
void latch_gen_C2(){
    LATCbits.LATC2=1;     // Positive Edge Triggering
    LATCbits.LATC2=0;     // Negative Edge Triggering
    return;
}
void num_state_C1(int digit){
    switch(digit){
        case 0: LATCbits.LATC1=0; pulse_gen_C0(1); LATCbits.LATC1=1; pulse_gen_C0(6); break;
        case 1: LATCbits.LATC1=0; pulse_gen_C0(4); LATCbits.LATC1=1; pulse_gen_C0(2); LATCbits.LATC1=0; pulse_gen_C0(1); break;
        case 2: LATCbits.LATC1=1; pulse_gen_C0(1); LATCbits.LATC1=0; pulse_gen_C0(1); LATCbits.LATC1=1; pulse_gen_C0(2);
                LATCbits.LATC1=0; pulse_gen_C0(1); LATCbits.LATC1=1; pulse_gen_C0(2); break;
        case 3: LATCbits.LATC1=1; pulse_gen_C0(1); LATCbits.LATC1=0; pulse_gen_C0(2); LATCbits.LATC1=1; pulse_gen_C0(4); break;
        case 4: LATCbits.LATC1=1; pulse_gen_C0(2); LATCbits.LATC1=0; pulse_gen_C0(2); LATCbits.LATC1=1; pulse_gen_C0(2); LATCbits.LATC1=0; pulse_gen_C0(1); break;
        case 5: LATCbits.LATC1=1; pulse_gen_C0(2); LATCbits.LATC1=0; pulse_gen_C0(1); LATCbits.LATC1=1; pulse_gen_C0(2);
                LATCbits.LATC1=0; pulse_gen_C0(1); LATCbits.LATC1=1; pulse_gen_C0(1); break;
        case 6: LATCbits.LATC1=1; pulse_gen_C0(5); LATCbits.LATC1=0; pulse_gen_C0(1); LATCbits.LATC1=1; pulse_gen_C0(1); break;
        case 7: LATCbits.LATC1=0; pulse_gen_C0(4); LATCbits.LATC1=1; pulse_gen_C0(3); break;
        case 8: LATCbits.LATC1=1; pulse_gen_C0(7); break;
        default: LATCbits.LATC1=1; pulse_gen_C0(2); LATCbits.LATC1=0; pulse_gen_C0(1); LATCbits.LATC1=1; pulse_gen_C0(4);
    }
    return;
}
// Stop the counting (version 1)
void stop_counting();
// Second Counting Down
void sec_countdown(int min_value){
    int sec_counter1=5, sec_counter2=9;   
    while(sec_counter1>=0){
        while(sec_counter2>=0){
            num_state_C1(sec_counter1); pulse_gen_C0(1); 
            num_state_C1(sec_counter2); latch_gen_C2();
            stop_counting(min_value, sec_counter1, sec_counter2); __delay_ms(20);   
            __delay_ms(250);
            stop_counting(min_value, sec_counter1, sec_counter2); __delay_ms(20);
            sec_counter2--;
        }
        sec_counter1--;
        sec_counter2=9;
    }
    return;
}

// Minute Digits //
void pulse_gen_C3(int n_1){
    for(int i_1=0;i_1<=(n_1-1);i_1++){
        LATCbits.LATC3=1;     // Positive Edge Triggering
        LATCbits.LATC3=0;     // Negative Edge Triggering
    }
    return;
}
// Latching Pulses Generator
void latch_gen_C5(){
    LATCbits.LATC5=1;     // Positive Edge Triggering
    LATCbits.LATC5=0;     // Negative Edge Triggering
    return;
}
void num_state_C4(int digit_1){
    switch(digit_1){
        case 0: LATCbits.LATC4=0; pulse_gen_C3(1); LATCbits.LATC4=1; pulse_gen_C3(6); break;
        case 1: LATCbits.LATC4=0; pulse_gen_C3(4); LATCbits.LATC4=1; pulse_gen_C3(2); LATCbits.LATC4=0; pulse_gen_C3(1); break;
        case 2: LATCbits.LATC4=1; pulse_gen_C3(1); LATCbits.LATC4=0; pulse_gen_C3(1); LATCbits.LATC4=1; pulse_gen_C3(2);
                LATCbits.LATC4=0; pulse_gen_C3(1); LATCbits.LATC4=1; pulse_gen_C3(2); break;
        case 3: LATCbits.LATC4=1; pulse_gen_C3(1); LATCbits.LATC4=0; pulse_gen_C3(2); LATCbits.LATC4=1; pulse_gen_C3(4); break;
        case 4: LATCbits.LATC4=1; pulse_gen_C3(2); LATCbits.LATC4=0; pulse_gen_C3(2); LATCbits.LATC4=1; pulse_gen_C3(2); LATCbits.LATC4=0; pulse_gen_C3(1); break;
        case 5: LATCbits.LATC4=1; pulse_gen_C3(2); LATCbits.LATC4=0; pulse_gen_C3(1); LATCbits.LATC4=1; pulse_gen_C3(2);
                LATCbits.LATC4=0; pulse_gen_C3(1); LATCbits.LATC4=1; pulse_gen_C3(1); break;
        case 6: LATCbits.LATC4=1; pulse_gen_C3(5); LATCbits.LATC4=0; pulse_gen_C3(1); LATCbits.LATC4=1; pulse_gen_C3(1); break;
        case 7: LATCbits.LATC4=0; pulse_gen_C3(4); LATCbits.LATC4=1; pulse_gen_C3(3); break;
        case 8: LATCbits.LATC4=1; pulse_gen_C3(7); break;
        default: LATCbits.LATC4=1; pulse_gen_C3(2); LATCbits.LATC4=0; pulse_gen_C3(1); LATCbits.LATC4=1; pulse_gen_C3(4);
    }
    return;
}
// Stop the counting (version 1)
void stop_counting(int min_value, int sec_digit1, int sec_digit2){
    while(PORTBbits.RB7==0){
        // Minute displaying
        num_state_C4(min_value/10); pulse_gen_C3(1); 
        num_state_C4(min_value%10); latch_gen_C5();
        // Second displaying
        num_state_C1(sec_digit1); pulse_gen_C0(1); 
        num_state_C1(sec_digit2); latch_gen_C2();
    }
    return;
}

// Main Function
void main(void) {
    __delay_ms(80);
    // Initializing pins, variables and state
    TRISC = 0;
    ANSELC = 0; // Disabling Analog mode of TRIS register C
    ANSELB = 0; // Disabling Analog mode of TRIS register B
    TRISBbits.TRISB4=1; // "1" means input mode
    TRISBbits.TRISB5=1; // "1" means input mode
    TRISBbits.TRISB6=1; // "1" means input mode 
    OPTION_REGbits.nWPUEN = 0;
    WPUBbits.WPUB4=1; // Enabling Internal Weak-Pull up of RB4
    WPUBbits.WPUB5=1; // Enabling Internal Weak-Pull up of RB5
    WPUBbits.WPUB6=1;
    WPUBbits.WPUB7=1;// Enabling Internal Weak-Pull up of RB6
    int count=0, temp_val=0; // Counting variable
    int min_digit_1=0, min_digit_2=0, sec_digit_1=0, sec_digit_2=0; // Two digits for each part
    
    while(1){
        // Increasing
        if(PORTBbits.RB5==0){
            __delay_ms(90);
            if(PORTBbits.RB5==0){
                count++;
                temp_val++;
            }
        }
        // Decreasing
        if(PORTBbits.RB6==0){
            __delay_ms(90);
            if(PORTBbits.RB6==0){
                count--;
                temp_val--;
            }
        }
        // Start counting down
        if(PORTBbits.RB4==0){
            if(count!=0){
                while(count>=0){
                    // If user set X minutes, the clock will start from (X-1):59
                    if (count>=temp_val){
                        count-=1;}
                    num_state_C4(count/10); pulse_gen_C3(1); // Minute displaying
                    num_state_C4(count%10); latch_gen_C5();
                    sec_countdown(count); // Second displaying
                    count-=1; 
                    min_digit_1 = count/10;
                    min_digit_2 = count%10;
                    num_state_C4(min_digit_1); pulse_gen_C3(1); // Minute displaying
                    num_state_C4(min_digit_2); latch_gen_C5();
                }
                count=0;
                temp_val=0;
            }
        }
        // Value range
        if(count>60||count<0){
            count=0;
        }
        min_digit_1 = count/10;
        min_digit_2 = count%10;
        // Displaying
            // Second
        num_state_C1(sec_digit_1); pulse_gen_C0(1);
        num_state_C1(sec_digit_2); latch_gen_C2();
            // Minute
        num_state_C4(min_digit_1); pulse_gen_C3(1);
        num_state_C4(min_digit_2); latch_gen_C5();
    }
    return;
}
