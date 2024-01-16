///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
//  Distributed under The Unlicense
//

#include <app/app_lcd_util.h>
#include <mcal/mcal_gpt.h>
#include <os/os.h>
#include <startup/asm_util.h>

void main(void)
{
  // The main() subroutine initializes the needed hardware
  // and controls the multitasking scheduler, which subsequently
  // controls the blinky and hello-world tasks.

  // Initialize the microcontroller abstraction layer peripheral
  // general purpose timer.
  mcal_gpt_init();

  // Initialize the LCD application utilities.
  app_lcd_util_init();

  // Engage the multitasking scheduler. This controls both
  // the blinky as well as the hello-world tasks.
  // Do not return until the "ENTER" key is pressed.
  os_schedule();

  // De-initialize the general purpose timer.
  mcal_gpt_de_init();

  // Exit the Application and return to the home screen
  // using the JForceCmdNoChar function. See also page 16
  // in "TI-83 Plus System Routines", Third Release,
  // (Jan. 25, 2002).

  __asm__("rst 0x28\n" ".dw #0x4027\n");
}
