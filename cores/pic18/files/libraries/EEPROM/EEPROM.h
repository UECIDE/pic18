#ifndef _EEPROM_H
#define _EEPROM_H

#include <api.h>

struct _eeprom_object {
    uint8_t (*read)(uint16_t);
    void (*write)(uint16_t, uint8_t);
};

extern struct _eeprom_object EEPROM;

#endif
