///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
//  Distributed under The Unlicense
//

#ifndef APP_UTIL_2024_01_7_H
  #define APP_UTIL_2024_01_7_H

  #include <stdint.h>

  #if defined(_MSC_VER)
  #define __asm__(x)
  #endif

  // _ClrLCDFull       #0x4540
  // _HomeUp           #0x4558
  // _JForceCmdNoChar  #0x4027
  // skClear           #0xF
  // skEnter           #0x9

  // curRow            #0x844B
  // curCol            #0x844C
  // _PutC             #0x4504

  void    app_util_init      (void);
  uint8_t app_util_wants_exit(void);

#endif // APP_UTIL_2024_01_7_H
