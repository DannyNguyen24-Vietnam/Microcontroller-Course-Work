/*
 * File:   ex7-1.c
 * Author: NGUYEN HAI DANG
 * Major: Mechatronics Engineering
 * Nationality: Vietnam
 * Created on April 16, 2022, 9:43 PM
 */

  /////////////////////////
 // Libraries Inclusion //
/////////////////////////

#include "16F887_config.h"
#include <xc.h>
#include <math.h>

  ////////////////////////////////
 // Pins and Values Definition //
////////////////////////////////

    // Pin definitions
#define _XTAL_FREQ 1000000
#define CLK  PORTDbits.RD0
#define DATA PORTDbits.RD1
#define LAT  PORTDbits.RD2
#define SET  PORTDbits.RD3

    // Value definitions
        // For Common Cathode 7-seg displays
unsigned char Com_Ca[10] = {0b1111110, 0b0110000, 0b1101101, 0b1111001, 0b0110011,
                            0b1011011, 0b1011111, 0b1110000, 0b1111111, 0b1111011};

  /////////////////////////////
 // Clock Pulses Generating //
/////////////////////////////

void clk_pulse(){
    
    // This function generates clock pulses for bits shifting
    CLK = 1;
    CLK = 0;
    
    return;   
    
}

  /////////////////////////////
 // Latch Pulses Generating //
/////////////////////////////

void lat_pulse(){
    
    // This function latches out bits for 74HC595
    LAT = 1;
    LAT = 0;
    
    return; 
    
}

  /////////////////
 //  POT value  //
/////////////////

int pot_value(){
    
    // Variables Definition   
    int pot_low    = 0; // For Pot level's lower significant digits
    int pot_high   = 0; // For Pot level's higher significant digits
    int pot_level  = 0; // For Pot resultant decimal level value
    
    int adres_high = 0; // Store higher bits from ADC
    int adres_low  = 0; // Store lower bits from ADC
    
    // Start converting
    ADCON0bits.GO_DONE = 1;
        
    while(ADCON0bits.GO_DONE == 1); // Keep waiting as the uncompleted conversion
        
    // Turn a binary number to an integer
    
    adres_high = ADRESH;
    adres_low  = ADRESL;
       
    // The resultant decimal level
    pot_level = adres_high * pow(2, 8) + adres_low;
    
    return pot_level;
    
}

  /////////////////////
 //  Bits shifting  //
/////////////////////

void bit_shift(int counter){
    
     // Variables Definition
        // Following this formula: counter = digit_1*10 + digit_2
    int digit_1     = 0; 
    int digit_2     = 0;
    unsigned char i = 0;
    
    // Main Operation
    digit_1 = counter/10;
    digit_2 = counter%10;
    
    // Digit 2's bits shifting
    for(i=0;i<7;i++){
        
        // If chosen bit is 1
        if(((Com_Ca[digit_2]&(0b0000001<<i))>>i)==1){
            
            // Then Data is set to HIGH
            DATA = 1;
        
        } else{
            
            // Else, Data is set to LOW
            DATA = 0;         
            
        }
        
        // and shifted next
        clk_pulse();
    
    }
    
    // Due to the missing bit for Q7, there must be a spare pulse
    clk_pulse();
    
    
    // Digit 1's bits shifting
        // Re-update i for the next turn
    i = 0;

    for(i=0;i<7;i++){
        
        // If chosen bit is 1
        if(((Com_Ca[digit_1]&(0b0000001<<i))>>i)==1){
            
            // Then Data is set to HIGH
            DATA = 1;
            
        } else{
            
            // Else, Data is set to LOW
            DATA = 0;
            
        }
        
        // and shifted next 
        clk_pulse();    
    
    }
    
    return;
}

  ////////////////////
 //  Main function //
////////////////////

