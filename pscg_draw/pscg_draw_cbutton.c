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

void gr2_draw_cbutton(
    int16_t x1,
    int16_t y1,
    int16_t x2,
    int16_t y2,
    uint8_t *str,
    uint8_t active,
    uint16_t id,
    gr2context * c
) {
  LCD_setSubDrawArea(x1, y1, x2, y2);
  if ((c->pscgElements[id].grayout == 0) && (global_grayout_flag == 0))  {
    if ((active == 1) && (c->pscgElements[id].pre_active == 0)) {
      gr2_button_draw_bg(x1, y1, x2, y2, c->active_color, c->pscgElements[id].status_reg);
    } else if (active == 0) {
      gr2_button_draw_bg(x1, y1, x2, y2, c->pscgElements[id].value, c->pscgElements[id].status_reg);
    }
    LCD_DrawText_ext(
      x1 + gr2_get_text_align_x(id, x1, x2, c->pscgElements[id].param, c),
      y1 + PSCG_TEXT_Y_GAP,
      ~c->pscgElements[id].value,
      str
    );
    gr2_button_draw_frame(x1, y1, x2, y2, c->border_color, c->pscgElements[id].status_reg);
    if (c->pscgElements[id].status_reg & GR2_SELECT_B) {
      gr2_button_draw_frame(x1 + 4, y1 + 3, x2 - 4, y2 - 3, ~c->pscgElements[id].value, c->pscgElements[id].status_reg);
    }
  }  else {
    LCD_FillRect(x1, y1, x2, y2, LCD_get_gray16(c->pscgElements[id].value));
    LCD_DrawText_ext(
      x1 + gr2_get_text_align_x(id, x1, x2, c->pscgElements[id].param, c),
      y1 + PSCG_TEXT_Y_GAP,
      LCD_get_gray16(~c->pscgElements[id].value),
      str
    );
    gr2_button_draw_frame(x1, y1, x2, y2, LCD_get_gray16(c->border_color), c->pscgElements[id].status_reg);
  }
  c->pscgElements[id].pre_active = active;
}