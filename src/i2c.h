#ifndef _I2C_H_
#define _I2C_H_
#include <MKL46Z4.h>
#include "gpio.h"

void I2C0_init(void);		// I2C0 init
void I2C1_init(void);		// I2C1 init

void I2C_en(I2C_Type *I2C_mod);		// wlacz I2C
void I2C_dis(I2C_Type *I2C_mod);		// wylacz I2C
void I2C_TX(I2C_Type *I2C_mod);		// nadajnik
void I2C_RX(I2C_Type *I2C_mod);		// odbiornik

void I2C_start(I2C_Type *I2C_mod);		// wyslij sygnal Start
void I2C_stop(I2C_Type *I2C_mod);		// wyslij sygnal Stop
void I2C_restart(I2C_Type *I2C_mod);		// wyslij sygnal Reset
void I2C_ack(I2C_Type *I2C_mod);		// wyslij ACK
void I2C_nack(I2C_Type *I2C_mod);		// wyslij NACK
uint8_t check_ACK(I2C_Type *I2C_mod);		// sprawdz odpowiedz

void I2C_send(I2C_Type *I2C_mod, uint8_t data);		// wyslij bajt
uint8_t I2C_read(I2C_Type *I2C_mod);		// odczytaj bajt
void I2C_wait(I2C_Type *I2C_module);		// czekaj na koniec transmisji

uint8_t I2C_read_cycle(I2C_Type *I2C_mod, uint8_t dev_address, uint8_t read_register);		// czytaj jeden bajt z urzadzenia
void I2C_write_cycle(I2C_Type *I2C_mod, uint8_t dev_write_address, uint8_t write_register, uint8_t data);		// wpisz jeden bajt do danego rejestru


#endif