/*
 * File:   baitap1.c
 * Author: Admin
 *
 * Created on October 10, 2022, 7:32 AM
 */
// PIC16F887 Configuration Bit Settings
// 'C' source line config statements
// CONFIG1
#define _XTAL_FREQ 20000000
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
char rxdata;
unsigned int dem;

void sendchar (char c);
void sendstring (const char* s);
void tx_init();
void rx_init();

char buffer[6];
char ptr;

unsigned int counter = 0;   // Number of overflow times
unsigned int counter1 = 0;
unsigned int value   = 0;   // Number of pulses
char str_pulse[30];
char str_speed[30];
int rot_speed1 = 0;
int rot_speed2 = 0;

void main(void) {
    // Initialize
    tx_init();
    rx_init();
       // Ports
    ANSEL = ANSELH = 0;     // No use of Analog mode
    TRISAbits.TRISA4 = 1;   // Input mode
        // Timer 0
    TMR0                = 0;        // Initial Timer 0 value
    OPTION_REGbits.T0CS = 1;        // Counter mode
    OPTION_REGbits.T0SE = 0;        // High Trigger Edge count
        // Timer 1
    T1CONbits.TMR1GE = 0;
    T1CONbits.TMR1CS = 0;
    T1CONbits.T1CKPS = 0b00;    // 1:1
    TMR1 = 15535;
    T1CONbits.TMR1ON = 1;
        // Interrupt
    INTCONbits.T0IF = 0;    // Clear Interrupt Flag
    INTCONbits.T0IE = 1;    // Enable Timer 0 Interrupt
    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE  = 1;    // Global Interrupt Enable
    while(1){
        if(counter1==200){
            value = (counter*256 + TMR0);       
            rot_speed1 = (15*value)/187;  // Digit 1 (374 CPR)
            rot_speed2 = ((float)((15*value)/187) - rot_speed1)*100;
            sprintf(str_pulse, "PPS: %03d\n", value/2);
            if(rot_speed2>9){
                sprintf(str_speed, "RPM: %d.%2d\n", rot_speed1,rot_speed2);
            }
            else{
                sprintf(str_speed, "RPM: %d.%02d\n", rot_speed1,rot_speed2);
            }
            sendstring(str_pulse);
            sendstring(str_speed);
        }
    }
    return;
}

void sendchar (char c){		
	while (TXIF==0){}
	TXREG = c;
}

void sendstring (const char* s){
	while(*s){
		sendchar(*s++);
	}
}
void tx_init(){
	SPBRGH =0x02;
	SPBRG = 0x08;	
	BRGH=1;
	BRG16= 1;
	
	SYNC=0;
	SPEN=1;
	
	TX9=0;
	
	TXEN=1;
}
void rx_init(){

	SPBRGH =0x02;  // calculate --> 520 <-> br:9600
	SPBRG = 0x08;	
	BRGH=1;
	BRG16= 1;
	
	SYNC=0;
	SPEN=1;
	
	RCIF=0;
	RCIE=1;
	PEIE=1;
	GIE=1;
	
	RX9=0;
	
	CREN=1;	
}

void __interrupt() ISR(void){
	if( RCIE && RCIF)
	{
        rxdata=RCREG;
	}   
	//// kiem tra loi
	if( OERR==1)
	{
	  CREN=0;/// de xoa loi
	  CREN=1;/// cho hoat dong lai		
	}
    if(INTCONbits.T0IF){
        counter +=1 ;
        TMR0 = 0;
        INTCONbits.T0IF = 0;    // Clear flag
    }
    if(PIR1bits.TMR1IF){
        counter1+=1;
        if(counter1>200){
            TMR0 = 0;
            counter  = 0;
            counter1 = 0;
        }
        TMR1 = 15537;
        PIR1bits.TMR1IF = 0;
    }
 RCIF=0;
}
