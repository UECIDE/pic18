#ifndef _HARDWARE_SERIAL_H
#define _HARDWARE_SERIAL_H

#include <api.h>

#ifdef _HAS_EUSART

#define _SERIAL_BUFFER 16

struct _hardware_serial_object {
    uint8_t rx[_SERIAL_BUFFER];
    uint8_t rx_head;
    uint8_t rx_tail;

    void (*begin)(uint32_t);
    int (*available)();
    int (*read)();
    void (*write)(char);
    void (*ungetc)(uint8_t);
    void (*print)(char *);
    void (*println)(char *);
    void (*print_P)(const char *);
    void (*println_P)(const char *);
};

extern struct _hardware_serial_object Serial;

#endif
#endif
