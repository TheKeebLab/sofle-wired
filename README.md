# TheKeebLab Sofle, wired

Firmware for the wired Sofle hand-built by [TheKeebLab](https://www.thekeeblab.com): Vial (QMK) on an RP2040 Pro Micro.

> Generated from TheKeebLab's private source. Edit in your fork; pull requests are read but not merged.

## Download

Ready-to-flash files are in the [latest release](https://github.com/TheKeebLab/sofle-wired/releases/latest): one file per
layout.

| Layout | Keymap | File |
|---|---|---|
| QWERTY (US) | `keyboards/sofle_choc/keymaps/qwerty_us/` | `sofle-wired-qwerty-us.uf2` |
| AZERTY (French) | `keyboards/sofle_choc/keymaps/azerty_fr/` | `sofle-wired-azerty-fr.uf2` |
| QWERTZ (German) | `keyboards/sofle_choc/keymaps/qwertz_de/` | `sofle-wired-qwertz-de.uf2` |
| QWERTY (Italian) | `keyboards/sofle_choc/keymaps/qwerty_it/` | `sofle-wired-qwerty-it.uf2` |
| QWERTY (Spanish) | `keyboards/sofle_choc/keymaps/qwerty_es/` | `sofle-wired-qwerty-es.uf2` |

Flash the same file on both halves: they only work together on the same firmware. Plug a half in over USB and
press its reset button twice quickly: it shows up as a USB drive named RPI-RP2. Copy the file onto it; the half
restarts on its own. The USB cable goes into the left half.

Flashing a different file resets the keymap Vial keeps on the keyboard to the layout of that file. If you changed keys in
Vial, save your layout to a file in Vial first and load it back after.

Set your computer's keyboard language to the layout you flash. The base layer's keys stay where they are; the
other layers type the same characters as the US keymap, and a few extra keys are listed at the top of each
`keymap.c`.

## Change the keymap

- Without rebuilding: [Vial](https://get.vial.today) changes any key while the keyboard is plugged in.
- In the source: fork this repository, edit the `keymap.c` of your layout and push. GitHub Actions builds every
  layout (Actions tab, the run, Artifacts, `Firmware`).
  GitHub turns workflows off in a fork: enable them once in your fork's Actions tab.
- `users/thekeeblab/tkl_brightness.c` already defines `keyboard_post_init_user`, `process_record_user` and
  `housekeeping_task_user`: add your code in those functions, a second definition in `keymap.c` fails to build.

This is a QMK userspace built against [vial-qmk](https://github.com/vial-kb/vial-qmk), at the commit
`.github/workflows/build.yml` pins.

## What is in here

| Path | What |
|---|---|
| `keyboards/sofle_choc/keymaps/<layout>/` | One keymap per layout: `keymap.c`, `config.h`, `rules.mk`, `vial.json` |
| `users/thekeeblab/` | Shared by every layout: layer switching, the screen brightness key, the screens |
| `qmk.json` | What GitHub Actions builds |

The release files show TheKeebLab's screens. Firmware built from this source shows the layer number and caps lock
on the left half and the logo on the right instead: TheKeebLab's screens aren't part of this repository.

## Licence

GPL-2.0-or-later, like QMK: see `LICENSE`.
