// Shared by every TheKeebLab wired build, included by each board's config.h.
#pragma once

// USB goes into the left half, like the wireless builds where the left half is the central.
#define MASTER_LEFT
#define SPLIT_USB_DETECT

// 8 layers: room for every layout and for the customer's own layers.
#undef DYNAMIC_KEYMAP_LAYER_COUNT
#define DYNAMIC_KEYMAP_LAYER_COUNT 8

// Both screens go to sleep and wake up together.
#define SPLIT_ACTIVITY_ENABLE

// The screen brightness key (tkl_brightness.c) sends its level to the other half.
#define SPLIT_TRANSACTION_IDS_USER TKL_SYNC_BRIGHTNESS

#define TAPPING_TERM 200

// Screens start at the brightness key's medium level, like the wireless builds.
#define OLED_BRIGHTNESS 128
