#pragma once

#include <stdbool.h>
#include <stdint.h>

// Left in RAM by a boot that found no computer, until the half on USB is heard (tkl_split.c).
#define TKL_SPLIT_RETRY 0x544B4C52u

// How long this boot looks for the computer, from the word the previous boot left in RAM.
uint16_t tkl_usb_wait_ms(uint32_t word);

// False while this half has found neither the computer nor the half on USB: it does not know yet which half it is.
bool tkl_split_settled(void);

// Called on every pass of the main loop (tkl_brightness.c owns housekeeping_task_user).
void tkl_split_task(void);
