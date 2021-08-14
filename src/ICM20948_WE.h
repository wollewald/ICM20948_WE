/******************************************************************************
 *
 * This is a library for the 9-axis gyroscope, accelerometer and magnetometer ICM20948.
 *
 * You'll find several example sketches which should enable you to use the library. 
 *
 * You are free to use it, change it or build on it. In case you like it, it would
 * be cool if you give it a star.
 *
 * If you find bugs, please inform me!
 * 
 * Written by Wolfgang (Wolle) Ewald
 *
 * Further information can be found on:
 *
 * https://wolles-elektronikkiste.de/icm-20948-9-achsensensor-teil-i (German)
 * https://wolles-elektronikkiste.de/en/icm-20948-9-axis-sensor-part-i (English)
 *
 * 
 ******************************************************************************/

#ifndef ICM20948_WE_H_
#define ICM20948_WE_H_

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Wire.h>

#define AK09916_ADDRESS 0x0C

/* Registers ICM20948 USER BANK 0*/
#define ICM20948_WHO_AM_I            0x00
#define ICM20948_USER_CTRL           0x03
#define ICM20948_LP_CONFIG           0x05
#define ICM20948_PWR_MGMT_1          0x06
#define ICM20948_PWR_MGMT_2          0x07
#define ICM20948_INT_PIN_CFG         0x0F
#define ICM20948_INT_ENABLE          0x10
#define ICM20948_INT_ENABLE_1        0x11
#define ICM20948_INT_ENABLE_2        0x12
#define ICM20948_INT_ENABLE_3        0x13
#define ICM20948_I2C_MST_STATUS      0x17
#define ICM20948_INT_STATUS          0x19
#define ICM20948_INT_STATUS_1        0x1A
#define ICM20948_INT_STATUS_2        0x1B
#define ICM20948_INT_STATUS_3        0x1C
#define ICM20948_DELAY_TIME_H        0x28
#define ICM20948_DELAY_TIME_L        0x29
#define ICM20948_ACCEL_OUT           0x2D // accel data registers begin
#define ICM20948_GYRO_OUT            0x33 // gyro data registers begin
#define ICM20948_TEMP_OUT            0x39 
#define ICM20948_EXT_SLV_SENS_DATA_00  0x3B
#define ICM20948_EXT_SLV_SENS_DATA_01  0x3C
#define ICM20948_FIFO_EN_1           0x66
#define ICM20948_FIFO_EN_2           0x67
#define ICM20948_FIFO_RST            0x68
#define ICM20948_FIFO_MODE           0x69
#define ICM20948_FIFO_COUNT          0x70
#define ICM20948_FIFO_R_W            0x72
#define ICM20948_DATA_RDY_STATUS     0x74
#define ICM20948_FIFO_CFG            0x76

/* Registers ICM20948 USER BANK 1*/
#define ICM20948_SELF_TEST_X_GYRO    0x02
#define ICM20948_SELF_TEST_Y_GYRO    0x03
#define ICM20948_SELF_TEST_Z_GYRO    0x04
#define ICM20948_SELF_TEST_X_ACCEL   0x0E
#define ICM20948_SELF_TEST_Y_ACCEL   0x0F
#define ICM20948_SELF_TEST_Z_ACCEL   0x10
#define ICM20948_XA_OFFS_H           0x14
#define ICM20948_XA_OFFS_L           0x15
#define ICM20948_YA_OFFS_H           0x17
#define ICM20948_YA_OFFS_L           0x18
#define ICM20948_ZA_OFFS_H           0x1A
#define ICM20948_ZA_OFFS_L           0x1B
#define ICM20948_TIMEBASE_CORR_PLL   0x28

