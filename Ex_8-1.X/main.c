/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementation on for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F1509
        Driver Version    :  2.00
    /////////////////
   // Author info //
  ///////////////// 

 * Full name: NGUYEN HAI DANG
 * Major: Mechatronics Engineering
 * Email: dannynguyen2710@gmail.com
 * Phone number: 0981642324
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your respturns onibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP 'AS IS'. NO WARRANTIES, WHETHER 
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
                            /////////////////////////
                           // MCC Generated Files //
                          /////////////////////////

#include "mcc_generated_files/mcc.h"

// Store data
unsigned char CMD[10] = {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0};

/*                      ////////////////////////
                       //  Main application  //
                      ////////////////////////
 */

void LEDs_on(){
    
         ///////////////////
        // LED turning on//
       ///////////////////
         
        // If the command string is 'ON0X#' (X is a particular integer from 1 to 8), then
        
            // LED 01 turns on
        if((CMD[0]=='O')&&(CMD[1]=='N')&&(CMD[2]=='0')&&(CMD[3]=='1')&&(CMD[4]=='#')){
            LATCbits.LATC0 = 1;
        }
        
            // LED 02 turns on
        if((CMD[0]=='O')&&(CMD[1]=='N')&&(CMD[2]=='0')&&(CMD[3]=='2')&&(CMD[4]=='#')){
            LATCbits.LATC1 = 1;
        }
        
            // LED 03 turns on
        if((CMD[0]=='O')&&(CMD[1]=='N')&&(CMD[2]=='0')&&(CMD[3]=='3')&&(CMD[4]=='#')){
            LATCbits.LATC2 = 1;
        }
        
            // LED 04 turns on
        if((CMD[0]=='O')&&(CMD[1]=='N')&&(CMD[2]=='0')&&(CMD[3]=='4')&&(CMD[4]=='#')){
            LATCbits.LATC3 = 1;
        }
        
            // LED 05 turns on
        if((CMD[0]=='O')&&(CMD[1]=='N')&&(CMD[2]=='0')&&(CMD[3]=='5')&&(CMD[4]=='#')){
            LATCbits.LATC4 = 1;
        }
        
            // LED 06 turns on
        if((CMD[0]=='O')&&(CMD[1]=='N')&&(CMD[2]=='0')&&(CMD[3]=='6')&&(CMD[4]=='#')){
            LATCbits.LATC5 = 1;
        }
        
            // LED 07 turns on
        if((CMD[0]=='O')&&(CMD[1]=='N')&&(CMD[2]=='0')&&(CMD[3]=='7')&&(CMD[4]=='#')){
            LATCbits.LATC6 = 1;
        }
        
            // LED 08 turns on
        if((CMD[0]=='O')&&(CMD[1]=='N')&&(CMD[2]=='0')&&(CMD[3]=='8')&&(CMD[4]=='#')){
            LATCbits.LATC7 = 1;
        }
        
        // If the command string is 'ON*#', then
            // All LEDs on
        if((CMD[0]=='O')&&(CMD[1]=='N')&&(CMD[2]=='*')&&(CMD[3]=='#')){
            LATC = 0xFF;
        }
        
}

void USART_read(){
       
       int  i = 0;
       
       for(i=0; i<9; i++){
           
           CMD[i] = 0;
             
       }

       i = 0;
       
       for(i=0; i<8; i++){

            //while(EUSART_is_rx_ready()==0); // Wait for signal
            CMD[i] = EUSART_Read();         // EUSART reading

            // If command string is 'ON0X#' (X is a number from 1 to 8)
            if(CMD[4] == '#'){

                // The last elements will be assigned with 0 and the loop will stop
                CMD[5] = 0;
                CMD[6] = 0;
                CMD[7] = 0;

                return;
            }

            // If command string is 'ON*#'
            if((CMD[2] == '*')&&(CMD[3] == '#')){

                // It means all LEDs on, the last elements will be assigned with 0 and the loop will stop
                CMD[4] = 0;
                CMD[5] = 0;
                CMD[6] = 0;
                CMD[7] = 0;

                return;
                
            }
            
            if(CMD[5] == '#'){

                // The last elements will be assigned with 0 and the loop will stop
                CMD[6] = 0;
                CMD[7] = 0;

                return;
            }
            
            // If command string is 'OFF*#'
            if((CMD[3] == '*')&&(CMD[4] == '#')){

                // It means all LEDs off, the last elements will be assigned with 0 and the loop will stop
                CMD[5] = 0;
                CMD[6] = 0;
                CMD[7] = 0;              

                return;

                // If command string is 'BLINK*#'
            } else if((CMD[5] == '*')&&(CMD[6] == '#')){

                // It means to blink all LEDs, the last elements will be assigned with 0 and the loop will stop
                CMD[7] = 0;

                return;
            }
        }
}

