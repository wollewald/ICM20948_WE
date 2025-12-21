# ICM20948_WE
An Arduino library for the ICM-20948 9-axis accelerometer, gyroscope and magnetometer. It contains many example sketches with lots of comments to make it easy to use. It works with I2C and SPI.

I have not implemented DMP features and most probably I won't do that in future. That would exceed the time I can invest. 

You can find a documentation in my blog:

https://wolles-elektronikkiste.de/icm-20948-9-achsensensor-teil-i (German)

https://wolles-elektronikkiste.de/en/icm-20948-9-axis-sensor-part-i (English)

If you find bugs please inform me. If you like the library it would be great if you could give it a star.

If you are not familiar with the ICM20948 I recommend to work through the example sketches.

<h3>Voltage Supply</h3>

When you wire the ICM-20948 you need to consider that the voltage range for VDD is 1.71 to 3.6 volts, but VDDIO is only 1.71-1.95 volts (see data sheet). Many cheap modules have VDDIO internally connected to VDD. Therefore you need to power them with 1.71 to 1.95 volts. Boards from Sparkfun, Pimoroni, Adafruit and others do have voltage regulators level shifters for the digital pins. 

There are also boards available called "version 2", "v2.0" or "v2". They have voltage regulators, but level shifters not for all digital Pins. Here you need to look into the details: 

<img width="1800" height="802" alt="icm20948_version_2" src="https://github.com/user-attachments/assets/6f585f2c-2cb5-4beb-b187-8fc57fb7e8a2" />

The module on the left has four MOSFETs for the level shifting of the pins labeled as SDA, SCL, SDO and INT. All fine with this, except for the CS pin for which you may need a voltage divider or you connect it to GND in case you only have one SPI device. The right one has only two MOSFETs (combined in the highlighted 6-pin-SMD) shifting the levels at SDA and SCL. Therefore it can only be used for I2C-communication. But still you have to take care of the INT-pin. If it goes HIGH it just has 1.8 V, which may not be recognized as a HIGH level by your microcontroller.


<h3>(Formerly) Known issue</h3>
Before version 1.2.0, using my library caused sporadic connection issues after re-powering. This has been solved by setting up the magnetometer as SLV4. The magnetometer data reading is still done using the magnetometer as SLV0. Please inform me if you should still have issues.      
