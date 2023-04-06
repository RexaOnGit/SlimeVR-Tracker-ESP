/*
IMU Communication Library built for SlimeVR - header file
Abstracts reading and writing of IMU registers into general class
*/

#ifndef IMU_COM_MANAGER
#define IMU_COM_MANAGER

#include <Arduino.h>


namespace ImuComManager {

    enum class ComStatus : int8_t {
        OK = 0,
        FAILED
    };

    class ImuComManager {
        public:
            ImuComManager() {}
            ~ImuComManager() {}   

            void setup();

            ComStatus readFromRegisters(uint8_t startAddress, uint8_t length, uint8_t* outBytes);
            ComStatus writeToRegisters(uint8_t startAddress, uint8_t length, uint8_t* inBytes);

            void readBitFromByte(uint8_t* byte, uint8_t bitPosition, uint8_t* bit);
            void writeBitInByte(uint8_t* byte, uint8_t bitPosition, uint8_t bit);

        protected:
            enum ComStatus status = ComStatus::OK;

        private:

    };
}

#endif // IMU_COM_MANAGER

