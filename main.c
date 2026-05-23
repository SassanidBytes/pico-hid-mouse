#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "pico/stdlib.h"
#include "tusb.h"

uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id,
                                hid_report_type_t report_type,
                                uint8_t* buffer, uint16_t reqlen) {
    return 0;
}

void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id,
                            hid_report_type_t report_type,
                            uint8_t const* buffer, uint16_t bufsize) {
}

int main(void) {
    stdio_init_all();
    tusb_init();

    while (1) {
        tud_task();
        
        int dx = 0, dy = 0;
        if (scanf("%d,%d", &dx, &dy) == 2) {
            if (tud_hid_ready()) {
                tud_hid_mouse_report(0, 0, dx, dy, 0, 0);
            }
        }
    }

    return 0;
}