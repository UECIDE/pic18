#include "api.h"

const struct ioPin _pins[] = {
    { &TRISC, &PORTC, &PORTC, 7, -1, -1 },
    { &TRISC, &PORTC, &PORTC, 6, -1, -1 },
    { &TRISC, &PORTC, &PORTC, 5, -1, -1 },
    { &TRISC, &PORTC, &PORTC, 4, -1, -1 },
    { &TRISC, &PORTC, &PORTC, 3, -1, -1 },
    { &TRISC, &PORTC, &PORTC, 2, -1, -1 },
    { &TRISC, &PORTC, &PORTC, 1, -1, -1 },
    { &TRISC, &PORTC, &PORTC, 0, -1, -1 },
    { &TRISB, &PORTB, &PORTB, 0, -1, -1 },
    { &TRISB, &PORTB, &PORTB, 1, -1, -1 },
    { &TRISB, &PORTB, &PORTB, 2, -1, -1 },
    { &TRISB, &PORTB, &PORTB, 3, -1, -1 },
    { &TRISB, &PORTB, &PORTB, 4, -1, -1 },
    { &TRISB, &PORTB, &PORTB, 5, -1, -1 },
    { &TRISA, &PORTA, &PORTA, 0, -1, -1 },
    { &TRISA, &PORTA, &PORTA, 1, -1, -1 },
    { &TRISA, &PORTA, &PORTA, 2, -1, -1 },
    { &TRISA, &PORTA, &PORTA, 3, -1, -1 },
    { &TRISA, &PORTA, &PORTA, 5, -1, -1 },
    { &TRISA, &PORTA, &PORTA, 4, -1, -1 },
};

const uint8_t _pins_max = (sizeof(_pins) / sizeof (_pins[0]));