void LEDs_off(){
    
         ////////////////////
        // LED turning off//
       ////////////////////
        
        // If the command string is 'OFF0X#' (X is a particular integer from 1 to 8), then
          
            // LED 01 turns off
        if((CMD[0]=='O')&&(CMD[1]=='F')&&(CMD[2]=='F')&&(CMD[3]=='0')&&(CMD[4]=='1')&&(CMD[5]=='#')){
            LATCbits.LATC0 = 0;
        }
        
            // LED 02 turns off
        if((CMD[0]=='O')&&(CMD[1]=='F')&&(CMD[2]=='F')&&(CMD[3]=='0')&&(CMD[4]=='2')&&(CMD[5]=='#')){
            LATCbits.LATC1 = 0;
        }
        
            // LED 03 turns off
        if((CMD[0]=='O')&&(CMD[1]=='F')&&(CMD[2]=='F')&&(CMD[3]=='0')&&(CMD[4]=='3')&&(CMD[5]=='#')){
            LATCbits.LATC2 = 0;
        }
        
            // LED 04 turns off
        if((CMD[0]=='O')&&(CMD[1]=='F')&&(CMD[2]=='F')&&(CMD[3]=='0')&&(CMD[4]=='4')&&(CMD[5]=='#')){
            LATCbits.LATC3 = 0;
        }
        
            // LED 05 turns off
        if((CMD[0]=='O')&&(CMD[1]=='F')&&(CMD[2]=='F')&&(CMD[3]=='0')&&(CMD[4]=='5')&&(CMD[5]=='#')){
            LATCbits.LATC4 = 0;
        }
        
            // LED 06 turns off
        if((CMD[0]=='O')&&(CMD[1]=='F')&&(CMD[2]=='F')&&(CMD[3]=='0')&&(CMD[4]=='6')&&(CMD[5]=='#')){
            LATCbits.LATC5 = 0;
        }
        
            // LED 07 turns off
        if((CMD[0]=='O')&&(CMD[1]=='F')&&(CMD[2]=='F')&&(CMD[3]=='0')&&(CMD[4]=='7')&&(CMD[5]=='#')){
            LATCbits.LATC6 = 0;
        }
        
            // LED 08 turns off
        if((CMD[0]=='O')&&(CMD[1]=='F')&&(CMD[2]=='F')&&(CMD[3]=='0')&&(CMD[4]=='8')&&(CMD[5]=='#')){
            LATCbits.LATC7 = 0;
        }
        
            // If the command string is 'OFF*#', then
            // All LEDs off
        if((CMD[0]=='O')&&(CMD[1]=='F')&&(CMD[2]=='F')&&(CMD[3]=='*')&&(CMD[4]=='#')){
            LATC = 0x00;
        }
        
}

