///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
//  Distributed under The Unlicense
//

#ifndef OS_2024_01_09_H
  #define OS_2024_01_09_H

  #include <stdint.h>

  typedef void(*os_function_type)(void);

  typedef struct os_task_control_block
  {
    os_function_type p_init;
    os_function_type p_func;
    uint8_t          cycle;
    uint8_t          timer;
  }
  os_task_control_block;

  void os_init    (void);
  void os_schedule(void);

#endif // OS_2024_01_09_H
