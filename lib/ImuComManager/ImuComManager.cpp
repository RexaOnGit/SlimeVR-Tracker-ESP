/*
IMU Communication Library built for SlimeVR - class file
Abstracts reading and writing of IMU registers into general class
*/

#include "ImuComManager.h"
#include "I2Cdev.h"
#include <SPI.h>

class ImuI2CManager : public ImuComManager {
    public:
        int8_t ImuI2CManager::readFromRegisters(uint8_t startAddress, uint8_t length, uint8_t* outBytes) {
            for (int i = 0; i < length; i++) {

            }
            status = imu_ok;
            return status;
        }

        int8_t ImuI2CManager::writeToRegisters(uint8_t startAddress, uint8_t length, uint8_t* inBytes) {
            for (int i = 0; i < length; i++) {

            }
            status = imu_ok;
            return status;
        }

        void ImuI2CManager::getBitFromByte(uint8_t* byte, uint8_t bitPosition, uint8_t* bit) {
            *bit = ((*byte >> bitPosition) & 0x01);
        }

        void ImuI2CManager::setBitInByte(uint8_t* byte, uint8_t bitPosition, uint8_t bit) {
            *byte |= bit << bitPosition;
        }
};

class ImuSPIManager : public ImuComManager {
    public:
        int8_t ImuSPIManager::readFromRegisters(uint8_t startAddress, uint8_t length, uint8_t* outBytes) {
            for (int i = 0; i < length; i++) {

            }
            status = imu_ok;
            return status;
        }

        int8_t ImuSPIManager::writeToRegisters(uint8_t startAddress, uint8_t length, uint8_t* inBytes) {
            for (int i = 0; i < length; i++) {

            }
            status = imu_ok;
            return status;
        }
        void ImuSPIManager::getBitFromByte(uint8_t* byte, uint8_t bitPosition, uint8_t* bit) {
            *bit = ((*byte >> bitPosition) & 0x01);
        }

        void ImuSPIManager::setBitInByte(uint8_t* byte, uint8_t bitPosition, uint8_t bit) {
            *byte |= bit << bitPosition;
        }
};


