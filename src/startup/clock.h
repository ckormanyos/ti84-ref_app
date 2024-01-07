///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
//  Distributed under The Unlicense
//

#ifndef CLOCK_2024_01_7_H
  #define CLOCK_2024_01_7_H

  #include <stdint.h>

  #include <startup/asm_util.h>

  uint8_t clock_seconds_get  (void) ATTRIBUTE_NAKED;
  void    clock_seconds_start(void) ATTRIBUTE_NAKED;
  void    clock_seconds_stop (void) ATTRIBUTE_NAKED;


#endif //CLOCK_2024_01_7_H
