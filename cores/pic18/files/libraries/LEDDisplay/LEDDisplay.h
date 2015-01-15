#ifndef LEDDISPLAY_H
#define	LEDDISPLAY_H

struct _led_object {
    void (*setPins)(const uint8_t *);
    void (*displayRaw)(const uint16_t);
    void (*displayValue)(const uint8_t);
};

extern const struct _led_object LED;

#endif	/* LEDDISPLAY_H */

