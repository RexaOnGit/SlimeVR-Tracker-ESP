/*
BMI160 Library built for SlimeVR - header file
*/

#ifndef _BMI160_H_
#define _BMI160_H_

// Add this define to use SPI
//#define BMI160_SPI

#include <Arduino.h>
#include <any>
#include "I2c.h"
#include "SpiCom.h"

// BMI160 Register Table

#define BMI160_CHIPID_REG               0x00
#define BMI160_ERR_REG                  0x02
#define BMI160_MAG_DATA_REG             0x04
#define BMI160_GYRO_DATA_REG            0x0C
#define BMI160_ACCEL_DATA_REG           0x12
#define BMI160_SENSORTIME_REG           0x18
#define BMI160_STATUS_REG               0x1B
#define BMI160_TEMPERATURE_REG          0x20
#define BMI160_FIFO_LENGTH_REG          0x22
#define BMI160_FIFO_DATA_REG            0x24
#define BMI160_ACCEL_CONF_REG           0x40
#define BMI160_ACCEL_RANGE_REG          0x41   
#define BMI160_GYRO_CONF_REG            0x42
#define BMI160_GYRO_RANGE_REG           0x43
#define BMI160_MAG_CONF_REG             0x44
#define BMI160_FIFO_CONFIG_REG          0x46
#define BMI160_NVM_CONF_REG             0x70
#define BMI160_ACCEL_OFFSET_REG         0x71
#define BMI160_GYRO_OFFSET_REG          0x74
#define BMI160_OFFSET_REG               0x77
#define BMI160_CMD_REG                  0x7E
#define BMI160_SPI_TEST_REG             0x7F

// BMI160 SPI read and write masks

#define BMI160_SPI_READ_MASK            0b10000000
#define BMI160_SPI_WRITE_MASK           0b00000000

// BMI160 I2C Address options

#define BMI160_I2C_68                   0x68
#define BMI160_I2C_69                   0x69

namespace BMI160{

    // Digital Low Pass Filter mode options
    enum class BMI160DLPFMode : int8_t {
        NORMAL = 0x2,
        OSR2   = 0x1,
        OSR4   = 0x0
    };

    // Accelerometer sensitivity range options
    enum class BMI160AccelRange : int8_t {
        G2  = 0x03,
        G4  = 0x05,
        G8  = 0x08,
        G16 = 0x0C
    };

    // Gyroscope sensitivity range options
    enum class BMI160GyroRange : int8_t {
        D2000 = 0,
        D1000,
        D500,
        D250,
        D125
    };

    // Magnetometer output data rate options
    enum class BMI160MagRate : int8_t {
        Hz25_32nd = 1,
        Hz25_16th,
        Hz25_8th,
        Hz25_4th,
        Hz25_2nd,
        Hz25,
        Hz50,
        Hz100,
        Hz200,
        Hz400,
        Hz800
    };

    // Accelerometer output data rate options
    enum class BMI160AccelRate : int8_t {
        Hz25 = 6,
        Hz50,
        Hz100,
        Hz200,
        Hz400,
        Hz800,
        Hz1600
    };

    // Gyroscope output data rate options
    enum class BMI160GyroRate : int8_t {
        Hz25 = 5,
        Hz50,
        Hz100,
        Hz200,
        Hz400,
        Hz800,
        Hz1600,
        Hz3200
    };

    enum class BMI160ComStatus : int8_t {
        OK = 0,
        FAIL
    };

    class BMI160 {
        public:
            BMI160() {}
            ~BMI160() {}

            BMI160ComStatus setup(uint8_t comAddress);

            int8_t getChipID();

            int8_t getAcceleration();
            int8_t getAccelerationX();
            int8_t getAccelerationY();
            int8_t getAccelerationZ();

            int8_t getRotation();
            int8_t getRotationX();
            int8_t getRotationY();
            int8_t getRotationZ();

            bool getGyroFIFOEnabled();
            void setGyroFIFOEnabled(bool enabled);
            bool getAccelFIFOEnabled();
            void setAccelFIFOEnabled(bool enabled);
            bool getMagFIFOEnabled();
            void setMagFIFOEnabled(bool enabled);

            bool getFIFOHeaderModeEnabled();
            void setFIFOHeaderModeEnabled(bool enabled);
            void resetFIFO();

            int8_t getFIFOCount();
            int8_t getFIFOBytes();

        protected:

        private:
            BMI160ComStatus setupI2C(uint8_t i2cAddress);
            BMI160ComStatus setupSPI(uint8_t selectPin);

            #ifdef BMI160_SPI
                ImuComManager::SpiCom comManager;
            #else
                ImuComManager::I2c comManager;
            #endif

    };
} // namespace BMI160

#endif // _BMI160_H_

