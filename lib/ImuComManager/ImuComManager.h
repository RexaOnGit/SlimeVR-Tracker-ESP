/*
IMU Communication Library built for SlimeVR - header file
Abstracts reading and writing of IMU registers into general class
*/

#ifndef IMU_COM_MANAGER
#define IMU_COM_MANAGER

#include <Arduino.h>

enum transferStatus : int8_t {
    imu_ok = 0,
    imu_transfer_failed
};

class ImuComManager {
    public:
        virtual void setup();

        virtual int8_t readFromRegisters(uint8_t startAddress, uint8_t length, uint8_t* outBytes);
        virtual int8_t writeToRegisters(uint8_t startAddress, uint8_t length, uint8_t* inBytes);

        virtual void readBitFromByte(uint8_t* byte, uint8_t bitPosition, uint8_t* bit);
        virtual void writeBitInByte(uint8_t* byte, uint8_t bitPosition, uint8_t bit);

    protected:
        ImuComManager() {}
        ~ImuComManager() {}    
        enum transferStatus status = imu_ok;

    private:

};

#endif // IMU_COM_MANAGER

