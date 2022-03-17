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

void pscg_draw_slider_v(
    int16_t x1,
    int16_t y1,
    int16_t x2,
    int16_t y2,
    uint16_t slider_size,
    int32_t param,
    int32_t value,
    uint16_t id,
    gr2context * c
) {
  int32_t slider_pos;
  uint16_t sirka = x2 - x1;

  LCD_setSubDrawArea(x1, y1, x2, y2);

  LCD_FillRect(x1, y1, x2, y2, c->background_color); // clear

  slider_pos = (int32_t)(((float)value / (float)param) * ((float)(y2 - y1 - slider_size)));

  if (slider_pos > (y2 - y1 - slider_size)) {
    slider_pos = (y2 - y1 - slider_size);
  }

  if ((c->pscgElements[id].grayout == 0) && (global_grayout_flag == 0)) {
    LCD_FillRect(
      x1 + sirka/4, y1, x2 - sirka/4, y2,
      c->fill_color
    );

    LCD_FillRect(
      x1 + sirka/4, y1 + slider_pos, x2 - sirka/4, y2,
      c->active_color
    );

    LCD_DrawRectangle(
      x1 + sirka/4, y1, x2 - sirka/4, y2,
      c->border_color
    );

    // slider
    LCD_FillRect(
      x1, y1 + slider_pos, x2, y1 + slider_pos + slider_size,
      c->active_color
    );
    LCD_DrawRectangle(
      x1, y1 + slider_pos, x2, y1 + slider_pos + slider_size,
      c->border_color
    );
  } else {
    LCD_FillRect(
      x1 + sirka/4, y1, x2 - sirka/4, y2,
      LCD_get_gray16(c->fill_color)
    );

    LCD_FillRect(
      x1 + sirka/4, y1 + slider_pos, x2 - sirka/4, y2,
      LCD_get_gray16(c->active_color)
    );

    LCD_DrawRectangle(
      x1 + sirka/4, y1, x2 - sirka/4, y2,
      LCD_get_gray16(c->border_color)
    );

    // slider
    LCD_FillRect(
      x1, y1 + slider_pos, x2, y1 + slider_pos + slider_size,
      LCD_get_gray16(c->active_color)
    );

    LCD_DrawRectangle(
      x1, y1 + slider_pos, x2, y1 + slider_pos + slider_size,
      LCD_get_gray16(c->border_color)
    );
  }

}

void pscg_draw_slider_v_f(
    int16_t x1,
    int16_t y1,
    int16_t x2,
    int16_t y2,
    uint16_t slider_size,
    int32_t param,
    int32_t value,
    int32_t oldval,
    uint16_t id,
    gr2context * c
) {
  int32_t slider_pos;
  int32_t slider_pos_o;

  LCD_setSubDrawArea(x1, y1, x2, y2);

  uint16_t sirka = x2 - x1;

  // new slider position
  slider_pos = (int32_t)(((float)value / (float)param) * ((float)(y2 - y1 - slider_size)));

  if (slider_pos > (y2 - y1 - slider_size)) {
    slider_pos = (y2 - y1 - slider_size);
  }

  // old slider position
  slider_pos_o = (int32_t)(((float)oldval / (float)param) * ((float)(y2 - y1 - slider_size)));

  if (slider_pos_o > (y2 - y1 - slider_size)) {
    slider_pos_o = (y2 - y1 - slider_size);
  }

  // clear old slider from screen
  LCD_FillRect(
    x1, y1 + slider_pos_o, x2, y1 + slider_pos_o + slider_size + 1,
    c->background_color
  );

  if ((c->pscgElements[id].grayout == 0) && (global_grayout_flag == 0)) {
    if (slider_pos >= slider_pos_o) {
      LCD_FillRect(
        x1 + sirka/4,
        y1 + slider_pos_o,
        x2 - sirka/4,
        y1 + slider_pos,
        c->fill_color
      );
    } else {
      LCD_FillRect(
        x1 + sirka/4,
        y1 + slider_pos,
        x2 - sirka/4,
        y1 + slider_pos_o + slider_size + 1,
        c->active_color
      );
    }
    LCD_DrawRectangle(
      x1 + sirka/4,
      y1,
      x2 - sirka/4,
      y2,
      c->border_color
    );

    // slider
    LCD_FillRect(
      x1,
      y1 + slider_pos,
      x2,
      y1 + slider_pos + slider_size,
      c->active_color
    );
    LCD_DrawRectangle(
      x1, y1 + slider_pos, x2, y1 + slider_pos + slider_size,
      c->border_color
    );
  } else {
    if (slider_pos >= slider_pos_o) {
      LCD_FillRect(
        x1 + sirka/4,
        y1 + slider_pos_o,
        x2 - sirka/4,
        y1 + slider_pos,
        LCD_get_gray16(c->fill_color)
      );
    } else {
      LCD_FillRect(
        x1 + sirka/4, y1 + slider_pos, x2 - sirka/4, y1 + slider_pos_o + slider_size + 1,
        LCD_get_gray16(c->active_color)
      );
    }
    LCD_DrawRectangle(
      x1 + sirka/4, y1, x2 - sirka/4, y2,
      LCD_get_gray16(c->border_color)
    );

    // slider
    LCD_FillRect(
      x1, y1 + slider_pos, x2, y1 + slider_pos + slider_size,
      LCD_get_gray16(c->active_color)
    );
    LCD_DrawRectangle(
      x1, y1 + slider_pos, x2, y1 + slider_pos + slider_size,
      LCD_get_gray16(c->border_color)
    );
  }
}

