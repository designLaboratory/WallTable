#include "gpio.h" 

void gpio_init(void)
{
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK  //podlaczenie zegarow
								| SIM_SCGC5_PORTD_MASK
								| SIM_SCGC5_PORTE_MASK;
		
	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
	PORTE->PCR[24] |= PORT_PCR_MUX(5) | PORT_PCR_DSE_MASK;  //SCL0 i SDA0 init
	PORTE->PCR[25] |= PORT_PCR_MUX(5) | PORT_PCR_DSE_MASK;

	SIM->SCGC4 |= SIM_SCGC4_I2C1_MASK;
	PORTE->PCR[0] |= PORT_PCR_MUX(6) | PORT_PCR_DSE_MASK; //SCL1 i SDA1 init
	PORTE->PCR[1] |= PORT_PCR_MUX(6) | PORT_PCR_DSE_MASK;
	
	PORTD->PCR[5] = PORT_PCR_MUX(1);                       //Pin 5 i 29 przeznaczone na LEDy
  PORTE->PCR[29] = PORT_PCR_MUX(1);                      
}
