#include <api.h>
#include <LEDDisplay.h>
/*
       A
     F   B
       G
     E   C
       D    P
 */

const uint8_t _led_digits[10] = {
    //abcdefgp
    0b11111100,
    0b01100000,
    0b11011010,
    0b11110010,
    0b01100110,
    0b10110110,
    0b10111110,
    0b11100100,
    0b11111110,
    0b11110110
};

const uint8_t *_led_pins = 0;

void Z5LED86setPins(const uint8_t *pins) {
    _led_pins = pins;
    uint8_t i;
    for (i = 0; i < 16; i++) {
        pinMode(_led_pins[i], OUTPUT);
        digitalWrite(_led_pins[i], LOW);
    }
}

void Z5LED86displayRaw(uint16_t tval) {
    uint8_t tbit;
    if (_led_pins == 0) return;
    for (tbit = 0; tbit < 16; tbit++) {
        digitalWrite(_led_pins[tbit], (tval & (1<<(15-tbit))) ? HIGH : 0);
    }
}

void Z5LED86displayValue(uint8_t v) {
    if (_led_pins == 0) return;
    while (v > 99) {
        v -= 100;
    }
    uint16_t tval = (_led_digits[v / 10] << 8) | _led_digits[v % 10];
    Z5LED86displayRaw(tval);
}

const struct _led_object LED = {
    &Z5LED86setPins, &Z5LED86displayRaw, &Z5LED86displayValue
};
