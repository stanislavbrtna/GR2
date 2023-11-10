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

#define GR2_SLIDER_RADIUS 8

#ifdef GR2_USE_LEGACY_SLIDER
static void draw_slider(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t select, uint8_t grayout, gr2context *c) {
  uint16_t ac, bc, bac;
  
  if (grayout == 0) {
    ac = c->active_color;
    bc = c->border_color;
    bac = c->background_color;
  } else {
    ac = LCD_get_gray16(c->active_color);
    bc = LCD_get_gray16(c->border_color);
  }

  LCD_FillRect(x1, y1, x2, y2, ac);
  LCD_DrawRectangle(x1, y1, x2, y2, bc);
  LCD_DrawRectangle(x1 + 1, y1 + 1, x2 - 1, y2 - 1, bc);

  if (select) {
    LCD_DrawRectangle(x1 + 5, y1 + 5, x2 - 5, y2 - 5, bac);
    LCD_DrawRectangle(x1 + 6, y1 + 6, x2 - 6, y2 - 6, bac);
  }
}
#else
static void draw_slider(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t select, uint8_t grayout, gr2context *c) {
  uint16_t ac, bc, bac;
  
  if (grayout == 0) {
    ac = c->active_color;
    bc = c->border_color;
    bac = c->background_color;
  } else {
    ac = LCD_get_gray16(c->active_color);
    bc = LCD_get_gray16(c->border_color);
  }

  LCD_FillRect(x1, y1 + GR2_SLIDER_RADIUS, x2, y2 - GR2_SLIDER_RADIUS, ac);
  LCD_FillRect(x1 + GR2_SLIDER_RADIUS, y1, x2 - GR2_SLIDER_RADIUS, y1 + GR2_SLIDER_RADIUS, ac);
  LCD_FillRect(x1 + GR2_SLIDER_RADIUS, y2 - GR2_SLIDER_RADIUS, x2 - GR2_SLIDER_RADIUS, y2, ac);

  LCD_DrawRectangle(x1 + GR2_SLIDER_RADIUS, y1, x2 - GR2_SLIDER_RADIUS, y1 + 1, bc);
  LCD_DrawRectangle(x1 + GR2_SLIDER_RADIUS, y2 - 1, x2 - GR2_SLIDER_RADIUS, y2, bc);

  LCD_DrawRectangle(x1, y1 + GR2_SLIDER_RADIUS, x1 + 1, y2 - GR2_SLIDER_RADIUS, bc);
  LCD_DrawRectangle(x2 - 1, y1 + GR2_SLIDER_RADIUS, x2, y2 - GR2_SLIDER_RADIUS, bc);

  LCD_FillCirclePart(x1 + GR2_SLIDER_RADIUS, y1 + GR2_SLIDER_RADIUS, GR2_SLIDER_RADIUS, 0, bc);
  LCD_FillCirclePart(x1 + GR2_SLIDER_RADIUS, y1 + GR2_SLIDER_RADIUS, GR2_SLIDER_RADIUS - 2, 0, ac);

  LCD_FillCirclePart(x2 - GR2_SLIDER_RADIUS, y1 + GR2_SLIDER_RADIUS, GR2_SLIDER_RADIUS, 1, bc);
  LCD_FillCirclePart(x2 - GR2_SLIDER_RADIUS, y1 + GR2_SLIDER_RADIUS, GR2_SLIDER_RADIUS - 2, 1, ac);

  LCD_FillCirclePart(x1 + GR2_SLIDER_RADIUS, y2 - GR2_SLIDER_RADIUS, GR2_SLIDER_RADIUS, 2, bc);
  LCD_FillCirclePart(x1 + GR2_SLIDER_RADIUS, y2 - GR2_SLIDER_RADIUS, GR2_SLIDER_RADIUS - 2, 2, ac);

  LCD_FillCirclePart(x2 - GR2_SLIDER_RADIUS, y2 - GR2_SLIDER_RADIUS, GR2_SLIDER_RADIUS, 3, bc);
  LCD_FillCirclePart(x2 - GR2_SLIDER_RADIUS, y2 - GR2_SLIDER_RADIUS, GR2_SLIDER_RADIUS - 2, 3, ac);


  if(x2 - x1 < y2 - y1) {
    if (y2 - y1 > 48) {
      if (select) {
        bc = bac;
      }
      LCD_FillRect(x1 + 6, y1 + (y2 - y1)/2, x2 - 6, y1 + (y2 - y1)/2 + 1, bc);
      LCD_FillRect(x1 + 6, y1 + (y2 - y1)/2 - 16, x2 - 6, y1 + (y2 - y1)/2 - 16 + 1, bc);
      LCD_FillRect(x1 + 6, y1 + (y2 - y1)/2 + 16, x2 - 6, y1 + (y2 - y1)/2 + 16 + 1, bc);
    } else {
      if (select) {
        LCD_DrawRectangle(x1 + GR2_SLIDER_RADIUS, y1 + GR2_SLIDER_RADIUS, x2 - GR2_SLIDER_RADIUS, y2 - GR2_SLIDER_RADIUS, bac);
        LCD_DrawRectangle(x1 + GR2_SLIDER_RADIUS + 1, y1 + GR2_SLIDER_RADIUS + 1, x2 - GR2_SLIDER_RADIUS - 1, y2 - GR2_SLIDER_RADIUS - 1, bac);
      }
    }
  } else {
    if (x2 - x1 > 48) {
      if (select) {
        bc = bac;
      }
      LCD_FillRect(x1 + (x2 - x1)/2, y1 + 6, x1 + (x2 - x1)/2 + 1, y2 - 6, bc);
      LCD_FillRect(x1 + (x2 - x1)/2 - 16, y1 + 6, x1 + (x2 - x1)/2 + 1 - 16, y2 - 6, bc);
      LCD_FillRect(x1 + (x2 - x1)/2 + 16, y1 + 6, x1 + (x2 - x1)/2 + 1 + 16, y2 - 6, bc);
    } else {
      if (select) {
        LCD_DrawRectangle(x1 + GR2_SLIDER_RADIUS, y1 + GR2_SLIDER_RADIUS, x2 - GR2_SLIDER_RADIUS, y2 - GR2_SLIDER_RADIUS, bac);
        LCD_DrawRectangle(x1 + GR2_SLIDER_RADIUS + 1, y1 + GR2_SLIDER_RADIUS + 1, x2 - GR2_SLIDER_RADIUS - 1, y2 - GR2_SLIDER_RADIUS - 1, bac);
      }
    }
  }

  
}
#endif

