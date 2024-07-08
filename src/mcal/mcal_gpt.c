///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
//  Distributed under The Unlicense
//

#include <mcal/mcal_gpt.h>
#include <startup/asm_util.h>

// The clock is a 32-bit value that represents the number of seconds
// after midnight, January 1st, 1970.

// The clock shadow is located at ports:41-44, where 41 is the least significant byte.
// The actual clock is located at ports:45-48, where 45 is the least significant byte.

// See also: https://wikiti.brandonw.net/index.php?title=83Plus:Ports:40
// See also: https://wikiti.brandonw.net/index.php?title=83Plus:Ports:41
// See also: https://wikiti.brandonw.net/index.php?title=83Plus:Ports:45

static bool clock_seconds_run_bit_initial_state;

static uint8_t clock_seconds_read_port40(void) ATTRIBUTE_NAKED;
static void    clock_seconds_start      (void) ATTRIBUTE_NAKED;
static void    clock_seconds_stop       (void) ATTRIBUTE_NAKED;
static uint8_t clock_seconds_value      (void) ATTRIBUTE_NAKED;

void mcal_gpt_init(void)
{
  const uint8_t clock_seconds_run_bit_value = (uint8_t) (clock_seconds_read_port40() & (uint8_t) UINT8_C(1));

  clock_seconds_run_bit_initial_state = ((clock_seconds_run_bit_value != (uint8_t) UINT8_C(0)) ? true : false);

  clock_seconds_start();
}

void mcal_gpt_de_init(void)
{
  if(!clock_seconds_run_bit_initial_state)
  {
    clock_seconds_stop();
  }
}

uint8_t mcal_gpt_get_time_elapsed(void)
{
  return clock_seconds_value();
}

static uint8_t clock_seconds_read_port40(void) ATTRIBUTE_NAKED
{
  ASM("in a, (0x40)\n");
  ASM("ld h, a\n");
  ASM("ret\n");

  RETURN_FROM_NAKED((uint8_t) UINT8_C(0));
}

static void clock_seconds_start(void) ATTRIBUTE_NAKED
{
  ASM("in a, (0x48)\n");  // Read  byte3 of the actual clock.
  ASM("out (0x44), a\n"); // Set   byte3 of the clock shadow (using the value read above).
  ASM("in a, (0x47)\n");  // Read  byte2 of the actual clock.
  ASM("out (0x43), a\n"); // Set   byte2 of the clock shadow (using the value read above).
  ASM("in a, (0x46)\n");  // Read  byte1 of the actual clock.
  ASM("out (0x42), a\n"); // Set   byte1 of the clock shadow (using the value read above).
  ASM("xor a\n");         // Clear register a.
  ASM("out (0x41), a\n"); // Clear byte0 of the clock shadow.

  // Ensure that the set command bit is off since its transition
  // to high will actually set the clock. The setting uses the values
  // from the clock shadow at ports:45-48.

  ASM("in a, (0x40)\n");
  ASM("and a, #0xFC\n");
  ASM("or a, #0x1\n");
  ASM("out (0x40), a\n");

  // Set and start the clock.

  ASM("or a, #0x3\n");
  ASM("out (0x40), a\n");
  ASM("ret\n");
}

static void clock_seconds_stop(void) ATTRIBUTE_NAKED
{
  // Stop the clock.

  ASM("in a, (0x40)\n");
  ASM("and a, #0xFE\n");
  ASM("out (0x40), a\n");
  ASM("ret\n");
}

static uint8_t clock_seconds_value(void) ATTRIBUTE_NAKED
{
  // Return the lower 8-bits of the clock, where port:45 is
  // the least significant byte of the clock.

  ASM("in a, (0x45)\n");
  ASM("ld h, a\n");
  ASM("ret\n");

  RETURN_FROM_NAKED((uint8_t) UINT8_C(0));
}
