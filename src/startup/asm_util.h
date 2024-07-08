///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
//  Distributed under The Unlicense
//

#ifndef ASM_UTIL_2024_01_07_H
  #define ASM_UTIL_2024_01_07_H

  #if defined(_MSC_VER)

  #define ASM(x)
  #define ATTRIBUTE_NAKED
  #define RETURN_FROM_NAKED(ret_val) return (ret_val)

  #else

  #define ATTRIBUTE_NAKED __naked
  #define ASM(x) __asm__(x)
  #define RETURN_FROM_NAKED(ret_val)

  #endif

#endif // ASM_UTIL_2024_01_07_H
