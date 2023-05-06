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
 * 
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

#define MCU_title   "\rMCU: "
#define User_title  "\rUser: "
#define greeting    "Welcome"
#define MCU_guess   "I guess "


unsigned char steps[3] = {5, 2, 1}; // For MCU last steps of guessing


//******* A sequence of Text display *******//
void EUSART_Write_Text(char textData[]){
    
    unsigned int  i       = 0;    // Index counter
    unsigned char endTrig = 0;    // String end trigger
    
    while(endTrig == 0){
        
        // If the program reaches a string end
        if(textData[i] == '\0'){
            
            // Then Trigger up
            endTrig = 1;
            
        }
        
        // If End Trigger is still 0
        if(endTrig != 1){
            
            // Then, continue writing data
            while(EUSART_is_tx_ready()==0);
            EUSART_Write(textData[i]);
             
        }
        
        // And update 'i'
        i++;
        
    }   
}

//******* User waiting *******//
char user_wait(){
    
    char user_res;
    
     // Wait for user to give result //    
    EUSART_Write_Text(User_title);
    
    while(EUSART_is_rx_ready()==0); // Wait for USART reader
    user_res = EUSART_Read();   
    
    return user_res;
    
}

//******* A correct answer from MCU *******//
void correct_guess(unsigned char user_res){
    
    if(user_res == '1'){
        
        EUSART_Write_Text(MCU_title);
        EUSART_Write_Text("Yay, I'm good right?");      
        
        // System dead loop
        while(1);
        
    }
   
    return;
    
}

//******* MCU confused by user *******//
void confuse_guess(){

    EUSART_Write_Text(MCU_title);
    EUSART_Write_Text("MCU is confusing. Invalid game!");
    
    //System dead loop
    while(1);
   
    return;
    
}

/*
                         Main application
 */

