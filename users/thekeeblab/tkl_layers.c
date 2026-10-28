#include "tkl_layers.h"

layer_state_t tkl_tri_layer(layer_state_t state, uint8_t lower, uint8_t raise, uint8_t upper) {
    static bool forced = false;
    layer_state_t upper_mask = (layer_state_t)1 << upper;

    if (layer_state_cmp(state, lower) && layer_state_cmp(state, raise)) {
        if (!(state & upper_mask)) {
            forced = true;
        }
        return state | upper_mask;
    }
    if (forced) {
        forced = false;
        return state & ~upper_mask;
    }
    return state;
}
