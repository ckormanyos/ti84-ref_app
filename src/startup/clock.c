///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
//  Distributed under The Unlicense
//

#include <startup/clock.h>

void _clock(void) ATTRIBUTE_NAKED
{
  // Mysterious _clock() method.

  __asm__("ld a, #0x2\n");
  __asm__("ret\n");
}

void clock_seconds_start(void) ATTRIBUTE_NAKED
{
  // This will set the clock back to its start time.
  __asm__("xor a\n");
  __asm__("out (0x41), a\n");
  __asm__("out (0x42), a\n");
  __asm__("out (0x43), a\n");
  __asm__("out (0x44), a\n");

  // Ensure that the set command bit is off since its trtansition
  // to high will actually set the clock.
  __asm__("ld  a, #0x1\n");
  __asm__("out (0x40), a\n");

  // Set and start the clock.
  __asm__("ld  a, #0x3\n");
  __asm__("out (0x40), a\n");
  __asm__("ret\n");
}

void clock_seconds_stop(void) ATTRIBUTE_NAKED
{
  // Stop the clock.
  __asm__("ld  a, #0x0\n");
  __asm__("out (0x40), a\n");
  __asm__("ret\n");
}

uint8_t clock_seconds_get(void) ATTRIBUTE_NAKED
{
  // Return the lower 8-bits of a 1hz counter function.

  // Port (45h) is the least significant byte in a 32-bit value that
  // represents the number of seconds after midnight, January 1st, 1997.

  // See also https://wikiti.brandonw.net/index.php?title=83Plus:Ports:45

  __asm__("in a, (0x45)\n");
  __asm__("ld h, a\n");
  __asm__("ret\n");
}
