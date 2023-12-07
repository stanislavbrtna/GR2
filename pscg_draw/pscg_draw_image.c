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

void gr2_draw_image(
    int16_t x1,
    int16_t y1,
    int16_t x2,
    int16_t y2,
    uint16_t id,
    gr2context * c
) {
  LCD_drawArea area;
  LCD_setSubDrawArea(x1, y1, x2, y2);
  LCD_getDrawArea(&area);

#ifdef PPM_SUPPORT_ENABLED
  if (svp_fexists(c->pscgElements[id].str_value)) {
    if (c->pscgElements[id].param != 0) {
      sda_p16_set_alpha(1, c->pscgElements[id].param - 1, c->background_color);
    }
    sda_img_draw(x1, y1, c->pscgElements[id].value, c->pscgElements[id].value, c->pscgElements[id].str_value);
    sda_p16_set_alpha(0, 0, c->background_color);
  }  else {
    LCD_FillRect(x1, y1, x2, y2, c->active_color);
    LCD_DrawRectangle(x1, y1, x2, y2, c->border_color);
    LCD_DrawLine(x1, y1, x2, y2, c->border_color);
    LCD_DrawLine(x1, y2, x2, y1, c->border_color);
  }
#endif
  LCD_setDrawAreaS(&area); //draw_ppm changes subdraw area, so it must be restored
}