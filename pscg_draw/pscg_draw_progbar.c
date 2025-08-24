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

#include "pscg_draw.h"

void gr2_draw_progbar_v(
    int16_t x1,
    int16_t y1,
    int16_t x2,
    int16_t y2,
    int32_t param,
    int32_t value,
    uint16_t id,
    gr2context * c
  ){
  uint16_t slider_pos;
  LCD_setSubDrawArea(x1, y1, x2, y2);

  slider_pos = (uint16_t)(((float)value/(float)param)*((float)(y2 - y1)));

  if (slider_pos > (y2 - y1)) {
    slider_pos = (y2 - y1);
  }

  if ((c->pscgElements[id].grayout == 0) && (global_grayout_flag == 0)) {
    // background
    LCD_FillRect(x1, y1, x2, y2 - slider_pos, c->fillColor);

    // slider
    LCD_FillRect(x1, y2 - slider_pos, x2, y2, c->activeColor);
  } else {
    // grayed out variants
    LCD_FillRect(x1, y1, x2, y2 - slider_pos, LCD_get_gray16(c->fillColor));
    LCD_FillRect(x1, y2 - slider_pos, x2, y2, LCD_get_gray16(c->activeColor));
  }

  // rest of the slider
  LCD_DrawLine(x1, y2 - slider_pos, x2, y2 - slider_pos, c->borderColor);

  // frame
  LCD_DrawRectangle(x1, y1, x2, y2, c->borderColor);
  LCD_DrawRectangle(x1 + 1, y1 + 1, x2 - 1, y2 - 1, c->borderColor);
}


void gr2_draw_progbar_h(
    int16_t x1,
    int16_t y1,
    int16_t x2,
    int16_t y2,
    int32_t param,
    int32_t value,
    uint16_t id,
    gr2context * c
  ){
  uint16_t slider_pos;
  LCD_setSubDrawArea(x1, y1, x2, y2);

  slider_pos = (int32_t)(((float)value/(float)param)*((float)(x2 - x1)));

  if (slider_pos > (x2 - x1)) {
    slider_pos = (x2 - x1);
  }

  if ((c->pscgElements[id].grayout == 0) && (global_grayout_flag == 0)) {
    // background
    LCD_FillRect(x1 + slider_pos, y1, x2, y2, c->fillColor);
    // slider
    LCD_FillRect(x1, y1, x1 + slider_pos, y2, c->activeColor);
  } else {
    LCD_FillRect(x1 + slider_pos, y1 , x2, y2, LCD_get_gray16(c->fillColor));
    LCD_FillRect(x1, y1, x1 + slider_pos, y2, LCD_get_gray16(c->activeColor));
  }

  LCD_DrawLine(x1 + slider_pos, y1, x1 + slider_pos, y2, c->borderColor);

  // frame
  LCD_DrawRectangle(x1, y1, x2, y2, c->borderColor);
  LCD_DrawRectangle(x1 + 1, y1 + 1, x2 - 1, y2 - 1, c->borderColor);
}