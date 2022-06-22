#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <msp430.h>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *                 Pushbutton
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *   GPIO      :  P1.3
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#define PUSHBUTTON_BIT						BIT3	// Port pin bit location for pushbutton
#define PUSHBUTTON_REN  					P1REN   // Register to enable resistors for pushbutton
#define PUSHBUTTON_PORT_IN					P1IN 	// Register to read port pin input
#define PUSHBUTTON_PORT						P1OUT 	// Register to select pull-up/pull-down
#define PUSHBUTTON_DDR						P1DIR 	// Data Direction Register (DDR) for pushbutton.
#define SET_PUSHBUTTON_TO_AN_INPUT			PUSHBUTTON_DDR &= ~PUSHBUTTON_BIT
#define ENABLE_PULL_UP_PULL_DOWN_RESISTORS	PUSHBUTTON_REN |= PUSHBUTTON_BIT
#define SELECT_PULL_UP_RESISTORS			PUSHBUTTON_PORT |= PUSHBUTTON_BIT
//#define ENABLE_INTERUPT                     P1IE |= PUSHBUTTON_BIT

// Prototypes
void InitializePushButtonPortPin(void);
//void _enable_interupts(void);

#endif
