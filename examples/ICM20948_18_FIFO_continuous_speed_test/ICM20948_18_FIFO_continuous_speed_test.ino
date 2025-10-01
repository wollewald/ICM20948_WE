/***************************************************************************
* Example sketch for the ICM20948_WE library
*
* This sketch shows a) how to measure the sample rate when writing to the 
* FIFO and b) how to retrieve data from the FIFO while it is continuously 
* filled.  
*
* The sketch has been written for an ESP32 board and SPI communication. If 
* you use a different board, you need to adjust the hardware timer part. 
* 
* Further information can be found on:
*
* https://wolles-elektronikkiste.de/icm-20948-9-achsensensor-teil-i (German)
* https://wolles-elektronikkiste.de/en/icm-20948-9-axis-sensor-part-i (English)
* 
***************************************************************************/

#include <ICM20948_WE.h>
#include <SPI.h>

volatile bool timerEvent = false;
const int CS_PIN = 5;    
const int intPin = 22;

// Hardware timer for FIFO reading
hw_timer_t* timer = NULL;

void IRAM_ATTR onTimer() {
  timerEvent = true;
}

// ICM20948 instance
ICM20948_WE myIMU(&SPI, CS_PIN, true);
xyzFloat gValue, gyr;

void setup() {
    // Initialize ICM20948
  Serial.begin(115200);
  delay(2000);
  if (!myIMU.init()) {
    Serial.println("ICM20948 does not respond");
  } else {
    Serial.println("ICM20948 is connected");
  }

  // Configure ICM20948 for high-speed sampling
  myIMU.setSPIClockSpeed(7000000);

  // Disable magnetometer
  if (myIMU.initMagnetometer()) {
    myIMU.setMagOpMode(AK09916_PWR_DOWN);
  }

  // Accelerometer configuration
  myIMU.setAccRange(ICM20948_ACC_RANGE_2G);
  myIMU.setAccDLPF(ICM20948_DLPF_1); 
  myIMU.setAccSampleRateDivider(0);    // 0 -> Divider = 1

  // Gyroscope configuration
  myIMU.setGyrRange(ICM20948_GYRO_RANGE_250);
  myIMU.setGyrDLPF(ICM20948_DLPF_1);  
  myIMU.setGyrSampleRateDivider(0);  // 0 -> Divider = 1

  myIMU.enableCycle(ICM20948_NO_CYCLE);

  // FIFO configuration
  myIMU.setFifoMode(ICM20948_CONTINUOUS);
  myIMU.enableFifo(true); delay(100);
  myIMU.startFifo(ICM20948_FIFO_ACC_GYR);

  Serial.println("ICM20948 configured");
  Serial.println("FIFO: Continuous mode");

  // Hardware timer setup (10ms interval)
  timer = timerBegin(1000000);
  timerAttachInterrupt(timer, &onTimer);
  timerAlarm(timer, 10000, true, 0); // 10000

  Serial.println("Timer: 10ms interval");

  // Find FIFO begin position
  myIMU.findFifoBegin();
}

void readFifoData() {
  unsigned long int fifoCount = myIMU.getFifoCount();
  unsigned long int dataSets = myIMU.getNumberOfFifoDataSets();
  static unsigned long int totalSets = 0;
  static unsigned long int readCount = 0;

  if (dataSets > 0) {
    unsigned long timestamp = millis();
    totalSets += dataSets;
    readCount++;
    myIMU.stopFifo();

    // Read accelerometer and gyroscope data from FIFO
    for (int i = 0; i < dataSets; i++) {
      myIMU.getGValuesFromFifo(&gValue);
      myIMU.getGyrValuesFromFifo(&gyr);
    }
    myIMU.resetFifo();
    myIMU.startFifo(ICM20948_FIFO_ACC_GYR);

    // Log output every 100 reads (approximately every 1 second)
    if (readCount % 100 == 0) {   //100
      Serial.printf(
          "FIFO: %lu sets, %lu bytes | Total: %lu sets, Read: %lu times\n",
          dataSets, fifoCount, totalSets, readCount);

      // Calculate sampling rate
      static uint32_t lastTotalSets = 0;
      static uint32_t lastTimestamp = 0;

      if (lastTimestamp > 0) {
        uint32_t deltaSets = totalSets - lastTotalSets;
        uint32_t deltaTime = timestamp - lastTimestamp;

        if (deltaTime > 0) {
          float instantRate = (float)deltaSets * 1000.0 / (deltaTime * 1.0);
          Serial.printf("Sampling rate: %.1f Hz (last %lu ms)\n", instantRate,
                        deltaTime);
        }
      }

      lastTotalSets = totalSets;
      lastTimestamp = timestamp;
    }
  }
}

void loop() {
  if (timerEvent) {
    readFifoData();
    timerEvent = false;
  }
}
