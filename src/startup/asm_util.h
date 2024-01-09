///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
//  Distributed under The Unlicense
//

#ifndef ASM_UTIL_2024_01_07_H
  #define ASM_UTIL_2024_01_07_H

  #if defined(_MSC_VER)
  #define __asm__(x)
  #endif

  #if defined(_MSC_VER)
  #define ATTRIBUTE_NAKED
  #else
  #define ATTRIBUTE_NAKED __naked
  #endif

#endif // ASM_UTIL_2024_01_07_H
