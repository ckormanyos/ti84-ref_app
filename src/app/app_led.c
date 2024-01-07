///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
//  Distributed under The Unlicense
//

#include <app/app_util.h>

static void app_led_on (void);
static void app_led_off(void);
static void app_led_clr(void);

void main(void)
{
  app_util_init();

  bool exit_flag = false;

  for(;;)
  {
    app_led_clr();
    app_led_on();

    for(volatile uint_fast16_t   i = (uint_fast16_t) UINT16_C(0x0);
                               ((i < (uint_fast16_t) UINT16_C(0x0F80)) && ((exit_flag = app_util_wants_exit()) == false));
                               ++i) { ; }

    if(exit_flag) { break; }

    app_led_clr();
    app_led_off();

    for(volatile uint_fast16_t   i = (uint_fast16_t) UINT16_C(0x0);
                               ((i < (uint_fast16_t) UINT16_C(0x0F80)) && ((exit_flag = app_util_wants_exit()) == false));
                               ++i) { ; }

    if(exit_flag) { break; }
  }

  // Exit the Application and return to the home screen
  // using the JForceCmdNoChar function. See also page 16
  // in "TI-83 Plus System Routines", Third Release,
  // (Jan. 25, 2002).

  __asm__("rst 0x28\n" ".dw #0x4027\n");
}

static void app_led_on(void)
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

static void app_led_off(void)
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

static void app_led_clr(void)
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
