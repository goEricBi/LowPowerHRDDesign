#include "FSM.h"
#include "DebugPins.h"
#define FALSE 0
#define TRUE 1

extern unsigned int g1msTimer;

void InitializeSwitch(SwitchDefine *Switch,char *SwitchPort,unsigned char SwitchBit,
		SwitchStatus Logic0Value, SwitchStatus Logic1Value,
		      unsigned char ActiveThreshold,unsigned char InactiveThreshold)
{
	Switch->CurrentState = WaitingForActive;
	Switch->SwitchPort = SwitchPort;
	Switch->SwitchPortBit = SwitchBit;
	Switch->Logic0Value = Logic0Value;
	Switch->Logic1Value = Logic1Value;

	Switch->ActiveThreshold = ActiveThreshold; // units equal milliseconds
	Switch->InactiveThreshold = InactiveThreshold; // units equal milliseconds
	Switch->EventTime = 0;
	Switch->DebouncedSwitchStatus = Inactive;
	Switch->SwitchCycleNotComplete = TRUE;
}

SwitchStatus ReadSwitchStatus(SwitchDefine *Switch)
{
	SwitchStatus ReturnValue = Inactive;
	unsigned char SwitchPinValue = 0;
	SwitchPinValue = *(Switch -> SwitchPort) & Switch->SwitchPortBit;
	if(SwitchPinValue){
	    ReturnValue = Switch->Logic1Value;
	}
	else{
	    ReturnValue = Switch->Logic0Value;
	}
	return ReturnValue;
}

DbState NextStateFunction(SwitchDefine *Switch,unsigned char X0,unsigned char X1)
{
/*
 * This function implements a 4-state Mealy state machine:
 *
 * WaitingForActive (WFA): 	The switch is currently in the inactive state and awaiting a transition to the
 * 							active state.
 * ValidateActive (VA): 	The state has transitioned to the active state, but the elapsed time from the
 * 							transition to the current time (in g1msTimer) has not exceeded the threshold,
 * 							HoldTime.
 * WaitingForInactive (WFI):The switch is currently in the active state and awaiting a transition to the
 * 							inactive state.
 * ValidateInactive (VI):	The state has transitioned to the inactive state, but the elapsed time from the
 * 							transition to the current time (in g1msTimer) has not exceeded the threshold,
 * 							ReleaseTime.
 *
 * The state machine has two inputs:
 *
 * X1:	This input is a logical condition based on the elapsed time from the transition from the inactive state
 * 		to the active state (or vice-versa). X1 = true implies the elapsed time is greater than the threshold.
 * X0:	This input is a logical condition based on the state of the switch (high or low). X0 = true implies
 * 		that the switch is in the active (High) state.
 *
 */
	DbState NextState;

	switch (Switch->CurrentState) {
		case WaitingForActive:
		    if(X0 == 1 /*Or TRUE*/){
		        NextState = ValidateActive;
		    }
		    else{
		        NextState = WaitingForActive;
		    }
		break;
		case ValidateActive:
		    if(X0==TRUE){
		        NextState=ValidateActive;
		        if(X1==TRUE){
		            NextState=WaitingForInactive;
		        }
		    }
		    else{
		        NextState=WaitingForActive;
		    }
		break;
		case WaitingForInactive:
		    if(X0==1){
		        NextState= WaitingForInactive;
		    }
		    else{
		        NextState=  ValidateInactive;
		    }
		break;
		case ValidateInactive:
		    if(X0==FALSE){
		        NextState = ValidateInactive;
		        if(X1 == TRUE){
		            NextState = WaitingForActive;
		        }
		    }
		    else {
		        NextState = WaitingForInactive;
		    }
		break;
		default: NextState = WaitingForActive;
	}
	
	return NextState;
}

void OutputFunction(SwitchDefine *Switch,unsigned char X0,unsigned char X1)
{
	switch (Switch->CurrentState) {
		case WaitingForActive:
		    Switch->DebouncedSwitchStatus = Inactive;
            D0_EQUALS_0;
            D1_EQUALS_0;
            D2_EQUALS_0;
            if (X0==TRUE){
                Switch->EventTime = g1msTimer;
            }
		break;
		case ValidateActive:
             Switch->DebouncedSwitchStatus = Inactive;
             D0_EQUALS_1;
             D1_EQUALS_0;
             D2_EQUALS_0;
		break;
		case WaitingForInactive:
		    Switch->DebouncedSwitchStatus = Active;
            D0_EQUALS_0;
            D1_EQUALS_1;
            D2_EQUALS_1;
            if(X0== FALSE){
                Switch->EventTime = g1msTimer;
            }
		break;
		case ValidateInactive:
		    Switch->DebouncedSwitchStatus = Active;
            D0_EQUALS_1;
            D1_EQUALS_1;
            D2_EQUALS_1;
            if(X0 ==FALSE && X1==TRUE){
                Switch->SwitchCycleNotComplete = FALSE;
            }
		break;
	}
}
