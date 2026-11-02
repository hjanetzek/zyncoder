/* Minimal stand-in for wiringPiI2C, see wiringPi.h. Every I2C device is absent. */
#ifndef WIRINGPII2C_STUB_H
#define WIRINGPII2C_STUB_H

#ifdef __cplusplus
extern "C" {
#endif

int wiringPiI2CSetup(const int devId);
int wiringPiI2CRead(int fd);
int wiringPiI2CWrite(int fd, int data);
int wiringPiI2CReadReg8(int fd, int reg);
int wiringPiI2CReadReg16(int fd, int reg);
int wiringPiI2CWriteReg8(int fd, int reg, int data);
int wiringPiI2CWriteReg16(int fd, int reg, int data);

#ifdef __cplusplus
}
#endif

#endif
