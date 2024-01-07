#include<stdint.h>

// These static variables are used to test the static initialization in crt0.s.

uint8_t app_dummy_test_non_initialized;
uint8_t app_dummy_test_initialized = (uint8_t) UINT8_C(42);
