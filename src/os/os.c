///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
//  Distributed under The Unlicense
//

#include <mcal/mcal_gpt.h>
#include <os/os.h>
#include <startup/asm_util.h>

#include <stddef.h>
#include <stdint.h>

typedef void(*os_function_type)(void);

typedef struct os_task_control_block
{
  os_function_type p_func;
  uint8_t          cycle;
  uint8_t          timer;
}
os_task_control_block;

#define TASK_COUNT (uint8_t) (sizeof(os_task_list) / sizeof((os_task_list)[(size_t) UINT8_C(0)]))

#define OS_TIMER_TIMEOUT(T) (bool) (((uint8_t) ((uint8_t) (mcal_gpt_get_time_elapsed() - (T)) & (uint8_t) UINT8_C(0x80)) == (uint8_t) UINT8_C(0)) ? true : false)

extern void app_led_task  (void);
extern void app_hello_task(void);

static bool os_wants_exit(void) ATTRIBUTE_NAKED;

static os_task_control_block os_task_list[(size_t) UINT8_C(2)] =
{
  { app_led_task,   (uint8_t) UINT8_C(1), (uint8_t) UINT8_C(0) },
  { app_hello_task, (uint8_t) UINT8_C(3), (uint8_t) UINT8_C(0) }
};

void os_schedule(void)
{
  while(!os_wants_exit())
  {
    for(uint8_t task_index = (uint8_t) UINT8_C(0); task_index < TASK_COUNT; ++task_index)
    {
      if(OS_TIMER_TIMEOUT(os_task_list[task_index].timer))
      {
        os_task_list[task_index].p_func();

        os_task_list[task_index].timer += os_task_list[task_index].cycle;
      }
    }
  }
}

static bool os_wants_exit(void) ATTRIBUTE_NAKED
{
  ASM("rst 0x28\n" ".dw #0x4018\n");
  ASM("ld h, #0x0\n");
  ASM("cp #0x9\n");
  ASM("jp nz, no_exit\n");
  ASM("ld h, #0x1\n");
  ASM("no_exit:\n");
  ASM("ret\n");

  RETURN_FROM_NAKED(false);
}
