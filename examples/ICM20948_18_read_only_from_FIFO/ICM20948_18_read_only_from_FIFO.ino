/***************************************************************************
* Example sketch for the ICM20948_WE library
*
* This sketch demonstrates how to read the gyroscope and accelerometer 
* measurements exclusively and continuously from the FIFO. In contrast to 
* the examples 12 and 13, the FIFO is continuously read and does not fill 
* completely (if your reading frequency is sufficient). With this method 
* every measured value will be read. The sketch also measures the data rate. 
*
* This is sketch should run on almost all MCUs as is.
* 
* For high-frequency reading I recommend using SPI. 
* 
* Further information can be found on:
*
* https://wolles-elektronikkiste.de/icm-20948-9-achsensensor-teil-i (German)
* https://wolles-elektronikkiste.de/en/icm-20948-9-axis-sensor-part-i (English)
* 
***************************************************************************/

#include <Wire.h>
#include <ICM20948_WE.h>
#define ICM20948_ADDR 0x68

/* If you use the accelerometer and the gyroscope, you should apply the same 
  sample rate divider */
#define DIVIDER 10  // Sample rate divider 
#define READ_INTERVAL_MS 100  // Read interval 

// ICM20948 instance
ICM20948_WE myIMU = ICM20948_WE(ICM20948_ADDR);
xyzFloat gValue, gyr;

void setup() {
  // Initialize ICM20948
  Wire.begin();
  Serial.begin(115200);
  delay(2000);
  if (!myIMU.init()) {
    Serial.println("ICM20948 does not respond");
  } else {
    Serial.println("ICM20948 is connected");
  }

  myIMU.setSPIClockSpeed(5000000);

  // Disable magnetometer
  if (myIMU.initMagnetometer()) {
    myIMU.setMagOpMode(AK09916_PWR_DOWN);
  
  // Accelerometer configuration
  myIMU.setAccRange(ICM20948_ACC_RANGE_2G);
  myIMU.setAccDLPF(ICM20948_DLPF_3); 
  myIMU.setAccSampleRateDivider(DIVIDER-1); // Sample rate divider = parameter + 1 
  myIMU.setGyrRange(ICM20948_GYRO_RANGE_250);
  myIMU.setGyrDLPF(ICM20948_DLPF_3); 
  myIMU.setGyrSampleRateDivider(DIVIDER-1);  
}

  myIMU.enableCycle(ICM20948_NO_CYCLE);

  // FIFO configuration
  myIMU.enableFifo(true);
  myIMU.setFifoMode(ICM20948_CONTINUOUS);
  myIMU.startFifo(ICM20948_FIFO_ACC_GYR);

  Serial.println(F("ICM20948 configured"));
  Serial.println(F("FIFO: Continuous mode"));

  Serial.print(F("Read Interval [ms]: "));
  Serial.println(READ_INTERVAL_MS);

  // Find FIFO begin position
  myIMU.findFifoBegin();
}

void readFifoData() {
  int16_t fifoCount = myIMU.getFifoCount();
  int16_t dataSets = myIMU.getNumberOfFifoDataSets();
  static uint32_t totalSets = 0;
  static uint32_t readCount = 0;

  if (dataSets > 0) {
    unsigned long timestamp = millis();
    totalSets += dataSets;
    readCount++;

    // Read accelerometer and gyroscope data from FIFO
    for (int i = 0; i < dataSets; i++) {
      myIMU.getGValuesFromFifo(&gValue);
      myIMU.getGyrValuesFromFifo(&gyr);
    }

    // Log output only every 10th reading
    if (readCount % 10 == 0) {
      Serial.print(F("FIFO: "));
      Serial.print(dataSets);
      Serial.print(F(" sets, "));
      Serial.print(fifoCount);
      Serial.print(F(" bytes | Total: "));
      Serial.print(totalSets);
      Serial.print(F(" sets, Read: "));
      Serial.print(readCount);
      Serial.println(F(" times"));

      // Calculate sampling rate
      static uint32_t lastTotalSets = 0;
      static uint32_t lastTimestamp = 0;

      if (lastTimestamp > 0) {
        uint32_t deltaSets = totalSets - lastTotalSets;
        uint32_t deltaTime = timestamp - lastTimestamp;

        if (deltaTime > 0) {
          float instantRate = (float)deltaSets * 1000.0 / deltaTime; 
          Serial.print(F("Sampling rate: "));
          Serial.print(instantRate);
          Serial.print(F(" Hz (last "));
          Serial.print(deltaTime);
          Serial.println(F(" ms)")); 
          
          /* The following output of the last data set is just to check if you get meaningful 
            data. Be careful with outputting every data set - the Serial output speed might become 
            the limiting factor. */
          Serial.print(F("Last set - acceleration: "));
          Serial.print(gValue.x); Serial.print(F(", ")); 
          Serial.print(gValue.y); Serial.print(F(", "));
          Serial.println(gValue.z);
          Serial.print(F("Last set - gyroscope: "));
          Serial.print(gyr.x); Serial.print(F(", ")); 
          Serial.print(gyr.y); Serial.print(F(", ")); 
          Serial.println(gyr.z); Serial.println();
        }      
      }
      lastTotalSets = totalSets;
      lastTimestamp = timestamp;
    }
  }
}

void loop() {
  static uint32_t lastRead = 0;
  if (millis() - lastRead > READ_INTERVAL_MS) { // apply the read interval
    lastRead = millis();
    readFifoData();
  }
}
