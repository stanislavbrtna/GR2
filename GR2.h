/*
Copyright (c) 2017 Stanislav Brtna

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#ifndef GR2_H
#define GR2_H

#define LCD_W 800 // deprecated
#define LCD_H 480

// GR2 verze 2.1
#define GR2_VERSION 220

//TODO: these defines are pure mess, fix this
#ifdef PC
#include <stdio.h>
#include <stdint.h>
#endif

#if defined(STM32F405xx) //defined(STM32F411xE)
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_cortex.h"
#endif

#if defined(STM32F407xx)
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_cortex.h"
#endif

typedef enum {EV_NONE,EV_PRESSED, EV_HOLD,EV_LONGHOLD, EV_RELEASED, EV_DRAGOUT} gr2EventType;

#include "lcd_io.h"
#include "lcd_basics.h"
#include "lcd_text.h"
#include "lcd_canvas.h"

#ifdef PPM_SUPPORT_ENABLED
void svp_ppm_set_pmc(uint8_t enable, uint16_t color);
void draw_ppm(uint16_t x,uint16_t y,uint8_t scale, uint8_t *filename);
#endif
#include "pscg.h"

#endif
