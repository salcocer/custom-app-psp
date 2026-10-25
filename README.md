
A new column next to Game, Network, etc.: possible in theory, but very hard, and I couldn't find any existing tool that does it.
- The columns are built into the XMB's own system files, so adding one means reverse-engineering those internals. A mistake could crash the XMB at startup.
- Realistic alternative 1: write our own XMB plugin, like ARK's XMB Control, that adds as many items as we want, with our own names, to existing columns.
- Realistic alternative 2: rename and re-icon an existing column with a custom theme. Old tools like CXMB did this with themes (CXMB (https://intimail.servindi.org/cxmb-psp-gamebrew.html), VSHmain Editor (https://gamergen.com/actualites/vshmain-editor-v2-0-utilitaire-customisation-vsh-28295-1/amp)). I haven't checked whether your ARK supports those themes.



# custom-app-psp

A Hello World homebrew for the Sony PSP that opens straight from the XMB,
through the **Custom App** item of [ARK-4](https://github.com/PSP-Archive/ARK-4)
custom firmware. It prints "Hello World" in the middle of the screen; START
goes back to the XMB.

Tested on a PSP-3000 running ARK-4.

## How the Custom App item works

ARK-4's XMB plugin (`xmbctrl`) checks for `PSP/APP/CUSTOM/EBOOT.PBP` on the
Memory Stick when the XMB starts. If the file is there, it adds a
**Custom App** item to the **Game** column, and selecting it launches that
EBOOT like any homebrew. Any homebrew can sit in the slot; this repository is
a starting point for your own.

## Building

Install the [pspdev toolchain](https://github.com/pspdev/pspdev/releases),
put its `bin` folder on your `PATH`, then run:

```sh
make
```

This writes `EBOOT.PBP`.

## Installing

1. Copy `EBOOT.PBP` to `PSP/APP/CUSTOM/EBOOT.PBP` on the Memory Stick.
2. Restart the XMB: press SELECT on the XMB and choose **Reset VSH**, or turn
   the PSP fully off and on (and run your ARK loader if ARK isn't permanent).
3. Open **Game → Custom App**.

On macOS, copy with `cp -X` (or run `dot_clean` on the Memory Stick
afterwards) so Finder's hidden `._` files don't end up on the PSP.
