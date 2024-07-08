///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2024.
//  Distributed under The Unlicense
//

#ifndef APP_LCD_UTIL_2024_01_07_H
  #define APP_LCD_UTIL_2024_01_07_H

  #include <startup/asm_util.h>

  #include <stdint.h>

  void app_lcd_util_puts(const char* p_str);

  void app_lcd_util_row(const uint8_t row) ATTRIBUTE_NAKED;
  void app_lcd_util_col(const uint8_t col) ATTRIBUTE_NAKED;

  void app_lcd_util_init(void) ATTRIBUTE_NAKED;

#endif // APP_LCD_UTIL_2024_01_07_H
