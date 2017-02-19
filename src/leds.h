#ifndef leds_h
#define leds_h

void ledsInitialize(void);
void ledsInitialize_empty(void);
void ledsOff (void);
void ledsOn (void);
void ledGreenOff (void);
void ledGreenOn (void);
void ledRedOff (void);
void ledRedOn (void);

void startStopFSM(void);
void ledsService1ms(void);
void nextLedState(void);

unsigned char phaseA(void);
unsigned char phaseB(void);
unsigned char phaseC(void);

void fastSlowFSM(void);
//void phaseNumber(void);

extern unsigned char slowFSM;


#endif
