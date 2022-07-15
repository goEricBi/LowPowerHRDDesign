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
#define idleTime
// Function Prototypes
void ConfigureClockModule();

int main(void)
{
    unsigned int HR[4] = {857,857,857,857};  //Resting Heart Rate (period) in ms
    unsigned int timerA = 0;
    unsigned int failover = 2;
    unsigned int index = 0;
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
	unsigned int activeTime = 500;
	while(TRUE) {

	    // Check for the threshold Time
	    X0 = ReadSwitchStatus(&PushButton) == Active;
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

		if(PushButton.CurrentState == ValidateInactive ||PushButton.CurrentState == ValidateActive ){
		    if(g1msTimer-timerA>0 && g1msTimer-timerA<activeTime){
		        HR[index]=g1msTimer-timerA;
		        TOGGLE_GREEN_LED;
		        index++;
		        if(index==4){
		            index = 0;
		        }
		    }
		    else{
		        TOGGLE_RED_LED; // MissCount Occurs
		        failover--;
		        if(failover==0){
		            TOGGLE_GREEN_LED;
		            TOGGLE_RED_LED;
		            failover = 2;
		        }
		    }
		    timerA = g1msTimer;
		}

	}
	//return 0;
}

void ConfigureClockModule()
{
	// Configure Digitally Controlled Oscillator (DCO) using factory calibrations
	DCOCTL  = CALDCO_1MHZ;
	BCSCTL1 = CALBC1_1MHZ;
}
