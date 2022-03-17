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


void pscg_draw_button(
    int16_t x1,
    int16_t y1,
    int16_t x2,
    int16_t y2,
    uint8_t *str,
    uint8_t active,
    uint16_t id,
    gr2context * c
) {
  uint8_t curr_font;
  LCD_setSubDrawArea(x1, y1, x2, y2);
  curr_font = LCD_Get_Font_Size();
  LCD_Set_Sys_Font(c->pscgElements[id].param2);
  if ((c->pscgElements[id].grayout == 0) && (global_grayout_flag == 0)) {
    if((active == 1) && (c->pscgElements[id].pre_active == 0)) {
      LCD_FillRect(x1, y1, x2, y2, c->active_color);
    }else if (active == 0) {
      if ((c->pscgElements[id].status_reg & GR2_GHOST_B) == 0) {
        LCD_FillRect(x1, y1, x2, y2, c->fill_color);
      } else {
        LCD_FillRect(x1, y1, x2, y2, c->background_color);
      }
    }
    LCD_DrawText_ext(
      x1 + pscg_get_text_align_x(id, x1, x2, c->pscgElements[id].param, c),
      y1 + PSCG_TEXT_Y_GAP,
      c->text_color,
      str
    );
    if (c->pscgElements[id].status_reg & GR2_SELECT_B) {
      LCD_DrawRectangle(x1 + 5, y1 + 4, x2 - 5, y2 - 4, c->active_color);
      LCD_DrawRectangle(x1 + 4, y1 + 3, x2 - 4, y2 - 3, c->active_color);
    }
    LCD_DrawRectangle(x1,y1,x2,y2,c->border_color);
    LCD_DrawRectangle(x1+1,y1+1,x2-1,y2-1,c->border_color);
  }  else {
    LCD_FillRect(x1, y1, x2, y2, LCD_get_gray16(c->fill_color));
    LCD_DrawText_ext(
      x1 + pscg_get_text_align_x(id, x1, x2,c->pscgElements[id].param, c),
      y1 + PSCG_TEXT_Y_GAP,
      LCD_get_gray16(c->text_color),
      str
    );
    LCD_DrawRectangle(x1, y1, x2, y2, LCD_get_gray16(c->border_color));
    LCD_DrawRectangle(x1 + 1, y1 + 1, x2 - 1, y2 - 1, LCD_get_gray16(c->border_color));
  }
  LCD_Set_Sys_Font(curr_font);
  c->pscgElements[id].pre_active = active;
}