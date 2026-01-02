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


// GR2 version 2.4
#define GR2_VERSION 240

#ifdef PC
#include <stdio.h>
#include <stdint.h>
#endif

#if defined(STM32F405xx) || defined(STM32F411xE) || defined(STM32F407xx)
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_cortex.h"
#endif

#if defined(STM32H743xx)
#include "stm32h7xx_hal.h"
#include "stm32h7xx.h"
#endif

typedef enum {EV_NONE,EV_PRESSED, EV_HOLD,EV_LONGHOLD, EV_RELEASED, EV_DRAGOUT} gr2EventType;

#include "lcd_io.h"
#include "lcd_basics.h"
#include "lcd_text.h"
#include "lcd_canvas.h"

#ifdef PPM_SUPPORT_ENABLED
// to be deprecated
void svp_ppm_set_pmc(uint8_t enable, uint16_t color);
void draw_ppm(uint16_t x,uint16_t y,uint8_t scale, uint8_t *filename);

// now using img api
void sda_img_set_mix_color(uint8_t enable, uint16_t color);
void sda_img_draw(int16_t x, int16_t y, int16_t scale_w, int16_t scale_h, uint8_t *filename);
uint16_t sda_img_get_width(uint8_t *filename);
uint16_t sda_img_get_height(uint8_t *filename);
#endif

#include "pscg.h"
#include "GR2_keypad_input.h"

#endif
