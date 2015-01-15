#ifndef API_H
#define	API_H

#include <xc.h>
#include <stdint.h>
#include <stdio.h>
    
#include "board_settings.h"

#include <HardwareSerial.h>

#define OUTPUT 0
#define INPUT 1
#define INPUT_PULLUP 2
#define LOW 0
#define HIGH 1

struct ioPin {
    volatile uint8_t *tris;
    volatile uint8_t *port;
    volatile uint8_t *lat;
    uint8_t pin;
    int8_t adc;
    int8_t pullup;
};

extern const struct ioPin _pins[];
extern const uint8_t _pins_max;

extern uint32_t millis();
extern void delay(uint32_t del);
extern void pinMode(uint8_t pin, uint8_t mode);
extern void digitalWrite(uint8_t pin, uint8_t val);
extern uint8_t digitalRead(uint8_t pin);
extern void savePower();

#endif	/* API_H */

