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

#include "SensorManagerSPI.h"
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
        void SensorManagerSPI::setup()
        {
            {

//check what SPI devices exist
int ssPins[] = PIN_IMU_SELECT_LIST;
byte IMUIDs[MAX_IMU_COUNT];
for (int i = 0; i < MAX_IMU_COUNT; i++) {
    byte response = 0;
    SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
    digitalWrite(ssPins[i], LOW);
    response = SPI.transfer(0x00);
    digitalWrite(ssPins[i], HIGH);
    SPI.endTransaction();
    #if IMU == IMU_BMI160
        if (response == BMI160_RA_CHIP_ID) {
            IMUIDs[i] = response;
        }
        else {
            IMUIDs[i] = -1;
        }
    #else
    #error Unsupported IMU
    #endif
}
//step through each device ID, creating a new sensor object for each valid one
for (int i = 0; i < MAX_IMU_COUNT; i++) {
    byte thisID = IMUIDs[i];
    if (thisID == 0) {
        m_Logger.debug("No IMU connected at position " + (i+1));
    }
    else if (thisID == -1) {
        m_Sensors[i] = new ErroneousSensor(0, IMU);
    }
    else {
        m_Sensors[i] = new BMI160Sensor(0, (i+1), IMU_ROTATION);
    }
    m_Sensors[i]->motionSetup();
}

            }
        }

        void SensorManagerSPI::postSetup()
        {
            for (Sensor *i : m_Sensors) {
                i->postSetup();
            }
        }

        void SensorManagerSPI::update()
        {
            // Gather IMU data
            for (Sensor *i : m_Sensors) {
                i->motionLoop();
            }

            if (!ServerConnection::isConnected())
            {
                return;
            }

            // Send updates
            for (Sensor *i : m_Sensors) {
                i->sendData();
            }
        }
    }
}
