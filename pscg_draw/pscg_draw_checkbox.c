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

void gr2_draw_checkbox(
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
  uint16_t bc, fc, ac, tc;
  LCD_setSubDrawArea(x1, y1, x2, y2);
  curr_font = LCD_Get_Font_Size();
  LCD_Set_Sys_Font(c->pscgElements[id].param2);

  // So the background is matching rest of the screen
  // If the screen is grey, background will be gray
  if (global_grayout_flag == 0) {
    LCD_FillRect(x1, y1, x2, y2, c->background_color);
  } else {
    LCD_FillRect(x1, y1, x2, y2, LCD_get_gray16(c->background_color));
  }

  if ((c->pscgElements[id].grayout == 0) && (global_grayout_flag == 0)) {
    bc = c->border_color;
    fc = c->fill_color;
    ac = c->active_color;
    tc = c->text_color;
  } else {
    bc = LCD_get_gray16(c->border_color);
    fc = LCD_get_gray16(c->fill_color);
    ac = LCD_get_gray16(c->active_color);
    tc = LCD_get_gray16(c->text_color);
  }

  if((active == 1)) {
    // bigger rectangle
    LCD_FillRect(
      x1 + PSCG_CHECKBOX_HSPACE_UP,
      y1 + PSCG_CHECKBOX_VSPACE_UP,
      x1 + y2 - y1 - PSCG_CHECKBOX_HSPACE_DN,
      y2 - PSCG_CHECKBOX_VSPACE_DN,
      fc
    );
    // the inner smaller one
    LCD_FillRect(
      x1 + PSCG_CHECKBOX_HSPACE_UP + PSCG_CHECKBOX_IN_HSPACE,
      y1 + PSCG_CHECKBOX_VSPACE_UP + PSCG_CHECKBOX_IN_VSPACE,
      x1 + y2 - y1 - PSCG_CHECKBOX_HSPACE_DN - PSCG_CHECKBOX_IN_HSPACE,
      y2 - PSCG_CHECKBOX_VSPACE_DN - PSCG_CHECKBOX_IN_VSPACE,
      ac
    );
    // outlne of the inner smaller one
    LCD_DrawRectangle(
      x1 + PSCG_CHECKBOX_HSPACE_UP + PSCG_CHECKBOX_IN_HSPACE,
      y1 + PSCG_CHECKBOX_VSPACE_UP + PSCG_CHECKBOX_IN_VSPACE,
      x1 + y2 - y1 - PSCG_CHECKBOX_HSPACE_DN - PSCG_CHECKBOX_IN_HSPACE,
      y2 - PSCG_CHECKBOX_VSPACE_DN - PSCG_CHECKBOX_IN_VSPACE,
      tc
    );
  } else if (c->pscg_active_element == id) {
    LCD_FillRect(
      x1 + PSCG_CHECKBOX_HSPACE_UP,
      y1 + PSCG_CHECKBOX_VSPACE_UP,
      x1 + y2 - y1 - PSCG_CHECKBOX_HSPACE_DN,
      y2 - PSCG_CHECKBOX_VSPACE_DN,
      fc
    );
    LCD_DrawRectangle(
      x1 + PSCG_CHECKBOX_HSPACE_UP + PSCG_CHECKBOX_IN_HSPACE,
      y1 + PSCG_CHECKBOX_VSPACE_UP + PSCG_CHECKBOX_IN_VSPACE,
      x1 + y2 - y1 - PSCG_CHECKBOX_HSPACE_DN - PSCG_CHECKBOX_IN_HSPACE,
      y2 - PSCG_CHECKBOX_VSPACE_DN - PSCG_CHECKBOX_IN_VSPACE,
      tc
    );
    c->pscgElements[id].pre_active = 1;
  } else if (active == 0) {
     LCD_FillRect(
      x1 + PSCG_CHECKBOX_HSPACE_UP,
      y1 + PSCG_CHECKBOX_VSPACE_UP,
      x1 + y2 - y1 - PSCG_CHECKBOX_HSPACE_DN,
      y2 - PSCG_CHECKBOX_VSPACE_DN,
      fc
    );
  }

  // outlineof the larger one
  LCD_DrawRectangle(x1 + PSCG_CHECKBOX_HSPACE_UP,
    y1 + PSCG_CHECKBOX_VSPACE_UP,
    x1 + y2 - y1 - PSCG_CHECKBOX_HSPACE_DN,
    y2 - PSCG_CHECKBOX_VSPACE_DN,
    bc
  );

  // another line of the outline of the larger one
  LCD_DrawRectangle(
    x1 + PSCG_CHECKBOX_HSPACE_UP + 1,
    y1 + PSCG_CHECKBOX_VSPACE_UP + 1,
    x1 + y2 - y1 - PSCG_CHECKBOX_HSPACE_DN - 1,
    y2 - PSCG_CHECKBOX_VSPACE_DN - 1,
    bc
  );

  // text position behind box
  LCD_DrawText_ext(x1 + y2 - y1 + PSCG_CHECKBOX_TEXT_GAP, y1 + PSCG_TEXT_Y_GAP, tc, str);
  LCD_Set_Sys_Font(curr_font);
}