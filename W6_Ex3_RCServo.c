/*
 * File:   rcservo.c
 * Author: Admin
 *
 * Created on October 15, 2022, 3:21 PM
 */
// PIC16F887 Configuration Bit Settings
// 'C' source line config statements
// CONFIG1
#define _XTAL_FREQ 250000
#pragma config FOSC = INTRC_CLKOUT// Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
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
int ADC_val    = 0;
float result_out = 0;
float temp_res = 0;
//char temp;
void PWMRegist(float ang_percent){
    float val;
    val = 15.60*ang_percent + 15.60;
    //temp = val;
    CCPR1L= (char)val>>2;
    if(((char)val& 0b00000010)>>1 == 1)
        DC1B1 = 1;
    else{
        DC1B1 = 0;
    }
    if((char)val& 0b00000001 == 1)
        DC1B0 = 1;
    else{
        DC1B0 = 0;
    }

    return;
}

void main(void) {
    // Initialize
        // Osc
    IRCF2= 0;   // 250kHz
    IRCF1= 1;
    IRCF0= 0;
    SCS= 1;
        // Timer 2
    T2CKPS0= 1;
    T2CKPS1= 1; // Prescale 1:16
    TMR2IF= 0;
        // PWM
    CCP1CON= 0b00001100;
    PR2 = 77;
    DC1B0= 0;
    DC1B1= 0;
    TRISC2= 0;
    TMR2ON= 1;
        // ADC Converter
    ADCS1 = 1;
    ADCS0 = 0;
    VCFG0 = 0;   // Internal Vdd Reference
    VCFG1 = 0;   // Vss = GND
    CHS3  = 0;
    CHS2  = 0;
    CHS1  = 0;
    CHS0  = 1;
    ADFM  = 1;   // Right Justified Result
    ADON  = 1;   // Enable ADC module
        // Interrupt
    ANS12= 0;
    TRISB0= 1;
    TRISA1= 1;
    ANS1= 1;
    WPUB0= 0;
    INTEDG= 0;
    INTF= 0;
    INTE= 1;
    GIE= 1;
    GO_DONE = 1; // Start Converting
    while(1){
        __delay_ms(5);
		while(GO_DONE==1){
            // Wait
        }
        // Read Data value
        ADC_val   = ADRESH*256 + ADRESL;	
        result_out= (float)ADC_val/1023.00; // Duty cycle
        if(temp_res!=result_out){
            PWMRegist(result_out);
            temp_res = result_out;
        }
        ADCON0bits.GO_DONE=1;
 
    }
    return;
}
void __interrupt() ISR(void){
//    if(INTF){
//        count+=1;
//        if(count==4){
//            count=1;
//        }
//        if(count==3){
//            PWMRegist(10);
//        }
//        if(count==2){
//            PWMRegist(7.5);
//        }
//        if(count==1){
//            PWMRegist(5);
//        }
//    }
//    INTF= 0;
}