/*----------------------------------------------------------------------------
 *      
 *----------------------------------------------------------------------------
 *      Name:    LEDS.C
 *      Purpose: Microprocessors Laboratory
 *----------------------------------------------------------------------------
 *      
 *      Author: Pawel Russek AGH University of Science and Technology
 *---------------------------------------------------------------------------*/

#include "MKL46Z4.h"                    //Device header
#include "leds.h"												//Declarations

const uint32_t red_mask= 1UL<<5;				//Red led is Port D bit 5
const uint32_t green_mask= 1UL<<29;			//Green led is Port C bit 5/


const unsigned int PHASE_DELAY_MS=400;		//FSM delay 
const unsigned char PHASE_A=0;						//FSM state Red=on Green=off
const unsigned char PHASE_B=1;						//FSM state Red=off Green=on
const unsigned char PHASE_C=2;						//FSM state Red=off Green=off
//const unsigned char PHASE_D=3;
//const unsigned char PHASE_E=4;

unsigned char slowFSM =1;									//FSM speed control flag. Initialize to 1: fast
unsigned char skipPhase = 0;							//Auxiliary variable to allow FSM slow mode					

unsigned char startFSM;										//FSM go control
unsigned char phase;											//FSM current state
unsigned int nextStateDelay;							//FSM delay counter

/*----------------------------------------------------------------------------
  Function that initializes LEDs
 *----------------------------------------------------------------------------*/
 void ledsInitialize_empty(void) {
	 SIM->SCGC5 |=  (SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK);      /* Enable Clock to Port D & E */ 
  PORTD->PCR[5] = PORT_PCR_MUX(1);                       /* Pin PTD5 is GPIO */
  PORTE->PCR[29] = PORT_PCR_MUX(1);                      /* Pin PTE29 is GPIO */
  
	FPTD->PSOR = red_mask	;          /* switch Red LED off */
	FPTE->PSOR = green_mask	;        /* switch Green LED off */
  FPTD->PDDR = red_mask	;          /* enable PTB18/19 as Output */
	FPTE->PDDR = green_mask	;  
 }
void ledsInitialize(void) {
volatile int delay;
	
//Initialize registers	
  SIM->SCGC5 |=  (SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK);      /* Enable Clock to Port D & E */ 
  PORTD->PCR[5] = PORT_PCR_MUX(1);                       /* Pin PTD5 is GPIO */
  PORTE->PCR[29] = PORT_PCR_MUX(1);                      /* Pin PTE29 is GPIO */
  
	FPTD->PSOR = red_mask	;          /* switch Red LED off */
	FPTE->PSOR = green_mask	;        /* switch Green LED off */
  FPTD->PDDR = red_mask	;          /* enable PTB18/19 as Output */
	FPTE->PDDR = green_mask	;        /* enable PTB18/19 as Output */
	
	nextStateDelay=0;
	phase=PHASE_A;
	startFSM=1;

//Welcome sequence
	for(delay=0; delay<300000; delay++);
	FPTD->PCOR = red_mask	;          /* switch Red LED on */
	for(delay=0; delay<300000; delay++);
	FPTD->PSOR = red_mask	;          /* switch Red LED off */
	for(delay=0; delay<300000; delay++);
	FPTD->PCOR = red_mask	;          /* switch Red LED on */
	for(delay=0; delay<300000; delay++);
	FPTD->PSOR = red_mask	;          /* switch Red LED off */
	for(delay=0; delay<300000; delay++);
	FPTD->PCOR = red_mask	;          /* switch Red LED on */
	for(delay=0; delay<300000; delay++);
	FPTD->PSOR = red_mask	;          /* switch Red LED off */
	
	for(delay=0; delay<600000; delay++);
	FPTE->PCOR = green_mask	;          /* switch Green LED on */
	for(delay=0; delay<600000; delay++);
	FPTE->PSOR = green_mask	;          /* switch Green LED off */
	for(delay=0; delay<600000; delay++);
	FPTE->PCOR = green_mask	;          /* switch Green LED on */
	for(delay=0; delay<600000; delay++);
	FPTE->PSOR = green_mask	;          /* switch Green LED off */
	for(delay=0; delay<600000; delay++);
	FPTE->PCOR = green_mask	;          /* switch Green LED on */
	for(delay=0; delay<600000; delay++);
	FPTE->PSOR = green_mask	;          /* switch Green LED off */
	
	for(delay=0; delay<1200000; delay++);
	FPTD->PCOR = red_mask	;          /* switch Red LED on */
	FPTE->PCOR = green_mask	;        /* switch Green LED on */
	for(delay=0; delay<6000000; delay++);
	FPTD->PSOR = red_mask	;          /* switch Red LED off */
	FPTE->PSOR = green_mask	;        /* switch Green LED off */
}


