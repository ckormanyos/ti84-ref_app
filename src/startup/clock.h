///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
//  Distributed under The Unlicense
//

#ifndef CLOCK_2024_01_7_H
  #define CLOCK_2024_01_7_H

  #include <stdint.h>

  #include <startup/asm_util.h>

  void    clock_seconds_start(void);
  void    clock_seconds_stop (void);
  uint8_t clock_seconds_get  (void);


#endif //CLOCK_2024_01_7_H
