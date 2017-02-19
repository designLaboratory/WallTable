#ifndef _I2C_H_
#define _I2C_H_
#include <MKL46Z4.h>
#include "gpio.h"

void I2C0_init(void);		// init of I2C0
void I2C1_init(void);		// init of I2C1

void I2C_en(I2C_Type *I2C_mod);		// enable I2C module
void I2C_dis(I2C_Type *I2C_mod);		// disable I2C module
void I2C_TX(I2C_Type *I2C_mod);		// mode: transmiter
void I2C_RX(I2C_Type *I2C_mod);		// mode: reciver

void I2C_start(I2C_Type *I2C_mod);		// send start signal
void I2C_stop(I2C_Type *I2C_mod);		// send stop signal
void I2C_restart(I2C_Type *I2C_mod);		// send restart signal
void I2C_ack(I2C_Type *I2C_mod);		// send ACK signal
void I2C_nack(I2C_Type *I2C_mod);		// send NACK signal
uint8_t check_ACK(I2C_Type *I2C_mod);		// check slave answer

void I2C_send(I2C_Type *I2C_mod, uint8_t data);		// send byte
uint8_t I2C_read(I2C_Type *I2C_mod);		// read byte
void I2C_wait(I2C_Type *I2C_module);		// wait for end of transmission

uint8_t I2C_read_cycle(I2C_Type *I2C_mod, uint8_t dev_address, uint8_t read_register);		// reads one byte form slave devices
void I2C_write_cycle(I2C_Type *I2C_mod, uint8_t dev_write_address, uint8_t write_register, uint8_t data);		// writes one byte to the pointed register 


#endif