#include "api.h"

#include "board_config.h"

extern void setup();
extern void loop();

extern void __initSystem();

void main(void) {
    __initSystem();

    setup();
    while (1) {
        loop();
    }
}
