#include "dsk6713.h"
#include "dsk6713_led.h"
#include "dsk6713_flash.h"

interrupt void c_int11()
{
	return;
}


void main(void)
{
	DSK6713_init();

	DSK6713_LED_init();
	
	while (1)
	{
		DSK6713_LED_toggle(2);
		DSK6713_waitusec(500000);
	}
}

