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

uint16_t background_color; //for set text fit

void pscg_draw_text(
    int16_t x1,
    int16_t y1,
    int16_t x2,
    int16_t y2,
    uint8_t *str,
    uint8_t active,
    uint8_t editable,
    uint16_t cursor,
    uint16_t font_size,
    uint8_t fit,
    uint8_t pwd,
    uint16_t id,
    gr2context * c
) {
  LCD_setSubDrawArea(x1, y1, x2, y2);
  background_color = c->background_color;
  uint8_t curr_font;

  // printf("DBG font size: %u\n", font_size);
  curr_font = LCD_Get_Font_Size();
  LCD_Set_Sys_Font(font_size);

  // get additional alignment
  int16_t x_add = 0;
  x_add = pscg_get_text_align_x(id, x1, x2, 10, c);

  if ((c->pscgElements[id].grayout == 0) && (global_grayout_flag == 0)) {
    if (active == 1) {
      LCD_FillRect(x1, y1, x2, y2, c->active_color);
      if (pwd == 0) {
        LCD_Text_Draw_Cursor(x_add + x1, y1 + 5, str, cursor, c->text_color);
      } else {
        LCD_Text_Draw_Cursor_Pwd(x_add + x1, y1 + 5, str, c->text_color);
      }
    } else {
      LCD_FillRect(x1, y1, x2, y2, c->background_color);
    }

    LCD_set_fitText(fit, x2);
    if (pwd == 1) {
      LCD_DrawText_Pwd(x_add + x1, y1 + PSCG_TEXT_Y_GAP, c->text_color, str);
    } else {
      LCD_DrawText_ext(x_add + x1, y1 + PSCG_TEXT_Y_GAP, c->text_color, str);
      if (fit) {
        c->pscgElements[id].param = LCD_get_fitText_breakpoint();
      }
    }
    LCD_set_fitText(0, 0);

    if (editable) {
      LCD_DrawRectangle(x1, y1, x2, y2, c->border_color);
    }
  } else {
    if (active == 1) {
      LCD_FillRect(x1, y1, x2, y2, LCD_get_gray16(c->active_color)); // background
      if (pwd == 0) {
        LCD_Text_Draw_Cursor(x_add + x1, y1 + 5, str, cursor, LCD_get_gray16(c->text_color));
      }
    } else {
      LCD_FillRect(x1, y1, x2, y2, LCD_get_gray16(c->background_color));
    }

    LCD_set_fitText(fit, x2);
    if (pwd == 1) {
      LCD_DrawText_Pwd(x_add + x1, y1 + PSCG_TEXT_Y_GAP, LCD_get_gray16(c->text_color), str);
    } else {
      LCD_DrawText_ext(x_add + x1, y1 + PSCG_TEXT_Y_GAP, LCD_get_gray16(c->text_color), str);
      if (fit) {
        c->pscgElements[id].param = LCD_get_fitText_breakpoint();
      }
    }
    LCD_set_fitText(0, 0);

    if (editable) {
      LCD_DrawRectangle(x1, y1, x2, y2, LCD_get_gray16(c->border_color));
    }
  }

  LCD_Set_Sys_Font(curr_font);
}