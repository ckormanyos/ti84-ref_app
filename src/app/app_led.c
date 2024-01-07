///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
//  Distributed under The Unlicense
//

#include <app/app_util.h>
#include <startup/clock.h>

static void app_led_on (void);
static void app_led_off(void);
static void app_led_clr(void);

void main(void)
{
  app_util_init();

  bool exit_flag = false;

  uint8_t current_tick = clock_seconds_get();

  for(;;)
  {
    app_led_clr();
    app_led_on();

    uint8_t next_tick;

    while
    (
         ((next_tick = clock_seconds_get()) == current_tick)
      && ((exit_flag = app_util_wants_exit()) == false)
    ) { ; }

    if(exit_flag) { break; }

    current_tick = next_tick;

    app_led_clr();
    app_led_off();

    while
    (
         ((next_tick = clock_seconds_get()) == current_tick)
      && ((exit_flag = app_util_wants_exit()) == false)
    ) { ; }

    if(exit_flag) { break; }

    current_tick = next_tick;
  }

  clock_seconds_stop();

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
