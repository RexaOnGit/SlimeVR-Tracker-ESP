/*
BMI160 Library built for SlimeVR - class file
*/

#include "bmi160.h"

namespace BMI160{
    using P = BMI160ComProtocol;
    using S = BMI160ComStatus;
    namespace M = ImuComManager;

    /** Establish communication and initialize the BMI160
     * @param comProtocol whether to use I2C or SPI for the BMI160
     * @param comAddress i2c address or select pin for the BMI160
     * @return OK means success
     */
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

    /** I2C specific setup method
     * @param i2cAddress 
     * @return OK means success
     */
    S BMI160::setupI2C(uint8_t i2cAddress) {
        M::ImuI2cManager i2cManager;
        comManager = i2cManager;
        std::any_cast<M::ImuI2cManager>(comManager).setup(i2cAddress);
        return S::OK;
    }

    /** SPI specific setup method
     * @param selectPin 
     * @return OK means success
     */
    S BMI160::setupSPI(uint8_t selectPin) {
        M::ImuSpiManager spiManager;
        comManager = &spiManager;
        std::any_cast<M::ImuSpiManager>(comManager).setup(selectPin, BMI160_SPI_READ_MASK, BMI160_SPI_WRITE_MASK, 
                          10000000, MSBFIRST, SPI_MODE0);
        return S::OK;
    }

} // namespace BMI160

