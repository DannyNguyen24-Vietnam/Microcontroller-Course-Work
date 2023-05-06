/*
 * Author: NGUYEN HAI DANG
 * Field of Study: Mechatronics Engineering
 * Phone number: 0981642324
 * Work mail: 20146110@student.hcmute.edu.vn
 * My thought: "It's not about the homework, it's about the way I'm gonna solve it"
 * Created on March 30, 2022, 9:37 PM
 */
// PIC16F1509 Configuration Bit Settings
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

#include <xc.h>
#define _XTAL_FREQ 1000000
// For the first two ICs
#define CLK0 LATCbits.LATC0
#define DAT0 LATCbits.LATC1
#define LAT0 LATCbits.LATC2
// For the second two ICs
#define CLK1 LATCbits.LATC5
#define DAT1 LATCbits.LATC6
#define LAT1 LATCbits.LATC7
// For the buttons
#define START PORTBbits.RB4
#define SET_P PORTBbits.RB5 // Minute increment (Setting the clock) - "P" stands for "Plus"
#define SET_S PORTBbits.RB6 // Minute decrement (Setting the clock) - "S" stands for "Subtract"

// Clock pulse for the first two ICs
void clk0_pulse(){
    CLK0 = 0;   // LOW state
    CLK0 = 1;   // HIGH state
    return;
}
// Latch pulse for the first two ICs
void lat0_pulse(){
    LAT0 = 1;   // HIGH state
    LAT0 = 0;   // LOW state
    return;
}
// Clock pulse for the second two ICs
void clk1_pulse(){
    CLK1 = 0;   // LOW state
    CLK1 = 1;   // HIGH state
    return;
}
// Latch pulse for the second two ICs
void lat1_pulse(){
    LAT1 = 1;   // LOW state
    LAT1 = 0;   // HIGH state
    return;
}
// States for the Common Anode 7-Segment display
char ComA_state[10]={0b1000000, 0b1111001, 0b0100100, 0b0110000, 0b0011001,
                     0b0010010, 0b0000010, 0b1111000, 0b0000000, 0b0010000};
// Data for the first two ICs
void data_0(int index_0){
    int i=0;
    for(i=0;i<=6;i++){
        if((ComA_state[index_0]&(0b1000000>>i))==0){
                DAT0=0; 
            } else{ 
                DAT0=1;
            }
            clk0_pulse();
    }
    return;
}
// Data for the second two ICs
void data_1(int index_1){
    int i=0;
    for(i=0;i<=6;i++){
        if((ComA_state[index_1]&(0b1000000>>i))==0){
                DAT1=0; 
            } else{ 
                DAT1=1;
            }
            clk1_pulse();
    }
    return;
}
// Clock setting display
void set_clock(int min_set){
    unsigned char min_dis1, min_dis2; // For displaying the setting mode
    int i=0;
    min_dis1 = min_set/10;
    min_dis2 = min_set%10;
 // Minute Display
    // Minute Digit 2
    data_0(min_dis2);
    clk0_pulse(); 
    // Minute Digit 1
    data_0(min_dis1);
    lat0_pulse();
    return;
}
void process_n_display(int min_input){
    int sec_counter=59;
    unsigned char i=0;
    int min_digit1, min_digit2, sec_digit1, sec_digit2;
    // Counting Operation
    while(min_input>=0){
        // Minute digits
        min_digit1 = min_input/10;
        min_digit2 = min_input%10;
        // Minute Digit 2
        data_0(min_digit2);
        clk0_pulse();   // Because of the missing bit for Q7, there must be a clock pulse for next shift
        // Minute Digit 1
        data_0(min_digit1);
        lat0_pulse();   // Display all second digits
        
        // Second counting down
        while(sec_counter>=0){
            // Second digits
            sec_digit1 = sec_counter/10;
            sec_digit2 = sec_counter%10;
            // Second Digit 2
            data_1(sec_digit2);
            clk1_pulse(); // Because of the missing bit for Q7, there must be a clock pulse for next shift
            // Second Digit 1
            data_1(sec_digit1);
            lat1_pulse(); // Display all second digits
            __delay_ms(150);
            sec_counter-=1; // Re-update for the next lower second
        }
        // Re-update for the next lower minute
        min_input-=1;
        sec_counter=59;
    }
    return;
}
void main(void) {
    // Setting up Ports
    TRISCbits.TRISC0=0; // "0" means output mode
    TRISCbits.TRISC1=0;
    TRISCbits.TRISC2=0;
    TRISCbits.TRISC5=0; 
    TRISCbits.TRISC6=0; 
    TRISCbits.TRISC7=0;
    TRISBbits.TRISB4=1; // "1" means input mode
    TRISBbits.TRISB5=1;
    TRISBbits.TRISB6=1;
    LATC=0;
    ANSELC=0;   // Deselect Analog mode
    ANSELB=0;
    int min_counter=0;  // For minute setting
    int i=0;
    unsigned char start_state=0; // For "START" button states
    
    // Initial state of the clock: "00:00"
    set_clock(min_counter); // Minute display
        // Second display
    // Second Digit 2
    data_1(0);
    clk1_pulse(); 
    // Second Digit 1
    data_1(0);
    lat1_pulse(); // Display all second digits
    
    // Clock Operation
    while(1){
        // Minute Setting: Every time the user presses or holds the button "SET_P", the minute will increase
        // The maximum minute value is 99 minutes
        if(SET_P==1){
            __delay_ms(100);
            if(SET_P==1){
                min_counter+=1;
                if(min_counter>99){
                    min_counter=0;
                }
                set_clock(min_counter);
            }
        }
        // Minute Setting: Every time the user presses or holds the button "SET_S", the minute will decrease
        // The minimum minute value is 0 minute means nothing
        if(SET_S==1){
            __delay_ms(100);
            if(SET_S==1){
                min_counter-=1;
                if(min_counter<0){
                    min_counter=0;
                }
                set_clock(min_counter);
            }
        }
        // Clock starts counting down after the user released the button
        if(START==1&&start_state==0){
            __delay_ms(50); // Debouncing
            if(START==1&&start_state==0){
                start_state=1;
                }
        }
        if(start_state==1&&START==0){
                start_state=2;
                }
        // Start working
        if(start_state==2){
            min_counter-=1;
            process_n_display(min_counter);
            min_counter=0;
            start_state=0;
        }        
    }
    return;
}
