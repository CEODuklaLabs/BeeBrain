#ifndef CUPREXIT_H
#define CUPREXIT_H

#include <stdint.h>
#include "stm32l4xx_hal.h" // Adjust this include according to your MCU
#include "main.h"
#include "spi.h"
#include "cuprexit.h"

typedef struct {
    SPI_HandleTypeDef *hspi;
    uint8_t User_ID;
    uint16_t pin;
    uint16_t port;
    uint32_t Device_UID[3];
    uint8_t active;
    uint64_t timestamp;
    float32_t calib[10];
} CUPREXIT_Device;

typedef enum {
    CUPREXIT_COMMAND_GET_CALIB,
    CUPREXIT_COMMAND_SET_CALIB,
    CUPREXIT_COMMAND_GET_MEAS,
    CUPREXIT_COMMAND_GET_STATUS,
    CUPREXIT_COMMAND_MEAS,
    CUPREXIT_COMMAND_SET_USER_ID,
    CUPREXIT_COMMAND_GET_USER_ID,
    CUPREXIT_COMMAND_GET_UID,
    CUPREXIT_COMMAND_RESET,
    CUPREXIT_COMMAND_PING
} CUPREXIT_Command;


extern CUPREXIT_Command active_command;
extern CUPREXIT_Device *active_device;

extern CUPREXIT_Device CU_devices[NMBR_CU];


void CUPREXIT_InitDevice(CUPREXIT_Device *device, SPI_HandleTypeDef *hspi, uint8_t device_id, uint16_t pin, uint16_t port);

// Function prototypes
void handleCUPCommand(uint8_t command);
void getCuCalib();
void setCuCalib();
void getMeas();
void getStatus();
void meas();
void setUserId();
void getUserId();
void getUid();

#endif // CUPREXIT_H
