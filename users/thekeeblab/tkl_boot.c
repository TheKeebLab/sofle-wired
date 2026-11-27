// Double-tap reset to the bootloader (the RPI-RP2 drive), counting only the reset button.
// vial-qmk's own double-tap (platforms/chibios/bootloaders/rp2040.c, renamed out of the way in common.mk) counts any
// second boot within its window: a USB plug-in that bounces boots twice and lands in the bootloader. Here only resets
// from the RP2040's RUN pin, where the reset button is wired, count; a power-on never does. Same window, same RAM word.
#include <stdbool.h>
#include <stdint.h>

#define TKL_CHIP_RESET_HAD_RUN 0x00010000u // VREG_AND_CHIP_RESET CHIP_RESET: last reset from the RUN pin
#define TKL_BOOT_MAGIC 0xCAFEB0BAu
#define TKL_BOOT_SOFT 0x544B4C53u // left in RAM by mcu_reset(): the firmware restarted itself

typedef enum { TKL_BOOT_START, TKL_BOOT_WAIT, TKL_BOOT_BOOTLOADER } tkl_boot_t;

// What a boot does, from the cause of the last chip reset and the word the previous boot left in RAM.
tkl_boot_t tkl_boot_action(uint32_t chip_reset, uint32_t magic) {
    if (!(chip_reset & TKL_CHIP_RESET_HAD_RUN)) {
        return TKL_BOOT_START;
    }
    return magic == TKL_BOOT_MAGIC ? TKL_BOOT_BOOTLOADER : TKL_BOOT_WAIT;
}

// The reset cause that counts. CHIP_RESET keeps saying "reset button" through every restart the firmware asks for
// (tkl_split.c restarts a half every 6 s while it finds no computer): those are no press of the button.
uint32_t tkl_boot_cause(uint32_t chip_reset, uint32_t soft) {
    return soft == TKL_BOOT_SOFT ? 0 : chip_reset;
}

#ifdef RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#    include "quantum.h"
#    include "hal.h"
#    include "wait.h"
#    include "pico/bootrom.h"
#    include "hardware/structs/vreg_and_chip_reset.h"

_Static_assert(TKL_CHIP_RESET_HAD_RUN == VREG_AND_CHIP_RESET_CHIP_RESET_HAD_RUN_BITS, "HAD_RUN bit");

// The same defaults as vial-qmk's.
#    if !defined(RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT)
#        define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U
#    endif
#    if !defined(RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED)
#        define TKL_BOOT_LED_MASK 0U
#    else
#        define TKL_BOOT_LED_MASK (1U << RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED)
#    endif

// A RAM section that no boot initialises: the word survives a reset.
static volatile uint32_t __attribute__((section(".ram0.bootloader_magic"))) magic_location;
static volatile uint32_t __attribute__((section(".ram0.tkl_boot_soft"))) soft_location;
static bool restarted_itself;

// Replaces vial-qmk's (weak, platforms/chibios/bootloaders/rp2040.c): the split watchdog, QK_REBOOT and Vial go through it.
void mcu_reset(void) {
    soft_location = TKL_BOOT_SOFT;
    NVIC_SystemReset();
}

#    ifdef BOOTMAGIC_ENABLE
// Replaces vial-qmk's (weak, quantum/bootmagic/bootmagic.c), same key: held at power-on or at a press of the reset
// button it clears the Vial settings and opens the flashing drive. Not when the firmware restarted itself: a half
// that finds no computer does so every 6 s, with someone typing on it.
bool bootmagic_should_reset(void) {
    if (restarted_itself) {
        return false;
    }
    uint8_t row = BOOTMAGIC_ROW;
    uint8_t col = BOOTMAGIC_COLUMN;
#        if defined(SPLIT_KEYBOARD) && defined(BOOTMAGIC_ROW_RIGHT) && defined(BOOTMAGIC_COLUMN_RIGHT)
    if (!is_keyboard_left()) {
        row = BOOTMAGIC_ROW_RIGHT;
        col = BOOTMAGIC_COLUMN_RIGHT;
    }
#        endif
    return matrix_get_row(row) & (1 << col);
}
#    endif

// Runs just before main(), as vial-qmk's.
void __late_init(void) {
    // The bootloader jump and the busy wait need the clocks running.
    clocks_init();
    // .bss is already cleared here: the flag stays for bootmagic_should_reset().
    restarted_itself = soft_location == TKL_BOOT_SOFT;
    uint32_t cause = tkl_boot_cause(vreg_and_chip_reset_hw->chip_reset, soft_location);
    soft_location = 0;
    switch (tkl_boot_action(cause, magic_location)) {
        case TKL_BOOT_BOOTLOADER:
            magic_location = 0;
            reset_usb_boot(TKL_BOOT_LED_MASK, 0U);
            break;
        case TKL_BOOT_WAIT:
            magic_location = TKL_BOOT_MAGIC;
            wait_us(RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT * 1000U);
            magic_location = 0;
            break;
        default:
            magic_location = 0;
            break;
    }
}
#endif