void main(void) {
    
      ////////////////////
     // Values Setting //
    ////////////////////
    
        // Counters
    unsigned char state       = 0; // For states
    unsigned int min_counter  = 0; // For tracking minute value
    unsigned int sec_counter  = 0; // For tracking second value
    unsigned int min_limit    = 0; // For time counting
    unsigned int sec_limit    = 0; // For time counting
    unsigned int pot_levelval = 0; // POT level value
    unsigned int temp_min     = 0; // For storing purposes
    unsigned int temp_sec     = 0;
    
      //////////////////
     // Pins Setting //
    //////////////////
    
       // Output Ports
    TRISD = 0b00001000; // RD3 is input mode and the others are output
    PORTD = 0;          // Clear output latches
    // TRISE = 0;          // Uncomment this line and a sequence of code named "Test my PIC" to test
    
       // Input Port
    TRISAbits.TRISA0 = 1; // "Input" mode
    
      ////////////////////////////
     // A/D Control Register 0 //
    ////////////////////////////
    
        // bit 7-6 = 10 = Fosc/32
            // bit 5-2 = 0000 = AN0 (AN) selected)
                // bit 1 = GO/DONE = 0 (Not in progress)
                    // bit 0 = ADON = 1 (Enabled)
    ADCON0 = 0b10000001;
    
      ////////////////////////////
     // A/D Control Register 1 //
    ////////////////////////////
    
        // bit 7 = Result Formatting = 1 (Right justified)
            // bit 6 = 0 = Unimplemented
                // bit 5 = Voltage reference = 0 (Vss)
                    // bit 4 = Voltage reference = 0 (Vdd)
                        // bit 3-0 = 0 = Unimplemented
    ADCON1 = 0b10000001;
    
        // Wait for Tacq
    __delay_ms(80);
    
      /////////////////
     // Test my PIC //
    /////////////////
    
    //~Note: Remember to disable your main operation inside the infinite loop before testing~//
    
     // Try this //
    /* 48% of a 5K Potentiometer connected to 5V has its output is 2.4V
       By using 2.4/5*1024, we have 491 levels, which is 0111101011 */
/*   
    // Start converting
    ADCON0bits.GO_DONE = 1;
    
    while(ADCON0bits.GO_DONE == 1); // Keep waiting as the uncompleted conversion
    
    // Output display on PORT D and E
    PORTD = ADRESL;
    PORTE = ADRESH;
*/
    
      /////////////////////
     //  Initial State  //
    /////////////////////
    
        // Set clock pulse to low trigger edge
    CLK = 0;
    
        // 00:00 display
    if(state==0){
        
        // Light up D1
        PORTDbits.RD4 = 1;
        
        // Second digits
        bit_shift(0);
        clk_pulse();
        
        // Minute digits
        bit_shift(0);
        lat_pulse();
        
    }
       
      ////////////////////////
     //  Timing Operation  //
    ////////////////////////
    
    while(1){

         //////////////
        //  States  //
       //////////////
        
        // If initial state is 0 with a HIGH input
        if((state==0)&&(SET==1)){
            
            // Turn to state 1
            state = 1;
            
        }
        // If state 1 with a LOW input
        if((state==1)&&(SET==0)){
            
            // Turn to state 1
            state = 2;
            
        }
        // If state 2 with a HIGH input
        if((state==2)&&(SET==1)){
            
            // Turn to state 3
            state = 3;
            
        }
        // If state 3 with a LOW input
        if((state==3)&&(SET==0)){
            
            // Turn to state 4
            state = 4;
            
        }
        // If state 4 with a HIGH input
        if((state==4)&&(SET==1)){
            
            // Turn to state 5
            state = 5;
            
        }
        // If state 5 with a LOW input
        if((state==5)&&(SET==0)){
            
            // Turn to the last one - state 6
            state = 6;
            
        }
        
        // If 0th state
        if(state==0){
            
            // Light up D1
            PORTDbits.RD7 = 0;
            PORTDbits.RD4 = 1;
        
            // Display user prior settings or initial state of timer
                // Second digits
            bit_shift(sec_limit);
            clk_pulse();
        
                // Minute digits
            bit_shift(min_limit);
            lat_pulse();
            
        }
        
          //////////////////////
         //  Minute setting  //
        //////////////////////          
        
            // If 2nd state
        if(state==2){
            
            // Light up D2
            PORTDbits.RD4 = 0;
            PORTDbits.RD5 = 1;
            
            // Minute Calculating
            pot_levelval = pot_value();
            
            // Using while to avoid the program not to run the display several times even the value hasn't changed
                // While temporary value and main value are different
            while(temp_min != pot_levelval){
                
                // Re-update temporary value
                temp_min = pot_levelval;
                
                // Calculate the minute value
                min_counter = (pot_levelval*60)/1024;   
            
                // Shift and Display
                bit_shift(sec_counter);
                clk_pulse();
            
                bit_shift(min_counter);               
                lat_pulse();
                
            }
        }
        
          //////////////////////
         //  Second setting  //
        //////////////////////
        
        // If 3rd state
        if(state==4){
            
            // Light up D3
            PORTDbits.RD5 = 0;
            PORTDbits.RD6 = 1;
            
            // Second Calculating            
            pot_levelval = pot_value();
            
            // Using while to avoid the program not to run the display several times even the value hasn't changed
                // While temporary value and main value are different
            while(temp_sec != pot_levelval){
                
                // Re-update temporary value
                temp_sec = pot_levelval;
                
                sec_counter = (pot_levelval*60)/1024;
            
                // Shift and Display
                bit_shift(sec_counter);
                clk_pulse();
            
                bit_shift(min_counter);
                lat_pulse();
                
            }
        }
        
          /////////////////////
         //  Time counting  //
        /////////////////////
        
        // If 6th state
        if(state==6){
            
            // Light up D4
            PORTDbits.RD6 = 0;
            PORTDbits.RD7 = 1;
            
            // Re-update
            state     = 0;
            min_limit = min_counter;
            sec_limit = sec_counter;
            
            // Re-update minute and second counter for time counting (no more setting)
            min_counter = 0;
            sec_counter = 0;
            
            // Display 00:00 before counting up
            
                // Second digits
            bit_shift(0);
            clk_pulse();
        
                // Minute digits
            bit_shift(0);
            lat_pulse();
            
            // Time counting
            
                // While minute value is less than or equal to minute limitation
            while(min_counter <= min_limit){
                
                // Continue counting
                    // If minute counter is equal to its limitation
                if(min_counter == min_limit){
                    
                        // Then the second counter only needs to reach its limitation
                    for(sec_counter=0; sec_counter<=sec_limit; sec_counter++){
                        
                        // Second digits
                        bit_shift(sec_counter);
                        clk_pulse();
                    
                        // Minute digits
                        bit_shift(min_counter);
                        lat_pulse();
                        
                        __delay_ms(50);
                        
                    }
                    
                        // Re-update to get out of loop
                    min_counter = min_limit+1;
                    
                    
                    // Else, the second counter must reach 59th second for the next minute counter value
                } else{
                    
                    for(sec_counter=0; sec_counter<=59; sec_counter++){
                        
                        // Second digits
                         bit_shift(sec_counter);
                        clk_pulse();
                    
                        // Minute digits
                        bit_shift(min_counter);
                        lat_pulse();
                        
                        __delay_ms(50);
                        
                    }
                    
                        // Re-update for the next counting state
                    min_counter += 1;
                    sec_counter =  0;
                
                }                   
            }
            
            // Display user's prior settings and end up the counting
            min_counter = min_limit;
            sec_counter = sec_limit;
            
        }        
    }
    
    return;
}
