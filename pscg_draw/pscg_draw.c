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
#include "pscg_draw.h"

uint8_t global_grayout_flag;


void gr2_set_global_grayout_flag(uint8_t val) {
  global_grayout_flag = val;
}


uint8_t gr2_get_global_grayout_flag() {
  return global_grayout_flag;
}


int16_t gr2_get_text_align_x(uint16_t id, int16_t x1, int16_t x2, int16_t offset, gr2context * c) {
  uint8_t alignment;
  int16_t x_add = 0;
  alignment = gr2_text_get_align(id, c);
  if (alignment != GR2_ALIGN_LEFT) {
    if (alignment == GR2_ALIGN_RIGHT) {
      x_add = x2 - x1 - LCD_Text_Get_Width(c->pscgElements[id].str_value, 0) - offset;
    } else if (alignment == GR2_ALIGN_CENTER) {
      x_add = (x2 - x1)/2 - LCD_Text_Get_Width(c->pscgElements[id].str_value, 0)/2 + 1;
    }
  } else {
    x_add += offset;
  }

  return x_add;
}

void gr2_draw_end(gr2context * c) {
  c->invisible_flag = 0;

  if (c->reset_active_element_flag) {
    c->pscgElements[c->pscg_active_element].pre_active = 0;
    c->pscgElements[c->pscg_active_element].modified = 1;

    c->pscg_active_element = 0;
    c->reset_active_element_flag = 0;
  }

  gr2_set_global_grayout_flag(0);
}
