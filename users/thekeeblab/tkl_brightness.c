// Screen brightness key on the wired builds. The USB half handles the key, keeps the
// level in EEPROM and sends it to the other half, which only shows it.
#include QMK_KEYBOARD_H
#include "transactions.h"
#include "tkl_brightness.h"

#ifdef OLED_ENABLE

// Also sent while nothing changes, so a half that restarts on its own catches up.
#define TKL_SYNC_MS 1000

// High, medium and low.
static const uint8_t levels[] = {255, 128, 32};

static uint8_t picked; // 0 = never pressed
static uint32_t last_sync;
static bool synced;
static volatile uint8_t received; // other half: set by the split link, shown by housekeeping

uint8_t tkl_brightness(uint8_t fallback) { return picked ? picked : fallback; }

static uint8_t next_level(uint8_t now) {
    for (uint8_t i = 0; i < sizeof(levels); i++) {
        if (levels[i] < now) {
            return levels[i];
        }
    }
    return levels[0];
}

static bool is_level(uint32_t value) {
    for (uint8_t i = 0; i < sizeof(levels); i++) {
        if (value == levels[i]) {
            return true;
        }
    }
    return false;
}

static void on_sync(uint8_t in_len, const void *in_data, uint8_t out_len, void *out_data) {
    if (in_len == 1) {
        received = *(const uint8_t *)in_data;
    }
}

void keyboard_post_init_user(void) {
    transaction_register_rpc(TKL_SYNC_BRIGHTNESS, on_sync);
    if (is_keyboard_master()) {
        uint32_t saved = eeconfig_read_user();
        if (is_level(saved)) {
            picked = saved;
            oled_set_brightness(picked);
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode != TKL_BRI) {
        return true;
    }
    if (record->event.pressed) {
        picked = next_level(oled_get_brightness());
        oled_set_brightness(picked);
        eeconfig_update_user(picked);
        synced = false;
    }
    return false;
}

void housekeeping_task_user(void) {
    if (is_keyboard_master()) {
        if (picked && (!synced || timer_elapsed32(last_sync) >= TKL_SYNC_MS)) {
            synced = transaction_rpc_send(TKL_SYNC_BRIGHTNESS, sizeof(picked), &picked);
            last_sync = timer_read32();
        }
    } else if (is_level(received) && received != picked) {
        picked = received;
        oled_set_brightness(picked);
    }
}

#endif
