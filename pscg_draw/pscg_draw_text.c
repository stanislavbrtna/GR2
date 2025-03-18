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

void gr2_draw_text(
    int16_t x1,
    int16_t y1,
    int16_t x2,
    int16_t y2,
    uint16_t id,
    gr2context * c
) {
  LCD_setSubDrawArea(x1, y1, x2, y2);
  background_color = c->background_color;
  uint8_t curr_font;
  uint16_t text_bg = c->background_color;

  uint8_t showCursor = 0;

  // printf("DBG font size: %u\n", font_size);
  curr_font = LCD_Get_Font_Size();
  LCD_Set_Sys_Font(c->pscgElements[id].param2);

  // get additional alignment
  int16_t x_add = 0;
  x_add = gr2_get_text_align_x(id, x1, x2, 10, c);

  if ((c->pscgElements[id].grayout == 0) && (global_grayout_flag == 0)) {
    if (c->pscgElements[id].value == 1) { // active
      
      uint16_t text_select = c->fill_color;

      if(gr2_text_get_invert_select(id, c)) {
        text_bg = c->fill_color;
        text_select = c->active_color;
      } else {
        text_bg = c->active_color;
      }

      if (gr2_text_get_pwd(id, c) == 1) {
        LCD_FillRect(x1, y1, x2, y2, text_bg);
      }

      LCD_FillRect(x1 + 1, y1 + 1, x1 + x_add, y2 - 1, text_bg);
      LCD_FillRect(x1 + 1, y1 + 1, x2 - 1, y1 + PSCG_TEXT_Y_GAP, text_bg);

      if (c->textBlockStart != 0 || c->textBlockEnd != 0) {
        LCD_set_text_block(c->textBlockStart - 1, c->textBlockEnd, text_select);
      } else {
        LCD_set_text_block(0, 0, 0);
      }
      if (gr2_text_get_pwd(id, c) == 0) {
        if (c->textBlockStart == c->textBlockEnd) {
          LCD_set_fitText(gr2_text_get_fit(id, c), x2);
          showCursor = 1;
        }
      } else {
        LCD_Text_Draw_Cursor_Pwd(x_add + x1, y1 + 5, c->pscgElements[id].str_value, c->text_color);
      }
    } else {
      if (c->pscgElements[c->pscgElements[id].screen_id].str_value == 0) {
        LCD_FillRect(x1, y1, x2, y2, c->background_color);
      }
    }

    LCD_set_fitText(gr2_text_get_fit(id, c), x2);
    if (gr2_text_get_pwd(id, c) == 1) {
      LCD_DrawText_Pwd(x_add + x1, y1 + PSCG_TEXT_Y_GAP, c->text_color, c->pscgElements[id].str_value);
    } else {
      if(c->pscgElements[id].value == 1)
        LCD_set_text_bg(1, text_bg, x2 - x1, y2 - y1);
      LCD_DrawText_ext(x_add + x1, y1 + PSCG_TEXT_Y_GAP, c->text_color, c->pscgElements[id].str_value);
      
      if(c->pscgElements[id].value == 1)
        LCD_set_text_bg(0, 0, 0, 0);
      if(showCursor)
        LCD_Text_Draw_Cursor(x_add + x1, y1 + 5, c->pscgElements[id].str_value, c->pscgElements[id].param, c->text_color);
    }
    LCD_set_fitText(0, 0);
    LCD_set_text_block(0, 0, 0);

    if (gr2_text_get_editable(id, c)) {
      if (gr2_get_select(id, c) == 1) {
        LCD_DrawRectangle(x1 + 1, y1 + 1, x2 - 1, y2 - 1, c->active_color);
        LCD_DrawRectangle(x1 + 2, y1 + 2, x2 - 2, y2 - 2, c->active_color);
      }
      LCD_DrawRectangle(x1, y1, x2, y2, c->border_color);
      LCD_DrawRectangle(x1 + 1, y1 + 1, x2 - 1, y2 - 1, c->border_color);
    } else {
      if (gr2_get_select(id, c) == 1) {
        LCD_DrawRectangle(x1, y1, x2, y2, c->border_color);
      }
    }
  } else {
    // grayed out
    if (c->pscgElements[id].value == 1) {
      LCD_FillRect(x1, y1, x2, y2, LCD_get_gray16(c->active_color)); // background
    } else {
      LCD_FillRect(x1, y1, x2, y2, LCD_get_gray16(c->background_color));
    }

    if (gr2_text_get_pwd(id, c) == 1) {
      LCD_DrawText_Pwd(x_add + x1, y1 + PSCG_TEXT_Y_GAP, LCD_get_gray16(c->text_color), c->pscgElements[id].str_value);
    } else {
      LCD_DrawText_ext(x_add + x1, y1 + PSCG_TEXT_Y_GAP, LCD_get_gray16(c->text_color), c->pscgElements[id].str_value);
    }
    LCD_set_fitText(0, 0);
    LCD_set_text_block(0, 0, 0);

    if (gr2_text_get_editable(id, c)) {
      LCD_DrawRectangle(x1, y1, x2, y2, LCD_get_gray16(c->border_color));
      LCD_DrawRectangle(x1 + 1, y1 + 1, x2 - 1, y2 - 1, LCD_get_gray16(c->border_color));
    }
  }

  LCD_Set_Sys_Font(curr_font);
}