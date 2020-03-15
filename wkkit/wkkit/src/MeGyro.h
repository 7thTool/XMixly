

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MeGyro_H
#define MeGyro_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include <Wire.h>


/* Exported macro ------------------------------------------------------------*/
#define I2C_ERROR                  (-1)
#define GYRO_DEFAULT_ADDRESS       (0x68)


class MeGyro
{
public:

  MeGyro(void);
  void begin();
  void update(void);
  void fast_update(void);
  uint8_t getDevAddr(void);
  double getAngleX(void);
  double getAngleY(void);
  double getAngleZ(void);
  double getGyroX(void);
  double getGyroY(void);
  double getAngle(uint8_t index);

private:
  double  gSensitivity; /* for 500 deg/s, check data sheet */
  double  gx, gy, gz;
  double  gyrX, gyrY, gyrZ;
  int16_t accX, accY, accZ;
  double  gyrXoffs, gyrYoffs, gyrZoffs;
  uint8_t i2cData[14];
  uint8_t Device_Address;
  

  void deviceCalibration(void);

  int8_t writeReg(int16_t reg, uint8_t data);


  int8_t readData(uint8_t start, uint8_t *buffer, uint8_t size);

  int8_t writeData(uint8_t start, const uint8_t *pData, uint8_t size);
};
#endif //  MeGyro_H
