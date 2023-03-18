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
// #include "bno055sensor.h"
// #include "bno080sensor.h"
// #include "mpu9250sensor.h"
// #include "mpu6050sensor.h"
#include "sensors/bmi160sensor.h"
// #include "icm20948sensor.h"
#include "sensors/ErroneousSensor.h"

namespace SlimeVR
{
    namespace Sensors
    {
        void SensorManagerSPI::setup()
        {
            {

//check what SPI devices exist
int ssPins[] = {PIN_IMU_SS1, PIN_IMU_SS2, PIN_IMU_SS3};
byte IMUIDs[] = {0,0,0};
for (int i = 0; i <= 2; i++) {
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
if (IMUIDs[0] == 0) {
    m_Logger.debug("No IMU connected at position 1");
}
else if (IMUIDs[0] == -1) {
    m_Sensor1 = new ErroneousSensor(0, IMU);
}
else {
    m_Sensor1 = new BMI160Sensor(0, 1, IMU_ROTATION);
}
m_Sensor1->motionSetup();

if (IMUIDs[1] == 0) {
    m_Logger.debug("No IMU connected at position 1");
}
else if (IMUIDs[0] == -1) {
    m_Sensor2 = new ErroneousSensor(0, IMU);
}
else {
    m_Sensor2 = new BMI160Sensor(0, 2, IMU_ROTATION);
}
m_Sensor2->motionSetup();

if (IMUIDs[2] == 0) {
    m_Logger.debug("No IMU connected at position 1");
}
else if (IMUIDs[0] == -1) {
    m_Sensor3 = new ErroneousSensor(0, IMU);
}
else {
    m_Sensor3 = new BMI160Sensor(0, 3, IMU_ROTATION);
}
m_Sensor3->motionSetup();

            }
        }

        void SensorManagerSPI::postSetup()
        {
            m_Sensor1->postSetup();
            m_Sensor2->postSetup();
            m_Sensor3->postSetup();
        }

        void SensorManagerSPI::update()
        {
            // Gather IMU data
            m_Sensor1->motionLoop();
            m_Sensor2->motionLoop();
            m_Sensor3->motionLoop();

            if (!ServerConnection::isConnected())
            {
                return;
            }

            // Send updates
            m_Sensor1->sendData();
            m_Sensor2->sendData();
            m_Sensor3->sendData();
        }
    }
}
