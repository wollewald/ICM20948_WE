/***************************************************************************
* Example sketch for the ICM20948_WE library
*
* This sketch shows how to use the FSYNC interrupt. Since it can't propagate to the 
* INT pin, you have to request the interrupt status. 
*   
* Further information can be found soon on:
*
* https://wolles-elektronikkiste.de/ (German)
* https://wolles-elektronikkiste.de/en/ (English)
* 
***************************************************************************/

#include <Wire.h>
#include <ICM20948_WE.h>
#define ICM20948_ADDR 0x68

ICM20948_WE myIMU = ICM20948_WE(Wire, ICM20948_ADDR);

const int intPin = 2;
volatile bool fsyncEvent = false;

void setup() {
  Wire.begin();
  Serial.begin(115200);
  while(!Serial) {}
  
  if(!myIMU.init()){
    Serial.println("ICM20948 does not respond");
  }
  else{
    Serial.println("ICM20948 is connected");
  }
 
  /* Set the interrupt pin:
   * ICM20948_ACT_LOW  = active-low
   * ICM20948_ACT_HIGH = active-high (default) 
   */
   //myIMU.setIntPinPolarity(ICM20948_ACT_LOW);

  /*  If latch is enabled the interrupt pin level is held until the interrupt status 
   *  is cleared. If latch is disabled the interrupt pulse is ~50µs (default).
   */
   myIMU.enableIntLatch(true);

  /* The interrupts ICM20948_FSYNC_INT, ICM20948_WOM_INT and ICM20948_DMP_INT can be 
   * cleared by any read or will only be cleared if the interrupt status register is 
   * read (default).
   */
   //myIMU.enableClearIntByAnyRead(true);

  /* Set the FSync interrupt pin:
   *  ICM20948_ACT_LOW  = interrupt if low
   *  ICM20948_ACT_HIGH = interrupt if high (default) 
   */
   //myIMU.setFSyncIntPolarity(ICM20948_ACT_LOW);

  /* The following interrupts can be enabled or disabled:
   *  ICM20948_FSYNC_INT        FSYNC pin interrupt, can't propagate to the INT pin  
   *  ICM20948_WOM_INT          Wake on motion
   *  ICM20948_DATA_READY_INT   New data available
   *  ICM20948_FIFO_OVF_INT     FIFO overflow
   */
  myIMU.enableInterrupt(ICM20948_FSYNC_INT);
  //myIMU.disableInterrupt(ICM20948_DATA_READY_INT);

  Serial.println("Pull down the FSYNC pin with a 10kOhm resistor.");
  Serial.println("A HIGH signal to pin FSYNC will then cause an interrupt - try it!");
}

void loop() {
  byte source = myIMU.readAndClearInterrupts();
  if(myIMU.checkInterrupt(source, ICM20948_FSYNC_INT)){
    Serial.println("Interrupt! Type: FSync Pin Interrupt");
  }
}
