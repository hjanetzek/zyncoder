/* Minimal stand-in for wiringPi, see wiringPi.h. */
#include <stdint.h>
#include <time.h>
#include "wiringPi.h"
#include "wiringPiI2C.h"

int wiringPiSetup(void) { return 0; }
int wiringPiSetupGpio(void) { return 0; }
int wiringPiSetupPinType(enum WPIPinType pinType) { (void)pinType; return 0; }
void pinMode(int pin, int mode) { (void)pin; (void)mode; }
void pullUpDnControl(int pin, int pud) { (void)pin; (void)pud; }
int digitalRead(int pin) { (void)pin; return HIGH; }
void digitalWrite(int pin, int value) { (void)pin; (void)value; }
int wiringPiISR(int pin, int mode, void (*function)(void)) { (void)pin; (void)mode; (void)function; return -1; }

static uint64_t now_us(void) {
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (uint64_t)ts.tv_sec * 1000000u + (uint64_t)ts.tv_nsec / 1000u;
}

void delayMicroseconds(unsigned int howLong) {
	struct timespec ts = { howLong / 1000000u, (long)(howLong % 1000000u) * 1000L };
	nanosleep(&ts, NULL);
}
void delay(unsigned int howLong) { delayMicroseconds(howLong * 1000u); }
unsigned int millis(void) { return (unsigned int)(now_us() / 1000u); }
unsigned int micros(void) { return (unsigned int)now_us(); }

int wiringPiI2CSetup(const int devId) { (void)devId; return -1; }
int wiringPiI2CRead(int fd) { (void)fd; return -1; }
int wiringPiI2CWrite(int fd, int data) { (void)fd; (void)data; return -1; }
int wiringPiI2CReadReg8(int fd, int reg) { (void)fd; (void)reg; return -1; }
int wiringPiI2CReadReg16(int fd, int reg) { (void)fd; (void)reg; return -1; }
int wiringPiI2CWriteReg8(int fd, int reg, int data) { (void)fd; (void)reg; (void)data; return -1; }
int wiringPiI2CWriteReg16(int fd, int reg, int data) { (void)fd; (void)reg; (void)data; return -1; }