void gr2_draw_slider_v(
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
  uint16_t width = x2 - x1;

  LCD_setSubDrawArea(x1, y1, x2, y2);

  LCD_FillRect(x1, y1, x2, y2, c->background_color); // clear

  slider_pos = (int32_t)(((float)value / (float)param) * ((float)(y2 - y1 - slider_size)));

  if (slider_pos > (y2 - y1 - slider_size)) {
    slider_pos = (y2 - y1 - slider_size);
  }

  if ((c->pscgElements[id].grayout == 0) && (global_grayout_flag == 0)) {
    LCD_FillRect(
      x1 + width/4, y1, x2 - width/4, y2,
      c->fill_color
    );

    LCD_FillRect(
      x1 + width/4, y1 + slider_pos, x2 - width/4, y2,
      c->active_color
    );

    LCD_DrawRectangle(
      x1 + width/4, y1, x2 - width/4, y2,
      c->border_color
    );

    // slider
    draw_slider(x1, y1 + slider_pos, x2, y1 + slider_pos + slider_size, gr2_get_select(id, c), 0, c);

  } else {
    LCD_FillRect(
      x1 + width/4, y1, x2 - width/4, y2,
      LCD_get_gray16(c->fill_color)
    );

    LCD_FillRect(
      x1 + width/4, y1 + slider_pos, x2 - width/4, y2,
      LCD_get_gray16(c->active_color)
    );

    LCD_DrawRectangle(
      x1 + width/4, y1, x2 - width/4, y2,
      LCD_get_gray16(c->border_color)
    );

    // slider
    draw_slider(x1, y1 + slider_pos, x2, y1 + slider_pos + slider_size, gr2_get_select(id, c), 1, c);
  }
}


