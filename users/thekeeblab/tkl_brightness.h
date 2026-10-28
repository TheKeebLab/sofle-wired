#pragma once

#include QMK_KEYBOARD_H

// Screen brightness key: each press steps both screens to high, medium, low, then
// high again; the level is kept when unplugged. Vial shows it as the first custom
// keycode (vial.json "customKeycodes").
#define TKL_BRI QK_KB_0

// The level picked with TKL_BRI, or `fallback` until it is pressed.
uint8_t tkl_brightness(uint8_t fallback);
