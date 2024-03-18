/*
Copyright (c) 2022 Stanislav Brtna

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

#include "../GR2.h"

#ifdef PPM_SUPPORT_ENABLED
uint16_t ppm_get_width(uint8_t *filename);
uint8_t svp_fexists(uint8_t *fname);
void sda_p16_set_alpha(uint8_t enable, uint16_t color, uint16_t bg_color);
#endif

extern uint8_t global_grayout_flag;

void gr2_button_draw_bg (int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t col, uint16_t stat);
void gr2_button_draw_frame(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t col, uint16_t stat);


