ti84-ref_app
==================

<p align="center">
    <a href="https://github.com/ckormanyos/ti84-ref_app/actions">
        <img src="https://github.com/ckormanyos/ti84-ref_app/actions/workflows/ti84-ref_app.yml/badge.svg" alt="build"></a>
    <a href="https://github.com/ckormanyos/ti84-ref_app/issues?q=is%3Aissue+is%3Aopen+sort%3Aupdated-desc">
        <img src="https://custom-icon-badges.herokuapp.com/github/issues-raw/ckormanyos/ti84-ref_app?logo=github" alt="Issues" /></a>
    <a href="https://github.com/ckormanyos/ti84-ref_app/blob/main/UNLICENSE">
        <img src="https://img.shields.io/badge/license-The Unlicense-blue.svg" alt="The Unlicense"></a>
</p>

`ckormanyos/ti84-ref_app` creates a fully functioning reference application
for the z80-based TI84-Plus monochrome graphics calculator. It runs in the
open `Asm(prgm)` interface provided in the calculator's _CATALOG_ menu.
It uses the TI84's on-board Z80 processor.

The reference application implements a small _blinky_-show.

The text _ON_/_OFF_ is written on the calculator screen.
Text is used since there is no actual LED present on the calculator-target system.
This is intended to simulate an LED-blinky by _toggling_ between _ON_ and _OFF_.

The toggle frequency has been empirically tuned to about ${\sim}{\frac{1}{2}}Hz$
and the _ON_/_OFF_ text messages are printed at row $2$, column $7$.

A skinny `main()` subroutine controls the toggling.
It is written in high-level C (as opposed to assembly).
This application has a complete C-runtime initialization based on (and using) the
free [`sdcc`](https://sdcc.sourceforge.net) toolchain.

## Building

The build system is supported on both `Win*` and `*nix`. Ported `*nix` tools
support the `Win*`-build.

### Build on `Win*`

Prerequisites:
  - Install sdcc version 4.3 or higher.
  - Install python.

```cmd
cd ti84-ref_app\build
make TYP_OS=WIN all
```

The build results including HEX-File and `refapp.8xp` will be built in the `bin`-directory.

### Build on `*nix`

Prerequisites:
  - Install sdcc version 4.3 or higher.

```sh
cd ti84-ref_app/build
make TYP_OS=UNIX all
```

The build results including HEX-File and `refapp.8xp` will be built in the `bin`-directory.

## Testing and Continuous Integration

Testing has been performed on the target system, which is a fully-functioning
TI84-Plus calculator purchased years ago from a commercial retailer.

Continuous integration builds the application on an ubuntu-latest GHA runner
and verifies the presence of `bin/refapp-8xp`.

## Images

TBD: Provide images of the _blinking_ text.

## Aditional Information

Licensing TBD.

This project has been inspired by and influenced by numerous previous works,
including (but not limited to)
the [azertyfun/LibTI](https://github.com/azertyfun/LibTI) project.
