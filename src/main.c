
#include "gpio.h"
#include "i2c.h"
#include "mpu6050.h"
#include "leds.h"
void SysTick_Handler(void)
{
	
	// temp array to store MPU data
 int16_t results[3];
volatile int16_t z;
volatile int16_t x;
volatile	int16_t y;
	
get_data(results);	
x=results[0];
y=results[1];
z=results[2];
	if(z<7000){
		ledsOn();
	}
		else {
		ledGreenOff();
		}
	

	


}

int main(){

	
	ledsInitialize(); 
	SystemCoreClockUpdate();		// SysTick init
	SysTick_Config(SystemCoreClock / 10);
	//I2C0_init();
	//I2C1_init();
	 mpu_init();
		while (1)
	{
		
	}
}
