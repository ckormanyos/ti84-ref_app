ti84-ref_app
==================

<p align="center">
    <a href="https://github.com/ckormanyos/ti84-ref_app/actions">
        <img src="https://github.com/ckormanyos/ti84-ref_app/actions/workflows/ti84-ref_app.yml/badge.svg" alt="build"></a>
    <a href="https://github.com/ckormanyos/ti84-ref_app/issues?q=is%3Aissue+is%3Aopen+sort%3Aupdated-desc">
        <img src="https://custom-icon-badges.herokuapp.com/github/issues-raw/ckormanyos/ti84-ref_app?logo=github" alt="Issues" /></a>
    <a href="https://github.com/ckormanyos/ti84-ref_app/blob/main/UNLICENSE">
        <img src="https://img.shields.io/badge/license-Unlicense-blue.svg" alt="Unlicense"></a>
</p>

`ckormanyos/ti84-ref_app` creates a fully functioning reference application
for the TI-84 Plus monochrome graphics calculator. It runs in the
open `Asm(prgm)` interface provided in the calculator's `CATALOG` menu.
It uses the TI-84's on-board [Z80 processor](https://en.wikipedia.org/wiki/Zilog_Z80).

The reference application implements parallel _blinky_ and _hello_-_world_ text sequences.
A minimalistic cooperative multitasking scheduler controls
the presentations of the associated ASCII-text messages.

The text sequences _ON_/_OFF_ and _hello_/_world_ are presented in
cyclic, alternating fashion(s) on the calculator screen.
Text is used since there is no actual LED present on the calculator-target system.
This is intended to simulate an LED-blinky by _toggling_ between _ON_ and _OFF_
and support an independent _hello_-_world_-task as well.
The _ON_/_OFF_ messages are printed every $1s$ and the _hello_/_world_ messages every $3s$.

The cooperative multitasking timebase is derived from a $1s$ tick.
The underlying 32-bit timer resides on ports `0x45`-`0x48`,
where the lower byte at port `0x45` is used.
This timer is only available on the TI-84, not the TI-83.

The blinky _ON_/_OFF_ and _hello_/_world_ text messages are printed
at rows $2$ and $3$, respectively, and both at column $6$.

