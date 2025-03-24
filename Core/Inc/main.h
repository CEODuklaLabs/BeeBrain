/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef enum {
  CUx_State_RESET             = 0x0FU,    /*!< CU0 not Initialized                           */
  CUx_State_READY             = 0x10U,    /*!< CU0 ready state                               */

} CU_StateTypeDef;

typedef enum{
USB_COMMAND_RESET           = 0x23U,    /*!< USB reset command                              */
USB_COMMAND_PING            = 0x24U,    /*!< USB ping command                               */
  USB_COMMAND_CONF         = 0x25U,    /*!< USB status command                             */
USB_COMMAND_GET_CU_CALIB    = 0x26U,    /*!< USB CU calibration command                     */
USB_COMMAND_SET_CU_CALIB    = 0x27U,    /*!< USB CU calibration command                     */
  USB_COMMAND_CU_STATUS       = 0x28U,    /*!< USB CU status command                          */
  USB_COMMAND_GET_MEAS        = 0x29U,    /*!< USB get measurements command                   */
USB_COMMAND_GET_AUDIO       = 0x2AU,    /*!< USB get FFT data command                       */
USB_COMMAND_CLIMA    = 0x2BU,    /*!< USB get temperature command                    */
  USB_COMMAND_SCD_CALIB       = 0x2CU,    /*!< USB SCD calibration command                    */
  USB_COMMAND_SCD_STATUS      = 0x2DU,    /*!< USB SCD status command                         */
USB_COMMAND_GET_CU_TEMP     = 0x2EU,    /*!< USB get CU temperature command                 */
} USB_COMMANDS;

typedef enum{
  CUx_DATA                    = 0x40U,    /*!< CU data 0x60-0x69                              */
  SCD_DATA                    = 0x50U,    /*!< SCD data command                              */
  AUDIO_DATA                    = 0x51U,    /*!< MIC data command                              */
  SCD_DATA_CALIB              = 0x52U,    /*!< SCD calibration data command                  */
  BEEBRAIN_STAT               = 0x53U,    /*!< BeeBrain status command                      */
  END_MASAGE                = 0xFFU     /*!< End of message command                        */
} DATA_DESCRIPTOR;



/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
#define NMBR_CU 10
#define NMBR_CU_TEMP 10
#define NMBR_Audio 100
#define WAV_WRITE_SAMPLE_COUNT 8192

#define STEREO 1
#define MONO 2
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
/**
 * @brief Resets the device.
 */
void resetDevice(void);




/**
 * @brief Retrieves data from the specified CU (Control Unit).
 * 
 * @param CU_number The number of the Control Unit.
 * @param command The command to be sent to the Control Unit.
 * @return uint8_t The data retrieved from the Control Unit.
 */
uint8_t getCUdata(uint8_t CU_number, uint8_t command);



/**
 * @brief Selects the specified device.
 * 
 * @param deviceNumber The number of the device to be selected.
 * @param select The selection state of the device. 0 for deselect, 1 for select.
 */
void selectDeselectDevice(uint8_t deviceNumber, uint8_t select);


/**
 * @brief Callback function called when SAI (Serial Audio Interface) receive is complete.
 * 
 * @param hsai Pointer to the SAI handle.
 */
void HAL_SAI_RxCpltCallback(SAI_HandleTypeDef *hsai);

/**
 * @brief Callback function called when SAI (Serial Audio Interface) receive is half complete.
 * 
 * @param hsai Pointer to the SAI handle.
 */
void HAL_SAI_RxHalfCpltCallback(SAI_HandleTypeDef *hsai);

/**
 * @brief Sends and receives an SPI command.
 *
 * This function sends a command to a specified control unit (CU) over SPI
 * and receives the response.
 *
 * @param CU_number The number of the control unit to communicate with.
 * @param command The command to send to the control unit.
 * @return 0 if the command was successful or error code if an error occurred.
 */
uint8_t sendRecieveSPICommand(uint8_t CU_number, uint8_t command);




/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define TEST_Pin GPIO_PIN_0
#define TEST_GPIO_Port GPIOC
#define CS_CU1_Pin GPIO_PIN_4
#define CS_CU1_GPIO_Port GPIOA
#define CS_CU3_Pin GPIO_PIN_5
#define CS_CU3_GPIO_Port GPIOA
#define CS_CU5_Pin GPIO_PIN_6
#define CS_CU5_GPIO_Port GPIOA
#define CS_CU7_Pin GPIO_PIN_7
#define CS_CU7_GPIO_Port GPIOA
#define CS_CU9_Pin GPIO_PIN_4
#define CS_CU9_GPIO_Port GPIOC
#define CS_CU8_Pin GPIO_PIN_0
#define CS_CU8_GPIO_Port GPIOB
#define CS_CU6_Pin GPIO_PIN_1
#define CS_CU6_GPIO_Port GPIOB
#define CS_CU4_Pin GPIO_PIN_2
#define CS_CU4_GPIO_Port GPIOB
#define CS_CU2_Pin GPIO_PIN_10
#define CS_CU2_GPIO_Port GPIOB
#define CS_CU0_Pin GPIO_PIN_11
#define CS_CU0_GPIO_Port GPIOB
#define STAT_Pin GPIO_PIN_12
#define STAT_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
