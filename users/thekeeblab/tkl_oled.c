// Stock TheKeebLab screens for the wired builds: the half plugged into USB
// shows the layer number and caps lock, the other half shows the logo.
#include QMK_KEYBOARD_H
#include "tkl_logo.h"

#ifdef OLED_ENABLE

static void render_status(void) {
    uint8_t layer = get_highest_layer(layer_state | default_layer_state);
    oled_write_P(PSTR("Layer "), false);
    oled_write_char('0' + layer % 10, false);
    oled_advance_page(true);
    oled_advance_page(true);
    oled_advance_page(true);
    oled_write_ln_P(host_keyboard_led_state().caps_lock ? PSTR("CAPS LOCK") : PSTR(""), false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status();
    } else {
        oled_write_raw_P(tkl_logo, sizeof(tkl_logo));
    }
    return false;
}

#endif
