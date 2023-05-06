/**
  Generated Main Source File
 * 
  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F1827
        Driver Version    :  2.00
*/

            // Author Information //
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

#include "mcc_generated_files/mcc.h"

                // Motor Values and System Values Specifying //

    // Motor Variables //
#define Motor_IN1 LATAbits.LATA0
#define Motor_IN2 LATAbits.LATA1
#define Motor_Stop 0
#define Motor_CW   1       // Motor Clockwise
#define Motor_CCW  -1      // Motor Counter Clockwise

    // 74HC595 Variables //
#define CLK_pulse  LATBbits.LATB2
#define DAT_output LATBbits.LATB3
#define LAT_pulse  LATBbits.LATB4

    // Button variables //
#define Button_1   PORTBbits.RB0
#define Button_2   PORTBbits.RB1
#define LED_Indi   LATBbits.LATB5     // Operational Indicator

    // Bits array for 7-segment display //
unsigned char Com_Cathode[6] = {0b1111110, 0b0110000, 0b1101101, 0b1111001, 0b0110011, 0b1011011};

                // Functions //

// Clock pulse //

void clk_pulse(){
    
    CLK_pulse = 1;     // HIGH edge
    CLK_pulse = 0;     // LOW edge
    
    return;
    
}

// Latch pulse //

void lat_pulse(){
    
    LAT_pulse = 1;      // HIGH edge
    LAT_pulse = 0;      // LOW edge
    
    return;
    
}

// Bits shifting and display //

void bit_shift(unsigned char index){
    
    // Variables specifying
    unsigned char i        = 0;          // For using 'for' loop
    unsigned char temp_val = 0;          // For positional bit calculating
    
    // Bits isolating and shifting
    for(i=0; i<7; i++){
        
        // Positional bit calculation
        temp_val = (Com_Cathode[index] & (0x01<<i))>>i;
        
        // If the isolated bit is '1'
        if(temp_val == 1){
            
            // Then, data is set to '1' and shifted to the IC
            DAT_output = 1;
        
        // Else, if the isolated bit is '0'
        } else if(temp_val == 0){
            
            // Then, data is set to '0' and shifted to the IC
            DAT_output = 0;

        }
        
        clk_pulse();

    }
    
    // Display
    lat_pulse();
    
    return;
      
}


// Motor Direction Controlling //

void motor_dir(char dir){
    
    // If the setting is clockwise rotation
    if(dir == Motor_CW){
        
        // Then rotate the motor clockwise
        Motor_IN1 = 1;
        Motor_IN2 = 0;
        
    // If the setting is counter clockwise rotation
    } else if(dir == Motor_CCW){
        
        // Then rotate the motor counter clockwise
        Motor_IN1 = 0;
        Motor_IN2 = 1;
     
    // If the "Stop" is required
    } else if(dir == Motor_Stop){
                
        // Then, stop IN1, IN2
        Motor_IN1 = 0;
        Motor_IN2 = 0;
        
        // and set the PWM to output 0% of Power
        PWM3_LoadDutyValue(0);
        
    }

    return;
}

/*
                         Main application
 */

void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    
    // Clear output latches
    CLK_pulse  = 0;
    DAT_output = 0;
    LAT_pulse  = 0;

    // System status
    unsigned char state       = 0;        // Indicates level of speed
    unsigned char motor_state = 0;        // Indicates whether motor is working or not: '0' = Not working; '1' = Running
    unsigned char temp        = 0;
    
    // Initial state
    PWM3_LoadDutyValue(0);
    bit_shift(0);
    
        // Weak Pull-up Disable
    WPUBbits.WPUB0 = 0;
    WPUBbits.WPUB1 = 0;
    
    
    while(1){
        
//==================// Motor Starting/Stopping //==================//
        
        // If the button 1 is pressed and the motor isn't working
        if((Button_1) == 1&&(motor_state == 0)){
            
            __delay_ms(100); // Debounce
            
            if((Button_1) == 1&&(motor_state == 0)){
                
               // Then, turn system on
                motor_state = 1;
         
            }
            
        }         
        
//==================// Motor works //==================//
        
                     /////////////
                    // Running //
                   /////////////
        
        // If the motor has been started
        if(motor_state == 1){
                        
            // Then, turn on indicator LED
            LED_Indi = 1;
            
                    // Number Displaying //

            // If the button 2 is pressed
            if(Button_2 == 1){
                
                __delay_ms(90); // Debounce
                
                if(Button_2 == 1){
                    
                    // Then, increase the level
                    state+=1;
                    
                }

            }
            
                // If the level setting exceeds the maximum value
            if(state > 5){

                    // Then, reset it back to the lowest
                state = 1;

            } 
            
                // If the 'temp' and the 'state' are truly different
            if(temp != state){
                
                    // Then, update 'temp'
                temp = state;
                
                    //  and display the number
                bit_shift(state);

            }
            
            // If the button 1 is pressed and the motor is working
            if((Button_1 == 1)&&(motor_state == 1)){

                __delay_ms(100); // Debounce

                if((Button_1 == 1)&&(motor_state == 1)){

                    // Then, turn it off
                    motor_state = 0;

                }

            }
            
            
   //==================// Levels setting via States machine //==================//
            
               // Note: The motor rotates clockwise at default //
            
            // If it's set to level 1
            if(state == 1){
                
                // Then, run the motor with 20% duty cycle clockwise
                PWM3_LoadDutyValue(199);
                motor_dir(Motor_CW);


            }
            
            // If it's set to level 2
            if(state == 2){
                
                // Then, run the motor with 40% duty cycle clockwise
                PWM3_LoadDutyValue(399);
                motor_dir(Motor_CW);


            }
            
            // If it's set to level 3
            if(state == 3){
                
                // Then, run the motor with 60% duty cycle clockwise
                PWM3_LoadDutyValue(599);
                motor_dir(Motor_CW);


            }
            
            // If it's set to level 4
            if(state == 4){
                
                // Then, run the motor with 80% duty cycle clockwise
                PWM3_LoadDutyValue(799);
                motor_dir(Motor_CW);


            }
            
             // If it's set to level 5
            if(state == 5){
                
                // Then, run the motor with 100% duty cycle clockwise
                PWM3_LoadDutyValue(999);
                motor_dir(Motor_CW);


            }
            
        }
                    //////////////
                   // Stopping //
                  //////////////
        
        // Else, if the motor has been stopped
        else if(motor_state == 0){
            
            // Then, stop sending pulses
            motor_dir(Motor_Stop);
            
                            
            // and turn off indicator LED
            LED_Indi = 0;
            bit_shift(0);
            
            // and re-update trackers
            motor_state = 0;
            state       = 0;                 
            
        }
    
    }
}
/**
 End of File
*/