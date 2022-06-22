#include "pushbutton.h"

void InitializePushButtonPortPin (void)
{
	// Configure port pin for pushbutton
	ENABLE_PULL_UP_PULL_DOWN_RESISTORS;
	SELECT_PULL_UP_RESISTORS;
	SET_PUSHBUTTON_TO_AN_INPUT;
}
/*void _enable_interupts(void){
    ENABLE_INTERUPT;
}*/

