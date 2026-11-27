// Shared by every TheKeebLab wired build, included by each board's config.h.
#pragma once

// USB goes into the left half, like the wireless builds where the left half is the central.
#define MASTER_LEFT
#define SPLIT_USB_DETECT
// A half that found neither the computer nor the half on USB restarts and looks again (tkl_split.c).
#define SPLIT_WATCHDOG_ENABLE

// 8 layers: room for every layout and for the customer's own layers.
#undef DYNAMIC_KEYMAP_LAYER_COUNT
#define DYNAMIC_KEYMAP_LAYER_COUNT 8

// Both screens go to sleep and wake up together.
#define SPLIT_ACTIVITY_ENABLE

// The screens pace their own redraws: QMK's 50 ms step on split boards made 60 ms animation frames uneven.
#define OLED_UPDATE_INTERVAL 0

// The screen brightness key (tkl_brightness.c) sends its level to the other half.
#define SPLIT_TRANSACTION_IDS_USER TKL_SYNC_BRIGHTNESS

#define TAPPING_TERM 200

// Screens start at the brightness key's medium level, like the wireless builds.
#define OLED_BRIGHTNESS 128