void pscg_draw_slider_h(
    int16_t x1,
    int16_t y1,
    int16_t x2,
    int16_t y2,
    uint16_t slider_size,
    int32_t param,
    int32_t value,
    uint16_t id,
    gr2context * c
  ){
  int32_t slider_pos;
  LCD_setSubDrawArea(x1, y1, x2, y2+1);

  uint16_t sirka = 0;
  sirka = y2 - y1;

  LCD_FillRect(x1, y1, x2, y2 + 1, c->background_color);

  slider_pos = (int32_t)(((float)value/(float)param)*((float)(x2 - x1 - slider_size)));

  if (slider_pos > (x2 - x1 - slider_size)) {
    slider_pos = (x2 - x1 - slider_size);
  }

  if ((c->pscgElements[id].grayout == 0) && (global_grayout_flag == 0)) {
    LCD_FillRect(
      x1, y1 + sirka/4, x2, y2 - sirka/4,
      c->active_color
    ); // upper background
    LCD_FillRect(
      x1 + slider_pos, y1 + sirka/4, x2, y2 - sirka/4,
      c->fill_color
    ); // lower background
    LCD_DrawRectangle(
      x1, y1 + sirka/4, x2, y2 - sirka/4,
      c->border_color
    ); // frame
    // slider
    LCD_FillRect(
      x1 + slider_pos, y1, x1 + slider_pos + slider_size, y2,
      c->active_color
    );
    LCD_DrawRectangle(
      x1 + slider_pos, y1, x1 + slider_pos + slider_size, y2,
      c->border_color
    );
  } else {
    LCD_FillRect(
      x1, y1 + sirka/4, x2, y2 - sirka/4,
      LCD_get_gray16(c->active_color)
    );
    LCD_FillRect(
      x1 + slider_pos, y1 + sirka/4, x2, y2 - sirka/4,
      LCD_get_gray16(c->fill_color)
    );
    LCD_DrawRectangle(
      x1, y1 + sirka/4, x2, y2 - sirka/4,
      LCD_get_gray16(c->border_color)
    );
    //slider
    LCD_FillRect(
      x1 + slider_pos, y1, x1 + slider_pos + slider_size, y2,
      LCD_get_gray16(c->active_color)
    );
    LCD_DrawRectangle(
      x1 + slider_pos, y1, x1 + slider_pos + slider_size, y2,
      LCD_get_gray16(c->border_color)
    );
  }
}

void pscg_draw_slider_h_f(
    int16_t x1,
    int16_t y1,
    int16_t x2,
    int16_t y2,
    uint16_t slider_size,
    int32_t param,
    int32_t value,
    int32_t oldval,
    uint16_t id,
    gr2context * c
  ){
  uint16_t slider_pos;
  uint16_t slider_pos_o;
  LCD_setSubDrawArea(x1, y1, x2, y2 + 1);

  uint16_t sirka = 0;
  sirka = y2 - y1;

  // new slider position
  slider_pos = (int32_t)(((float)value/(float)param)*((float)(x2 - x1 - slider_size)));
  if (slider_pos > (x2 - x1 - slider_size)) {
    slider_pos = (x2 - x1 - slider_size);
  }

  // old slider position
  slider_pos_o = (int32_t)(((float)oldval/(float)param)*((float)(x2 - x1 - slider_size)));
  if (slider_pos_o > (x2 - x1 - slider_size)) {
    slider_pos_o = (x2 - x1 - slider_size);
  }

  // remove old slider
  LCD_FillRect(
    x1 + slider_pos_o, y1, x1 + slider_pos_o + slider_size, y2,
    c->background_color
  );

  if ((c->pscgElements[id].grayout == 0) && (global_grayout_flag == 0)) {
    if (slider_pos >= slider_pos_o) {
      LCD_FillRect(
        x1 + slider_pos_o, y1 + sirka/4, x1 + slider_pos, y2 - sirka/4,
        c->active_color
      );
    } else {
      LCD_FillRect(
        x1 + slider_pos, y1 + sirka/4, x1 + slider_pos_o + slider_size, y2 - sirka/4,
        c->fill_color
        );
    }
    LCD_DrawRectangle(
      x1, y1 + sirka/4, x2, y2 - sirka/4,
      c->border_color
    );
    //slider
    LCD_FillRect(
      x1 + slider_pos, y1, x1 + slider_pos + slider_size, y2,
      c->active_color
    );
    LCD_DrawRectangle(
      x1 + slider_pos, y1, x1 + slider_pos + slider_size, y2,
      c->border_color
    );
  } else {
    if (slider_pos >= slider_pos_o) {
      LCD_FillRect(
        x1 + slider_pos_o, y1 + sirka/4, x1 + slider_pos, y2 - sirka/4,
        LCD_get_gray16(c->active_color)
      );
    } else {
      LCD_FillRect(
        x1 + slider_pos, y1 + sirka/4, x1 + slider_pos_o + slider_size, y2 - sirka/4,
        LCD_get_gray16(c->fill_color)
      );
    }
    LCD_DrawRectangle(
      x1, y1 + sirka/4, x2, y2 - sirka/4,
      LCD_get_gray16(c->border_color)
    );
    LCD_FillRect(
      x1 + slider_pos, y1, x1 + slider_pos + slider_size, y2,
      LCD_get_gray16(c->active_color)
    );
    LCD_DrawRectangle(
      x1 + slider_pos, y1, x1 + slider_pos + slider_size, y2,
      LCD_get_gray16(c->border_color)
    );
  }
}