void gr2_draw_slider_v_f(
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

  uint16_t width = x2 - x1;

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
        x1 + width/4,
        y1 + slider_pos_o,
        x2 - width/4,
        y1 + slider_pos,
        c->fill_color
      );
    } else {
      LCD_FillRect(
        x1 + width/4,
        y1 + slider_pos,
        x2 - width/4,
        y1 + slider_pos_o + slider_size + 1,
        c->active_color
      );
    }
    LCD_DrawRectangle(
      x1 + width/4,
      y1,
      x2 - width/4,
      y2,
      c->border_color
    );

    // slider
    draw_slider(x1, y1 + slider_pos, x2, y1 + slider_pos + slider_size, gr2_get_select(id, c), 0, c);
  } else {
    if (slider_pos >= slider_pos_o) {
      LCD_FillRect(
        x1 + width/4,
        y1 + slider_pos_o,
        x2 - width/4,
        y1 + slider_pos,
        LCD_get_gray16(c->fill_color)
      );
    } else {
      LCD_FillRect(
        x1 + width/4, y1 + slider_pos, x2 - width/4, y1 + slider_pos_o + slider_size + 1,
        LCD_get_gray16(c->active_color)
      );
    }
    LCD_DrawRectangle(
      x1 + width/4, y1, x2 - width/4, y2,
      LCD_get_gray16(c->border_color)
    );

    // slider
    draw_slider(x1, y1 + slider_pos, x2, y1 + slider_pos + slider_size, gr2_get_select(id, c), 1, c);
  }
}


void gr2_draw_slider_h(
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
  LCD_setSubDrawArea(x1, y1, x2, y2);

  uint16_t height = 0;
  height = y2 - y1;

  LCD_FillRect(x1, y1, x2, y2 + 1, c->background_color);

  slider_pos = (int32_t)(((float)value/(float)param)*((float)(x2 - x1 - slider_size)));

  if (slider_pos > (x2 - x1 - slider_size)) {
    slider_pos = (x2 - x1 - slider_size);
  }

  if ((c->pscgElements[id].grayout == 0) && (global_grayout_flag == 0)) {
    LCD_FillRect(
      x1, y1 + height/4, x2, y2 - height/4,
      c->active_color
    ); // upper background
    LCD_FillRect(
      x1 + slider_pos, y1 + height/4, x2, y2 - height/4,
      c->fill_color
    ); // lower background
    LCD_DrawRectangle(
      x1, y1 + height/4, x2, y2 - height/4,
      c->border_color
    ); // frame

    // slider
    draw_slider(x1 + slider_pos, y1, x1 + slider_pos + slider_size, y2, gr2_get_select(id, c), 0, c);
    
  } else {
    LCD_FillRect(
      x1, y1 + height/4, x2, y2 - height/4,
      LCD_get_gray16(c->active_color)
    );
    LCD_FillRect(
      x1 + slider_pos, y1 + height/4, x2, y2 - height/4,
      LCD_get_gray16(c->fill_color)
    );
    LCD_DrawRectangle(
      x1, y1 + height/4, x2, y2 - height/4,
      LCD_get_gray16(c->border_color)
    );
    //slider
    draw_slider(x1 + slider_pos, y1, x1 + slider_pos + slider_size, y2, gr2_get_select(id, c), 1, c);
  }
}


void gr2_draw_slider_h_f(
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
  LCD_setSubDrawArea(x1, y1, x2, y2);

  uint16_t height = 0;
  height = y2 - y1;

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
        x1 + slider_pos_o, y1 + height/4, x1 + slider_pos, y2 - height/4,
        c->active_color
      );
    } else {
      LCD_FillRect(
        x1 + slider_pos, y1 + height/4, x1 + slider_pos_o + slider_size, y2 - height/4,
        c->fill_color
        );
    }
    LCD_DrawRectangle(
      x1, y1 + height/4, x2, y2 - height/4,
      c->border_color
    );
    //slider
    draw_slider(x1 + slider_pos, y1, x1 + slider_pos + slider_size, y2, gr2_get_select(id, c), 0, c);
  } else {
    if (slider_pos >= slider_pos_o) {
      LCD_FillRect(
        x1 + slider_pos_o, y1 + height/4, x1 + slider_pos, y2 - height/4,
        LCD_get_gray16(c->active_color)
      );
    } else {
      LCD_FillRect(
        x1 + slider_pos, y1 + height/4, x1 + slider_pos_o + slider_size, y2 - height/4,
        LCD_get_gray16(c->fill_color)
      );
    }
    LCD_DrawRectangle(
      x1, y1 + height/4, x2, y2 - height/4,
      LCD_get_gray16(c->border_color)
    );
    draw_slider(x1 + slider_pos, y1, x1 + slider_pos + slider_size, y2, gr2_get_select(id, c), 1, c);
  }
}