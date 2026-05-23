#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bsp/board.h"
#include "tusb.h"

int main(void) {
    board_init();
    tusb_init();

    while (1) {
        tud_task(); // TinyUSB läuft hier
    }

    return 0;
}