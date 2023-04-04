/*
BMI160 Library built for SlimeVR - header file
*/

#ifndef _BMI160_H_
#define _BMI160_H_

#include "ImuComManager.h"

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

class BMI160 {
    public:
        BMI160() {}
        ~BMI160() {}

        void setup();

    protected:

    private:
}

#endif // _BMI160_H_