void main(void){

    // Initialize the device
    SYSTEM_Initialize();
    
    int init_age  = 0;      // Initial age value
    int age_track = 0;      // Following the main value 'init_age' 
    char age_str[10];       // Storing initial age in form of a string
    
    unsigned char state      = 0;    // For the use of state machine
    unsigned char user_input = 0;    // Storing user's input
    unsigned char i          = 0;    // Last steps indicator
    
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
    
    // Greetings //
    EUSART_Write_Text(MCU_title);  
    EUSART_Write_Text(greeting);
    EUSART_Write_Text(". Let's guess your age\r");         
    
    // First Guess
    init_age = 52;                          // Initial age is 52 as at default
    sprintf(age_str, "%d\r", init_age);
    
    // MCU guessing
    EUSART_Write_Text(MCU_title); 
    EUSART_Write_Text(MCU_guess); 
    EUSART_Write_Text(age_str); 
    
    while (1){
        
        //* Note: User input is 1 means 'Correct', '2' means 'Younger' and '3' means 'Older' *//
        
        if(state==0){
            
            // Wait for user
            user_input = user_wait();
            
            // Update 'state'
            state = 1;
  
        }
        
        //***** State 1 *****//
        
        if(state==1){
            
            // If user answered it's correct, then
            correct_guess(user_input);
            
            // If user replied that he/she is younger
            while((user_input == '2') && (state==1)){
                
                // Then, minus 10 from the initial age
                init_age -= 10;      
                sprintf(age_str, "%d\r", init_age);

                // MCU guessing
                EUSART_Write_Text(MCU_title); 
                EUSART_Write_Text(MCU_guess); 
                EUSART_Write_Text(age_str); 
                
                // Wait for next answer
                user_input = user_wait();
                
                // Check for correct answer
                correct_guess(user_input);
                
                // If user answered that he/she is older
                if(user_input == '3'){
                    
                    // Then, change state
                    age_track = init_age;
                    state = 2;                  
                    
                }
                
            } 
            
            // If user replied that he/she is older
            while((user_input == '3') && (state==1)){
                  
                // Then, add 10 to the initial age
                init_age += 10;      
                sprintf(age_str, "%d\r", init_age);

                // MCU guessing
                EUSART_Write_Text(MCU_title); 
                EUSART_Write_Text(MCU_guess); 
                EUSART_Write_Text(age_str); 
                
                // Wait for next answer
                user_input = user_wait();
                
                // Check for correct answer
                correct_guess(user_input);
                
                // If user answered that he/she is younger
                if(user_input == '2'){
                    
                    // Then, change state
                    age_track = init_age;
                    state = 2;
                    
                }
                
            } 
              
        }
        
        //***** State 2 *****//
        
        if(state == 2){
            
            // If user replied that he/she is older
            while((user_input == '3') && (state==2)){                                
                
                // Then, add step to the age
                init_age += steps[i];
                
                // Check for confusion
                if((init_age == (init_age+10))||(init_age<0)){
                    
                    confuse_guess();
                    state = 4;
                    break;
                    
                }
                
                sprintf(age_str, "%d\r", init_age);

                // MCU guessing
                EUSART_Write_Text(MCU_title); 
                EUSART_Write_Text(MCU_guess); 
                EUSART_Write_Text(age_str); 
                
                // Wait for next answer
                user_input = user_wait();
                
                // Check for correct answer
                correct_guess(user_input);
                
                // If user replied that he/she is younger
                if(user_input == '2'){
                    
                    // Then, change state
                    age_track = init_age;
                    state = 3;
                    
                }
                
                if(i<2){
                    
                    // Update 'i' for next step
                    i++;
                            
                } else{
                    
                    i = 2;
                    
                }    
            }
            
            // If user replied that he/she is younger
            while((user_input == '2') && (state==2)){                                
                
                // Then, minus step from the age
                init_age -= steps[i];
                
                // Check for confusion
                if((init_age ==(init_age-10))||(init_age<0)){
                    
                    confuse_guess();
                    state = 4;
                    break;
                    
                }
                
                sprintf(age_str, "%d\r", init_age);

                // MCU guessing
                EUSART_Write_Text(MCU_title); 
                EUSART_Write_Text(MCU_guess); 
                EUSART_Write_Text(age_str); 
                
                // Wait for next answer
                user_input = user_wait();
                
                // Check for correct answer
                correct_guess(user_input);
                
                // If user replied that he/she is older
                if(user_input == '3'){
                    
                    // Then, change state
                    age_track = init_age;
                    state = 3;
                    
                }
                
                if(i<2){
                    
                    // Update 'i' for next step
                    i++;
                            
                } else{
                    
                    i = 2;
                    
                }    
            }
        }
        
        //***** State 3 *****//
        
        if(state == 3){
            
            // If user replied that he/she is younger
            while((user_input == '2') && (state==3)){
        
                // Then, calculate age
                init_age -= 1;
                
                // Check for confusion
                if((init_age == (age_track-steps[i-1]))||(init_age<0)){
                    
                    confuse_guess();
                    state = 4;
                    break;
                    
                }   
                
                sprintf(age_str, "%d\r", init_age);

                // MCU guessing
                EUSART_Write_Text(MCU_title); 
                EUSART_Write_Text(MCU_guess); 
                EUSART_Write_Text(age_str);
                
                // Wait for next answer
                user_input = user_wait();
                
                // Check for correct answer
                correct_guess(user_input);
     
            }
            
            // If user replied that he/she is older
            while((user_input == '3') && (state==3)){
        
                // Then, calculate age
                init_age += 1;

                // Check for confusion
                if((init_age == (age_track+steps[i-1]))||(init_age<0)){
                    
                    confuse_guess();
                    state = 4;
                    break;
                    
                }              
                
                sprintf(age_str, "%d\r", init_age);

                // MCU guessing
                EUSART_Write_Text(MCU_title); 
                EUSART_Write_Text(MCU_guess); 
                EUSART_Write_Text(age_str);
                
                // Wait for next answer
                user_input = user_wait();
                
                // Check for correct answer
                correct_guess(user_input);
     
            }
        } 
        
    }
}
/**
 End of File
*/