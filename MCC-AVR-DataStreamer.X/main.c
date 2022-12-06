 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
*/

/*
© [2022] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h" 
//#include <util/delay.h>

const struct TMR_INTERFACE *Timer = &TCA0_Interface;

volatile bool SEND_FRAME = false;

// custom datastreamer
struct{
    uint8_t count;
    uint16_t count16;
    uint16_t new16;
    uint32_t count32;
    uint32_t new32;
    float count_f;
}my_struct;

// Custom generated data streamer package
void DS_Frame_Update(void){
    my_struct.count +=5; /*Update variable values */
    my_struct.count16 += 1000;
    my_struct.new16 += 2000;
    my_struct.count32 += 50000000;
    my_struct.new32 += 30000000;
    my_struct.count_f += 1.5;
    SEND_FRAME = true;   /* Variable values updated, a new Data Streamer frame can be sent. */
    LED_SetLow();
}

// MCC generated data streamer package
//void DS_Frame_Update(void){
//    DataStreamer.count +=5; /*Update variable values */
//    DataStreamer.count16 += 1000;
//    DataStreamer.count32 += 50000000;
//    DataStreamer.count_f += 1.5;
//    SEND_FRAME = true;   /* Variable values updated, a new Data Streamer frame can be sent. */
//    LED_SetLow();
//}

/*
    Main application
*/

int main(void)
{
    SYSTEM_Initialize();
    // using MCC generated 
    DataStreamer_PackageSet(&my_struct, sizeof(my_struct));
    Timer->TimeoutCallbackRegister(DS_Frame_Update);
    
    my_struct.count = 0;
    my_struct.count16 = 0;
    my_struct.new16 = 0;
    my_struct.count32 = 0;
    my_struct.new32 = 0;
    my_struct.count_f = 1.5;
    
    while(1)
    {
        if(SEND_FRAME){
            WriteFrame();
            SEND_FRAME = false;
            LED_SetHigh();
        }
    }
}
