/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : SAI.c
  * Description        : This file provides code for the configuration
  *                      of the SAI instances.
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

/* Includes ------------------------------------------------------------------*/
#include "sai.h"
#include "usbd_cdc_if.h"

/* USER CODE BEGIN 0 */
extern int32_t data_mic_left[WAV_WRITE_SAMPLE_COUNT/4];
extern int32_t data_mic_right[WAV_WRITE_SAMPLE_COUNT/4];
/* USER CODE END 0 */

SAI_HandleTypeDef hsai_BlockB1;
DMA_HandleTypeDef hdma_sai1_b;

/* SAI1 init function */
void MX_SAI1_Init(void)
{

  /* USER CODE BEGIN SAI1_Init 0 */

  /* USER CODE END SAI1_Init 0 */

  /* USER CODE BEGIN SAI1_Init 1 */

  /* USER CODE END SAI1_Init 1 */

  hsai_BlockB1.Instance = SAI1_Block_B;
  hsai_BlockB1.Init.AudioMode = SAI_MODEMASTER_RX;
  hsai_BlockB1.Init.Synchro = SAI_ASYNCHRONOUS;
  hsai_BlockB1.Init.OutputDrive = SAI_OUTPUTDRIVE_DISABLE;
  hsai_BlockB1.Init.NoDivider = SAI_MASTERDIVIDER_ENABLE;
  hsai_BlockB1.Init.FIFOThreshold = SAI_FIFOTHRESHOLD_EMPTY;
  hsai_BlockB1.Init.AudioFrequency = SAI_AUDIO_FREQUENCY_96K;
  hsai_BlockB1.Init.SynchroExt = SAI_SYNCEXT_DISABLE;
  hsai_BlockB1.Init.MonoStereoMode = SAI_STEREOMODE;
  hsai_BlockB1.Init.CompandingMode = SAI_NOCOMPANDING;
  if (HAL_SAI_InitProtocol(&hsai_BlockB1, SAI_I2S_STANDARD, SAI_PROTOCOL_DATASIZE_16BIT, 2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SAI1_Init 2 */

  /* USER CODE END SAI1_Init 2 */

}
static uint32_t SAI1_client =0;

void HAL_SAI_MspInit(SAI_HandleTypeDef* saiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct;
/* SAI1 */
    if(saiHandle->Instance==SAI1_Block_B)
    {
      /* SAI1 clock enable */
      if (SAI1_client == 0)
      {
       __HAL_RCC_SAI1_CLK_ENABLE();
      }
    SAI1_client ++;

    /**SAI1_B_Block_B GPIO Configuration
    PB3 (JTDO/TRACESWO)     ------> SAI1_SCK_B
    PB5     ------> SAI1_SD_B
    PB6     ------> SAI1_FS_B
    */
    GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF13_SAI1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* Peripheral DMA init*/

    hdma_sai1_b.Instance = DMA2_Channel7;
    hdma_sai1_b.Init.Request = DMA_REQUEST_1;
    hdma_sai1_b.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_sai1_b.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_sai1_b.Init.MemInc = DMA_MINC_ENABLE;
    hdma_sai1_b.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_sai1_b.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_sai1_b.Init.Mode = DMA_NORMAL;
    hdma_sai1_b.Init.Priority = DMA_PRIORITY_HIGH;
    if (HAL_DMA_Init(&hdma_sai1_b) != HAL_OK)
    {
      Error_Handler();
    }

    /* Several peripheral DMA handle pointers point to the same DMA handle.
     Be aware that there is only one channel to perform all the requested DMAs. */
    __HAL_LINKDMA(saiHandle,hdmarx,hdma_sai1_b);
    __HAL_LINKDMA(saiHandle,hdmatx,hdma_sai1_b);
    }
}

void HAL_SAI_MspDeInit(SAI_HandleTypeDef* saiHandle)
{

/* SAI1 */
    if(saiHandle->Instance==SAI1_Block_B)
    {
    SAI1_client --;
      if (SAI1_client == 0)
      {
      /* Peripheral clock disable */
      __HAL_RCC_SAI1_CLK_DISABLE();
      }

    /**SAI1_B_Block_B GPIO Configuration
    PB3 (JTDO/TRACESWO)     ------> SAI1_SCK_B
    PB5     ------> SAI1_SD_B
    PB6     ------> SAI1_FS_B
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_6);

    HAL_DMA_DeInit(saiHandle->hdmarx);
    HAL_DMA_DeInit(saiHandle->hdmatx);
    }
}

/* USER CODE BEGIN 1 */
void HAL_SAI_RxCpltCallback(SAI_HandleTypeDef *hsai)
{
	full_sai = 1;
}

void HAL_SAI_RxHalfCpltCallback(SAI_HandleTypeDef *hsai)
{
	half_sai = 1;
}

void Meas_Audio() {
  uint8_t cycle = 0; // reset the counter
  HAL_SAI_Receive_DMA(&hsai_BlockB1, (uint8_t *)data_sai, sizeof(data_sai));
  addDataToUSBBuffer((int8_t*)STEREO, 1, AUDIO_DATA); // add the state to the USB buffer
  addDataToUSBBuffer((int8_t*)(NMBR_Audio*2), 1, 0); // add the size of the data to the USB buffer
  
  while(cycle < NMBR_Audio) { // send 50 FFTs to the PC
    if(half_sai == 1) {
      for(int i = 0; i < WAV_WRITE_SAMPLE_COUNT/4; i++) {
        data_mic_left[i] = data_sai[i*2]  >> 8;
        data_mic_right[i] = data_sai[i*2+1]  >> 8;
      }
      USB_SendBlock((uint8_t*)data_mic_left, sizeof(data_mic_left)); // send the data of the first microphone
      USB_SendBlock((uint8_t*)data_mic_right, sizeof(data_mic_right)); // send the data of the second microphone
      half_sai = 0;
    }

    // The buffer is full
    if(full_sai == 1) {
      for(int i = 0; i < WAV_WRITE_SAMPLE_COUNT/2; i++) {
        data_mic_left[i] = data_sai[WAV_WRITE_SAMPLE_COUNT/2+i*2]  >> 8;
        data_mic_right[i] = data_sai[WAV_WRITE_SAMPLE_COUNT/2+i*2+1]  >> 8;
      }
      USB_SendBlock((uint8_t*)data_mic_left, sizeof(data_mic_left)); // send the data of the first microphone
      USB_SendBlock((uint8_t*)data_mic_right, sizeof(data_mic_right)); // send the data of the second microphone 
      full_sai = 0;
      cycle++;
    }
  }
}

/* USER CODE END 1 */
/**
  * @}
  */

/**
  * @}
  */
