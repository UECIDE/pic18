#include <EEPROM.h>

uint8_t Z5EEPROM91read(uint16_t address) {
    EEADR = address & 0xFF;
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
    EECON1bits.RD = 1;
    while (EECON1bits.RD == 1);
    uint8_t value = EEDATA;
    return value;
}

void Z5EEPROM91write(uint16_t address, uint8_t value) {
    EEADR = address & 0xFF;
    EEDATA = value;
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
    EECON1bits.WREN = 1;
    INTCONbits.GIE = 0;
    asm ("MOVLW 55h");
    asm ("MOVWF EECON2");
    asm ("MOVLW 0AAh");
    asm ("MOVWF EECON2");
    asm ("BSF EECON1, 1");
    while (EECON1bits.WR == 1);
    INTCONbits.GIE = 1;
    EECON1bits.WREN = 0;
}

struct _eeprom_object EEPROM = {
    &Z5EEPROM91read,
    &Z5EEPROM91write
};
