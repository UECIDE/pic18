#include "api.h"

static volatile uint32_t __millis = 0;

#define N_PINS (sizeof(_pins) / sizeof (_pins[0]))

#if defined(_PIC18)

void interrupt low_priority __isr_handler(void) {
    if (INTCONbits.TMR0IE && INTCONbits.T0IF) {
        INTCONbits.T0IF = 0;
        uint16_t tpr = (F_CPU/4)/1000;
        tpr = 0xFFFF - tpr;
        TMR0H = tpr >> 8;
        TMR0L = tpr & 0xFF;
        __millis++;
    }
#ifdef _HAS_EUSART
    if (PIE1bits.RCIE && PIR1bits.RCIF) {
        PIR1bits.RCIF = 0;
        Serial.ungetc(RCREG);
    }
#endif
}

#elif defined(_PIC14)

void interrupt __isr_handler(void) {
    if (PIE1bits.TMR1IE && PIR1bits.TMR1IF) {
        PIR1bits.TMR1IF = 0;
        uint16_t tpr = (F_CPU/4)/1000;
        tpr = 0xFFFF - tpr;
        TMR1H = tpr >> 8;
        TMR1L = tpr & 0xFF;
        __millis++;
    }
#ifdef _HAS_EUSART
    if (PIE1bits.RCIE && PIR1bits.RCIF) {
        PIR1bits.RCIF = 0;
        Serial.ungetc(RCREG);
    }
#endif
}

#endif

uint32_t millis() {
    uint32_t mil;
    INTCONbits.T0IE = 0;
    mil = __millis;
    INTCONbits.T0IE = 1;
    return mil;
}

void delay(uint32_t del) {
    uint32_t start = millis();
    while (millis() - start < del) {
        savePower();
    }
}

void pinMode(uint8_t pin, uint8_t mode) {
    if (pin >= _pins_max) {
        return;
    }

    switch(mode) {
        case OUTPUT:
            *(_pins[pin].tris) &= ~(1<<_pins[pin].pin);
            break;

        case INPUT_PULLUP:
            *(_pins[pin].tris) |= (1<<_pins[pin].pin);
            if (_pins[pin].adc >= 0) {
                if (_pins[pin].adc < 8) {
                    ANSEL &= ~(1<<_pins[pin].adc);
                } else {
                    ANSELH &= ~(1<<(_pins[pin].adc-8));
                }
            }
            if (_pins[pin].pullup >= 0) {
                WPUB |= (1<<_pins[pin].pullup);
            }
            break;

        case INPUT:
            *(_pins[pin].tris) |= (1<<_pins[pin].pin);
            if (_pins[pin].adc >= 0) {
                if (_pins[pin].adc < 8) {
                    ANSEL &= ~(1<<_pins[pin].adc);
                } else {
                    ANSELH &= ~(1<<(_pins[pin].adc-8));
                }
            }
            if (_pins[pin].pullup >= 0) {
                WPUB &= ~(1<<_pins[pin].pullup);
            }
            break;
    }
}

void digitalWrite(uint8_t pin, uint8_t val) {
    if (pin >= _pins_max) {
        return;
    }

    if (val > 0) {
        *_pins[pin].lat |= (1<<_pins[pin].pin);
    } else {
        *_pins[pin].lat &= ~(1<<_pins[pin].pin);
    }
}

uint8_t digitalRead(uint8_t pin) {
    if (pin >= _pins_max) {
        return LOW;
    }
    return (*_pins[pin].port & (1<<_pins[pin].pin)) ? HIGH : LOW;
}

void __initSystem() {

#if defined(_HAS_INITPLL)
    extern void __initPLL();
    __initPLL();
#endif

#if defined(_PIC18)
    // Set up TIMER0 to tick at 1ms intervals.
    // The oscillator ticks at Fosc/4, so 4MHz. That is 1/16000000 s per tick.
    // or 0.000000063s, or 0.000063ms, so 1 ms is 16000 ticks.
    T0CONbits.T08BIT = 0; // 16-bit
    T0CONbits.T0CS = 0; // Internal clock
    T0CONbits.PSA = 1; // No prescaler
    uint16_t tpr = (F_CPU/4)/1000;
    tpr = 0xFFFF - tpr;
    TMR0H = tpr >> 8;
    TMR0L = tpr & 0xFF;
    INTCONbits.T0IF = 0;
    INTCONbits.T0IE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
    T0CONbits.TMR0ON = 1;

    INTCON2bits.RBPU = 0;
    WPUB = 0;

    LATA = 0;
    LATB = 0;
    LATC = 0;
#elif defined(_PIC14)
    // Set up TIMER1 to tick at 1ms intervals.
    // The oscillator ticks at Fosc/4, so 4MHz. That is 1/16000000 s per tick.
    // or 0.000000063s, or 0.000063ms, so 1 ms is 16000 ticks.
    T1CONbits.TMR1CS = 0; // Internal clock
    T1CONbits.T1CKPS = 0; // No prescaler
    uint16_t tpr = (F_CPU/4)/1000;
    tpr = 0xFFFF - tpr;
    TMR1H = tpr >> 8;
    TMR1L = tpr & 0xFF;
    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
    T1CONbits.TMR1ON = 1;

    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
#endif
}

// Put the system to sleep until the next "tick" of the timer.  This will
// sleep for up to 1 ms.
void savePower() {
#if defined(_PIC18)
    OSCCONbits.IDLEN = 1;
    OSCCONbits.SCS = 0b00;
    asm("SLEEP");
#endif
}

