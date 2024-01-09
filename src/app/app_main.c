///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
//  Distributed under The Unlicense
//

#include <mcal/mcal_gpt.h>
#include <os/os.h>
#include <startup/asm_util.h>

void main(void)
{
  mcal_gpt_init();

  os_init();

  os_schedule();

  mcal_gpt_de_init();

  // Exit the Application and return to the home screen
  // using the JForceCmdNoChar function. See also page 16
  // in "TI-83 Plus System Routines", Third Release,
  // (Jan. 25, 2002).

  __asm__("rst 0x28\n" ".dw #0x4027\n");
}
