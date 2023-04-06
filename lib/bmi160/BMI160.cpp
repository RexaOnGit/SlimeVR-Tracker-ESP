/*
BMI160 Library built for SlimeVR - class file
*/

#include "bmi160.h"

namespace BMI160{
    using P = BMI160ComProtocol;
    using S = BMI160ComStatus;

    S BMI160::setup(P comProtocol, uint8_t comAddress) {
        if (comProtocol == P::I2C) {
            return setupI2C(comAddress);
        }
        if (comProtocol == P::SPI) {
            return setupSPI(comAddress);
        }
        else {
            return S::FAIL;
        }
    }

    S BMI160::setupI2C(uint8_t i2cAddress) {
        return S::OK;
    }

    S BMI160::setupSPI(uint8_t selectPin) {
        return S::OK;
    }

} // namespace BMI160

