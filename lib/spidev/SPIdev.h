// SPIdev library collection - Main SPI device class
// Abstracts SPI R/W functions into a convenient class

#ifndef _SPIDEV_H_
#define _SPIDEV_H_

#include <Arduino.h>


#endif /* _SPIDEV_H_ */

class SPIdev {
    public:
        SPIdev();

        static int8_t readBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t *data, void *wireObj=0);
        static int8_t readBitW(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint16_t *data, void *wireObj=0);
        static int8_t readBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t *data, void *wireObj=0);
        static int8_t readBitsW(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint16_t *data, void *wireObj=0);
        static int8_t readByte(uint8_t devAddr, uint8_t regAddr, uint8_t *data, void *wireObj=0);
        static int8_t readWord(uint8_t devAddr, uint8_t regAddr, uint16_t *data, void *wireObj=0);
        static int8_t readBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data, void *wireObj=0);
        static int8_t readWords(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint16_t *data, void *wireObj=0);

        static bool writeBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t data, void *wireObj=0);
        static bool writeBitW(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint16_t data, void *wireObj=0);
        static bool writeBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data, void *wireObj=0);
        static bool writeBitsW(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint16_t data, void *wireObj=0);
        static bool writeByte(uint8_t devAddr, uint8_t regAddr, uint8_t data, void *wireObj=0);
        static bool writeWord(uint8_t devAddr, uint8_t regAddr, uint16_t data, void *wireObj=0);
        static bool writeBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data, void *wireObj=0);
        static bool writeWords(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint16_t *data, void *wireObj=0);
};