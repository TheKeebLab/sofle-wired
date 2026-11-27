// Stock TheKeebLab screens for the wired builds: the half plugged into USB
// shows the layer number and caps lock, the other half shows the logo.
#include QMK_KEYBOARD_H
#include "tkl_logo.h"
#include "tkl_split.h"

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
    // Dark until this half knows which one it is (tkl_split.c).
    if (!tkl_split_settled()) {
        if (is_oled_on()) {
            oled_off();
        }
        return false;
    }
#if OLED_TIMEOUT > 0
    // QMK wakes a panel for its own half's keys or for changed pixels only: a key on the other half
    // (SPLIT_ACTIVITY_ENABLE) must wake it too, while the keyboard is not idle.
    static uint32_t woken_by;
    uint32_t key_time = last_input_activity_time();
    if (key_time != woken_by && last_input_activity_elapsed() <= OLED_TIMEOUT) {
        woken_by = key_time;
        oled_on();
    }
#endif
    // QMK no longer paces the screens (OLED_UPDATE_INTERVAL 0): redraw every 50 ms, as before.
    static uint32_t last_draw;
    if (timer_elapsed32(last_draw) < 50) {
        return false;
    }
    last_draw = timer_read32();
    if (is_keyboard_master()) {
        render_status();
    } else {
        oled_write_raw_P(tkl_logo, sizeof(tkl_logo));
    }
    return false;
}

#endif
