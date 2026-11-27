// Which half is on USB, asked again until it is known.
// vial-qmk decides once, 2 s after power-on: a half the computer has not set up by then (a hub that was asleep, a
// computer still starting, a plug that bounces) takes itself for the other half for good and switches its USB off.
// Both screens then show the right half's design and no key works until the cable is plugged in again.
// Here that decision is provisional. A half that found no computer listens for the half on USB (vial-qmk's split
// watchdog, SPLIT_WATCHDOG_ENABLE in tkl_config.h); when none speaks within 2.1 s it restarts and looks for the
// computer again, for 4 s this time, and so on until one of the two is found. Its screen stays dark meanwhile.
#include "tkl_split.h"

#define TKL_USB_FIRST_MS 2000 // vial-qmk's SPLIT_USB_TIMEOUT: the right half joins 2 s after a normal plug-in, as before
#define TKL_USB_RETRY_MS 4000
#define TKL_USB_POLL_MS 10

uint16_t tkl_usb_wait_ms(uint32_t word) {
    return word == TKL_SPLIT_RETRY ? TKL_USB_RETRY_MS : TKL_USB_FIRST_MS;
}

#ifdef SPLIT_WATCHDOG_ENABLE
#    include "quantum.h"
#    include "split_util.h"
#    include "usb_util.h"

// A RAM section that no boot initialises: the word survives the watchdog's restart, not a power cut.
static volatile uint32_t __attribute__((section(".ram0.tkl_split_retry"))) retry_word;

// Replaces vial-qmk's (weak, quantum/split_common/split_util.c). MASTER_LEFT: the half on USB is the left one.
bool is_keyboard_master_impl(void);
bool is_keyboard_master_impl(void) {
    uint16_t wait = tkl_usb_wait_ms(retry_word);
    for (uint16_t waited = 0; waited < wait; waited += TKL_USB_POLL_MS) {
        if (usb_connected_state()) {
            retry_word = 0;
            return true;
        }
        wait_ms(TKL_USB_POLL_MS);
    }
    retry_word = TKL_SPLIT_RETRY;
    // As vial-qmk: a half with its USB left on and no computer would stop working (USB suspend).
    usb_disconnect();
    return false;
}

bool tkl_split_settled(void) {
    return is_keyboard_master() || split_watchdog_check();
}

void tkl_split_task(void) {
    // Heard the half on USB: this is the other half, a later restart looks for the computer for 2 s again.
    if (retry_word == TKL_SPLIT_RETRY && tkl_split_settled()) {
        retry_word = 0;
    }
}
#endif
