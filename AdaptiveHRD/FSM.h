#ifndef FSM_H_
#define FSM_H_

#include <msp430.h>

// Constant Definitions
#define ACTIVE_THRESHOLD 10 // Time (in ms) to wait after button press.
#define INACTIVE_THRESHOLD 20 // Time (in ms) to wait after button release.

// Type Definitions
typedef enum {
	WaitingForActive, ValidateActive, WaitingForInactive, ValidateInactive
} DbState;

typedef enum {
	Inactive, Active
} SwitchStatus;

typedef struct {
	DbState CurrentState;			        // Current state of the FSM
    unsigned int EventTime;                 // Output: Records time of an event, 
    SwitchStatus DebouncedSwitchStatus;     // Output: Current state of debounced switch.
    unsigned char SwitchCycleNotComplete;   // Output: Boolean that indicates if switch has completed FSM cycle.
	char * SwitchPort;                      // Input port associated with switch
	unsigned char SwitchPortBit;	        // Port pin associated with switch
	SwitchStatus Logic0Value;		        // Switch state associated with logic 0.
	SwitchStatus Logic1Value;               // Switch state associated with logic 1.
	unsigned char ActiveThreshold;		    // Time switch must remain Active after being Inactive.
	unsigned char InactiveThreshold;	    // Time switch must remain Inactive after being Active
} SwitchDefine;

// Function Prototypes
void InitializeSwitch(SwitchDefine *Switch,char *SwitchPort,unsigned char SwitchBit,
		SwitchStatus Logic0Value, SwitchStatus Logic1Value,
		      unsigned char ActiveThreshold,unsigned char InactiveThreshold);

//This function returns the instantaneous value of the selected switch
SwitchStatus ReadSwitchStatus(SwitchDefine *Switch);

DbState NextStateFunction(SwitchDefine *Switch,unsigned char X0,unsigned char X1);
void OutputFunction(SwitchDefine *Switch,unsigned char X0,unsigned char X1);

#endif
