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
    unsigned int HR[4] = [857,857,857,857];  //Resting Heart Rate (period) in ms
    unsigned int index = 0;
    unsigned int sum = 3388; //857*4
    unsigned int avgThresh = 2000;// 2000ms => 2s => 0.5 Hz
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

	while(TRUE) {
	    unsigned int activeTime = 0;
	    unsigned int inactiveTime = 0;

	    // Check for the threshold Time
	    X0 = ReadSwitchStatus(&PushButton) == Active;
	    if(PushButton.CurrentState==ValidateActive){
	        if((g1msTimer - PushButton.EventTime) >=PushButton.ActiveThreshold){
	            X1 = TRUE;
	            // pass the debouncing filter: 
	            //activeTime = PushButton.EventTime;
	        }else{
	            X1 = FALSE;
	        }
	    }
        if(PushButton.CurrentState==ValidateInactive){
            if((g1msTimer - PushButton.EventTime) >=PushButton.InactiveThreshold){
                X1 = TRUE;
                // pass the debouncing filter: 
                //inactiveTime = PushButton.EventTime;
            }else{
                X1 = FALSE;
            }
        }
        
        // threshold setting:
        unsigned int avgWind = sum/4; 
        if(avgWind -(inactiveTime - activeTime)<= avgThresh){
            // good, and just replace the array
            
            index += 1;
            if(index == 4){
                index =0; 
            }
            /replacing the index 
            sum = sum - HR[index] +  inactiveTime - activeTime;
            HR[index] = inactiveTime - activeTime; /              
        }
        else{
            missCount += 1;
            if (missCount >=2){
                //trigger alert:
          
               misCount = 0;
            }
        }
	    // Next, based on the input values and the current state, determine the next state.
	    PushButton.CurrentState = NextStateFunction(&PushButton,X0,X1);
	    // Perform the output function based on the inputs and current state.
		OutputFunction(&PushButton,X0,X1);

		if(PushButton.CurrentState == ValidateInactive ||PushButton.CurrentState == ValidateActive ){
		    TOGGLE_GREEN_LED;
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








