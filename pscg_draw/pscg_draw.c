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
  if (alignment == GR2_ALIGN_LEFT) {
    x_add += offset;
  } else if (alignment == GR2_ALIGN_RIGHT) {
    x_add = x2 - x1 - LCD_Text_Get_Width(c->pscgElements[id].str_value, 0) - offset;
  } else if (alignment == GR2_ALIGN_CENTER) {
    x_add = (x2 - x1)/2 - LCD_Text_Get_Width(c->pscgElements[id].str_value, 0)/2 + 1;
  }

  return x_add;
}

void gr2_draw_end(gr2context * c) {
  c->invisibleFlag = 0;

  if (c->resetActiveElementFlag) {
    c->pscgElements[c->activeElement].pre_active = 0;
    c->pscgElements[c->activeElement].modified = 1;

    c->activeElement = 0;
    c->resetActiveElementFlag = 0;
  }

  gr2_set_global_grayout_flag(0);
}


void gr2_button_draw_bg (int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t col, uint16_t stat) {
  if(stat & GR2_ROUNDED_B) {
    LCD_FillRect(x1, y1 + GR2_ROUND_RADIUS, x2, y2 - GR2_ROUND_RADIUS, col);
    LCD_FillRect(x1 + GR2_ROUND_RADIUS, y1, x2 - GR2_ROUND_RADIUS, y1 + GR2_ROUND_RADIUS, col);
    LCD_FillRect(x1 + GR2_ROUND_RADIUS, y2 - GR2_ROUND_RADIUS, x2 - GR2_ROUND_RADIUS, y2, col);

    LCD_FillCirclePart(x1 + GR2_ROUND_RADIUS, y1 + GR2_ROUND_RADIUS, GR2_ROUND_RADIUS, 0, col);
    LCD_FillCirclePart(x2 - GR2_ROUND_RADIUS, y1 + GR2_ROUND_RADIUS, GR2_ROUND_RADIUS, 1, col);
    LCD_FillCirclePart(x1 + GR2_ROUND_RADIUS, y2 - GR2_ROUND_RADIUS, GR2_ROUND_RADIUS, 2, col);
    LCD_FillCirclePart(x2 - GR2_ROUND_RADIUS, y2 - GR2_ROUND_RADIUS, GR2_ROUND_RADIUS, 3, col);
  } else {
    LCD_FillRect(x1, y1, x2, y2, col);
  }
}


void gr2_button_draw_frame(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t col, uint16_t stat) {
  if(stat & GR2_ROUNDED_B) {
    LCD_FillRect(x1 + GR2_ROUND_RADIUS, y1, x2 - GR2_ROUND_RADIUS, y1 + 1, col);
    LCD_FillRect(x1 + GR2_ROUND_RADIUS, y2 - 1, x2 - GR2_ROUND_RADIUS, y2, col);

    LCD_FillRect(x1, y1 + GR2_ROUND_RADIUS, x1 + 1, y2 - GR2_ROUND_RADIUS, col);
    LCD_FillRect(x2 - 1, y1 + GR2_ROUND_RADIUS, x2, y2 - GR2_ROUND_RADIUS, col);

    LCD_DrawCirclePart(x1 + GR2_ROUND_RADIUS, y1 + GR2_ROUND_RADIUS, GR2_ROUND_RADIUS, 0, col);
    LCD_DrawCirclePart(x1 + GR2_ROUND_RADIUS, y1 + GR2_ROUND_RADIUS + 1, GR2_ROUND_RADIUS, 0, col);

    LCD_DrawCirclePart(x2 - GR2_ROUND_RADIUS, y1 + GR2_ROUND_RADIUS, GR2_ROUND_RADIUS, 1, col);
    LCD_DrawCirclePart(x2 - GR2_ROUND_RADIUS, y1 + GR2_ROUND_RADIUS + 1, GR2_ROUND_RADIUS, 1, col);

    LCD_DrawCirclePart(x1 + GR2_ROUND_RADIUS, y2 - GR2_ROUND_RADIUS, GR2_ROUND_RADIUS, 2, col);
    LCD_DrawCirclePart(x1 + GR2_ROUND_RADIUS, y2 - GR2_ROUND_RADIUS - 1, GR2_ROUND_RADIUS, 2, col);

    LCD_DrawCirclePart(x2 - GR2_ROUND_RADIUS, y2 - GR2_ROUND_RADIUS, GR2_ROUND_RADIUS, 3, col);
    LCD_DrawCirclePart(x2 - GR2_ROUND_RADIUS, y2 - GR2_ROUND_RADIUS - 1, GR2_ROUND_RADIUS, 3, col);
  } else {
    LCD_DrawRectangle(x1, y1, x2, y2, col);
    LCD_DrawRectangle(x1 + 1, y1 + 1, x2 - 1, y2 - 1, col);
  }
}