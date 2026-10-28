# Shared by every keymap of this repository (USER_NAME := thekeeblab in their rules.mk).
VIA_ENABLE = yes
VIAL_ENABLE = yes
LTO_ENABLE = yes

OLED_ENABLE = yes
EXTRAKEY_ENABLE = yes
MOUSEKEY_ENABLE = yes
CAPS_WORD_ENABLE = yes
TAP_DANCE_ENABLE = yes
COMBO_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes
QMK_SETTINGS = yes

RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = no
VIALRGB_ENABLE = no
BACKLIGHT_ENABLE = no
CONSOLE_ENABLE = no
COMMAND_ENABLE = no

SRC += tkl_layers.c tkl_oled.c
SRC += tkl_brightness.c