A skinny `main()` subroutine in the soruce file
[`app_main.c`](./src/app/app_main.c) controls the program flow.
After starting the multitasking scheduler with
[`os_schedule()`](https://github.com/ckormanyos/ti84-ref_app/blob/8291393f971d234c3493e18589b60421d22f61cc/src/app/app_main.c#L27),
it services the two alternating tasks
[`app_led_task()`](https://github.com/ckormanyos/ti84-ref_app/blob/8291393f971d234c3493e18589b60421d22f61cc/src/app/app_led.c#L10)
and
[`app_hello_task()`](https://github.com/ckormanyos/ti84-ref_app/blob/8291393f971d234c3493e18589b60421d22f61cc/src/app/app_hello.c#L10)
based on their cycle times.

The application is written in C23.
There is minimal use of assembly for startup and to interface with
[TI-83 Plus System Routines](https://education.ti.com/html/eguides/discontinued/computer-software/EN/SDK-TI-83-System-Routines_EN.pdf).

## Running on the Calculator

Programming the calculator:
  - After build, locate `bin/refapp.8xp`.
  - Drag `refapp.8xp` onto the calculator using the standard method with [TI Connect version 4](https://education.ti.com/en/software/details/en/B59F6C83468C4574ABFEE93D2BC3F807/swticonnectsoftware). Important: Use version 4 for the TI-84 Plus.
  - The on-calculator name of the program is `REFAPP`.

To start the program, use the usual `Asm(prgm)` option found in the `CATALOG`
menu and select the `REFAPP` program. The explicit keystrokes are listed below.

Let's execute the program on the calculator using keystrokes:
  - Hit $2^{nd}$-CATALOG.
  - Use the arrows to navigate down to the `Asm(` entry.
  - Hit the `ENTER`-key.
  - Then hit the `PRGM`-key.
  - select `REFAPP`.
  - The calculator screen should now show `Asm(prgmREFAPP`.
  - Hit the `ENTER`-key and the program should start to run.
  - To exit the blinky _ON_/_OFF_ show, press the `ENTER`-key.
  - Clear the screen (if desired) with the `CLEAR`-key.

The running programm in the display-state _ON_/_hello_ is shown in the image below.

![](./images/ti84-ref_app.jpg)

## Pre-built Program

A fully-built `ref_app` can be found in the [`bin`](./bin) directory.
This pre-built program can be used to trouble-shoot the environment.

## Tools and Build

This application uses the free
[`sdcc`](https://sdcc.sourceforge.net) toolchain.
C-runtime initialization (i.e., static initialization prior to the call of `main()`)
is supported with the file [crt0.s](./src/startup/crt0.s) in the `startup` directory.

The build system:
  - The build system uses GNUmake with a straighforward [`Makefile`](./build/Makefile).
  - The build system is supported on both `Win*` and `*nix`.
  - The `Win*`-build requires a small selection of ported `*nix` tools. These are included in the [`wbin`](./build/tools/UnxUtils/usr/local/wbin) directory.
  - The on-calculator image is packed by [BinPac8x v1.2](https://www.cemetech.net/news/2010/6/389/_/binpac8x-v12).
  - Build results including HEX-File and the on-calculator image `refapp.8xp` are placed in the `bin`-directory.

### Build on `Win*`

Prerequisites:
  - Install [`sdcc`](https://sdcc.sourceforge.net) version 4.3 or higher.
  - Install python.

Then build in the command shell with:

```cmd
cd ti84-ref_app\build
make TYP_OS=WIN all
```

### Build on `*nix`

Prerequisites:
  - Install [`sdcc`](https://sdcc.sourceforge.net) version 4.3 or higher.

Then build in the bash shell with:

```sh
cd ti84-ref_app/build
make TYP_OS=UNIX all
```

## Testing and Continuous Integration

Testing has been performed on the target system, which is a fully-functioning
TI-84 Plus calculator purchased years ago from a commercial retailer.

Continuous integration is performed on GHA using an ubuntu-latest runner.
The [workflow run](./.github/workflows/ti84-ref_app.yml)
builds the application and verifies the presence of `bin/refapp.8xp`.

## Aditional Details

### Origins (and Reservations)

  - This project has been inspired by and influenced by numerous previous works, including (but not limited to) the [azertyfun/LibTI](https://github.com/azertyfun/LibTI) project.
  - The aforementioned [project](https://github.com/azertyfun/LibTI) was ground-breaking and excellent.

Please do, however, use at your own discretion and observe also
the [license](./LICENSE) details. This project is not in any way
affiliated with Texas Instruments Inc, or any of its subsidiaries,
including the educational products division.

Some of this software has been reverse engineered
from other projects or terse technical notes.
In addition, the software actively writes to calculator
_ports_, such as port `0x40` and port `0x41`.
Personally. I do not consider this to be a $100\\%$ sound basis
for project reliability and/or stability.

Nonetheless, empirical evidence shows a working,
and fully/properly initialized C-language, non-trivial application.
It provides a basis that seems to adhere to the established,
common rules of modern C. Larger projects could be built or modelled
from this.

### References

  - _TI_-_83_ _Plus_ _System_ _Routines_, Third Release (Jan. 25, 2002), located [here](https://education.ti.com/html/eguides/discontinued/computer-software/EN/SDK-TI-83-System-Routines_EN.pdf)
  - _SDCC_ _Compiler_ _User_ _Guide_, SDCC 4.4.1, Revision 14549 (at the time of writing this doc, Jan. 29, 2024), located [here](https://sdcc.sourceforge.net/doc/sdccman.pdf)

### Licensing

  - The source code written for this repo (in the [`src`](./src)) directory is licensed under [_The_ _Unlicense_](./LICENSE).
  - `Win*`-ported `*nix` tools in [`wbin`](./build/tools/UnxUtils/usr/local/wbin) originate from [UnxTools](https://sourceforge.net/projects/unxutils) and include their own [distribution statements](./build/tools/UnxUtils).
  - The `Win*`-ported `objcopy.exe` originates from Steven T. Lavavej's [`MinGW Distro`](https://nuwen.net/mingw.html).
  - The `Win*`-ported GNUmake is taken from [`ckormanyos/make-4.2.1-msvc-build`](https://github.com/ckormanyos/make-4.2.1-msvc-build).
