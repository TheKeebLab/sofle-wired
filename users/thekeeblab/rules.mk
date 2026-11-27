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
SRC += tkl_brightness.c tkl_split.c

# Double-tap reset: tkl_boot.c counts only the reset button. vial-qmk's own one is renamed out of the way (a build
# where this line stops applying fails to link: two __late_init).
SRC += tkl_boot.c
$(INTERMEDIATE_OUTPUT)/platforms/chibios/bootloaders/rp2040.o: FILE_SPECIFIC_CFLAGS += -D__late_init=vial_qmk_late_init_unused
