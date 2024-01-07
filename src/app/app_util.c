///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
//  Distributed under The Unlicense
//

#include <app/app_util.h>

void app_util_init(void)
{
  __asm__("rst 0x28\n" ".dw #0x4540\n");
  __asm__("rst 0x28\n" ".dw #0x4558\n");
}

uint8_t app_util_wants_exit(void)
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
