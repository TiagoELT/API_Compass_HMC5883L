/*
* Data: 14/11/2022
* Universidade: UFMG - Universidade Federal de Minas Gerais
* Autores: Eduarde e Tiago Rezende Valadares
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

#include "stm32f1xx_hal.h"

#define HMC5883L_ADDRESS      0x1E

#define REG_CONFIG_A          0x00
#define REG_CONFIG_B          0x01
#define REG_MODE              0x02
#define REG_DATA_OUT_X_MSB    0x03
#define REG_DATA_OUT_X_LSB    0x04
#define REG_DATA_OUT_Z_MSB    0x05
#define REG_DATA_OUT_Z_LSB    0x06
#define REG_DATA_OUT_Y_MSB    0x07
#define REG_DATA_OUT_Y_LSB    0x08
#define REG_STATUS            0x09
#define REG_IDENT_A           0x0A
#define REG_IDENT_B           0x0B
#define REG_IDENT_C           0x0C

// Configuration Register B
#define HMC5883L_RANGE_0_88GA	0x00,
#define HMC5883L_RANGE_1_3GA	0x20,
#define HMC5883L_RANGE_1_9GA	0x40,
#define HMC5883L_RANGE_2_5GA  0x60,
#define HMC5883L_RANGE_4GA    0x80,
#define HMC5883L_RANGE_4_7GA  0xA0,
#define HMC5883L_RANGE_5_7GA  0xC0,
#define HMC5883L_RANGE_8_1GA  0xE0

void HMC5883L_initialize();

void HMC5883L_calibration();

