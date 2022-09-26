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

void gr2_draw_icon(
    int16_t x1,
    int16_t y1,
    int16_t x2,
    int16_t y2,
    uint8_t active,
    uint16_t id,
    gr2context *c
) {
  LCD_drawArea area;
  uint16_t size = 0;
  uint16_t bc, fc, ac, tc;
  uint8_t curr_font;
  curr_font = LCD_Get_Font_Size();

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

  if (((x2 - x1 + 1) / 32 - 1) > ((y2 - y1 + 1) / 80)) {
    size = ((y2 - y1 + 1) / 80);
  } else {
    size = ((x2 - x1 + 1) / 32 - 1);
  }

  LCD_setSubDrawArea(x1, y1, x1 + 32 * (size + 1), y2); // set sub-draw area

  LCD_getDrawArea(&area); // store the area

  //printf("xsize: %d, ysize: %d size: %d txsize: %d ttxt: %s\n",((x2-x1)/64),((y2-y1)/80), size , (15*size)/8, pscgElements[id].str_value);

  if (size < 1) {
    gr2_error((uint8_t *)"PSCG element icon too small!\n", c);
    return;
  }

  if ((active == 1) && (c->pscgElements[id].pre_active == 0)) {
#ifdef PPM_SUPPORT_ENABLED
    if (svp_fexists(c->pscgElements[id].str_value2)) {
      svp_ppm_set_pmc(1, ac);
      if (c->pscgElements[id].param != 0) {
        sda_p16_set_alpha(1, c->pscgElements[id].param - 1, c->background_color);
      }
      if (ppm_get_width(c->pscgElements[id].str_value2) == 32) {
        draw_ppm(x1, y1, size + 1, c->pscgElements[id].str_value2);
      } else if (ppm_get_width(c->pscgElements[id].str_value2) == 64) {
        draw_ppm(x1, y1, size, c->pscgElements[id].str_value2);
      }
      sda_p16_set_alpha(0, 0, c->background_color);
      svp_ppm_set_pmc(0, 0);
    } else {
      // if there is no icon, will draw empty rectangle
      LCD_FillRect(x1, y1, x1 + 64 * size, y1 + 64 * size, ac);
      LCD_DrawRectangle(x1, y1, x1 + 64 * size, y1 + 64 * size, bc);
      LCD_DrawLine(x1, y1, x1 + 64 * size, y1 + 64 * size, bc);
      LCD_DrawLine(x1, y1 + 64 * size, x1 + 64 * size, y1, bc);
    }
#endif
    LCD_setDrawAreaS(&area); // draw_ppm changed the sub-draw area, so we will restore it

    c->pscgElements[id].pre_active = active;

    // if there is no text, we will draw no rectangle
    if (c->pscgElements[id].str_value[0] == 0) {
      return;
    }

    LCD_FillRect(
      x1,
      y1 + 2 + 32 * (size + 1),
      x1 + 32 * (size + 1),
      y1 + 2 + 32 * (size + 1) + 8 * ((22 * size) / 8) + 2,
      ac
    );
    LCD_DrawRectangle(
      x1,
      y1 + 2 + 32 * (size + 1),
      x1 + 32 * (size + 1),
      y1 + 2 + 32 * (size + 1) + 8 * ((22 * size) / 8) + 2,
      bc
    );
    LCD_Set_Sys_Font(12);
    LCD_DrawText_ext(
      x1 + gr2_get_text_align_x(id, x1, x1 + 64 * size, 5, c),
      y1 + 5 + 32 * (size + 1),
      tc,
      c->pscgElements[id].str_value
    );
  } else if (active == 0) {
#ifdef PPM_SUPPORT_ENABLED
    if (svp_fexists(c->pscgElements[id].str_value2)) {
      if (c->pscgElements[id].param != 0) {
        sda_p16_set_alpha(1, c->pscgElements[id].param - 1, c->background_color);
      }
      if (c->pscgElements[id].grayout == 1) {
        svp_ppm_set_pmc(1, ac);
      } else if (c->pscgElements[id].status_reg & GR2_SELECT_B) {
        svp_ppm_set_pmc(1, ac);
      }
      if (ppm_get_width(c->pscgElements[id].str_value2) == 32) {
        draw_ppm(x1, y1, size + 1, c->pscgElements[id].str_value2);
      } else if (ppm_get_width(c->pscgElements[id].str_value2) == 64) {
        draw_ppm(x1, y1, size, c->pscgElements[id].str_value2);
      }
      svp_ppm_set_pmc(0, 0);
      sda_p16_set_alpha(0, 0, c->background_color);
    } else {
      LCD_FillRect(x1, y1, x1 + 64 * size, y1 + 64 * size, fc);
      LCD_DrawRectangle(x1, y1, x1 + 64 * size, y1 + 64 * size, bc);
      LCD_DrawLine(x1, y1, x1 + 64 * size, y1 + 64 * size, bc);
      LCD_DrawLine(x1, y1 + 64 * size, x1 + 64 * size, y1, bc);
    }
#endif

    c->pscgElements[id].pre_active = active;

    // if there is no string under the icon, no rectangle will be drawn
    if (c->pscgElements[id].str_value[0] == 0) {
      return;
    }

    LCD_setDrawAreaS(&area); // restore sub draw area
    LCD_FillRect(
      x1,
      y1 + 2 + 32 * (size + 1),
      x1 + 32 * (size + 1),
      y1 + 2 + 32 * (size + 1) + 8 * ((22 * size) / 8) + 2,
      c->background_color
    );
    LCD_DrawRectangle(
      x1,
      y1 + 2 + 32 * (size + 1),
      x1 + 32 * (size + 1),
      y1 + 2 + 32 * (size + 1) + 8 * ((22 * size) / 8) + 2,
      c->border_color
    );

    LCD_Set_Sys_Font(12);
    LCD_DrawText_ext(
      x1 + gr2_get_text_align_x(id, x1, x1 + 64 * size, 5, c),
      y1 + 5 + 32 * (size + 1),
      tc,
      c->pscgElements[id].str_value
    );
  }
  LCD_Set_Sys_Font(curr_font);
}