/* Registers ICM20948 USER BANK 2*/
#define ICM20948_GYRO_SMPLRT_DIV     0x00
#define ICM20948_GYRO_CONFIG_1       0x01
#define ICM20948_GYRO_CONFIG_2       0x02
#define ICM20948_XG_OFFS_USRH        0x03
#define ICM20948_XG_OFFS_USRL        0x04
#define ICM20948_YG_OFFS_USRH        0x05
#define ICM20948_YG_OFFS_USRL        0x06
#define ICM20948_ZG_OFFS_USRH        0x07
#define ICM20948_ZG_OFFS_USRL        0x08
#define ICM20948_ODR_ALIGN_EN        0x09
#define ICM20948_ACCEL_SMPLRT_DIV_1  0x10
#define ICM20948_ACCEL_SMPLRT_DIV_2  0x11
#define ICM20948_ACCEL_INTEL_CTRL    0x12
#define ICM20948_ACCEL_WOM_THR       0x13
#define ICM20948_ACCEL_CONFIG        0x14
#define ICM20948_ACCEL_CONFIG_2      0x15
#define ICM20948_FSYNC_CONFIG        0x52
#define ICM20948_TEMP_CONFIG         0x53
#define ICM20948_MOD_CTRL_USR        0x54

/* Registers ICM20948 USER BANK 3*/
#define ICM20948_I2C_MST_ODR_CFG     0x00
#define ICM20948_I2C_MST_CTRL        0x01
#define ICM20948_I2C_MST_DELAY_CTRL  0x02
#define ICM20948_I2C_SLV0_ADDR       0x03
#define ICM20948_I2C_SLV0_REG        0x04
#define ICM20948_I2C_SLV0_CTRL       0x05
#define ICM20948_I2C_SLV0_DO         0x06

/* Registers ICM20948 ALL BANKS */
#define ICM20948_REG_BANK_SEL        0x7F


/* Registers AK09916 */
#define AK09916_WIA_1    0x00 // Who I am, Company ID
#define AK09916_WIA_2    0x01 // Who I am, Device ID
#define AK09916_STATUS_1 0x10 
#define AK09916_HXL      0x11
#define AK09916_HXH      0x12
#define AK09916_HYL      0x13
#define AK09916_HYH      0x14
#define AK09916_HZL      0x15
#define AK09916_HZH      0x16
#define AK09916_STATUS_2 0x18
#define AK09916_CNTL_2   0x31
#define AK09916_CNTL_3   0x32

/* Register Bits */
#define ICM20948_RESET              0x80
#define ICM20948_I2C_MST_EN         0x20
#define ICM20948_SLEEP              0x40
#define ICM20948_LP_EN              0x20
#define ICM20948_BYPASS_EN          0x02
#define ICM20948_GYR_EN             0x07
#define ICM20948_ACC_EN             0x38
#define ICM20948_FIFO_EN            0x40
#define ICM20948_INT1_ACTL          0x80
#define ICM20948_INT_1_LATCH_EN     0x20
#define ICM20948_ACTL_FSYNC         0x08
#define ICM20948_INT_ANYRD_2CLEAR   0x10
#define ICM20948_FSYNC_INT_MODE_EN  0x06
#define AK09916_16_BIT              0x10
#define AK09916_OVF                 0x08
#define AK09916_READ                0x80

/* Others */
#define AK09916_WHO_AM_I            0x4809
#define ICM20948_ROOM_TEMP_OFFSET   0.0f
#define ICM20948_T_SENSITIVITY      333.87f
#define AK09916_MAG_LSB             0.1495f


/* Enums */


typedef enum ICM20948_CYCLE {
    ICM20948_NO_CYCLE              = 0x00,
    ICM20948_GYR_CYCLE             = 0x10, 
    ICM20948_ACC_CYCLE             = 0x20,
    ICM20948_ACC_GYR_CYCLE         = 0x30,
    ICM20948_ACC_GYR_I2C_MST_CYCLE = 0x70
} ICM20948_cycle;

typedef enum ICM20948_INT_PIN_POL {
    ICM20948_ACT_HIGH, ICM20948_ACT_LOW
} ICM20948_intPinPol;

typedef enum ICM20948_INT_TYPE {
    ICM20948_FSYNC_INT      = 0x01,
    ICM20948_WOM_INT        = 0x02,
    ICM20948_DMP_INT        = 0x04,
    ICM20948_DATA_READY_INT = 0x08,
    ICM20948_FIFO_OVF_INT   = 0x10,
    ICM20948_FIFO_WM_INT    = 0x20
} ICM20948_intType;

