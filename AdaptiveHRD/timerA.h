#ifndef TIMER_A_H
#define TIMER_A_H

#include <msp430.h>

/*
 * The timer A clock frequency determines the value for TACCR0 so that the global timer, g1msTimer,
 * is updated every millisecond.  For example, SMCLK = 1 MHz => period = 1 microsecond (us).
 * Therefore, 1 ms/1 us = 1000
 */

// Timer A period is TACCR0+1
#define TA0CCR0_VALUE 	1001

// Prototypes
void ConfigureTimerA(void);

#endif
