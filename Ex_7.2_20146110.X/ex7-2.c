/*
 * File:   ex7-2.c
 * Author: NGUYEN HAI DANG
 * Major: Mechatronics Engineering
 * Nationality: Vietnam
 * Created on April 20, 2022, 11:40 PM
 */

  /////////////////////////
 // Libraries Inclusion //
/////////////////////////

#define _XTAL_FREQ 1000000
#include <xc.h>
#include "16F887_config.h"
#include <math.h>
#include <stdio.h>
#include "lcd.h"

  //////////////////
 //  LM35 value  //
//////////////////

unsigned int lm35_value(){
    
    // Variables Definition   
    unsigned int lm_val = 0; // For LM35 resultant decimal level value
      
    // The resultant decimal level
    lm_val = ADRESH*pow(2,8) + ADRESL;
    
    return lm_val;
    
}

  ////////////////////////////////
 // Pins and Values Definition //
////////////////////////////////

void main(void) {
    
      ////////////////////
     // Values Setting //
    ////////////////////
    
    unsigned int temp_val      = 0; // Storing integer part of temperature value
    unsigned int decimal_part  = 0; // Storing decimal part of temperature value
    unsigned int comp_val      = 0; // Comparing the present value and input value
    char         temp_string[20];   // A string to display
    
      //////////////////
     // Pins Setting //
    //////////////////
    
       // Output Ports
    PORTC = 0;          // Clear output latches
    TRISC = 0b00000000; // Output mode
    
      // LCD initializing
    LCD_Initialize();
    
      // "Test my PIC"
        // Uncomment these lines and a sequence of code named "Test my PIC" below to test
    
    TRISD = 0b00000000; // Output mode
    PORTD = 0;          // Clear output latches
    TRISB = 0;          // Output mode
    PORTB = 0;          // Clear output latches
    
       // Input Port
    TRISAbits.TRISA0 = 1; // "Input" mode
 
      ////////////////////////////
     // A/D Control Register 0 //
    ////////////////////////////
    
        // bit 7-6 = 10 = Fosc/32
            // bit 5-2 = 0010 = AN2 (AN) selected)
                // bit 1 = GO/DONE = 0 (Not in progress)
                    // bit 0 = ADON = 1 (Enabled)
    ADCON0 = 0b10000001;
    
      ////////////////////////////
     // A/D Control Register 1 //
    ////////////////////////////
    
        // bit 7 = Result Formatting = 1 (Right justified)
            // bit 6 = 0 = Unimplemented
                // bit 5 = Voltage reference = 0 (Vss)
                    // bit 4 = Voltage reference = 1 (Vref+)
                        // bit 3-0 = 0 = Unimplemented
    ADCON1 = 0b10010000;
    
        // Wait for Tacq
    __delay_ms(80);
    
 /*     /////////////////
     // Test my PIC //
    /////////////////
    
        //~Note: Remember to disable your main operation inside the infinite loop before testing~// 
        // Start reading
    ADCON0bits.GO_DONE = 1;       
    while(ADCON0bits.GO_DONE == 1); // Keep waiting as the uncompleted conversion
    
       // Output display on PORT D and B ~ Use this display to define the ADC read by the PIC
    PORTB = ADRESH;
    PORTD = ADRESL;
    
        // Temperature Calculating
            // Integer part
    temp_val = lm35_value()*0.1733;
    
            // Decimal part ~ Only 1 digits behind the point
    decimal_part = (lm35_value()*0.1733 - (int)(lm35_value()*0.1733))*10; 
    
            // Put all into a string
    sprintf(temp_string, "Temp= %u.%u C", temp_val, decimal_part);
   
      ///////////////////////////
     // Name and Temp display //
    ///////////////////////////
    
        // Temperature
    LCDGoto(0, 1);
    LCDPutStr(temp_string);*/
        
        // Name
    LCDGoto(0, 0);
    LCDPutStr("DANG 20146110");

      ////////////////////
     // Main Operation //
    ////////////////////
    
    while(1){
        
        // Start reading
    ADCON0bits.GO_DONE = 1;
    
    while(ADCON0bits.GO_DONE == 1); // Keep waiting as the uncompleted conversion
    
         // Temperature Calculating
            // Integer part
    temp_val = lm35_value()*0.1465;
    
        // Decimal part ~ Only 1 digits behind the point
    decimal_part = (lm35_value()*0.1465 - (int)(lm35_value()*0.1465))*10;
    
        // For checking
    PORTB = ADRESH;
    PORTD = ADRESL;
    
        // Put all into a string
    sprintf(temp_string, "Temp= %u.%u C", temp_val, decimal_part);
    
            // Display emperature
    LCDGoto(0, 1);
    LCDPutStr(temp_string);
    
    
    
    __delay_ms(300);
    
    }
    return;
}



