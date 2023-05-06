/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F1509
        Driver Version    :  2.00
*/

/*                          AUTHOR'S INFO
 * Full name: Dang Hai Nguyen
 * Student's ID: 20146110
 * Phone number: 0981642324
 * Major: Mechatronics Engineering
*/ 



/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include <stdio.h>
#define TRIGGER  LATCbits.LATC0
#define ECHO     PORTCbits.RC1


/*
                         Main application
 */

void putch(char ch){
    
    EUSART_Write(ch);
  
}



void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    
    // Variables initialize
    float distance_cm = 0;

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    while (1)
    {
        TRIGGER = 1;
        
        __delay_us(10);
        
        TRIGGER = 0;
        
        while(ECHO == 0){  // Wait when Echo is 0
            
            PIR1bits.TMR1IF = 0;    // Reset Timer 1
            
            
        } 
        
        TMR1 = 0;
        
        while(ECHO == 1);  // Wait   
        
        // Distance calculation and display
        distance_cm = (float)TMR1*4/58 - 1.5;
        
        printf("Distance in cm: %f \r", distance_cm);
        
        __delay_ms(500);
        
        
        

    }
}
/**
 End of File
*/