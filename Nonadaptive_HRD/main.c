#include <msp430.h>
#include "InterruptServiceRoutines.h"
#include "FSM.h"
#include "LED.h"
#include "pushbutton.h"
#include "timerA.h"
#include "DebugPins.h"

// Global Variables
unsigned int g1msTimer;			// Global 1 ms timer
#define FALSE 0
#define TRUE 1
#define missCount 2
#define idleTime
// Function Prototypes
void ConfigureClockModule();

int main(void)
{
	SwitchDefine PushButton;
	unsigned char X1 = FALSE;
	unsigned char X0 = FALSE;

    WDTCTL = WDTPW | WDTHOLD;		// Stop watchdog timer
    ConfigureClockModule();

    // Initialize hardware.
    ConfigureTimerA();
	InitializeLEDPortPins();
	InitializePushButtonPortPin();
	SET_D0_PIN_AS_AN_OUTPUT;
	SET_D1_PIN_AS_AN_OUTPUT;
	SET_D2_PIN_AS_AN_OUTPUT;

	// Initialize the pushbutton active-low switch.
	InitializeSwitch(&PushButton,(char *) &PUSHBUTTON_PORT_IN,(unsigned char) PUSHBUTTON_BIT,
			Active, Inactive, ACTIVE_THRESHOLD,INACTIVE_THRESHOLD);

	// Enable interrupts
	_enable_interrupts();
	// Loop forever
	while(TRUE) {
		// First, determine the current inputs, X1 and X0.
	    //X0 = ReadSwitchStatus(&PushButton);
	    // if readswitchstatus == active, x0 = true
	    X0 = ReadSwitchStatus(&PushButton) == Active;
	    //X1 = X0?(g1msTimer- PushButton.EventTime) >=PushButton.ActiveThreshold:(g1msTimer- PushButton.EventTime) >= PushButton.InactiveThreshold;
	    if(PushButton.CurrentState==ValidateActive){
	        if((g1msTimer - PushButton.EventTime) >=PushButton.ActiveThreshold){
	            X1 = TRUE;
	        }else{
	            X1 = FALSE;
	        }
	    }
        if(PushButton.CurrentState==ValidateInactive){
            if((g1msTimer - PushButton.EventTime) >=PushButton.InactiveThreshold){
                X1 = TRUE;
            }else{
                X1 = FALSE;
            }
        }
	    // Next, based on the input values and the current state, determine the next state.
	    PushButton.CurrentState = NextStateFunction(&PushButton,X0,X1);
	    // Perform the output function based on the inputs and current state.
		OutputFunction(&PushButton,X0,X1);
//		if (PushButton.SwitchCycleNotComplete == FALSE){
//		    TOGGLE_GREEN_LED;
//			PushButton.SwitchCycleNotComplete = TRUE;
//		}
//        if (PushButton.SwitchCycleNotComplete == FALSE){
//          TOGGLE_RED_LED;
//          PushButton.SwitchCycleNotComplete = TRUE;
//        }

		if(PushButton.CurrentState == ValidateInactive ||PushButton.CurrentState == ValidateActive ){
		    TOGGLE_GREEN_LED;
		}
//		else{
//		    TURN_OFF_GREEN_LED;
//		}
	}
	//return 0;
}

void ConfigureClockModule()
{
	// Configure Digitally Controlled Oscillator (DCO) using factory calibrations
	DCOCTL  = CALDCO_1MHZ;
	BCSCTL1 = CALBC1_1MHZ;
}








