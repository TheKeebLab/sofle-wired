#pragma once

#include QMK_KEYBOARD_H

// Turns `upper` on while `lower` and `raise` are both active. Unlike QMK's
// update_tri_layer_state() and ZMK's conditional layers, it only turns `upper`
// off if it turned it on, so MO/TG/TO keys on lower layers still reach it.
layer_state_t tkl_tri_layer(layer_state_t state, uint8_t lower, uint8_t raise, uint8_t upper);
