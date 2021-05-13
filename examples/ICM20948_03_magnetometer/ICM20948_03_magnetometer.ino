/***************************************************************************
  Example sketch for the ICM20948_WE library

  This sketch shows how to setup the magnetometer and how to query magnetometer
  data. The magnetometer is a seperate unit on the module. It has its own I2C 
  address. All read and write accesses are done via a kind of I2C "sub-bus". You
  don't access the magnetometer registers directly. 
   
  Further information can be found soon on:

  https://wolles-elektronikkiste.de/ (German)
  https://wolles-elektronikkiste.de/en/ (English)

***************************************************************************/

#include <Wire.h>
#include <ICM20948_WE.h>
#define ICM20948_ADDR 0x68

ICM20948_WE myIMU = ICM20948_WE(Wire, ICM20948_ADDR);

void setup() {
  Wire.begin();
  Serial.begin(115200);
  while (!Serial) {}

  if (!myIMU.init()) {
    Serial.println("ICM20948 does not respond");
  }
  else {
    Serial.println("ICM20948 is connected");
  }

  if (!myIMU.initMagnetometer()) {
    Serial.println("Magnetometer does not respond");
  }
  else {
    Serial.println("Magnetometer is connected");
  }

  /* You can set the following modes for the magnetometer:
   * AK09916_PWR_DOWN          Power down to save energy
   * AK09916_TRIGGER_MODE      Measurements on request, a measurement is triggered by 
   *                           calling setMagOpMode(AK09916_TRIGGER_MODE)
   * AK09916_CONT_MODE_10HZ    Continuous measurements, 10 Hz rate
   * AK09916_CONT_MODE_20HZ    Continuous measurements, 20 Hz rate
   * AK09916_CONT_MODE_50HZ    Continuous measurements, 50 Hz rate
   * AK09916_CONT_MODE_100HZ   Continuous measurements, 100 Hz rate (default)
   */
  myIMU.setMagOpMode(AK09916_CONT_MODE_20HZ);
}

void loop() {
  myIMU.readSensor();
  xyzFloat magValue = myIMU.getMagValues(); // returns magnetic flux density [µT]

  Serial.println("Magnetometer Data in µTesla: ");
  Serial.print(magValue.x);
  Serial.print("   ");
  Serial.print(magValue.y);
  Serial.print("   ");
  Serial.println(magValue.z);

  delay(1000);
}
