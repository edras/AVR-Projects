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
#include <util/delay.h>
/* Create a pointer of the type TMR_INTERFACE and assign it to the address of the TCA0_Interface TMR_INTERFACE struct.
This enables us to get access to the portable API interface, ensuring that it's easy to change the peripheral instance the timer runs on. */
const struct TMR_INTERFACE *Timer = &TCA0_Interface;  

#define LED_100ms (0x30D3)
#define LED_500ms (0xF423)
volatile bool CHANGE_PERIOD = false;
volatile bool PERIOD_100ms = true;


void Timer_Callback(void)
{
    LED_Toggle();
}

void SW_Callback(void)
{
    CHANGE_PERIOD = true;
}

void Timer_Change_Frequency(void)
{
    Timer->Stop();
    if(PERIOD_100ms)
    {
        TCA0.SINGLE.CNT = 0x0;  //Clear the Counter register
        Timer->PeriodCountSet(LED_500ms);
        PERIOD_100ms = false;
    }
    else
    {
        TCA0.SINGLE.CNT = 0x0;   //Clear the Counter register
        Timer->PeriodCountSet(LED_100ms);
        PERIOD_100ms = true;
    }
    Timer->Start();
}

/*
    Main application
*/

int main(void)
{
    SYSTEM_Initialize();

    Timer->TimeoutCallbackRegister(Timer_Callback);
    PF6_SetInterruptHandler(SW_Callback);
    while(1)
    {
        if(CHANGE_PERIOD)
        {
            Timer_Change_Frequency();
            _delay_ms(100);    //De-bounce delay
            CHANGE_PERIOD = false;
        }
    }
}
