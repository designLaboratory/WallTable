#include "MKL46Z4.h"                    
#include "leds.h"												

const uint32_t red_mask= 1UL<<5;				//Czerwona Port D bit 5
const uint32_t green_mask= 1UL<<29;			//Zielona	 Port C bit 5/

/*----------------------------------------------------------------------------
  Funkcja inicializujaca diody LED
 *----------------------------------------------------------------------------*/
 void ledsInitialize(void) 
{
	FPTD->PSOR = red_mask	;
	FPTE->PSOR = green_mask	;        
  FPTD->PDDR = red_mask	;          
	FPTE->PDDR = green_mask	;  
}

/*----------------------------------------------------------------------------
  Funkcja wlaczajaca czerwona diode LED
 *----------------------------------------------------------------------------*/
void ledRedOn (void) 
{
	FPTE->PCOR=green_mask;       		
	FPTD->PSOR=red_mask;          
}

/*----------------------------------------------------------------------------
 Funkcja wlaczajaca zielona diode LED
 *----------------------------------------------------------------------------*/
void ledGreenOn (void) 
{
	
	FPTD->PCOR=red_mask;
	FPTE->PSOR=green_mask; 
	
}
/*----------------------------------------------------------------------------
  Funkcja wylaczajaca wszystkie diody
 *----------------------------------------------------------------------------*/
void ledsOff (void) 
{
		FPTD->PSOR=red_mask;          
	  FPTE->PSOR=green_mask;        
}

/*----------------------------------------------------------------------------
  Funkcja wlaczajaca wszystkie diody
 *----------------------------------------------------------------------------*/
void ledsOn (void) 
{
		FPTD->PCOR=red_mask;      	
	  FPTE->PCOR=green_mask;     	
}



