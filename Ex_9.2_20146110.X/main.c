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

            // Author Information //
// Full name: NGUYEN HAI DANG
// Major: Mechatronics Engineering
// Phone number: 0981642324
// Private email: nguyenhaidangvietnam@gmail.com            // Author Information //
// Full name: NGUYEN HAI DANG
// Major: Mechatronics Engineering
// Phone number: 0981642324
// Private email: nguyenhaidangvietnam@gmail.com

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

                //====         Libraries in use         ====//

#include "mcc_generated_files/mcc.h"
#include "lcd.h"
#include <stdio.h>


                //====         Main application         ====//
 
void main(void){
    
    // Initialize the device //
    SYSTEM_Initialize();
    LCD_Initialize();
    
        // Timer Initializing
    TMR0 = 0;
    
    // Variables in use //
    unsigned int num_of_revs = 0;     // Storing number of counted revolutions
    unsigned int speed_rpm   = 0;     // Storing speed in RPM (Round per Minute)
    char         revs_Str[10]   ;     // Storing display string of number of revolutions
    char         speed_Str[10]  ;     // Storing display string of Speed in RPM
    //char         timer0_Str[10] ;     // Storing display string of Timer (Uncomment to use for checking Timer 0 value)
    
    
    // Titles display //
    LCDPutStr2("N.O REVS: ", 0, 0);
    LCDPutStr2("SPEED RPM: ", 0, 1);

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
    
    while (1){

        //===     Revolutions Counting (For only 1 Functionality works)    ===//
        
        // If there are 24 counted pulses
//        if(TMR0 == 24){
//            
//            // Then:
//            
//                // Increase 1 revolution
//                num_of_revs += 1;
//                
//                // And String process
//                sprintf(revs_Str, "%u", num_of_revs);
//                LCDPutStr2(revs_Str, 11, 0);
//            
//        }
        
        //===     Speed Calculation     ===//
        
        // For 1s of pulses counting
        __delay_ms(1000);
             
        // Speed Calculation
        speed_rpm = (float)((TMR0*60)/24);
        
        // Increase 1 revolution
        num_of_revs = num_of_revs + (float)(TMR0/24);

        // And String process
        sprintf(revs_Str, "%u", num_of_revs);
        LCDPutStr2(revs_Str, 10, 0);
    
        // String Process and Display
        sprintf(speed_Str, "%u", speed_rpm);
        LCDPutStr2(speed_Str, 11, 1);

        // Reset the Timer 0
        TMR0 = 0;
  
    }
}

/**
 End of File
*/