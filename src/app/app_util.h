///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
//  Distributed under The Unlicense
//

#ifndef APP_UTIL_2024_01_7_H
  #define APP_UTIL_2024_01_7_H

  #include <stdbool.h>
  #include <stdint.h>

  #include <startup/asm_util.h>

  // See also: https://wikiti.brandonw.net/index.php?title=Category:83Plus:Ports:By_Address
  // and also: https://education.ti.com/html/eguides/discontinued/computer-software/EN/SDK-TI-83-System-Routines_EN.pdf

  // _ClrLCDFull       #0x4540
  // _HomeUp           #0x4558
  // _JForceCmdNoChar  #0x4027
  // skClear           #0xF
  // skEnter           #0x9

  // curRow            #0x844B
  // curCol            #0x844C
  // _PutC             #0x4504

  void app_util_init      (void);
  bool app_util_wants_exit(void);

#endif // APP_UTIL_2024_01_7_H
