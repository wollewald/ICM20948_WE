/***************************************************************************
* Example sketch for the ICM20948_WE library
*
* This sketch shows how to reuse autocalibration data by saving it to the 
* EEPROM or by writing it to the sketch. Use the defines REUSE_OFFSETS and 
* USE_EEPROM to switch between modes and options. 
*
* The sketch has been written for an ESP32 board. If you use a different 
* board, you might have to adjust the EEPROM functions.
* 
* Further information can be found on:
*
* https://wolles-elektronikkiste.de/icm-20948-9-achsensensor-teil-i (German)
* https://wolles-elektronikkiste.de/en/icm-20948-9-axis-sensor-part-i (English)
* 
***************************************************************************/

//#define REUSE_OFFSETS // comment out for calibration, uncomment for reuse
#define USE_EEPROM  // commented out if you don't want to use the EEPROM 
#ifdef USE_EEPROM
#include <EEPROM.h>
#endif
#include <Wire.h>
#include <ICM20948_WE.h>
#define ICM20948_ADDR 0x68

ICM20948_WE myIMU = ICM20948_WE(ICM20948_ADDR);
xyzFloat aOffs; // acceleration offsets
xyzFloat gOffs; // gyroscope offsets

void setup() {
  delay(2000); // optional, might be needed to display everything on serial monitor
#ifdef USE_EEPROM
  EEPROM.begin(sizeof(xyzFloat)*2); // space for to xyzFloats
#endif
  Wire.begin();
  Serial.begin(115200);
  while(!Serial) {}

  if(!myIMU.init()){
    Serial.println("ICM20948 does not respond");
  }
  else{
    Serial.println("ICM20948 is connected");
  }

#ifndef REUSE_OFFSETS
  Serial.println("Position your ICM20948 flat and don't move it - calibrating...");
  delay(1000);
  myIMU.autoOffsets();
  Serial.println("Done!"); 

  aOffs = myIMU.getAccOffsets();  // get acceleration offsets
  gOffs = myIMU.getGyrOffsets();  // get gyroscope offsets 
  
  char buffer[35];
  sprintf(buffer, "{%d.0, %d.0, %d.0}", (int)aOffs.x, (int)aOffs.y, (int)aOffs.z);  
  Serial.print("Acceleration offsets, rounded: ");
  Serial.println(buffer); 
  sprintf(buffer, "{%d.0, %d.0, %d.0}", (int)gOffs.x, (int)gOffs.y, (int)gOffs.z);  
  Serial.print("Gyroscope offsets, rounded   : ");
  Serial.println(buffer); 

#ifdef USE_EEPROM
  EEPROM.put(0, aOffs);
  EEPROM.put(sizeof(xyzFloat), gOffs);
  EEPROM.commit();
#endif // USE_EEPROM
#endif // not REUSE_OFFSETS
  
#ifdef REUSE_OFFSETS
#ifndef USE_EEPROM 
  /* Now you can copy the offsets for reuse. Uncomment line 2. */
  aOffs = { /* copy your offsets here for reuse */ }; 
  gOffs = { /* copy your offsets here for reuse */ };
#endif // not USE_EEPROM

/* Alternatively read your offsets back from EEPROM, if you have saved them there */
#ifdef USE_EEPROM  
  EEPROM.get(0, aOffs);
  EEPROM.get(sizeof(xyzFloat), gOffs);
#endif // USE_EEPROM
  
  myIMU.setAccOffsets(aOffs);
  myIMU.setGyrOffsets(gOffs);
#endif // REUSE_OFFSETS
  
  myIMU.setAccRange(ICM20948_ACC_RANGE_2G);
  myIMU.setAccDLPF(ICM20948_DLPF_6);    
}

void loop() {
/* _Now you can test your calibration data */
#ifdef REUSE_OFFSETS  
  xyzFloat gVal;
  xyzFloat gyr;
  myIMU.readSensor();
  myIMU.getGValues(&gVal);
  myIMU.getGyrValues(&gyr);

  Serial.println("g-values (x,y,z):");
  Serial.print(gVal.x);
  Serial.print("   ");
  Serial.print(gVal.y);
  Serial.print("   ");
  Serial.println(gVal.z);
  
  Serial.println("Gyroscope data in degrees/s: ");
  Serial.print(gyr.x);
  Serial.print("   ");
  Serial.print(gyr.y);
  Serial.print("   ");
  Serial.println(gyr.z);
  Serial.println("\n");

  delay(1000);
#endif // REUSE_OFFSETS
}
