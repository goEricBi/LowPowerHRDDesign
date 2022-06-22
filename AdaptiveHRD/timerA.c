#include "timerA.h"
extern unsigned int g1msTimer;
void ConfigureTimerA(void)
{
    // Stop the timer and clear it.
    TA0CTL =(MC_0 |TACLR);
    // Initialize Capture-Compare Register 0 (TA0CCR0).
	TACCR0 = TA0CCR0_VALUE;
    // TACCR0 interrupt enabled (see Section 12.2.6 of User's Guide)
	TACCTL0  |= CCIE;
    // Start the timer in up mode, using SMCLK with no clock division.
	TA0CTL |= TASSEL_2 | ID_0 |MC_1;
}

