/*
IMU Communication Library built for SlimeVR - class file
Abstracts reading and writing of IMU registers into general class
*/

#include "ImuComManager.h"
#include "I2Cdev.h"
#include <SPI.h>

class ImuI2CManager : public ImuComManager {
    public:
        /** Initilize member variables of the ImuI2CManager. Call this before using other methods.
         * @param devAddress I2C device address
         * @param timeout Optional I2C timeout in ms. 0 to disable, leave off for default
         */
        void ImuI2CManager::setup(uint8_t device_address, uint16_t time_out = -1) {
            deviceAddress = device_address;
            if (time_out != -1) {
                timeOut = time_out;
            }
        }

        /** Read from a specified range of register addresses
         * @param startAddress register address to start on
         * @param length number of registers to read
         * @param outBytes pointer for getting the read bytes
         * @return I2C read status. imu_ok(0) means success 
         */
        int8_t ImuI2CManager::readFromRegisters(uint8_t startAddress, uint8_t length, uint8_t* outBytes) {
            if (i2c.readBytes(deviceAddress, startAddress, length, buffer) == -1) {
                status = imu_transfer_failed;
            } else {
                outBytes = buffer;
                status = imu_ok;
            }
            return status;
        }

        /** Write to a specified range of register addresses
         * @param startAddress register address to start on
         * @param length number of registers to write
         * @param inBytes pointer for passing bytes to write
         * @return I2C read status. imu_ok(0) means success
         */
        int8_t ImuI2CManager::writeToRegisters(uint8_t startAddress, uint8_t length, uint8_t* inBytes) {
            if (i2c.writeBytes(deviceAddress, startAddress, length, inBytes) == -1) {
                status = imu_transfer_failed;
            } else {
                status = imu_ok;
            }
            return status;
        }

        /** Helper method for reading specific bits from a byte
         * @param byte pointer to byte to read from
         * @param bitPosition which bit to read
         * @param bit pointer for getting the read bit
         */
        void ImuI2CManager::readBitFromByte(uint8_t* byte, uint8_t bitPosition, uint8_t* bit) {
            *bit = ((*byte >> bitPosition) & 0x01);
        }

        /** Helper method for writing specific bits in a byte
         * @param byte pointer to byte to modify
         * @param bitPosition which bit to change
         * @param bit bit value to write
         */
        void ImuI2CManager::writeBitInByte(uint8_t* byte, uint8_t bitPosition, uint8_t bit) {
            *byte &= (~0x01 << bitPosition);
            *byte |= (bit << bitPosition);
        }

        uint8_t deviceAddress; //I2C device address
        uint16_t timeOut = i2c.readTimeout;
    private:
        I2Cdev i2c;
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


