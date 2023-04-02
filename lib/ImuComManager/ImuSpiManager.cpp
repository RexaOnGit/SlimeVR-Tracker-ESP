/*
IMU Communication Library built for SlimeVR - class file
Abstracts reading and writing of IMU registers into general class
*/

#include "ImuComManager.h"
#include <SPI.h>

class ImuSpiManager : public ImuComManager {
    public:
        /** Initialize member variables of the ImuSpiManager. Call this before using other methods.
         * @param select_pin chip select pin to use for this instance
         * @param read_mask bit mask to specify a read. 0x80 if not specified
         * @param write_mask bit mask to specify a write. 0x00 if not specified
         * @param clock_speed SPI clock speed. 10MHz if not specified
         * @param data_order SPI data order. MSBFIRST if not specified
         * @param data_mode SPI data mode. SPI_MODE0 if not specified
         */
        void ImuSpiManager::setup(uint8_t select_pin, uint8_t read_mask = 0x80, uint8_t write_mask = 0x00, 
                                  uint8_t clock_speed = 10000000, 
                                  uint8_t data_order = MSBFIRST, 
                                  uint8_t data_mode = SPI_MODE0) {
            selectPin = select_pin;
            readMask = read_mask;
            writeMask = write_mask;
            settings = SPISettings(clock_speed, data_order, data_mode);
            SPI.setHwCs(false);
        }

        /** Read from a specified range of register addresses
         * @param startAddress register address to start on
         * @param length number of registers to read
         * @param outBytes pointer for getting the read bytes
         * @return SPI read status. imu_ok(0) means success
         */
        int8_t ImuSpiManager::readFromRegisters(uint8_t startAddress, uint8_t length, uint8_t* outBytes) {
            readBytes(startAddress, length, outBytes);
            return status;
        }

        int8_t ImuSpiManager::writeToRegisters(uint8_t startAddress, uint8_t length, uint8_t* inBytes) {
            writeBytes(startAddress, length, inBytes);
            return status;
        }
        void ImuSpiManager::getBitFromByte(uint8_t* byte, uint8_t bitPosition, uint8_t* bit) {
            *bit = ((*byte >> bitPosition) & 0x01);
        }

        void ImuSpiManager::setBitInByte(uint8_t* byte, uint8_t bitPosition, uint8_t bit) {
            *byte |= bit << bitPosition;
        }
    
    private:
        /** Read bytes from a device using SPI
         * @param start_address first register to read from
         * @param length number of registers to read from
         * @param bytes pointer for getting the read bytes
         */
        void ImuSpiManager::readBytes(uint8_t start_address, uint8_t length, uint8_t* bytes) {
            //Initiate the transfer
            SPI.beginTransaction(settings);
            pinMode(selectPin, OUTPUT);
            digitalWrite(selectPin, LOW);

            //Perform transfers, exiting the loop if there is a problem
            status = imu_ok;
            try {
                for (int i = 0; i < length; i++) {
                    buffer[i] = SPI.transfer((start_address & readMask) + i);
                }
                bytes = buffer;
            } catch (...) {
                status = imu_transfer_failed;
            }

            //End the transfer
            digitalWrite(selectPin, HIGH);
            SPI.endTransaction();
        }

        void ImuSpiManager::writeBytes(uint8_t start_address, uint8_t length, uint8_t* bytes) {
            //Initiate the transfer
            SPI.beginTransaction(settings);
            pinMode(selectPin, OUTPUT);
            digitalWrite(selectPin, LOW);

            //Perform transfers, exiting the loop if there is a problem
            status = imu_ok;
            try {
                for (int i = 0; i < length; i++) {
                    SPI.transfer16(word((start_address & writeMask) + i, buffer[i]));
                }
            } catch (...) {
                status = imu_transfer_failed;
            }
                        
            //End the transfer
            digitalWrite(selectPin, HIGH);
            SPI.endTransaction();
        }

        uint8_t selectPin; //Chip select pin
        SPISettings settings;
        uint8_t readMask;
        uint8_t writeMask;
};

