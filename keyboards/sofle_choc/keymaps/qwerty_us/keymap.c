// TheKeebLab Sofle, wired (Vial). Same layers as the wireless Sofle keymap;
// wireless-only keys are left empty.
#include QMK_KEYBOARD_H
#include "tkl_brightness.h"
#include "tkl_layers.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_GRV,         KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
        KC_TAB,         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_PIPE,
        KC_LSFT,        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        LCTL_T(KC_ESC), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MUTE,    KC_MPLY, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_CAPS,
                                 KC_LALT, MO(2),   KC_LGUI, MO(1),   KC_ENT,     KC_SPC,  KC_BSPC, KC_DEL,  MO(1),   KC_RALT
    ),
    [1] = LAYOUT(
        _______,        _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
        KC_GRV,         KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE,
        _______,        KC_QUES, KC_EQL,  KC_UNDS, KC_MINS, KC_PLUS,                      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_COLN, _______,
        _______,        XXXXXXX, XXXXXXX, XXXXXXX, KC_LCBR, KC_RCBR, _______,    _______, KC_LBRC, KC_RBRC, KC_LT,   KC_GT,   KC_BSLS, XXXXXXX,
                                 _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______
    ),
    [2] = LAYOUT(
        _______,        KC_F1,   KC_F2,   KC_F3,   KC_F4,   XXXXXXX,                      XXXXXXX, KC_7,    KC_8,    KC_9,    KC_MINS, XXXXXXX,
        _______,        KC_F5,   KC_F6,   KC_F7,   KC_F8,   XXXXXXX,                      XXXXXXX, KC_4,    KC_5,    KC_6,    KC_PLUS, XXXXXXX,
        _______,        KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,                      XXXXXXX, KC_1,    KC_2,    KC_3,    KC_ASTR, XXXXXXX,
        _______,        KC_HOME, KC_PGUP, KC_PGDN, KC_END,  KC_INS,  XXXXXXX,    XXXXXXX, XXXXXXX, KC_0,    XXXXXXX, KC_DOT,  KC_SLSH, XXXXXXX,
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
