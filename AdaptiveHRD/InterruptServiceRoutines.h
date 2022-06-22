#ifndef INTERRUPTSERVICEROUTINES_H_
#define INTERRUPTSERVICEROUTINES_H_
#include "DebugPins.h"

// If you're using the TI compiler, comment out this #define statement
#define USING_GNU_COMPILER

// Global variables used within ISRs
extern unsigned int g1msTimer;
#define TIME_BUTTON_IS_PRESSED 50
#define TIME_BOUNCE_BEGINS 54
#define TIME_BOUNCE_ENDS 55
#define TIME_BUTTON_IS_RELEASED 150
#define PUSHBUTTON_PERIOD 200
// Interrupt handler for port register 1
#ifdef USING_GNU_COMPILER
__attribute__((interrupt(PORT1_VECTOR)))
#else
#pragma vector = PORT1_VECTOR
__interrupt
#endif
void PORT1_ISR(void)
{
}

// Interrupt handler for port register 2
#ifdef USING_GNU_COMPILER
__attribute__((interrupt(PORT2_VECTOR)))
#else
#pragma vector = PORT2_VECTOR
__interrupt
#endif
void PORT2_ISR(void)
{
}

// Interrupt handler for 10-bit ADC
#ifdef USING_GNU_COMPILER
__attribute__((interrupt(ADC10_VECTOR)))
#else
#pragma vector = ADC10_VECTOR
__interrupt
#endif
void ADC10_ISR(void)
{
}

// Interrupt handler for TX on USCI A and B.
#ifdef USING_GNU_COMPILER
__attribute__((interrupt(USCIAB0TX_VECTOR)))
#else
#pragma vector = USCIAB0TX_VECTOR
__interrupt
#endif
void USCIAB0TX_ISR(void)
{
}

// Interrupt handler for RX on USCI A and B.
#ifdef USING_GNU_COMPILER
__attribute__((interrupt(USCIAB0RX_VECTOR)))
#else
#pragma vector = USCIAB0RX_VECTOR
__interrupt
#endif
void USCIAB0RX_ISR(void)
{
}

// Interrupt handler for Timer0_A CCIFG2, CCIFG1 and TAIFG
#ifdef USING_GNU_COMPILER
__attribute__((interrupt(TIMER0_A1_VECTOR)))
#else
#pragma vector = TIMER0_A1_VECTOR
__interrupt
#endif
void TIMER0_A1_ISR(void)
{
}

// Interrupt handler for Timer0_A CCIFG0
#ifdef USING_GNU_COMPILER
__attribute__((interrupt(TIMER0_A0_VECTOR)))
#else
#pragma vector = TIMER0_A0_VECTOR
__interrupt
#endif
void TIMER0_A0_ISR(void)
{
    g1msTimer++;
    /*if(g1msTimer == TIME_BUTTON_IS_PRESSED){
        PRESS_PUSHBUTTON;
    }
    else if(g1msTimer == TIME_BOUNCE_BEGINS){
        RELEASE_PUSHBUTTON;
    }
    else if(g1msTimer == TIME_BUTTON_IS_RELEASED){
        RELEASE_PUSHBUTTON;
    }
    if(g1msTimer == PUSHBUTTON_PERIOD) g1msTimer=0;*/
}

// Interrupt handler for watchdog timer
#ifdef USING_GNU_COMPILER
__attribute__((interrupt(WDT_VECTOR)))
#else
#pragma vector = WDT_VECTOR
__interrupt
#endif
void WDT_ISR(void)
{
}

// Interrupt handler for comparator A
#ifdef USING_GNU_COMPILER
__attribute__((interrupt(COMPARATORA_VECTOR)))
#else
#pragma vector = COMPARATORA_VECTOR
__interrupt
#endif
void COMPARATORA_ISR(void)
{
}

// Interrupt handler for Timer0_A CCIFG2, CCIFG1 and TAIFG
#ifdef USING_GNU_COMPILER
__attribute__((interrupt(TIMER1_A1_VECTOR)))
#else
#pragma vector = TIMER1_A1_VECTOR
__interrupt
#endif
void TIMER1_A1_ISR(void)
{
}

// Interrupt handler for Timer0_A CCIFG0
#ifdef USING_GNU_COMPILER
__attribute__((interrupt(TIMER1_A0_VECTOR)))
#else
#pragma vector = TIMER1_A0_VECTOR
__interrupt
#endif
void TIMER1_A0_ISR(void)
{
}

#endif /* INTERRUPTSERVICEROUTINES_H_ */
