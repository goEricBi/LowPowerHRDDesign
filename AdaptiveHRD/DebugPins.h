/*
 * DebugPins.h
 *
 *      Author: ab6uy
 */

#ifndef DEBUGPINS_H_
#define DEBUGPINS_H_

#include <msp430.h>

// Simulate Pushbutton values
#define BUTTON_PUSH_BIT                     BIT3
#define BUTTON_PUSH_PORT                    P1OUT
#define BUTTON_PUSH_DIR                     P1DIR
#define SET_BUTTON_PUSH_PIN_AS_AN_OUTPUT    PUSHBUTTON_DDR &= ~PUSHBUTTON_BIT
#define PRESS_PUSHBUTTON                    BUTTON_PUSH_PORT |= BUTTON_PUSH_BIT
#define RELEASE_PUSHBUTTON                  BUTTON_PUSH_PORT  &= ~BUTTON_PUSH_BIT

//  Use port pins to map FSM states
// D2 is the debounced switch signal
#define D2_BIT                      BIT2
#define D2_PORT                     P2OUT
#define D2_DDR                      P2DIR
#define SET_D2_PIN_AS_AN_OUTPUT     D2_DDR |= D2_BIT
#define D2_EQUALS_1                 D2_PORT |= D2_BIT
#define D2_EQUALS_0                 D2_PORT &= ~D2_BIT

// D1 is binary state of elapsed time, where TRUE means the time is past the threshold
#define D1_BIT                      BIT1
#define D1_PORT                     P2OUT
#define D1_DDR                      P2DIR
#define SET_D1_PIN_AS_AN_OUTPUT     D1_DDR |= D1_BIT
#define D1_EQUALS_1                 D1_PORT |= D1_BIT
#define D1_EQUALS_0                 D1_PORT &= ~D1_BIT

// D0 is the binary state of the switch
#define D0_BIT                      BIT0
#define D0_PORT                     P2OUT
#define D0_DDR                      P2DIR
#define SET_D0_PIN_AS_AN_OUTPUT     D0_DDR |= D0_BIT
#define D0_EQUALS_1                 D0_PORT |= D0_BIT
#define D0_EQUALS_0                 D0_PORT &= ~D0_BIT

#endif /* DEBUGPINS_H_ */
