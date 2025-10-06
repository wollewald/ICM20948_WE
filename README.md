# ICM20948_WE
An Arduino library for the ICM-20948 9-axis accelerometer, gyroscope and magnetometer. It contains many example sketches with lots of comments to make it easy to use. It works with I2C and SPI.

I have not implemented DMP features and most probably I won't do that in future. That would exceed the time I can invest. 

You can find a documentation in my blog:

https://wolles-elektronikkiste.de/icm-20948-9-achsensensor-teil-i (German)

https://wolles-elektronikkiste.de/en/icm-20948-9-axis-sensor-part-i (English)

If you find bugs please inform me. If you like the library it would be great if you could give it a star.

If you are not familiar with the ICM20948 I recommend to work through the example sketches.

When you wire the ICM-20948 you need to consider that the voltage range for VDD is 1.71 to 3.6 volts, but VDDIO is only 1.71-1.95 volts (see data sheet). Most cheap modules have VDDIO internally connected to VDD. Therefore you need to power them with 1.71 to 1.95 volts. 

<h3>(Formerly) Known issue</h3>
Before version 1.2.0, using my library caused sporadic connection issues after re-powering. This has been solved by setting up the magnetometer as SLV4. The magnetometer data reading is still done using the magnetometer as SLV0. Please inform me if you should still have issues.      
