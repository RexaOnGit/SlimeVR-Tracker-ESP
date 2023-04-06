/*
BMI160 Library built for SlimeVR - class file
*/

#include "bmi160.h"

namespace BMI160 {
    using S = BMI160ComStatus;

    /** Establish communication and initialize the BMI160
     * @param comProtocol whether to use I2C or SPI for the BMI160
     * @param comAddress i2c address or select pin for the BMI160
     * @return OK means success
     */
    S BMI160::setup(uint8_t comAddress) {
        #ifdef BMI160_SPI
            comManager.setup(comAddress, BMI160_SPI_READ_MASK, BMI160_SPI_WRITE_MASK, 
                             10000000, MSBFIRST, SPI_MODE0);
        #else
            comManager.setup(comAddress);
        #endif
        return S::OK;
    }

} // namespace BMI160

