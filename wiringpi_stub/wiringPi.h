/*
 * Minimal stand-in for the wiringPi API, used when zyncore is built on a
 * system without wiringPi (desktop Linux, Nura/postmarketOS on non-Pi hardware).
 * There is no GPIO: setup succeeds, pins read as high (switches released),
 * interrupt registration fails, so no hardware input is ever reported.
 */
#ifndef WIRINGPI_STUB_H
#define WIRINGPI_STUB_H

#ifdef __cplusplus
extern "C" {
#endif

#define INPUT  0
#define OUTPUT 1
#define LOW  0
#define HIGH 1

#define PUD_OFF  0
#define PUD_DOWN 1
#define PUD_UP   2

#define INT_EDGE_SETUP   0
#define INT_EDGE_FALLING 1
#define INT_EDGE_RISING  2
#define INT_EDGE_BOTH    3

enum WPIPinType {
	WPI_PIN_BCM = 1,
	WPI_PIN_WPI,
	WPI_PIN_PHYS,
};

int wiringPiSetup(void);
int wiringPiSetupGpio(void);
int wiringPiSetupPinType(enum WPIPinType pinType);
void pinMode(int pin, int mode);
void pullUpDnControl(int pin, int pud);
int digitalRead(int pin);
void digitalWrite(int pin, int value);
int wiringPiISR(int pin, int mode, void (*function)(void));
void delay(unsigned int howLong);
void delayMicroseconds(unsigned int howLong);
unsigned int millis(void);
unsigned int micros(void);

#ifdef __cplusplus
}
#endif

#endif
