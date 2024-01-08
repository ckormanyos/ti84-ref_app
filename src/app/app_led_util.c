///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
//  Distributed under The Unlicense
//

#include <app/app_led_util.h>
#include <startup/clock.h>

void app_led_util_putc(char c) ATTRIBUTE_NAKED
{
  (void) c;

  __asm__("rst 0x28\n" ".dw #0x4504\n");
  __asm__("ret\n");
}

void app_led_util_home(void) ATTRIBUTE_NAKED
{
  __asm__("ld b,#0x02\n");
  __asm__("ld a,b\n");
  __asm__("ld (#0x844B), a\n");
  __asm__("ld b,#0x07\n");
  __asm__("ld a,b\n");
  __asm__("ld (#0x844C), a\n");
  __asm__("ret\n");
}

void app_led_util_init(void) ATTRIBUTE_NAKED
{
  __asm__("rst 0x28\n" ".dw #0x4540\n");
  __asm__("rst 0x28\n" ".dw #0x4558\n");
  __asm__("ret\n");
}

bool app_led_util_wants_exit(void) ATTRIBUTE_NAKED
{
  __asm__("rst 0x28\n" ".dw #0x4018\n");
  __asm__("ld h, #0x0\n");
  __asm__("cp #0x9\n");
  __asm__("jp nz, no_exit\n");
  __asm__("ld h, #0x1\n");
  __asm__("no_exit:\n");
  __asm__("ret\n");

  #if defined(_MSC_VER)
  return false;
  #endif
}
