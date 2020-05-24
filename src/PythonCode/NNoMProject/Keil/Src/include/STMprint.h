#ifndef STMprint
#define STMprint

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "stm32l4xx_hal_usart.h"
#include "stm32l4xx_hal_uart.h"

extern USART_HandleTypeDef husart1;

void vprint(const char *fmt, va_list argp);

void my_printf(const char *fmt, ...); // custom printf() function

#endif
