#include "MKL46Z4.h"
#include "i2c.h"
#include "mpu6050.h"

uint8_t mpu_init()  // MPU5060 init
{
	I2C1_init();

	if (!check()) return 0;

	
	write_byte(MPU6050_RA_SMPLRT_DIV, 0x07); 		//Czestotliwosc probkowania 1000Hz
	write_byte(MPU6050_RA_CONFIG, 0x00);				//Wylacz FSync
	write_byte(MPU6050_RA_GYRO_CONFIG, 0x08); 	//Test zyroskopu wylaczony
	write_byte(MPU6050_RA_ACCEL_CONFIG, 0x00);	//Test akcelerometru wylaczony
	write_byte(MPU6050_RA_FF_THR, 0x00);				//Ustawienie wartosci dla swobodnego spadku (czas i prog)
	write_byte(MPU6050_RA_FF_DUR, 0x00);				
	write_byte(MPU6050_RA_MOT_THR, 0x00);				//Ustawienie wartosci dla ruchu (czas i prog)
	write_byte(MPU6050_RA_MOT_DUR, 0x00);			
	write_byte(MPU6050_RA_ZRMOT_THR, 0x00);			
	write_byte(MPU6050_RA_ZRMOT_DUR, 0x00);			
	write_byte(MPU6050_RA_FIFO_EN, 0x00);				//Wyjscie sensora do buforu FIFO 

	//Konfiguracja I2C
	
	write_byte(MPU6050_RA_I2C_MST_CTRL, 0x00); //Ustawianie jednego mastera do I2C 
	//Ustawianie pozostalych niezbednych slave'ow I2C//
	write_byte(MPU6050_RA_I2C_SLV0_ADDR, 0x00);
	write_byte(MPU6050_RA_I2C_SLV0_REG, 0x00);
	write_byte(MPU6050_RA_I2C_SLV0_CTRL, 0x00);
	write_byte(MPU6050_RA_I2C_SLV1_ADDR, 0x00);
	write_byte(MPU6050_RA_I2C_SLV1_REG, 0x00);
	write_byte(MPU6050_RA_I2C_SLV1_CTRL, 0x00);
	write_byte(MPU6050_RA_I2C_SLV2_ADDR, 0x00);
	write_byte(MPU6050_RA_I2C_SLV2_REG, 0x00);
	write_byte(MPU6050_RA_I2C_SLV2_CTRL, 0x00);
	write_byte(MPU6050_RA_I2C_SLV3_ADDR, 0x00);
	write_byte(MPU6050_RA_I2C_SLV3_REG, 0x00);
	write_byte(MPU6050_RA_I2C_SLV3_CTRL, 0x00);
	write_byte(MPU6050_RA_I2C_SLV4_ADDR, 0x00);
	write_byte(MPU6050_RA_I2C_SLV4_REG, 0x00);
	write_byte(MPU6050_RA_I2C_SLV4_DO, 0x00);
	write_byte(MPU6050_RA_I2C_SLV4_CTRL, 0x00);
	write_byte(MPU6050_RA_I2C_SLV4_DI, 0x00);

	//Konfiguracja pinu INT
	write_byte(MPU6050_RA_INT_PIN_CFG, 0x00);
	//Wlacz przerwanie od gotowosci danych
	write_byte(MPU6050_RA_INT_ENABLE, 0x00);

	//Wyjscia slave
	write_byte(MPU6050_RA_I2C_SLV0_DO, 0x00);
	write_byte(MPU6050_RA_I2C_SLV1_DO, 0x00);
	write_byte(MPU6050_RA_I2C_SLV2_DO, 0x00);
	write_byte(MPU6050_RA_I2C_SLV3_DO, 0x00);

	write_byte(MPU6050_RA_I2C_MST_DELAY_CTRL, 0x00); 	
	write_byte(MPU6050_RA_SIGNAL_PATH_RESET, 0x00);		//Reset sciezek sygnalu 
	write_byte(MPU6050_RA_MOT_DETECT_CTRL, 0x00);			//Wykrywanie ruchu
	write_byte(MPU6050_RA_USER_CTRL, 0x00);						//FIFO i I2C wylaczone
	write_byte(MPU6050_RA_PWR_MGMT_1, 0x02);					//Zrodlo zegara
	write_byte(MPU6050_RA_PWR_MGMT_2, 0x00);					//Kontrola w LPM
	write_byte(MPU6050_RA_FIFO_R_W, 0x00);						//Transfer danych

	return 1;

}

uint8_t read_byte(uint8_t read_reg)
{
	return I2C_read_cycle(I2C1, MPU6050_ADDRESS, read_reg);		// Odczyt jednego bajta z MPU
}

void write_byte(uint8_t writeregister, uint8_t data)
{
	I2C_write_cycle(I2C1, MPU6050_ADDRESS, writeregister, data);		// Zapis jednego bajta do MPU
}

void get_data(int16_t *raw_data)
{
	raw_data[0] = read_byte(MPU6050_RA_ACCEL_XOUT_H) << 8;			// Przesylanie danych do tablicy w celu dalszej obrobki
	raw_data[0] |= read_byte(MPU6050_RA_ACCEL_XOUT_L);					//X

	raw_data[1] = read_byte(MPU6050_RA_ACCEL_YOUT_H) << 8;
	raw_data[1] |= read_byte(MPU6050_RA_ACCEL_YOUT_L);					//Y

	raw_data[2] = read_byte(MPU6050_RA_ACCEL_ZOUT_H) << 8;
	raw_data[2] |= read_byte(MPU6050_RA_ACCEL_ZOUT_L);					//Z
}

uint8_t check(void)
{
	uint8_t result = 0;																				//Sprawdzanie czy wszystko ok podczas operacji
	result = I2C_read_cycle(I2C1, MPU6050_ADDRESS, MPU6050_RA_WHO_AM_I);
	if (result == 0x68) 
		return 1; // Jest dobrze
	else 
		return 0;		// Error
}
