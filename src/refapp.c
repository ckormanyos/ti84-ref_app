///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
//  Distributed under The Unlicense
//

#include <stdint.h>

// _ClrLCDFull       #0x4540
// _HomeUp           #0x4558
// _JForceCmdNoChar  #0x4027
// skClear           #0xF
// skEnter           #0x9

// curRow            #0x844B
// curCol            #0x844C
// _PutC             #0x4504


#if defined(_MSC_VER)
#define __asm__(x)
#endif


static void init(void);

static void led_on (void);
static void led_off(void);
static void led_clr(void);

static uint8_t wants_exit(void);

void main(void)
{
  init();

  volatile uint8_t exit_flag = (uint8_t) UINT8_C(0);

  for(;;)
  {
    led_clr();
    led_on();

    for(volatile uint_fast16_t   i = (uint_fast16_t) UINT16_C(0x0);
                               ((i < (uint_fast16_t) UINT16_C(0x0F80)) && ((exit_flag = wants_exit()) == (uint8_t) UINT8_C(0)));
                               ++i) { ; }

    if(exit_flag != (uint8_t) UINT8_C(0)) { break; }

    led_clr();
    led_off();

    for(volatile uint_fast16_t   i = (uint_fast16_t) UINT16_C(0x0);
                               ((i < (uint_fast16_t) UINT16_C(0x0F80)) && ((exit_flag = wants_exit()) == (uint8_t) UINT8_C(0)));
                               ++i) { ; }

    if(exit_flag != (uint8_t) UINT8_C(0)) { break; }
  }

  __asm__("rst 0x28\n" ".dw #0x4027\n");
}

void init(void)
{
  __asm__("rst 0x28\n" ".dw #0x4540\n");
  __asm__("rst 0x28\n" ".dw #0x4558\n");
}

void led_on(void)
{
  __asm__("ld b,#0x02\n");
  __asm__("ld a,b\n");
  __asm__("ld (#0x844B), a\n");
  __asm__("ld b,#0x07\n");
  __asm__("ld a,b\n");
  __asm__("ld (#0x844C), a\n");

  __asm__("ld a,#0x4F\n");
  __asm__("rst 0x28\n" ".dw #0x4504\n");
  __asm__("ld a,#0x4E\n");
  __asm__("rst 0x28\n" ".dw #0x4504\n");
}

void led_off(void)
{
  __asm__("ld b,#0x02\n");
  __asm__("ld a,b\n");
  __asm__("ld (#0x844B), a\n");
  __asm__("ld b,#0x07\n");
  __asm__("ld a,b\n");
  __asm__("ld (#0x844C), a\n");

  __asm__("ld a,#0x4F\n");
  __asm__("rst 0x28\n" ".dw #0x4504\n");
  __asm__("ld a,#0x46\n");
  __asm__("rst 0x28\n" ".dw #0x4504\n");
  __asm__("ld a,#0x46\n");
  __asm__("rst 0x28\n" ".dw #0x4504\n");
}

void led_clr(void)
{
  __asm__("ld b,#0x02\n");
  __asm__("ld a,b\n");
  __asm__("ld (#0x844B), a\n");
  __asm__("ld b,#0x07\n");
  __asm__("ld a,b\n");
  __asm__("ld (#0x844C), a\n");

  __asm__("ld a,#0x20\n");
  __asm__("rst 0x28\n" ".dw #0x4504\n");
  __asm__("ld a,#0x20\n");
  __asm__("rst 0x28\n" ".dw #0x4504\n");
  __asm__("ld a,#0x20\n");
  __asm__("rst 0x28\n" ".dw #0x4504\n");
}

uint8_t wants_exit(void)
{
  volatile uint8_t exit_flag = (uint8_t) UINT8_C(0);

  __asm__
  (
    "rst 0x28\n" ".dw #0x4018\n"
    "cp #0x9\n"
    "jp nz,no_exit\n"
  );

  exit_flag = (uint8_t) UINT8_C(1);

  __asm__
  (
    "no_exit:\n"
  );

  return exit_flag;
}
