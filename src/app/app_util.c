///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
//  Distributed under The Unlicense
//

#include <app/app_util.h>
#include <startup/clock.h>

static bool app_util_check_crt0(void);

extern uint8_t app_dummy_test_non_initialized;
extern uint8_t app_dummy_test_initialized;

void app_util_init(void)
{
  while(!app_util_check_crt0())
  {
    ;
  }

  __asm__("rst 0x28\n" ".dw #0x4540\n");
  __asm__("rst 0x28\n" ".dw #0x4558\n");

  clock_seconds_start();
}

bool app_util_wants_exit(void)
{
  volatile bool exit_flag = false;

  __asm__
  (
    "rst 0x28\n" ".dw #0x4018\n"
    "cp #0x9\n"
    "jp nz, no_exit\n"
  );

  exit_flag = true;

  __asm__
  (
    "no_exit:\n"
  );

  return exit_flag;
}

static bool app_util_check_crt0(void)
{
  // Check static initialization.

  const bool result_crt0_non_init_is_ok = ((app_dummy_test_non_initialized == (uint8_t) UINT8_C(0))  ? true : false);
  const bool result_crt0_init_is_ok     = ((app_dummy_test_initialized     == (uint8_t) UINT8_C(42)) ? true : false);

  const bool result_check_crt0_is_ok = ((result_crt0_non_init_is_ok && result_crt0_init_is_ok) ? true : false);

  return result_check_crt0_is_ok;
}
