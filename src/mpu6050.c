#include "MKL46Z4.h"
#include "i2c.h"
#include "mpu6050.h"

uint8_t mpu_init()  // MPU5060 init
{
	I2C1_init();

	if (!check()) return 0;

	//Sets sample rate to 8000/1+7 = 1000Hz
	write_byte(MPU6050_RA_SMPLRT_DIV, 0x07);
	//Disable FSync, 256Hz DLPF
	write_byte(MPU6050_RA_CONFIG, 0x00);
	//Disable gyro self tests, scale of 500 degrees/s
	write_byte(MPU6050_RA_GYRO_CONFIG, 0x08);
	//Disable accel self tests, scale of +-2g, no DHPF
	write_byte(MPU6050_RA_ACCEL_CONFIG, 0x00);
	//Freefall threshold of |0mg|
	write_byte(MPU6050_RA_FF_THR, 0x00);
	//Freefall duration limit of 0
	write_byte(MPU6050_RA_FF_DUR, 0x00);
	//Motion threshold of 0mg
	write_byte(MPU6050_RA_MOT_THR, 0x00);
	//Motion duration of 0s
	write_byte(MPU6050_RA_MOT_DUR, 0x00);
	//Zero motion threshold
	write_byte(MPU6050_RA_ZRMOT_THR, 0x00);
	//Zero motion duration threshold
	write_byte(MPU6050_RA_ZRMOT_DUR, 0x00);
	//Disable sensor output to FIFO buffer
	write_byte(MPU6050_RA_FIFO_EN, 0x00);

	//AUX I2C setup
	//Sets AUX I2C to single master control, plus other config
	write_byte(MPU6050_RA_I2C_MST_CTRL, 0x00);
	//Setup AUX I2C slaves
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

	//Setup INT pin and AUX I2C pass through
	write_byte(MPU6050_RA_INT_PIN_CFG, 0x00);
	//Enable data ready interrupt
	write_byte(MPU6050_RA_INT_ENABLE, 0x00);

	//Slave out, dont care
	write_byte(MPU6050_RA_I2C_SLV0_DO, 0x00);
	write_byte(MPU6050_RA_I2C_SLV1_DO, 0x00);
	write_byte(MPU6050_RA_I2C_SLV2_DO, 0x00);
	write_byte(MPU6050_RA_I2C_SLV3_DO, 0x00);
	//More slave config
	write_byte(MPU6050_RA_I2C_MST_DELAY_CTRL, 0x00);
	//Reset sensor signal paths
	write_byte(MPU6050_RA_SIGNAL_PATH_RESET, 0x00);
	//Motion detection control
	write_byte(MPU6050_RA_MOT_DETECT_CTRL, 0x00);
	//Disables FIFO, AUX I2C, FIFO and I2C reset bits to 0
	write_byte(MPU6050_RA_USER_CTRL, 0x00);
	//Sets clock source to gyro reference w/ PLL
	write_byte(MPU6050_RA_PWR_MGMT_1, 0x02);
	//Controls frequency of wakeups in accel low power mode plus the sensor standby modes
	write_byte(MPU6050_RA_PWR_MGMT_2, 0x00);
	//Data transfer to and from the FIFO buffer
	write_byte(MPU6050_RA_FIFO_R_W, 0x00);

	return 1;

}

uint8_t read_byte(uint8_t read_reg)
{
	return I2C_read_cycle(I2C1, MPU6050_ADDRESS, read_reg);		// read one byte from MPU
}

void write_byte(uint8_t writeregister, uint8_t data)
{
	I2C_write_cycle(I2C1, MPU6050_ADDRESS, writeregister, data);		// write one byte to MPU
}

void get_data(int16_t *raw_data)
{
	raw_data[0] = read_byte(MPU6050_RA_ACCEL_XOUT_H) << 8;			// MPU data to int array
	raw_data[0] |= read_byte(MPU6050_RA_ACCEL_XOUT_L);

	raw_data[1] = read_byte(MPU6050_RA_ACCEL_YOUT_H) << 8;
	raw_data[1] |= read_byte(MPU6050_RA_ACCEL_YOUT_L);

	raw_data[2] = read_byte(MPU6050_RA_ACCEL_ZOUT_H) << 8;
	raw_data[2] |= read_byte(MPU6050_RA_ACCEL_ZOUT_L);
}

uint8_t check(void)
{
	uint8_t result = 0;

	result = I2C_read_cycle(I2C1, MPU6050_ADDRESS, MPU6050_RA_WHO_AM_I);

	if (result == 0x68) return 1; // OK
	else return 0;		// EERROR
}
