
#include "gpio.h"
#include "i2c.h"
#include "leds.h"
#include "mpu6050.h"
void SysTick_Handler(void)
{
	
 int16_t results[3];
volatile int16_t z;
volatile int16_t x;
volatile	int16_t y;
	
get_data(results);	
x=results[0];
y=results[1];
z=results[2];
	if(z<7500){
		
		ledGreenOff();
		
	}
	
		else {
			ledGreenOn();
			}
}

int main(){

	
	ledsInitialize_empty(); 
	SystemCoreClockUpdate();		// SysTick init
	SysTick_Config(SystemCoreClock / 10);
	//I2C0_init();
	//I2C1_ini
	mpu_init();
		while (1)
	{
		
	}
}