/*----------------------------------------------------------------------------
  Function that turns on Red LED
 *----------------------------------------------------------------------------*/
void ledRedOn (void) {
		FPTE->PCOR=green_mask;       		/* switch Green LED on */
	FPTD->PSOR=red_mask;          /* switch Green LED off */
}

/*----------------------------------------------------------------------------
  Function that turns on Green LED
 *----------------------------------------------------------------------------*/
void ledGreenOn (void) {

FPTD->PCOR=red_mask;
FPTE->PSOR=green_mask; 	/* switch Red LED off  */
}
void ledGreenOff (void) {
	FPTE->PSOR=green_mask;       		/* switch Green LED on */
	FPTD->PSOR=red_mask;
	/* switch Red LED off  */
}
void ledRedOff (void) {
	        FPTE->PSOR=green_mask;       		/* switch Green LED on */
					FPTD->PSOR=red_mask;	/* switch Red LED off  */
}
/*----------------------------------------------------------------------------
  Function that turns all LEDs off
 *----------------------------------------------------------------------------*/
void ledsOff (void) {
		FPTD->PSOR=red_mask;          /* switch Red LED off  */
	  FPTE->PSOR=green_mask;        /* switch Green LED off  */
}

/*----------------------------------------------------------------------------
  Function that turns all LEDs on
 *----------------------------------------------------------------------------*/
void ledsOn (void) {
		//FPTD->PCOR=red_mask;      	/* switch Red LED on  */
	  FPTE->PCOR=green_mask;     	/* switch Green LED on */
}

/*----------------------------------------------------------------------------
 Function that moves FSM to phase A 
 *----------------------------------------------------------------------------*/
unsigned char phaseA(void){
	ledsOff();
	ledRedOn();
	return PHASE_B;								/*Return next state of FSM*/
}

/*----------------------------------------------------------------------------
 Function that moves FSM to phase B   
 *----------------------------------------------------------------------------*/
unsigned char phaseB(void){
	ledsOff();
	ledGreenOn();
	return PHASE_C;								/*Return next state of FSM*/				
}

/*----------------------------------------------------------------------------
 Function that moves FSM to phase C     
 *----------------------------------------------------------------------------*/
unsigned char phaseC(void){
	ledsOff();
	return PHASE_A;								/*Return next state of FSM*/
}

/*----------------------------------------------------------------------------
 Function that moves FSM to phase D   
 *----------------------------------------------------------------------------*/
/*unsigned char phaseD(void){
	ledsOff();
	ledGreenOn();
	ledRedOn();
	return PHASE_E;								//Return next state of FSM				
}*/

/*----------------------------------------------------------------------------
 Function that moves FSM to phase B   
 *----------------------------------------------------------------------------*/
/*unsigned char phaseE(void){
	ledsOff();
	return PHASE_D;								//Return next state of FSM				
}*/

/*----------------------------------------------------------------------------
 Function that stops FSM transitions     
 *----------------------------------------------------------------------------*/
void startStopFSM(void){
	startFSM^=1;
}

/*----------------------------------------------------------------------------
 Every 1 ms function that makes FSM run    
 *----------------------------------------------------------------------------*/
void ledsService1ms (void) {	
 
	if(nextStateDelay!=PHASE_DELAY_MS){
		nextStateDelay+=startFSM;
		return;
	}
	nextStateDelay=0;
	
	nextLedState();
	
}

/*----------------------------------------------------------------------------
 Function that makes FSM transition to the next state  
 *----------------------------------------------------------------------------*/
void nextLedState (void) {	
 
	/** Allow slower FSM transition */
	if (slowFSM==0) {
			skipPhase+=1;
			if( (skipPhase%3) != 0 ) return;		/* Every third call passes  to switch clause*/
	}
	/**/
	
	switch(phase){
		case PHASE_A:
			phase=phaseA();
			break;
		case PHASE_B:
			phase=phaseB();
		  break;
		/*case PHASE_D:
			phase=phaseD();
			break;
		case PHASE_E:
			phase=phaseE();
			break;*/
		default:
			phase=phaseC();
		  break;
	}
}

/*----------------------------------------------------------------------------
 Function controls transition speed of the FSM  
 *----------------------------------------------------------------------------*/
void fastSlowFSM(void){
	
	slowFSM^=1;				/* Toggle speed mode */

}

/*void phaseNumber(void){
	
	phase=3;				// Toggle speed mode 
	
}*/