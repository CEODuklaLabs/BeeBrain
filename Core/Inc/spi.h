/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    spi.h
  * @brief   This file contains all the function prototypes for
  *          the spi.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_H__
#define __SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

#include "cuprexit.h"
/* USER CODE END Includes */

extern SPI_HandleTypeDef hspi3;

/* USER CODE BEGIN Private defines */
extern int8_t SPIRxBuffer[64];
extern int8_t SPITxBuffer[64];
/* USER CODE END Private defines */

void MX_SPI3_Init(void);

/* USER CODE BEGIN Prototypes */

/**
 * @brief  Funkce pro zapnutí příjmu a vysílání přes SPI DMA
 * @param  hspi Ukazatel na SPI periferii
 * @retval None
 * @note   None
 */
void SPI_RxTxON(SPI_HandleTypeDef *hspi);

/**
 * @brief  Funkce pro vybrání zařízení
 * @param  device Ukazatel na strukturu zařízení
 * @retval None
 * @note   None
 */
void selectDevice(CUPREXIT_Device *device);

/**
 * @brief  Funkce pro vybrání všech zařízení pro broadcast
 * @param  CU_devices Pole struktur zařízení
 * @retval None 
 */
void selectAllDevices(CUPREXIT_Device CU_devices[]);

/**
 * @brief  Funkce pro odvybrání zařízení
 * @param  device Ukazatel na strukturu zařízení
 * @retval None
 * @note   None
 */
void deselectDevice(CUPREXIT_Device *device);

/**
 * @brief  Funkce pro odvybrání všech zařízení
 * @param  CU_devices Pole struktur zařízení
 * @retval None
 * @note   None
 */
void deselectAllDevices(CUPREXIT_Device CU_devices[]);

/**
 * @brief  Funkce pro odeslání SPI příkazu
 * @param  device Ukazatel na strukturu zařízení
 * @param  command Příkaz pro zařízení
 * @param  data Data k odeslání
 * @param  size Velikost dat
 * @retval None
 * @note   Pokud je device NULL, odesílá se broadcast použitím 0xFF jako adresy
 */
void sendSPICommand(CUPREXIT_Device *device, CUPREXIT_Command command, uint8_t *data, uint8_t size);

/**
 * @brief  Funkce pro zpracování přijatých dat
 * @param  data Ukazatel na přijatá data
 * @retval None
 * @note   None
 */
void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __SPI_H__ */

