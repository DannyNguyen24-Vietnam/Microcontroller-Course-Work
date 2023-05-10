/*
 * File:   togglestate.c
 * Author: Admin
 *
 * Created on October 15, 2022, 12:17 PM
 */
// PIC16F887 Configuration Bit Settings
// 'C' source line config statements
// CONFIG1
#define _XTAL_FREQ 4000000
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

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
char count=1;
char duty=15;
char val;
void PWMRegist(char duty_val){
    
    val= (PR2+1)*4*((float)duty_val/100);
    CCPR1L= val>>2;
    if((val& 0b00000010)>>1 == 1)
        DC1B1 = 1;
    else{
        DC1B1 = 0;
    }
    if(val& 0b00000001 == 1)
        DC1B0 = 1;
    else{
        DC1B0 = 0;
    }

    return;
}
void main(void) {
    // Initialize
        // OSC
    IRCF2= 1;
    IRCF1= 1;
    IRCF0= 0;
    SCS= 1;
       // CCPx
    TRISC2= 0;  // CCP1
    TRISB0= 1;
    ANS12= 0;
    WPUB0= 0;
    PR2= 16;
    CCP1CON= 0b00001100;
    CCPR1L = 0b00000010;
    DC1B1= 1;
    DC1B0= 0;
      // Timer 2
    T2CKPS1= 0;
    T2CKPS0= 1;
    TMR2ON= 1;
      // Interrupt
    INTF= 0;
    INTE= 1;
    INTEDG= 0;
    GIE= 1;
    while(1){
        
    } 
    return;
}

void __interrupt() ISR(void){  
    if(INTF){
        count+=1;       
        if(count==7){
            PWMRegist(15);
            count= 1;
        }
        else{
            duty= 15*count;
            PWMRegist(duty);
        }
        INTF= 0;
    }
}