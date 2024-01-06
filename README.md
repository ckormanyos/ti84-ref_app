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

`ckormanyos/ti84-ref_app` creates a fully functioning reference application for the z80-based TI84-Plus monochrome graphics calculator.

The reference application implements a small _blinky_-application supported by a skinny `main()`
subroutine written in high-level C (as opposed to assembly). Since there is no LED present
on the calculator-target system, the text _ON_/_OFF_ is printed at row-$2$, column-$7$,
_toggling_ between _ON_ and _OFF_ at a frequency of about ${\sim}\frac{1}{2}Hz$.

This application has a complete C-runtime initialization based on and using the
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

```cmd
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
