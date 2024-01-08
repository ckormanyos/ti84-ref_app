///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
//  Distributed under The Unlicense
//

#include <stdbool.h>

#include <startup/clock.h>

static bool clock_seconds_run_bit_initial_state;

static uint8_t clock_seconds_get_port40 (void) ATTRIBUTE_NAKED;
static void    clock_seconds_do_start   (void) ATTRIBUTE_NAKED;
static void    clock_seconds_do_stop    (void) ATTRIBUTE_NAKED;
static uint8_t clock_seconds_do_get     (void) ATTRIBUTE_NAKED;

void _clock(void) ATTRIBUTE_NAKED
{
  // Mysterious _clock() method.

  __asm__("ld a, #0x2\n");
  __asm__("ret\n");
}

void clock_seconds_start(void)
{
  const uint8_t clock_seconds_run_bit_value = (uint8_t) (clock_seconds_get_port40() & (uint8_t) UINT8_C(1));

  clock_seconds_run_bit_initial_state = ((clock_seconds_run_bit_value != (uint8_t) UINT8_C(0)) ? true : false);

  clock_seconds_do_start();
}

void clock_seconds_stop(void)
{
  if(!clock_seconds_run_bit_initial_state)
  {
    clock_seconds_do_stop();
  }
}

uint8_t clock_seconds_get(void)
{
  return clock_seconds_do_get();
}

static uint8_t clock_seconds_get_port40(void) ATTRIBUTE_NAKED
{
  __asm__("in a, (0x40)\n");
  __asm__("ld h, a\n");
  __asm__("ret\n");

  #if defined(_MSC_VER)
  return (uint8_t) UINT8_C(0);
  #endif
}

static void clock_seconds_do_start(void) ATTRIBUTE_NAKED
{
  // Reset the lower byte of the 32-bit clock.
  __asm__("xor a\n");
  __asm__("out (0x44), a\n");

  // Ensure that the set command bit is off since its trtansition
  // to high will actually set the clock.
  __asm__("ld a, #0x1\n");
  __asm__("out (0x40), a\n");

  // Set and start the clock.
  __asm__("ld a, #0x3\n");
  __asm__("out (0x40), a\n");
  __asm__("ret\n");
}

static void clock_seconds_do_stop(void) ATTRIBUTE_NAKED
{
  // Stop the clock.
  __asm__("ld a, #0x0\n");
  __asm__("out (0x40), a\n");
  __asm__("ret\n");
}

static uint8_t clock_seconds_do_get(void) ATTRIBUTE_NAKED
{
  // Return the lower 8-bits of a 1hz counter function.

  // Port (45h) is the least significant byte in a 32-bit value that
  // represents the number of seconds after midnight, January 1st, 1997.

  // See also https://wikiti.brandonw.net/index.php?title=83Plus:Ports:45

  __asm__("in a, (0x45)\n");
  __asm__("ld h, a\n");
  __asm__("ret\n");

  #if defined(_MSC_VER)
  return (uint8_t) UINT8_C(0);
  #endif
}
