// AZERTY (French) layout for the sofle, generated from the stock keymap.
// Layer 0 keys stay where they are (the computer's keyboard language decides what they type);
// the other layers type the same characters as the stock keymap. Extra keys:
//   layer 1, key 37: €
//   layer 1, key 38: ¨
// TheKeebLab Sofle, wired (Vial). Same layers as the wireless Sofle keymap;
// wireless-only keys are left empty.
#include QMK_KEYBOARD_H
#include "tkl_brightness.h"
#include "tkl_layers.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_GRV,         KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
        KC_TAB,         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    ALGR(KC_6),
        KC_LSFT,        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        LCTL_T(KC_ESC), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MUTE,    KC_MPLY, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_CAPS,
                                 KC_LALT, MO(2),   KC_LGUI, MO(1),   KC_ENT,     KC_SPC,  KC_BSPC, KC_DEL,  MO(1),   KC_RALT
    ),
    [1] = LAYOUT(
        _______,        _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
        ALGR(KC_7),         KC_SLSH, ALGR(KC_0),   ALGR(KC_3), KC_RBRC,  S(KC_QUOT),                      KC_LBRC, KC_1, KC_NUHS, KC_5, KC_MINS, ALGR(KC_6),
        _______,        S(KC_M), KC_EQL,  KC_8, KC_6, KC_PLUS,                      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_DOT, _______,
        _______,        ALGR(KC_E), S(KC_LBRC), XXXXXXX, ALGR(KC_4), ALGR(KC_EQL), _______,    _______, ALGR(KC_5), ALGR(KC_MINS), KC_NUBS,   S(KC_NUBS),   ALGR(KC_8), XXXXXXX,
                                 _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______
    ),
    [2] = LAYOUT(
        _______,        KC_F1,   KC_F2,   KC_F3,   KC_F4,   XXXXXXX,                      XXXXXXX, S(KC_7),    S(KC_8),    S(KC_9),    KC_6, XXXXXXX,
        _______,        KC_F5,   KC_F6,   KC_F7,   KC_F8,   XXXXXXX,                      XXXXXXX, S(KC_4),    S(KC_5),    S(KC_6),    KC_PLUS, XXXXXXX,
        _______,        KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,                      XXXXXXX, S(KC_1),    S(KC_2),    S(KC_3),    KC_NUHS, XXXXXXX,
        _______,        KC_HOME, KC_PGUP, KC_PGDN, KC_END,  KC_INS,  XXXXXXX,    XXXXXXX, XXXXXXX, S(KC_0),    XXXXXXX, S(KC_COMM),  S(KC_DOT), XXXXXXX,
                                 _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______
    ),
    // Reached by holding layers 1 and 2 together (see layer_state_set_user), or any layer key set up in Vial.
    [3] = LAYOUT(
        XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TG(4),
        XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,        XXXXXXX, XXXXXXX, TKL_BRI, KC_SLEP, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [4] = LAYOUT(
        _______,        _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
        _______,        _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
        _______,        _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
        _______,        _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, KC_SPC,     KC_ENT,  _______, _______, _______, _______
    ),
};

// Physical clockwise = volume up, scroll down, page down, as on the wireless keymap. QMK reads
// these knobs the same way round as ZMK, so the "CW" slot gets the counter-clockwise action.
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {ENCODER_CCW_CW(KC_VOLU, KC_VOLD), ENCODER_CCW_CW(MS_WHLD, MS_WHLU)},
    [1] = {ENCODER_CCW_CW(KC_VOLU, KC_VOLD), ENCODER_CCW_CW(KC_PGDN, KC_PGUP)},
    [2] = {ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)},
    [3] = {ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)},
    [4] = {ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)},
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return tkl_tri_layer(state, 1, 2, 3);
}