typedef enum ICM20948_FIFO_TYPE {
    ICM20948_FIFO_ACC        = 0x10,
    ICM20948_FIFO_GYR        = 0x0E,
    ICM20948_FIFO_ACC_GYR    = 0x1E
} ICM20948_fifoType;

typedef enum ICM20948_FIFO_MODE_CHOICE {
    ICM20948_CONTINUOUS, ICM20948_STOP_WHEN_FULL
} ICM20948_fifoMode;

typedef enum ICM20948_GYRO_RANGE {
    ICM20948_GYRO_RANGE_250, ICM20948_GYRO_RANGE_500, ICM20948_GYRO_RANGE_1000, ICM20948_GYRO_RANGE_2000
} ICM20948_gyroRange;

typedef enum ICM20948_DLPF {
    ICM20948_DLPF_0, ICM20948_DLPF_1, ICM20948_DLPF_2, ICM20948_DLPF_3, ICM20948_DLPF_4, ICM20948_DLPF_5, 
    ICM20948_DLPF_6, ICM20948_DLPF_7, ICM20948_DLPF_OFF
} ICM20948_dlpf;

typedef enum ICM20948_GYRO_AVG_LOW_PWR {
    ICM20948_GYR_AVG_1, ICM20948_GYR_AVG_2, ICM20948_GYR_AVG_4, ICM20948_GYR_AVG_8, ICM20948_GYR_AVG_16, 
    ICM20948_GYR_AVG_32, ICM20948_GYR_AVG_64, ICM20948_GYR_AVG_128
} ICM20948_gyroAvgLowPower;

typedef enum ICM20948_ACC_RANGE {
    ICM20948_ACC_RANGE_2G, ICM20948_ACC_RANGE_4G, ICM20948_ACC_RANGE_8G, ICM20948_ACC_RANGE_16G
} ICM20948_accRange;

typedef enum ICM20948_ACC_AVG_LOW_PWR {
    ICM20948_ACC_AVG_4, ICM20948_ACC_AVG_8, ICM20948_ACC_AVG_16, ICM20948_ACC_AVG_32
} ICM20948_accAvgLowPower;

typedef enum ICM20948_WOM_COMP {
    ICM20948_WOM_COMP_DISABLE, ICM20948_WOM_COMP_ENABLE
} ICM20948_womCompEn;

typedef enum AK09916_OP_MODE {
    AK09916_PWR_DOWN           = 0x00,
    AK09916_TRIGGER_MODE       = 0x01,
    AK09916_CONT_MODE_10HZ     = 0x02,
    AK09916_CONT_MODE_20HZ     = 0x04,
    AK09916_CONT_MODE_50HZ     = 0x06,
    AK09916_CONT_MODE_100HZ    = 0x08
} AK09916_opMode;

typedef enum ICM20948_ORIENTATION {
  ICM20948_FLAT, ICM20948_FLAT_1, ICM20948_XY, ICM20948_XY_1, ICM20948_YX, ICM20948_YX_1
} ICM20948_orientation;

struct xyzFloat {
    float x;
    float y;
    float z;
};


class ICM20948_WE
{
public: 
    
    /* Constructors */
    
    ICM20948_WE(int addr);
    ICM20948_WE();
    ICM20948_WE(TwoWire *w, int addr);
    ICM20948_WE(TwoWire *w);           
    
   
   /* Basic settings */

    bool init();
    void autoOffsets();
    void setAccOffsets(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);
    void setGyrOffsets(float xOffset, float yOffset, float zOffset);    
    uint8_t whoAmI();
    void enableAcc(bool enAcc);
    void setAccRange(ICM20948_accRange accRange);
    void setAccDLPF(ICM20948_dlpf dlpf); 
    void setAccSampleRateDivider(uint16_t accSplRateDiv);
    void enableGyr(bool enGyr);
    void setGyrRange(ICM20948_gyroRange gyroRange);
    void setGyrDLPF(ICM20948_dlpf dlpf); 
    void setGyrSampleRateDivider(uint8_t gyrSplRateDiv);
    void setTempDLPF(ICM20948_dlpf dlpf);
    void setI2CMstSampleRate(uint8_t rateExp);
        
            
    /* x,y,z results */
    
