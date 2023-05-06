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
#include "lcd.h"

                // Motor Values and System Values Specifying //

    // Motor Variables //
#define Motor_IN1  LATCbits.LATC3
#define Motor_IN2  LATCbits.LATC4
#define Motor_Stop 0
#define Motor_CW   1      // Motor Clockwise
#define Motor_CCW  2      // Motor Counter Clockwise

    // Button and LED variables //
#define Button_1   PORTCbits.RC5
#define Button_2   PORTCbits.RC6

 //////=========== Functions in use =========== //////

// Motor Direction Controlling //

void motor_dir(char dir){
    
    // If the setting is clockwise rotation
    if(dir == Motor_CW){
        
        // Then rotate the motor clockwise
        Motor_IN1 = 1;
        Motor_IN2 = 0;

    }
    
    // If the setting is counter clockwise rotation    
    if(dir == Motor_CCW){
          
        // Then rotate the motor counter clockwise
        Motor_IN1 = 0;
        Motor_IN2 = 1;
     
    }
    
    // If the "Stop" is required
    if(dir == Motor_Stop){
                
        // Then, stop IN1, IN2
        Motor_IN1 = 0;
        Motor_IN2 = 0;
        
        // and set the PWM to output 0% of Power
        PWM3_LoadDutyValue(0);
        
    }

    return;
    
}


 //////=========== Main application =========== //////

void main(void){
    
    // Initialize the device
    SYSTEM_Initialize();
    LCD_Initialize()   ;
        
    // System status
    unsigned char motor_state = 0;   // Indicates whether motor is working or not: '0' = Not working; '1' = Running
    unsigned char state_temp  = 1;   // Checking state changes corresponding to 'motor_state'
    
    int           motor_direc = 1;   // Indicates whether motor is working on which direction: '1' = CW; '0' = CCW
    int           direc_temp  = 0;   // Checking changes
    
    int  adc_read    = 0;   // Storing ADC value read from AN0
    
    int  pwm_value   = 0;   // PWM value here
    int  pwm_temp    = 0;   // PWM temporary value
    char pwm_string[20] ;
    
    int  duty_cycle  = 0;  // Duty Cycle value
    char duty_string[20];  // Duty Cycle display string
    
    // Initial state
    PWM3_LoadDutyValue(0);
    
        // Duty Cycle Display //
    LCDPutStr2("Duty Cycle: ", 1, 0);
    
        // PWM and Direction Display
    LCDPutStr2("PWM: ", 0, 1);
    LCDPutStr2("DR: ", 9, 1);

    while (1){
        
        //==================// Motor Starting //==================//
        
        // If the button 1 is pressed and the motor isn't working
        if((motor_state == 0)&&(Button_1 == 1)){
            
            __delay_ms(90); // Debounce
            
            if((motor_state == 0)&&(Button_1 == 1)){
                
               // Then, turn system on
                motor_state = 1;
         
            }
            
        }
                
        //==================// Motor works //==================//

        // If the motor has been started
        if(motor_state == 1){
            
              // Re-update state change
              state_temp = 1;
               
              // Then, read ADC value
                  // Start converting
              ADC_StartConversion();
              
                  // Get result
              adc_read = ADC_GetConversionResult();
              
              // Turn it into PWM value and Duty Cycle value
                  pwm_value =  adc_read * 0.976563;
                  
                  duty_cycle = pwm_value * 0.1 + 1;
    
              // If PWM result smaller than 199
              if(pwm_value < 199){
        
                    // Then, it's set to 0
                  pwm_value = 0;
                
                }
      
              // If the PWM_value has truly changed,
              if(pwm_temp != pwm_value){
                
                   // Then, re-update 'pwm_temp', put value into a string
                   pwm_temp = pwm_value;
                   sprintf(pwm_string, "%u", pwm_value);
                
                   sprintf(duty_string, "%u %%", duty_cycle);
                    
                   // and display it on LCD
                   LCDPutStr2(pwm_string, 5, 1);
                    
                   LCDPutStr2(duty_string, 13, 0);
                   
                   // Set/Reset motor speed                               
                        // * Read Note [2] in the end of this file for further info *//
                   PWM3_LoadDutyValue(pwm_value);       // Note [2]
                   
              }
    //================== Motor Rotation ==================// 
                  
            // Note: The motor rotates clockwise at default //

                // If the button 2 is pressed
                if((motor_direc == 1)&&(Button_2 == 1)){

                    __delay_ms(90); // Debounce

                    if((motor_direc == 1)&&(Button_2 == 1)){

                        // Then, change the rotational direction of the motor
                        motor_direc = 0;

                    }
                }

                // If the motor direction has truly changed  
                  // * Read Note [1] in the end of this file for further info *//
                if(motor_direc != direc_temp){

                    // If the motor direction is 1, it means "clockwise"
                    if(motor_direc == 1){

                        // Re-update direc_temp
                        direc_temp = 1;

                        // Then, LCD display
                        LCDPutStr2("    ", 12, 1);
                        LCDPutStr2(" CW", 12, 1);

                        // Set motor speed and run
                        PWM3_LoadDutyValue(pwm_value);

                        motor_dir(Motor_CW);

                    }

                    // If the motor direction is 0, it means "counter clockwise"  
                    if(motor_direc == 0){

                        // Re-update direc_temp
                        direc_temp = 0;

                        // Then, LCD display
                        LCDPutStr2("    ", 12, 1);
                        LCDPutStr2(" CCW", 12, 1);

                        // Set motor speed and run
                        motor_dir(Motor_CCW);
                        PWM3_LoadDutyValue(pwm_value);

                    }
                }

                // If the button 2 is pressed
                if((motor_direc == 0)&&(Button_2 == 1)){

                    __delay_ms(90); // Debounce

                    if((motor_direc == 0)&&(Button_2 == 1)){

                        // Then, change the rotational direction of the motor
                        motor_direc = 1;

                    }
                }         

            }

            // If the button 1 is pressed and the motor is working
            if((motor_state == 1)&&(Button_1 == 1)){

                __delay_ms(90); // Debounce

                if((motor_state == 1)&&(Button_1 == 1)){

                   // Then, turn system off
                    motor_state = 0;

                }

        }
        
        // State changed
        if(motor_state != state_temp){
            
            // Turning
            if(motor_state == 0){
                
                // Re-update 'state_temp'
                state_temp = 0;
                
                motor_dir(Motor_Stop);


                // Re-update variables
                motor_state = 0;
                motor_direc = 1; 

                adc_read    = 0;

                pwm_value   = 0;
                pwm_temp    = 0; 

                duty_cycle  = 0;

                // Duty Cycle Display // 
                LCDPutStr2("Duty Cycle:   ", 1, 0);

                // PWM and Direction Display //
                LCDPutStr2("PWM:    ", 0, 1);
                LCDPutStr2("DR:    ", 9, 1);
            
            }
        }
    }
}

/**
 End of File
*/

//************* Notes *************//

// Note [1] //
/* 
 * This condition is to avoid the program executing the LCD displays and motor settings multiple times.
 * But one shortage is that if we set the direction to clock wise and the 'direc_temp' has also been updated,
 * the code below won't be executed, so the new speed won't be updated to run it
 
 */

// Note [2] //
/*
 * This setting is to solve the Note [1] problem of speed changing
 */