#include <HardwareSerial.h>

#ifdef _HAS_EUSART

void Z5HardwareSerial48begin(uint32_t baud) {
    pinMode(_EUSART_TX_PIN, OUTPUT);
    pinMode(_EUSART_RX_PIN, INPUT);

    TXSTAbits.TXEN = 1;
    RCSTAbits.CREN = 1;

    uint32_t testval = 0;

    // First try with BRGH=0 and BRG16=0
    testval = F_CPU / (64 * (baud + 1));

    if (testval < 200 && testval > 10) {
        SPBRG = testval;
        TXSTAbits.BRGH = 0;
#if defined(_PIC18)
        BAUDCONbits.BRG16 = 0;
#elif defined(_PIC14)
        BAUDCTLbits.BRG16 = 0;
#endif
    } else {
        // That wasn't suitable. Let's turn on BRGH.
        testval = F_CPU / (16 * (baud + 1));
        if (testval < 200 && testval > 10) {
            SPBRG = testval;
            TXSTAbits.BRGH = 1;
#if defined(_PIC18)
            BAUDCONbits.BRG16 = 0;
#elif defined(_PIC14)
            BAUDCTLbits.BRG16 = 0;
#endif
        } else {
            // Still no good - let's slow it down even more.
            testval = F_CPU / (4 * (baud + 1));
            SPBRG = testval & 0xFF;
            SPBRGH = (testval >> 8) & 0xFF;
            TXSTAbits.BRGH = 1;
#if defined(_PIC18)
            BAUDCONbits.BRG16 = 1;
#elif defined(_PIC14)
            BAUDCTLbits.BRG16 = 1;
#endif
        }
    }

    RCSTAbits.SPEN = 1;
    PIR1bits.RCIF = 0;
    PIE1bits.RCIE = 1;
}

int Z5HardwareSerial48available() {
        return (_SERIAL_BUFFER + Serial.rx_head - Serial.rx_tail) % _SERIAL_BUFFER;
}

int Z5HardwareSerial48read() {
    uint8_t inch;

    if (Serial.rx_head == Serial.rx_tail) {
        return -1;
    } 
    inch = Serial.rx[Serial.rx_tail];
    Serial.rx_tail  = (Serial.rx_tail + 1) % _SERIAL_BUFFER;
    return inch;
}

void Z5HardwareSerial48write(uint8_t v) {
    while (TXSTAbits.TRMT != 1);
    TXREG = v;
}

void Z5HardwareSerial48ungetc(uint8_t v) {
    uint8_t bufIndex = (Serial.rx_head + 1) % _SERIAL_BUFFER;

    if (bufIndex != Serial.rx_tail)
    {
        Serial.rx[Serial.rx_head] = v;
        Serial.rx_head = bufIndex;
    }
}

void Z5HardwareSerial48print(char *str) {
    while (*str) {
        Z5HardwareSerial48write((uint8_t)*str);
        str++;
    }
}

void Z5HardwareSerial48print_P(const char *str) {
    while (*str) {
        Z5HardwareSerial48write((uint8_t)*str);
        str++;
    }
}

void Z5HardwareSerial48println(char *str) {
    Z5HardwareSerial48print(str);
    Z5HardwareSerial48print_P("\r\n");
}

void Z5HardwareSerial48println_P(const char *str) {
    Z5HardwareSerial48print_P(str);
    Z5HardwareSerial48print_P("\r\n");
}

struct _hardware_serial_object Serial = {
    "",
    0,
    0,
    &Z5HardwareSerial48begin,
    &Z5HardwareSerial48available,
    &Z5HardwareSerial48read,
    &Z5HardwareSerial48write,
    &Z5HardwareSerial48ungetc,
    &Z5HardwareSerial48print,
    &Z5HardwareSerial48println,
    &Z5HardwareSerial48print_P,
    &Z5HardwareSerial48println_P
};


#endif
