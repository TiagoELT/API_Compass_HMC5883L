/*
* Data: 14/11/2022
* Universidade: UFMG - Universidade Federal de Minas Gerais
* Autores: Eduardo Cardoso Mendes e Tiago Rezende Valadares
* Versão: 1.0
* Tipo de licença:
* Nome da api: HMC5883L
* Arquivos: 
*        - HMC5883L.c
*        - HMC5883L.h
* Requisitos de hardware: 
*   - Módulo Bússola Eletrônica HMC5883L
      Datasheet: 
      https://www.generationrobots.com/media/module%20boussole%203%20axes%20HMC5883L/29133-HMC5883L-Compass-Module-IC-Documentation-v1.0.pdf
*   - Kit NUCLEO 64 – STM32F103RB
* Requisitos de software: 
*   - STM32CubeIDE 1.6.1 
*     Disponível em: https://www.st.com/en/development-tools/stm32cubeide.html
*
* Esta API foi desenvolvida como trabalho da disciplina de Programação de 
* Sistemas Embarcados da UFMG – Prof. Ricardo de Oliveira Duarte – 
* Departamento de Engenharia Eletrônica”.
*/

/*
NOTES:
*** Polling mode IO operation ***
    =================================
    [..]
      (+) Transmit in master mode an amount of data in blocking mode using @ref HAL_I2C_Master_Transmit()
      (+) Receive in master mode an amount of data in blocking mode using @ref HAL_I2C_Master_Receive()
      (+) Transmit in slave mode an amount of data in blocking mode using @ref HAL_I2C_Slave_Transmit()
      (+) Receive in slave mode an amount of data in blocking mode using @ref HAL_I2C_Slave_Receive()

*/

/**
  * brief  Transmits in master mode an amount of data in blocking mode.
  * param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * param  DevAddress Target device address: The device 7 bits address value
  *         in datasheet must be shifted to the left before calling the interface
  * param  pData Pointer to data buffer
  * param  Size Amount of data to be sent
  * param  Timeout Timeout duration
  * retval HAL status
  
HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
*/

/**
  * brief  Receives in master mode an amount of data in blocking mode.
  * param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * param  DevAddress Target device address: The device 7 bits address value
  *         in datasheet must be shifted to the left before calling the interface
  * param  pData Pointer to data buffer
  * param  Size Amount of data to be sent
  * param  Timeout Timeout duration
  * retval HAL status
  
HAL_StatusTypeDef HAL_I2C_Master_Receive(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
*/

#include "HMC5883L.h"

extern I2C_HandleTypeDef hi2c1;

#define TIMEOUT 100

void write_register(uint8_t register_pointer, uint8_t register_value){
    uint8_t data[2];

    data[0] = register_pointer;
    data[1] = register_value;

    HAL_I2C_Master_Transmit(&hi2c1, HMC5883L_ADDRESS, data, 2, 100);  // data is the start pointer of our array
}

void read_register(uint8_t register_pointer, uint8_t* receive_buffer){
    // first set the register pointer to the register wanted to be read
    HAL_I2C_Master_Transmit(&hi2c1, HMC5883L_ADDRESS, &register_pointer, 1, 100); 

    // receive the 1 x 8bit data into the receive buffer
    HAL_I2C_Master_Receive(&hi2c1, HMC5883L_ADDRESS, receive_buffer, 1, 100);   
}

int8_t I2Cdev_writeBits(uint8_t reg_addr, uint8_t start_bit,
		uint8_t len, uint8_t data){
    uint8_t b;
    int8_t err;

    if ((err = I2Cdev_readByte(reg_addr, &b)) == 0) {
        uint8_t mask = ((1 << len) - 1) << (start_bit - len + 1);
        data <<= (start_bit - len + 1); // shift data into correct position
        data &= mask; // zero all non-important bits in data
        b &= ~(mask); // zero all important bits in existing byte
        b |= data; // combine data with existing byte

        return write_register(reg_addr, b);
    }
    else {
        return err;
    }
}

