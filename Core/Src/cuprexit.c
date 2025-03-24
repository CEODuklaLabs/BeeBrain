#include <stdint.h>
#include <stdio.h>
#include "spi.h"
#include "cuprexit.h"


void sendCommand(CUPREXIT_Device *device, CUPREXIT_Command command, uint8_t *data, uint8_t size) {
    selectDevice(device);
    sendSPICommand(device, command, data, size);
}

uint8_t isActive(CUPREXIT_Device *device) {
    selectDevice(device);
    sendSPICommand(device, CUPREXIT_COMMAND_GET_STATUS, NULL, 0);
}

// Main function to handle commands
void handleCUPCommand(uint8_t command) {
    switch (command) {
        case CUPREXIT_COMMAND_GET_CU_CALIB:
            getCuCalib();
            break;
        case CUPREXIT_COMMAND_SET_CU_CALIB:
            setCuCalib();
            break;
        case CUPREXIT_COMMAND_GET_MEAS:
            getMeas();
            break;
        case CUPREXIT_COMMAND_GET_STATUS:
            getStatus();
            break;
        case CUPREXIT_COMMAND_MEAS:
            meas();
            break;
        case CUPREXIT_COMMAND_SET_USER_ID:
            setUserId();
            break;
        case CUPREXIT_COMMAND_GET_USER_ID:
            getUserId();
            break;
        case CUPREXIT_COMMAND_GET_UID:
            getUid();
            break;
        case CUPREXIT_COMMAND_RESET:
            // Add reset functionality here
            break;
        case CUPREXIT_COMMAND_PING:
            // Add ping functionality here
            break;
    }
}

void handleCUPCommandResponse(uint8_t command) {
    switch (command) {
        case CUPREXIT_COMMAND_GET_CU_CALIB:
            getCuCalibresponse();
            break;
        case CUPREXIT_COMMAND_SET_CU_CALIB:
            // Add response handling for setting CU calibration
            break;
        case CUPREXIT_COMMAND_GET_MEAS:
            // Add response handling for getting measurement
            break;
        case CUPREXIT_COMMAND_GET_STATUS:
            // Add response handling for getting status
            break;
        case CUPREXIT_COMMAND_MEAS:
            // Add response handling for measurement
            break;
        case CUPREXIT_COMMAND_SET_USER_ID:
            // Add response handling for setting user ID
            break;
        case CUPREXIT_COMMAND_GET_USER_ID:
            // Add response handling for getting user ID
            break;
        case CUPREXIT_COMMAND_GET_UID:
            checkUIDresponse();
            break;
        case CUPREXIT_COMMAND_RESET:
            // Add response handling for reset
            break;
        case CUPREXIT_COMMAND_PING:
            // Add response handling for ping
            break;
    }
}

// Function to initialize CUPREXIT_Device structure
void CUPREXIT_InitDevice(CUPREXIT_Device *device, SPI_HandleTypeDef *hspi, uint8_t device_id, uint16_t pin, uint16_t port) {
    device->hspi = hspi;
    device->User_ID = device_id;
    device->pin = pin;
    device->port = port;
    device->active = 0;
    handleCUPCommand(CUPREXIT_COMMAND_GET_UID);
}


void checkCuprexitDevices(CUPREXIT_Device CU_devices[]) {
    for (int i = 0; i < NMBR_CU; i++) {
        isActive(&CU_devices[i]);
        checkUID(&CU_devices[i]);
    }
}

void checkUID(CUPREXIT_Device *device) {
    // Check if the device is active
    if (isActive(device) == 1) {    
        selectDevice(device);
        sendSPICommand(device, CUPREXIT_COMMAND_GET_UID, NULL, 0);
    }
}

void checkUIDresponse() {
    for (int i = 0; i < 3; i++) {
        active_device->Device_UID[i] = SPIRxBuffer[i+2];
    }
}

void getCuCalib(CUPREXIT_Device *device) {
    selectDevice(device);
    sendSPICommand(device, CUPREXIT_COMMAND_GET_CALIB, NULL, 0);
}

void getCuCalibresponse() {    
    addDataToUSBBuffer(active_device->Device_UID, 3, 0);
    addDataToUSBBuffer(SPIRxBuffer+1, 41, 0);
}





void getMeas(CUPREXIT_Device *device) {
    selectDevice(device);
    sendSPICommand(device, CUPREXIT_COMMAND_MEAS, NULL, 0);
}

void getStatus() {
    // Implementation for getting status
    printf("Getting status\n");
}

void meas() {
    selectAllDevice(CU_devices);
    sendSPICommand(NULL, CUPREXIT_COMMAND_MEAS, NULL, 0);
    while (HAL_SPI_GetState(&hspi3) != HAL_SPI_STATE_READY);
    deselectAllDevices(CU_devices);
}

void setUserId() {
    // Implementation for setting user ID
    printf("Setting user ID\n");
}

void getUserId() {
    // Implementation for getting user ID
    printf("Getting user ID\n");
}

void getUid(CUPREXIT_Device *device) {
    sendSPICommand(device, CUPREXIT_COMMAND_GET_UID, NULL, 0);
    while (HAL_SPI_GetState(&hspi3) != HAL_SPI_STATE_READY);
}