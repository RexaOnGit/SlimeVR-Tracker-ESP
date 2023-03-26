/*
    SlimeVR Code is placed under the MIT license
    Copyright (c) 2022 TheDevMinerTV

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/

#include "globals.h"
#ifdef COM_SPI

#include "SensorManager.h"
#include <SPI.h>
#include "network/network.h"
#include "bno055sensor.h"
#include "bno080sensor.h"
#include "mpu9250sensor.h"
#include "mpu6050sensor.h"
#include "bmi160sensor.h"
#include "icm20948sensor.h"
#include "ErroneousSensor.h"

namespace SlimeVR
{
    namespace Sensors
    {
        void SensorManager::setup()
        {
            {

pinMode(D8, OUTPUT);  ///TEMP
pinMode(D3, OUTPUT);  ///TEMP

SPI.begin();

//check what SPI devices exist
int ssPins[] = PIN_IMU_SELECT_LIST;
byte IMUIDs[m_Sensors.size()];
for (uint8_t i = 0; i < m_Sensors.size(); i++) {
    byte response = 0;
    SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
    digitalWrite(ssPins[i], LOW);
    SPI.transfer(0x7F | 0x80);
    response = SPI.transfer(0x00 | 0x80);
    digitalWrite(ssPins[i], HIGH);
    SPI.endTransaction();
    Serial.print(response, HEX);
    Serial.print("\n");
    #if IMU == IMU_BMI160
        if ((response == BMI160_CHIP_ID) | (response == 0x00)) {
            IMUIDs[i] = response;
        }
        else {
            IMUIDs[i] = 0xFF;
        }
    #else
    #error Unsupported IMU
    #endif
}

//step through each device ID, creating a new sensor object for each valid one
for (uint8_t i = 0; i < m_Sensors.size(); i++) {
    byte thisID = IMUIDs[i];
    if (thisID == 0) {
        String message = "No IMU connected at position " + String((i+1), DEC);
        m_Logger.debug(message.c_str());
        continue;
    }
    else if (thisID == BMI160_CHIP_ID) {
        String message = "BMI160 connected at position " + String((i+1), DEC);
        m_Logger.debug(message.c_str());
        m_Sensors[i] = (std::make_unique<BMI160Sensor>(i, (i+1), IMU_ROTATION));

    }
    else {
        String message = "Invalid sensor at position " + String((i+1), DEC);
        m_Logger.debug(message.c_str());
        m_Sensors[i] = (std::make_unique<ErroneousSensor>(i, IMU));
    }
    m_Sensors[i]->motionSetup();
}

            }
        }

        void SensorManager::postSetup()
        {
            for (const auto& i : m_Sensors) {
                i->postSetup();
            }
        }

        void SensorManager::update()
        {
            // Gather IMU data
            for (const auto& i : m_Sensors) {
                i->motionLoop();
            }
            if (!ServerConnection::isConnected())
            {
                return;
            }

            // Send updates
            for (const auto& i : m_Sensors) {
                i->sendData();
            }

        }
    }
}

#endif // COM_SPI