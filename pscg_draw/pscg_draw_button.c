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


void gr2_draw_button(
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
    uint16_t bg_color;

    if(active == 1) {
      bg_color = c->activeColor;
    } else {
      if ((c->pscgElements[id].status_reg & GR2_GHOST_B) == 0) {
        bg_color = c->fillColor;
      } else {
        bg_color = c->backgroundColor;
      }
    }

    if(active == 1 && c->pscgElements[id].pre_active == 0) {
      gr2_button_draw_bg(x1, y1, x2, y2, bg_color, c->pscgElements[id].status_reg);
    }else if (active == 0) {
      gr2_button_draw_bg(x1, y1, x2, y2, bg_color, c->pscgElements[id].status_reg);
    }

    int32_t sic_width = 0;

    if(c->pscgElements[id].str_value2 != 0 && !gr2_strcmp(c->pscgElements[id].str_value2, "")) {
#ifdef PPM_SUPPORT_ENABLED
      sda_draw_sic_file(x1 + 2 + c->pscgElements[id].param/2, y1 + 1, c->textColor, bg_color, c->pscgElements[id].str_value2);
      sic_width = sda_sic_get_last_width();
#endif
    }

    LCD_DrawText_ext(
      x1 + gr2_get_text_align_x(id, x1, x2, c->pscgElements[id].param + sic_width, c),
      y1 + PSCG_TEXT_Y_GAP,
      c->textColor,
      str
    );
    if (c->pscgElements[id].status_reg & GR2_SELECT_B) {
      gr2_button_draw_frame(x1 + 5, y1 + 4, x2 - 5, y2 - 4, c->activeColor, c->pscgElements[id].status_reg);
    }
    gr2_button_draw_frame(x1,y1,x2,y2,c->borderColor, c->pscgElements[id].status_reg);
    
  }  else {
    gr2_button_draw_bg(x1, y1, x2, y2, LCD_get_gray16(c->fillColor), c->pscgElements[id].status_reg);

    int32_t sic_width = 0;

    if(c->pscgElements[id].str_value2 != 0 && !gr2_strcmp(c->pscgElements[id].str_value2, "")) {
#ifdef PPM_SUPPORT_ENABLED
      sda_draw_sic_file(x1 + 2 + c->pscgElements[id].param/2, y1 + 1, c->textColor, LCD_get_gray16(c->fillColor), c->pscgElements[id].str_value2);
      sic_width = sda_sic_get_last_width();
#endif
    }

    LCD_DrawText_ext(
      x1 + gr2_get_text_align_x(id, x1, x2, c->pscgElements[id].param + sic_width, c),
      y1 + PSCG_TEXT_Y_GAP,
      LCD_get_gray16(c->textColor),
      str
    );
    gr2_button_draw_frame(x1,y1,x2,y2,LCD_get_gray16(c->borderColor), c->pscgElements[id].status_reg);
  }
  LCD_Set_Sys_Font(curr_font);
  c->pscgElements[id].pre_active = active;
}