    void readSensor(); 
    xyzFloat getAccRawValues();
    xyzFloat getCorrectedAccRawValues();
    xyzFloat getGValues();
    xyzFloat getAccRawValuesFromFifo();
    xyzFloat getCorrectedAccRawValuesFromFifo();
    xyzFloat getGValuesFromFifo();
    float getResultantG(xyzFloat gVal); 
    float getTemperature();
    xyzFloat getGyrRawValues();
    xyzFloat getCorrectedGyrRawValues();
    xyzFloat getGyrValues(); 
    xyzFloat getGyrValuesFromFifo();
    xyzFloat getMagValues();
    
        
    /* Angles and Orientation */ 
    
    xyzFloat getAngles();
    ICM20948_orientation getOrientation();
    String getOrientationAsString();
    float getPitch();
    float getRoll();
    
    
    /* Power, Sleep, Standby */ 
    
    void enableCycle(ICM20948_cycle cycle);
    void enableLowPower(bool enLP);
    void setGyrAverageInCycleMode(ICM20948_gyroAvgLowPower avg);
    void setAccAverageInCycleMode(ICM20948_accAvgLowPower avg);
    void sleep(bool sleep);
    
   
    /* Interrupts */
    
    void setIntPinPolarity(ICM20948_intPinPol pol);
    void enableIntLatch(bool latch);
    void enableClearIntByAnyRead(bool clearByAnyRead);
    void setFSyncIntPolarity(ICM20948_intPinPol pol);
    void enableInterrupt(ICM20948_intType intType);
    void disableInterrupt(ICM20948_intType intType);
    uint8_t readAndClearInterrupts();
    bool checkInterrupt(uint8_t source, ICM20948_intType type);
    void setWakeOnMotionThreshold(uint8_t womThresh, ICM20948_womCompEn womCompEn);
    
    
    /* FIFO */
    
    void enableFifo(bool fifo);
    void setFifoMode(ICM20948_fifoMode mode);
    void startFifo(ICM20948_fifoType fifo);
    void stopFifo();
    void resetFifo();
    int16_t getFifoCount();
    int16_t getNumberOfFifoDataSets();
    void findFifoBegin();
    
    
    /* Magnetometer */
    
    bool initMagnetometer();
    int16_t whoAmIMag();
    void setMagOpMode(AK09916_opMode opMode);
    void resetMag();
    
private:
    TwoWire *_wire;
    int i2cAddress;
    uint8_t currentBank;
    uint8_t buffer[20]; 
    xyzFloat accOffsetVal;
    xyzFloat accCorrFactor;
    xyzFloat gyrOffsetVal;
    uint8_t accRangeFactor;
    uint8_t gyrRangeFactor;
    uint8_t regVal;   // intermediate storage of register values
    ICM20948_fifoType fifoType;
    
    void setClockToAutoSelect();
    xyzFloat correctAccRawValues(xyzFloat accRawVal);
    xyzFloat correctGyrRawValues(xyzFloat gyrRawVal);
    void switchBank(uint8_t newBank);
    uint8_t writeRegister8(uint8_t bank, uint8_t reg, uint8_t val);
    uint8_t writeRegister16(uint8_t bank, uint8_t reg, int16_t val);
    uint8_t readRegister8(uint8_t bank, uint8_t reg);
    int16_t readRegister16(uint8_t bank, uint8_t reg);
    void readAllData(uint8_t* data);
    xyzFloat readICM20948xyzValFromFifo();
    void writeAK09916Register8(uint8_t reg, uint8_t val);
    uint8_t readAK09916Register8(uint8_t reg);
    int16_t readAK09916Register16(uint8_t reg);
    uint8_t reset_ICM20948();
    void enableI2CMaster();
    void enableMagDataRead(uint8_t reg, uint8_t bytes);

};

#endif

