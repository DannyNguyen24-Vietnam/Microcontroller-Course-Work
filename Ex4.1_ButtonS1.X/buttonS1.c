/*
 * File:   buttonS1.c
 * Author: NGUYEN HAI DANG
 *
 * Created on March 19, 2022, 6:26 PM
 */
// PIC16F1509 Configuration Bit Settings
// 'C' source line config statements
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

#define _XTAL_FREQ 1000000
#define D1_output LATCbits.LATC5
#define D2_output LATCbits.LATC6
#define D3_output LATCbits.LATC7
#define S1_input PORTCbits.RC0
#define S2_input PORTCbits.RC1
#define S3_input PORTCbits.RC2

#include <xc.h>

void main(void) {  
    // Output mode of pins connected to LEDs
    TRISCbits.TRISC5 =0;
    TRISCbits.TRISC6 =0;
    TRISCbits.TRISC7 =0;
    // Input mode of pins connected to Buttons
    TRISCbits.TRISC0 =1;
    TRISCbits.TRISC1 =1;
    TRISCbits.TRISC2 =1;
    ANSELC=0; // Deselecting Analog mode
    D1_output =0;
    D2_output =0;
    D3_output =0;
    int second_tracking=0;
    int state = 0;
    int reset_counter=0;
    while(1){
    // Button S1
        if((state==0&&S1_input==1)||(state==9&&S1_input==1)){
            __delay_ms(90);
            if(S1_input==1){
                state = 1;
            }
        }
        if(state==1&&S1_input==0){
            state = 2; // D1 on
        }
        if((state==2&&S1_input==1)||(state==11&&S1_input==1)){
            __delay_ms(90);
            if(S1_input==1){
                state = 3; // D1 still on
            }
        }   
        if(state==3&&S1_input==0){
            state = 4; // D2 on
        }
        if((state==4&&S1_input==1)||(state==13&&S1_input==1)){
            __delay_ms(90);
            if(S1_input==1){
                state = 5; // D2 still on
            }
        }
        if(state==5&&S1_input==0){
            state = 6; // D3 on  
        }    
        if(state==6&&S1_input==1){
            __delay_ms(90);
            if(S1_input==1){
                state = 7; // D3 still on
            }
        }
        if(state==7&&S1_input==0){
            state = 0;
        }
    // Button S2
        if((state==0&&S2_input==1)||(state==2&&S2_input==1)){
            __delay_ms(90);            
            if(S2_input==1){
                state = 8; 
            }
        }
        if(state==8&&S2_input==0){
            state = 9; // D1 flashing
        }
        if(state==9&&S2_input==1){
            __delay_ms(90);
            if(S2_input==1){
                state = 10; // D1 still flashing
            }
        }
    // For debugging a weird phenomena
        if(state==4&&S2_input==1){
            __delay_ms(90);
            if(S2_input==1){
                state = 15;
            }
        }
        if(state==10&&S2_input==0){
            state = 11; // D2 flashing
        }
        if(state==11&&S2_input==1){
            __delay_ms(90);
            if(S2_input==1){
                state = 12; // D2 still flashing
            }
        }
    // For debugging a weird phenomena
        if(state==6&&S2_input==1){
            __delay_ms(90);
            if(S2_input==1){
                state = 16; // D2 still flashing
            } 
        }
        if(state==12&&S2_input==0){
            state = 13; // D3 flashing
        }
        if(state==13&&S2_input==1){
            __delay_ms(90);
            if(S2_input==1){
                state = 14; // D3 still flashing
            }
        }
        if(state==15&&S2_input==0){
            state = 11; // D3 still flashing
        }
        if(state==16&&S2_input==0){
            state = 13; // D3 still flashing
        }
        if(state==14&&S2_input==0){
            state = 0; // D3 still flashing
        }
    // Button S3
        // The flashing motion consumes much time so its reset waiting time is shorter
        if(S3_input==1&&state<7){
            if(reset_counter<1200){
                reset_counter+=1;
            } else {reset_counter=0;
                        state=0;
                        D1_output=0;
                        D2_output=0;
                        D3_output=0;
            }
        } else if(S3_input==0){
            reset_counter=0;
        }
        if(S3_input==1&&state>7){
            if(reset_counter<650){
                reset_counter+=1;
            } else {reset_counter=0;
                        state=0;
                        D1_output=0;
                        D2_output=0;
                        D3_output=0;
            }
        } else if(S3_input==0){
            reset_counter=0;
        }
    // LEDs displaying
        if(state==0){
            D1_output=0;
            D2_output=0;
            D3_output=0;
        }
        if(state==2){
             D1_output=1;
             D2_output=0;
             D3_output=0;
           }
        if(state==4){
             D1_output=0;
             D2_output=1;
             D3_output=0;
           }
        if(state==6){
             D1_output=0;
             D2_output=0;
             D3_output=1;
           }
        if(state==9||state==10){
            if(second_tracking<250){
             D1_output=1;
             D2_output=0;
             D3_output=0;
             __delay_ms(1);
             second_tracking+=1;
           } else if(second_tracking<500){
             D1_output=0;
             __delay_ms(1);
             second_tracking+=1;
           } else {second_tracking=0;}
        }
        if(state==11||state==12){
            if(second_tracking<250){
             D1_output=0;
             D2_output=1;
             D3_output=0;
             __delay_ms(1);
             second_tracking+=1;
           } else if(second_tracking<500){
             D2_output=0;
             __delay_ms(1);
             second_tracking+=1;
           } else {second_tracking=0;}
        }
        if(state==13||state==14){
            if(second_tracking<250){
             D1_output=0;
             D2_output=0;
             D3_output=1;
             __delay_ms(1);
             second_tracking+=1;
           } else if(second_tracking<500){
             D3_output=0;
             __delay_ms(1);
             second_tracking+=1;
           } else {second_tracking=0;}
        }
    }
    return;
}

