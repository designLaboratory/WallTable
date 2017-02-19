#include "i2c.h"

void I2C0_init(void)
{
	I2C0->F = 0x20;		// BR => 300
	I2C0->C1 |= I2C_C1_IICEN_MASK;		// wlacz I2C0
}

void I2C1_init(void)
{
	I2C1->F = 0x20;		// BR => 300 kbps
	I2C1->C1 |= I2C_C1_IICEN_MASK;		// wlacz I2C1
}

void I2C_en(I2C_Type *I2C)
{
	I2C->C1 |= I2C_C1_IICEN_MASK;		// wlaczamy I2C				
}

void I2C_dis(I2C_Type *I2C)
{
	I2C->C1 &= ~I2C_C1_IICEN_MASK;		// wylaczamy I2C
}

void I2C_TX(I2C_Type *I2C)
{
	I2C->C1 |= I2C_C1_TX_MASK;		// I2C transmiter
}

void I2C_RX(I2C_Type *I2C)
{
	I2C->C1 &= ~I2C_C1_TX_MASK;		// I2C odbiorca
}

void I2C_start(I2C_Type *I2C)
{

	I2C_TX(I2C);
	I2C1->C1 |= I2C_C1_MST_MASK;		// generator sygnalu Start
}

void I2C_stop(I2C_Type *I2C)
{
	I2C1->C1 &= ~I2C_C1_MST_MASK;		// generator sygnalu Stop
	I2C_RX(I2C);
}

void I2C_restart(I2C_Type *I2C)
{
	I2C->C1 |= I2C_C1_RSTA_MASK;					// restart, ponowna generacja sygnalu Start
}

void I2C_ack(I2C_Type *I2C)
{
	I2C->C1 &= ~I2C_C1_TXAK_MASK;				//  ACK do rozpoznania trybu
}

void I2C_nack(I2C_Type *I2C)
{
	I2C->C1 |= I2C_C1_TXAK_MASK;					// NACK do rozpoznania trybu
}

uint8_t check_ACK(I2C_Type *I2C)
{
	if (!(I2C->S & I2C_S_RXAK_MASK)) return 0;   	// sprawdzenie czy odczytano bajt 
	else return 1;		
}

void I2C_send(I2C_Type *I2C, uint8_t data)
{
	I2C->D = data;												// wyslanie jednego bajtu
}

uint8_t I2C_read(I2C_Type *I2C)
{
	uint8_t data;													// odczytanie jednego bajtu
	data = I2C->D;
	return data;
}

void I2C_wait(I2C_Type *I2C)
{
	while (!(I2C->S & I2C_S_IICIF_MASK)) {}		// czekanie na koniec transmisji (koniec przerwania)
	I2C->S |= I2C_S_IICIF_MASK;		// czyszczenie flagi przerwania 
}

uint8_t I2C_read_cycle(I2C_Type *I2C, uint8_t mpu_add, uint8_t read_reg)  //funkcja odczyujaca
{
	uint8_t dt;		// zmienna z wartosciami odczytywanymi

	I2C_en(I2C);
	I2C_start(I2C);

	I2C_send(I2C, mpu_add);
	I2C_wait(I2C);
	check_ACK(I2C);

	I2C_send(I2C, read_reg);
	I2C_wait(I2C);
	check_ACK(I2C);

	I2C_restart(I2C);
	I2C_send(I2C, mpu_add + 1);
	I2C_wait(I2C);
	check_ACK(I2C);

	I2C_RX(I2C);
	dt = I2C_read(I2C);
	I2C_nack(I2C);
	I2C_wait(I2C);
	dt = I2C_read(I2C);

	I2C_stop(I2C);
	I2C_dis(I2C);

	return dt;
}


void I2C_write_cycle(I2C_Type *I2C, uint8_t mpu_write_add, uint8_t write_reg, uint8_t dt) //funkcja zapisujaca
{
	I2C_en(I2C);
	I2C_start(I2C);

	I2C_send(I2C, mpu_write_add);
	I2C_wait(I2C);
	check_ACK(I2C);

	I2C_send(I2C, write_reg);
	I2C_wait(I2C);
	check_ACK(I2C);

	I2C_send(I2C, dt);
	I2C_wait(I2C);
	check_ACK(I2C);

	I2C_stop(I2C);
	I2C_dis(I2C);
}