void main(void)
{   
    // Initialize the device
    SYSTEM_Initialize();
    
    // Clear output latch and set loop's counter
    LATC = 0x00;
    
    // For loops
    int i = 0;
    
    // For blinking timing
    int time_counter = 0;
    
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

    while(1){
        
        // USART reading
        if(EUSART_is_rx_ready()!=0){
            
            USART_read();
            
        }            
        
        LEDs_on();
        
        LEDs_off();

         //////////////////
        // LEDs blinking//
       //////////////////
         
        // If the command string is 'BLINK0X#' (X is a particular integer from 1 to 8), then
        
            // LED 01 blinks
        if((CMD[0]=='B')&&(CMD[1]=='L')&&(CMD[2]=='I')&&(CMD[3]=='N')&&(CMD[4]=='K')&&(CMD[5]=='0')&&(CMD[6]=='1')&&(CMD[7]=='#')){
            
            time_counter = 0;
            
            for(time_counter=0; time_counter<1000; time_counter++){
                
                // The first 0.5 second
                    // If the time counter is from 0th second
                if((time_counter>=0)&&(time_counter<500)){
                                        
                    // LED lights on
                    LATCbits.LATC0 = 1;
                    __delay_ms(1);
                             
                    // Else, if the time counter is from 500th second
                } else if((time_counter>=500)&&(time_counter<1000)){
                    
                    // LED lights off
                    LATCbits.LATC0 = 0;
                    __delay_ms(1);
                    
                }
                
                if(EUSART_is_rx_ready()!=0){
                
                    USART_read();

                    LEDs_on();
                    
                    LEDs_off();

                }
            }        
        }
        
            // LED 02 blinks
        if((CMD[0]=='B')&&(CMD[1]=='L')&&(CMD[2]=='I')&&(CMD[3]=='N')&&(CMD[4]=='K')&&(CMD[5]=='0')&&(CMD[6]=='2')&&(CMD[7]=='#')){
            
            time_counter = 0;
            
            for(time_counter=0; time_counter<1000; time_counter++){
                
                // The first 0.5 second
                    // If the time counter is from 0th second
                if((time_counter>=0)&&(time_counter<500)){
                                        
                    // LED lights on
                    LATCbits.LATC1 = 1;
                    __delay_ms(1);
                             
                    // Else, if the time counter is from 500th second
                } else if((time_counter>=500)&&(time_counter<1000)){
                    
                    // LED lights off
                    LATCbits.LATC1 = 0;
                    __delay_ms(1);
                    
                }
                
                if(EUSART_is_rx_ready()!=0){
                
                    USART_read();

                    LEDs_on();
                    
                    LEDs_off();

                }
            }        
        }
        
            // LED 03 blinks
        if((CMD[0]=='B')&&(CMD[1]=='L')&&(CMD[2]=='I')&&(CMD[3]=='N')&&(CMD[4]=='K')&&(CMD[5]=='0')&&(CMD[6]=='3')&&(CMD[7]=='#')){
            
            time_counter = 0;
            
            for(time_counter=0; time_counter<1000; time_counter++){
                
                // The first 0.5 second
                    // If the time counter is from 0th second
                if((time_counter>=0)&&(time_counter<500)){
                                        
                    // LED lights on
                    LATCbits.LATC2 = 1;
                    __delay_ms(1);
                             
                    // Else, if the time counter is from 500th second
                } else if((time_counter>=500)&&(time_counter<1000)){
                    
                    // LED lights off
                    LATCbits.LATC2 = 0;
                    __delay_ms(1);
                    
                }
                
                if(EUSART_is_rx_ready()!=0){
                
                    USART_read();

                    LEDs_on();
                    
                    LEDs_off();

                }
            }        
        } 
                   
        
            // LED 04 blinks
        if((CMD[0]=='B')&&(CMD[1]=='L')&&(CMD[2]=='I')&&(CMD[3]=='N')&&(CMD[4]=='K')&&(CMD[5]=='0')&&(CMD[6]=='4')&&(CMD[7]=='#')){
            
            time_counter = 0;
            
            for(time_counter=0; time_counter<1000; time_counter++){
                
                // The first 0.5 second
                    // If the time counter is from 0th second
                if((time_counter>=0)&&(time_counter<500)){
                                        
                    // LED lights on
                    LATCbits.LATC3 = 1;
                    __delay_ms(1);
                             
                    // Else, if the time counter is from 500th second
                } else if((time_counter>=500)&&(time_counter<1000)){
                    
                    // LED lights off
                    LATCbits.LATC3 = 0;
                    __delay_ms(1);
                    
                }
                
                if(EUSART_is_rx_ready()!=0){
                
                    USART_read();

                    LEDs_on();
                    
                    LEDs_off();

                }
            }        
        }
        
            // LED 05 blinks
        if((CMD[0]=='B')&&(CMD[1]=='L')&&(CMD[2]=='I')&&(CMD[3]=='N')&&(CMD[4]=='K')&&(CMD[5]=='0')&&(CMD[6]=='5')&&(CMD[7]=='#')){
            
            time_counter = 0;
            
            for(time_counter=0; time_counter<1000; time_counter++){
                
                // The first 0.5 second
                    // If the time counter is from 0th second
                if((time_counter>=0)&&(time_counter<500)){
                                        
                    // LED lights on
                    LATCbits.LATC4 = 1;
                    __delay_ms(1);
                             
                    // Else, if the time counter is from 500th second
                } else if((time_counter>=500)&&(time_counter<1000)){
                    
                    // LED lights off
                    LATCbits.LATC4 = 0;
                    __delay_ms(1);
                    
                }
                
                if(EUSART_is_rx_ready()!=0){
                
                    USART_read();

                    LEDs_on();
                    
                    LEDs_off();

                }
            }        
        }
        
            // LED 06 blinks
        if((CMD[0]=='B')&&(CMD[1]=='L')&&(CMD[2]=='I')&&(CMD[3]=='N')&&(CMD[4]=='K')&&(CMD[5]=='0')&&(CMD[6]=='6')&&(CMD[7]=='#')){
            
            time_counter = 0;
            
            for(time_counter=0; time_counter<1000; time_counter++){
                
                // The first 0.5 second
                    // If the time counter is from 0th second
                if((time_counter>=0)&&(time_counter<500)){
                                        
                    // LED lights on
                    LATCbits.LATC5 = 1;
                    __delay_ms(1);
                             
                    // Else, if the time counter is from 500th second
                } else if((time_counter>=500)&&(time_counter<1000)){
                    
                    // LED lights off
                    LATCbits.LATC5 = 0;
                    __delay_ms(1);
                    
                }
                
                if(EUSART_is_rx_ready()!=0){
                
                    USART_read();

                    LEDs_on();
                    
                    LEDs_off();

                }
            }        
        }
        
             // LED 07 blinks
        if((CMD[0]=='B')&&(CMD[1]=='L')&&(CMD[2]=='I')&&(CMD[3]=='N')&&(CMD[4]=='K')&&(CMD[5]=='0')&&(CMD[6]=='7')&&(CMD[7]=='#')){
            
            time_counter = 0;
            
            for(time_counter=0; time_counter<1000; time_counter++){
                
                // The first 0.5 second
                    // If the time counter is from 0th second
                if((time_counter>=0)&&(time_counter<500)){
                                        
                    // LED lights on
                    LATCbits.LATC6 = 1;
                    __delay_ms(1);
                             
                    // Else, if the time counter is from 500th second
                } else if((time_counter>=500)&&(time_counter<1000)){
                    
                    // LED lights off
                    LATCbits.LATC6 = 0;
                    __delay_ms(1);
                    
                }
                
                if(EUSART_is_rx_ready()!=0){
                
                    USART_read();

                    LEDs_on();
                    
                    LEDs_off();

                }
            }        
        }
        
            // LED 08 blinks
        if((CMD[0]=='B')&&(CMD[1]=='L')&&(CMD[2]=='I')&&(CMD[3]=='N')&&(CMD[4]=='K')&&(CMD[5]=='0')&&(CMD[6]=='8')&&(CMD[7]=='#')){
            
            time_counter = 0;
            
            for(time_counter=0; time_counter<1000; time_counter++){
                
                // The first 0.5 second
                    // If the time counter is from 0th second
                if((time_counter>=0)&&(time_counter<500)){
                                        
                    // LED lights on
                    LATCbits.LATC7 = 1;
                    __delay_ms(1);
                             
                    // Else, if the time counter is from 500th second
                } else if((time_counter>=500)&&(time_counter<1000)){
                    
                    // LED lights off
                    LATCbits.LATC7 = 0;
                    __delay_ms(1);
                    
                }
                
                if(EUSART_is_rx_ready()!=0){
                
                    USART_read();

                    LEDs_on();
                    
                    LEDs_off();

                }
            }        
        }    
        
        // If the command string is 'BLINK*#', then
             // All LEDs blink
        if((CMD[0]=='B')&&(CMD[1]=='L')&&(CMD[2]=='I')&&(CMD[3]=='N')&&(CMD[4]=='K')&&(CMD[5]=='*')&&(CMD[6]=='#')){
            
            time_counter = 0;
            
            for(time_counter=0; time_counter<1000; time_counter++){
                
                // The first 0.5 second
                    // If the time counter is from 0th second
                if((time_counter>=0)&&(time_counter<500)){
                                        
                    // LED lights on
                    LATC = 0xFF;
                    __delay_ms(1);
                             
                    // Else, if the time counter is from 500th second
                } else if((time_counter>=500)&&(time_counter<1000)){
                    
                    // LED lights off
                    LATC = 0x00;
                    __delay_ms(1);
                    
                }
                
                if(EUSART_is_rx_ready()!=0){
                
                    USART_read();

                    LEDs_on();
                    
                    LEDs_off();

                }
            }        
        }       
    }
}    
    
/**
 End of File
*/