int8_t I2Cdev_readBits(uint8_t reg_addr, uint8_t start_bit, 
		uint8_t len, uint8_t *data){
	int8_t err;

	uint8_t b;
	if ((err = read_register(reg_addr, &b)) == 0) {
		uint8_t mask = ((1 << len) - 1) << (start_bit - len + 1);
		b &= mask;
		b >>= (start_bit - len + 1);
		*data = b;
	}

	return err;
}


// Configuration Functions

// Configuration Register A

uint8_t HMC5883L_getSampleAveraging(){
  // TODO
  I2Cdev_readBits(REG_CONFIG_A, HMC5883L_CRA_SA_POS, HMC5883L_CRA_SA_TAM, buffer);
  return buffer[0];
}

void HMC5883L_setSampleAveraging(uint8_t averaging){
  I2Cdev_writeBits(REG_CONFIG_A, HMC5883L_CRA_SA_POS, HMC5883L_CRA_SA_TAM, averaging);
}

uint8_t HMC5883L_getDataRate(){
  //TODO
  I2Cdev_readBits(REG_CONFIG_A, HMC5883L_CRA_DATARATE_POS, HMC5883L_CRA_DATARATE_TAM, buffer);
  return buffer[0];
}

void HMC5883L_setDataRate(uint8_t rate){
  I2Cdev_writeBits(REG_CONFIG_A, HMC5883L_CRA_DATARATE_POS, HMC5883L_CRA_DATARATE_TAM, rate);
}

uint8_t HMC5883L_getMeasurementMode(){
  I2Cdev_readBits(REG_CONFIG_A, HMC5883L_CRA_MM_POS, HMC5883L_CRA_MM_TAM, buffer);
  return buffer[0];
}

void HMC5883L_setMeasurementMode(uint8_t bias){
  I2Cdev_writeBits(REG_CONFIG_A, HMC5883L_CRA_MM_POS, HMC5883L_CRA_MM_TAM, bias);
}


// CONFIG_B register
uint8_t HMC5883L_getRange(){
  I2Cdev_readBits(REG_CONFIG_B, HMC5883L_CRB_RANGE_POS, HMC5883L_CRB_RANGE_TAM, buffer);
  return buffer[0];
}

void HMC5883L_setRange(uint8_t range){
  I2Cdev_writeByte(REG_CONFIG_B, range << (HMC5883L_CRB_RANGE_POS - HMC5883L_CRB_RANGE_TAM + 1));
}

// MODE register
uint8_t HMC5883L_getMode(){
  I2Cdev_readBits(REG_MODE, HMC5883L_MODEREG_POS, HMC5883L_MODEREG_TAM, buffer);
  return buffer[0];
}

void HMC5883L_setMode(uint8_t mode){
  I2Cdev_writeByte(REG_MODE, newMode << (HMC5883L_MODEREG_POS - HMC5883L_MODEREG_TAM + 1));
}

// General Functions
void HMC5883L_initialize(){
     // write CONFIG_A register
    I2Cdev_writeByte(REG_CONFIG_A,
        (HMC5883L_SAMPLE_AVERAGE_8 << (HMC5883L_CRA_SA_POS - HMC5883L_CRA_SA_TAM + 1)) |
        (HMC5883L_DATARATE_15HZ     << (HMC5883L_CRA_DATARATE_POS - HMC5883L_CRA_DATARATE_TAM + 1)) |
        (HMC5883L_MEAS_MODE_NORMAL << (HMC5883L_CRA_MM_POS - HMC5883L_CRA_MM_TAM + 1)));

    // write CONFIG_B register
    HMC5883L_setRange(HMC5883L_RANGE_1_3GA);

    // write MODE register
    HMC5883L_setMode(HMC5883L_MODE_SINGLE);
}

void HMC5883L_measurement(int16_t *x, int16_t *y, int16_t *z){
  I2Cdev_readBytes(REG_DATA_OUT_X_MSB, 6, buffer);
  if (mode == HMC5883L_MODE_SINGLE){
    I2Cdev_writeByte(REG_MODE, HMC5883L_MODE_SINGLE << (HMC5883L_MODEREG_POS - HMC5883L_MODE_IDLE + 1));
  }
  *x = (((int16_t)buffer[0]) << 8) | buffer[1];
  *y = (((int16_t)buffer[4]) << 8) | buffer[5];
  *z = (((int16_t)buffer[2]) << 8) | buffer[3];
}