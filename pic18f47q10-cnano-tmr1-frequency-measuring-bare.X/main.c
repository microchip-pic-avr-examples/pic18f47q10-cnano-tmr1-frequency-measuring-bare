/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries.

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

/* WDT operating mode->WDT Disabled */
#pragma config WDTE = OFF
/* Low voltage programming enabled, RE3 pin is MCLR */
#pragma config LVP = ON 

#include <xc.h>
#include <stdint.h>

static void CLK_Initialize(void);
static void PORT_Initialize(void);
static void TMR1_Initialize(void);
static void INTERRUPT_Initialize(void);

static void TMR1_GATE_ISR(void);
static uint16_t TMR1_readTimer(void);
static void TMR1_writeTimer(uint16_t timerValue);

/* Clock initialization function */
static void CLK_Initialize(void)
{
    /* set HFINTOSC as new oscillator source */
    OSCCON1bits.NOSC = 0x6;

    /* set HFFRQ to 32MHz */
    OSCFRQbits.HFFRQ = 0x6;  
}

/* Port initialization function */
static void PORT_Initialize(void)
{
    /* configure RB5 as input */
    TRISBbits.TRISB5 = 1;
    
    /* configure RB5 as digital */
    ANSELBbits.ANSELB5 = 0;
}

/* TMR1 initialization function */
static void TMR1_Initialize(void)
{
    /* Timer controlled by gate function */
    T1GCONbits.GE = 1;

    /* Timer gate toggle mode enabled */
    T1GCONbits.GTM = 1;
    
    /* Timer gate active high */
    T1GCONbits.GPOL = 1;
    
    /* Timer acquistion is ready */
    T1GCONbits.GGO_nDONE = 1;
    
    /* Timer gate single pulse mode enabled */
    T1GCONbits.T1GSPM = 1;  

    /* Source Clock FOSC/4 */
    T1CLKbits.CS = 0x1;
    
    /* Clearing gate IF flag before enabling the interrupt */
    PIR5bits.TMR1GIF = 0;
    
    /* Enabling TMR1 gate interrupt */
    PIE5bits.TMR1GIE = 1;
    
    /* CLK Prescaler 1:8 */
    T1CONbits.CKPS = 0x3;

    /* TMR1 enabled */
    T1CONbits.ON = 1;  
}

/* Interrupt initialization function */
static void INTERRUPT_Initialize(void)
{
    /* Enable the Global Interrupts */
    INTCONbits.GIE = 1;

    /* Enable the Peripheral Interrupts */
    INTCONbits.PEIE = 1; 
}

/* Interrupt handler function */
static void __interrupt() INTERRUPT_InterruptManager(void)
{
    // interrupt handler
    if(INTCONbits.PEIE == 1)
    {
        if(PIE5bits.TMR1GIE == 1 && PIR5bits.TMR1GIF == 1)
        {
            TMR1_GATE_ISR();
        } 
        else
        {
            //Unhandled Interrupt
        }
    }      
    else
    {
        //Unhandled Interrupt
    }
}

/* TMR1 gate ISR function */
static void TMR1_GATE_ISR(void)
{
    volatile uint16_t value = 0;

    /* Clearing gate IF flag */
    PIR5bits.TMR1GIF = 0; 

    /* Read TMR1 value */
    value = TMR1_readTimer();

    /* Reset the counted value */
    TMR1_writeTimer(0);

    /* Prepare for next read */
    T1GCONbits.GGO_nDONE = 1;
}

/* TMR1 read counted value function */
static uint16_t TMR1_readTimer(void)
{
    /* Return TMR1 value */
    return ((uint16_t)TMR1H << 8) | TMR1L;
}

/* TMR1 write counter value function */
static void TMR1_writeTimer(uint16_t timerValue)
{
    /* Write TMR1H value */
    TMR1H = timerValue >> 8;

    /* Write TMR1L value */
    TMR1L = timerValue;
}

void main(void)
{
    CLK_Initialize();
    PORT_Initialize();
    TMR1_Initialize();
    INTERRUPT_Initialize();

    while (1)
    {
        ;
    }
}
