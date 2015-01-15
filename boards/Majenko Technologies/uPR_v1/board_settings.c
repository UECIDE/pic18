#include "api.h"

const struct ioPin _pins[] = {
    { &TRISB, &PORTB, &LATB, 7, -1, 7 },
    { &TRISB, &PORTB, &LATB, 6, -1, 6 },
    { &TRISB, &PORTB, &LATB, 0, 12, 0 },
    { &TRISB, &PORTB, &LATB, 1, 10, 1 },
    { &TRISA, &PORTA, &LATA, 0, 0, -1 },
    { &TRISA, &PORTA, &LATA, 1, 1, -1 },
    { &TRISC, &PORTC, &LATC, 7, -1, -1 },
    { &TRISC, &PORTC, &LATC, 6, -1, -1 },
    { &TRISC, &PORTC, &LATC, 5, -1, -1 },
    { &TRISC, &PORTC, &LATC, 4, -1, -1 },
    { &TRISC, &PORTC, &LATC, 3, -1, -1 },
    { &TRISC, &PORTC, &LATC, 2, -1, -1 },
    { &TRISC, &PORTC, &LATC, 1, -1, -1 },
    { &TRISC, &PORTC, &LATC, 0, -1, -1 },
    { &TRISA, &PORTA, &LATA, 5, 4, -1 },
    { &TRISA, &PORTA, &LATA, 4, -1, -1 },
    { &TRISA, &PORTA, &LATA, 3, 3, -1 },
    { &TRISA, &PORTA, &LATA, 2, 2, -1 },
    { &TRISB, &PORTB, &LATB, 5, -1, -1 },
    { &TRISB, &PORTB, &LATB, 4, 11, -1 },
    { &TRISB, &PORTB, &LATB, 3, 9, -1 },
    { &TRISB, &PORTB, &LATB, 2, 8, -1 },
};

const uint8_t _pins_max = (sizeof(_pins) / sizeof (_pins[0]));
