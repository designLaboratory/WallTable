#include "gpio.h" 

void gpio_init(void)
{
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK  //podlaczenie zegarow
								| SIM_SCGC5_PORTD_MASK
								| SIM_SCGC5_PORTE_MASK;
	




	
}
