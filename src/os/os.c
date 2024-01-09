///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
//  Distributed under The Unlicense
//

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <mcal/mcal_gpt.h>
#include <os/os.h>
#include <startup/asm_util.h>

typedef void(*os_function_type)(void);

typedef struct os_task_control_block
{
  os_function_type p_init;
  os_function_type p_func;
  uint8_t          cycle;
  uint8_t          timer;
}
os_task_control_block;

#define OS_COUNTOF(a) ((size_t) (sizeof(a) / sizeof((a)[(size_t) 0U])))

#define OS_TIMER_TIMEOUT(T) (bool) (((uint8_t) ((uint8_t) (mcal_gpt_get_time_elapsed() - (T)) & (uint8_t) UINT8_C(0x80)) == (uint8_t) UINT8_C(0)) ? true : false)

extern void app_led_init  (void);
extern void app_led_task  (void);
extern void app_hello_init(void);
extern void app_hello_task(void);

static bool os_wants_exit(void) ATTRIBUTE_NAKED;

static os_task_control_block os_task_list[2U] =
{
  { app_led_init,   app_led_task,   (uint8_t) UINT8_C(1), (uint8_t) UINT8_C(0) },
  { app_hello_init, app_hello_task, (uint8_t) UINT8_C(3), (uint8_t) UINT8_C(0) }
};

void os_init(void)
{
  for(uint8_t task_index = (uint8_t) UINT8_C(0); task_index < (uint8_t) OS_COUNTOF(os_task_list); ++task_index)
  {
    os_task_list[task_index].p_init();
  }
}

void os_schedule(void)
{
  while(!os_wants_exit())
  {
    for(uint8_t task_index = (uint8_t) UINT8_C(0); task_index < (uint8_t) OS_COUNTOF(os_task_list); ++task_index)
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
  __asm__("rst 0x28\n" ".dw #0x4018\n");
  __asm__("ld h, #0x0\n");
  __asm__("cp #0x9\n");
  __asm__("jp nz, no_exit\n");
  __asm__("ld h, #0x1\n");
  __asm__("no_exit:\n");
  __asm__("ret\n");

  #if defined(_MSC_VER)
  return false;
  #endif
}
