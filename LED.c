/***************************************************************/
/*                                                             */
/*      PROJECT NAME :  LED                                    */
/*      FILE         :  LED.c                                  */
/*      DESCRIPTION  :  Main Program                           */
/*                                                             */
/*      This file was generated by e2 studio.                  */
/*                                                             */
/***************************************************************/

#include <iodefine.h>
#include "clock.h"

#define LED_DDR		PORTD.DDR.BIT.B0
#define LED_DATA	PORTD.DR.BIT.B0
#define SW_DDR		PORTD.DDR.BIT.B4
#define SW_DATA		PORTD.PORT.BIT.B4
#define LED_EN		{LED_DDR = 1;}
#define SW_EN		{SW_DDR = 0;}
unsigned int UI_loopCount = 0;

/***********************************************************************************
 * Function : vDelay
 * param    : unsigned integer UI_value specifies the delay value in milliseconds
 * return   : None
 * usage    : Use this function to achieve delay in Ms between statements
 * *********************************************************************************/
void vDelay(unsigned int UI_value)
{
	unsigned int UI_innerLoopCount = 0;
	for(UI_loopCount = 0;UI_loopCount < UI_value; UI_loopCount++)
	{
		for(UI_innerLoopCount = 0;UI_innerLoopCount<20000;) // ICLK = 96Mhz, one clock pulse period = 0.0104 Microseconds
		{
			UI_innerLoopCount++; // Assuming this instruction would take 2 clock cycles ,we give count as 20000
		}
	}
}
/***********************************************************************************/

int main(void) {

	vSystemClockDiv(0);			// select ICLK as EXTAL * 8 = 12*8 = 96MHz
	vPeripheralClockDiv(1);		// select ICLK as EXTAL * 4 = 12*4 = 48MHz
	LED_DATA = 0;
	LED_EN;
	SW_EN;

    while(1) {

    	if(SW_DATA == 0)
    	        {
    	        	vDelay(10);				// software de bounce
    	        	if(SW_DATA == 0)
    	        	{
    	        		LED_DATA = 1;
    	        		vDelay(500);
    	        		LED_DATA = 0;
    	        		vDelay(500);
    	        	}
    	        }
    	       else
    	    {
    	        	LED_DATA = 0;
    				vDelay(700);
    				LED_DATA = 1;
    				vDelay(700);
    	       }

    	    }

return 0;
}
