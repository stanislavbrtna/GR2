/*
Copyright (c) 2017 Stanislav Brtna

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
#include "pscg.h"
/*
 * V tomto souboru se nachází funkce zajišťující vykreslení elementů na lcd
 * This file contains functions for drawing gui elements.
 */

#ifdef PPM_SUPPORT_ENABLED
uint16_t ppm_get_width(uint8_t *filename);
uint8_t svp_fexists(uint8_t *fname);
#endif

uint16_t background_color; //for set text fit

#define PSCG_STYLE2
//#define PSCG_STYLE2_BTN


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
#ifndef PSCG_STYLE2_BTN
  if (c->pscgElements[id].grayout == 0) {
    if((active == 1) && (c->pscgElements[id].pre_active == 0)) {
      LCD_FillRect(x1, y1, x2, y2, c->active_color);
    }else if (active == 0) {
      if ((c->pscgElements[id].status_reg & GR2_GHOST_B) == 0) {
        LCD_FillRect(x1, y1, x2, y2, c->fill_color);
      } else {
        LCD_FillRect(x1, y1, x2, y2, c->background_color);
      }
    }
    LCD_DrawRectangle(x1,y1,x2,y2,c->border_color);
    LCD_DrawRectangle(x1+1,y1+1,x2-1,y2-1,c->border_color);
    LCD_DrawText_ext(x1+c->pscgElements[id].param,y1+PSCG_TEXT_Y_GAP,c->text_color, str);
    if (c->pscgElements[id].status_reg & GR2_SELECT_B) {
      LCD_DrawRectangle(x1 + 5, y1 + 4, x2 - 5, y2 - 4, c->active_color);
      LCD_DrawRectangle(x1 + 4, y1 + 3, x2 - 4, y2 - 3, c->active_color);
    }
  }  else {
    LCD_FillRect(x1, y1, x2, y2, LCD_get_gray16(c->fill_color));
    LCD_DrawRectangle(x1, y1, x2, y2, LCD_get_gray16(c->border_color));
    LCD_DrawRectangle(x1 + 1, y1 + 1, x2 - 1, y2 - 1, LCD_get_gray16(c->border_color));
    LCD_DrawText_ext(x1 + c->pscgElements[id].param, y1 + PSCG_TEXT_Y_GAP, LCD_get_gray16(c->text_color), str);
  }
#else
  //DP view
  if ((active == 1) && (c->pscgElements[id].pre_active == 0)) {
    //LCD_FillRect(x1,y1,x2,y2,fill_color);
    LCD_DrawRectangle(x1, y1, x2, y2, active_color);
  }
  else if (active == 0) {
    LCD_FillRect(x1, y1, x2, y2, background_color);
    LCD_FillRect(x1 + 2, y1 + 2, x2 - 2, y1 + 2 + (y2 - y1) / 3, fill_color);
  }
  LCD_DrawRectangle(x1, y1, x2, y2, border_color);
  LCD_DrawText_ext(x1 + 10, y1 + 5, text_color, str);
#endif
  LCD_Set_Sys_Font(curr_font);
  c->pscgElements[id].pre_active = active;
}

void pscg_draw_cbutton(
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
#ifndef PSCG_STYLE2_BTN
  if (c->pscgElements[id].grayout == 0)  {
    if ((active == 1) && (c->pscgElements[id].pre_active == 0)) {
      LCD_FillRect(x1, y1, x2, y2, c->active_color);
    } else if (active == 0) {
      LCD_FillRect(x1, y1, x2, y2, c->pscgElements[id].value);
    }
    LCD_DrawRectangle(x1, y1, x2, y2, c->border_color);
    LCD_DrawRectangle(x1 + 1, y1 + 1, x2 - 1, y2 - 1, c->border_color);
    LCD_DrawText_ext(x1 + 10, y1 + PSCG_TEXT_Y_GAP, ~c->pscgElements[id].value, str);
  }  else {
    LCD_FillRect(x1, y1, x2, y2, LCD_get_gray16(c->pscgElements[id].value));
    LCD_DrawRectangle(x1, y1, x2, y2, LCD_get_gray16(c->border_color));
    LCD_DrawRectangle(x1 + 1, y1 + 1, x2 - 1, y2 - 1, LCD_get_gray16(c->border_color));
    LCD_DrawText_ext(x1 + 10, y1 + PSCG_TEXT_Y_GAP, LCD_get_gray16(~c->pscgElements[id].value), str);
  }
#else
  if ((active == 1) && (c->pscgElements[id].pre_active == 0)) {
    //LCD_FillRect(x1,y1,x2,y2,fill_color);
    LCD_DrawRectangle(x1, y1, x2, y2, active_color);
  }  else if (active == 0) {
    LCD_FillRect(x1, y1, x2, y2, background_color);
    LCD_FillRect(x1 + 2, y1 + 2, x2 - 2, y1 + 2 + (y2 - y1) / 3, fill_color);
  }
  LCD_DrawRectangle(x1, y1, x2, y2, border_color);
  LCD_DrawText_ext(x1 + 10, y1 + 5, text_color, str);
#endif
  c->pscgElements[id].pre_active = active;
}


void pscg_draw_checkbox(
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

  LCD_FillRect(x1, y1, x2, y2, c->background_color);

  if (c->pscgElements[id].grayout == 0) {
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
  } else if (active == 2) {
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
  c->pscgElements[id].pre_active = active;
}

void pscg_draw_image(
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
    draw_ppm(x1, y1, c->pscgElements[id].value, c->pscgElements[id].str_value);
  }  else {
    LCD_FillRect(x1, y1, x2, y2, c->active_color);
    LCD_DrawRectangle(x1, y1, x2, y2, c->border_color);
    LCD_DrawLine(x1, y1, x2, y2, c->border_color);
    LCD_DrawLine(x1, y2, x2, y1, c->border_color);
  }
#endif
  LCD_setDrawAreaS(&area); //draw_ppm changes subdraw area, so it must be restored
}

void pscg_draw_icon(
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

  if (((x2 - x1 + 1) / 32 - 1) > ((y2 - y1 + 1) / 80)) {
    size = ((y2 - y1 + 1) / 80);
  } else {
    size = ((x2 - x1 + 1) / 32 - 1);
  }

  LCD_setSubDrawArea(x1, y1, x1 + 32 * (size + 1), y2); // set sub-draw area

  LCD_getDrawArea(&area); // store the area

  //printf("xsize: %d, ysize: %d size: %d txsize: %d ttxt: %s\n",((x2-x1)/64),((y2-y1)/80), size , (15*size)/8, pscgElements[id].str_value);

  if (size < 1) {
    pscg_error((uint8_t *)"PSCG element icon too small!\n", c);
    return;
  }

  if ((active == 1) && (c->pscgElements[id].pre_active == 0)) {
#ifdef PPM_SUPPORT_ENABLED
    if (svp_fexists(c->pscgElements[id].str_value2)) {
      svp_ppm_set_pmc(1, c->active_color);
      if (ppm_get_width(c->pscgElements[id].str_value2) == 32) {
        draw_ppm(x1, y1, size + 1, c->pscgElements[id].str_value2);
      } else if (ppm_get_width(c->pscgElements[id].str_value2) == 64) {
        draw_ppm(x1, y1, size, c->pscgElements[id].str_value2);
      }
      svp_ppm_set_pmc(0, 0);
    } else {
      // if there is no icon, will draw empty rectangle
      LCD_FillRect(x1, y1, x1 + 64 * size, y1 + 64 * size, c->active_color);
      LCD_DrawRectangle(x1, y1, x1 + 64 * size, y1 + 64 * size, c->border_color);
      LCD_DrawLine(x1, y1, x1 + 64 * size, y1 + 64 * size, c->border_color);
      LCD_DrawLine(x1, y1 + 64 * size, x1 + 64 * size, y1, c->border_color);
    }
#endif
    LCD_setDrawAreaS(&area); // draw_ppm changed the sub-draw area, so we will restore it

    // if there is no text, we will draw no rectangle
    if (c->pscgElements[id].str_value[0] == 0) {
      return;
    }

    LCD_FillRect(
      x1,
      y1 + 2 + 32 * (size + 1),
      x1 + 32 * (size + 1),
      y1 + 2 + 32 * (size + 1) + 8 * ((15 * size) / 8) + 2,
      c->active_color
    );
    LCD_DrawRectangle(
      x1,
      y1 + 2 + 32 * (size + 1),
      x1 + 32 * (size + 1),
      y1 + 2 + 32 * (size + 1) + 8 * ((15 * size) / 8) + 2,
      c->border_color
    );
    LCD_DrawText(
      x1 + 5,
      y1 + 4 + 32 * (size + 1),
      c->text_color,
      0,
      c->pscgElements[id].str_value,
      (15 * size) / 8
    );
  } else if (active == 0) {
#ifdef PPM_SUPPORT_ENABLED
    if (svp_fexists(c->pscgElements[id].str_value2)) {
      if (ppm_get_width(c->pscgElements[id].str_value2) == 32) {
        draw_ppm(x1, y1, size + 1, c->pscgElements[id].str_value2);
      } else if (ppm_get_width(c->pscgElements[id].str_value2) == 64) {
        draw_ppm(x1, y1, size, c->pscgElements[id].str_value2);
      }
    } else {
      LCD_FillRect(x1, y1, x1 + 64 * size, y1 + 64 * size, c->fill_color);
      LCD_DrawRectangle(x1, y1, x1 + 64 * size, y1 + 64 * size, c->border_color);
      LCD_DrawLine(x1, y1, x1 + 64 * size, y1 + 64 * size, c->border_color);
      LCD_DrawLine(x1, y1 + 64 * size, x1 + 64 * size, y1, c->border_color);
    }
#endif

    // if there is no string under the icon, no rectangle will be drawn
    if (c->pscgElements[id].str_value[0] == 0){
      return;
    }

    LCD_setDrawAreaS(&area); // restore sub draw area
    LCD_FillRect(
      x1,
      y1 + 2 + 32 * (size + 1),
      x1 + 32 * (size + 1),
      y1 + 2 + 32 * (size + 1) + 8 * ((15 * size) / 8) + 2,
      c->background_color
    );
    LCD_DrawRectangle(
      x1,
      y1 + 2 + 32 * (size + 1),
      x1 + 32 * (size + 1),
      y1 + 2 + 32 * (size + 1) + 8 * ((15 * size) / 8) + 2,
      c->border_color
    );
    LCD_DrawText(
      x1 + 5,
      y1 + 4 + 32 * (size + 1),
      c->text_color,
      0,
      c->pscgElements[id].str_value,
      (15 * size) / 8
    );
  }
  c->pscgElements[id].pre_active = active;
}


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

  if (c->pscgElements[id].grayout == 0) {
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

  if (c->pscgElements[id].grayout == 0) {
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

// TODO: Continue with code revision

void pscg_draw_slider_h(int16_t x1,int16_t y1,int16_t x2,int16_t y2, uint16_t slider_size,int32_t param, int32_t value, uint16_t id, gr2context * c){
  int32_t slider_pos;
  LCD_setSubDrawArea(x1,y1,x2,y2+1);

  uint16_t sirka=0;
  sirka=y2-y1;

  LCD_FillRect(x1,y1,x2,y2+1,c->background_color);

  slider_pos=(int32_t)(((float)value/(float)param)*((float)(x2-x1-slider_size)));

  if (slider_pos>(x2-x1-slider_size)){
    slider_pos=(x2-x1-slider_size);
  }

  if (c->pscgElements[id].grayout==0){
    LCD_FillRect(x1,y1+sirka/4,x2,y2-sirka/4,c->active_color); //pozadí horní
    LCD_FillRect(x1+slider_pos,y1+sirka/4,x2,y2-sirka/4,c->fill_color); //pozadí spodní
    LCD_DrawRectangle(x1,y1+sirka/4,x2,y2-sirka/4,c->border_color); //orámování
    //slider
    LCD_FillRect(x1+slider_pos,y1,x1+slider_pos+slider_size,y2,c->active_color);
    LCD_DrawRectangle(x1+slider_pos,y1,x1+slider_pos+slider_size,y2,c->border_color);
  }else{
    LCD_FillRect(x1,y1+sirka/4,x2,y2-sirka/4,LCD_get_gray16(c->active_color)); //pozadí horní
    LCD_FillRect(x1+slider_pos,y1+sirka/4,x2,y2-sirka/4,LCD_get_gray16(c->fill_color)); //pozadí spodní
    LCD_DrawRectangle(x1,y1+sirka/4,x2,y2-sirka/4,LCD_get_gray16(c->border_color)); //orámování
    //slider
    LCD_FillRect(x1+slider_pos,y1,x1+slider_pos+slider_size,y2,LCD_get_gray16(c->active_color));
    LCD_DrawRectangle(x1+slider_pos,y1,x1+slider_pos+slider_size,y2,LCD_get_gray16(c->border_color));
  }

}

void pscg_draw_slider_h_f(int16_t x1,int16_t y1,int16_t x2,int16_t y2, uint16_t slider_size,int32_t param, int32_t value, int32_t oldval, uint16_t id, gr2context * c){
  uint16_t slider_pos;
  uint16_t slider_pos_o;
  LCD_setSubDrawArea(x1,y1,x2,y2+1);

  uint16_t sirka=0;
  sirka=y2-y1;

  //pozice nového slideru
  slider_pos=(int32_t)(((float)value/(float)param)*((float)(x2-x1-slider_size)));
  if (slider_pos>(x2-x1-slider_size)){
    slider_pos=(x2-x1-slider_size);
  }

  //pozice starého slideru
  slider_pos_o=(int32_t)(((float)oldval/(float)param)*((float)(x2-x1-slider_size)));
  if (slider_pos_o>(x2-x1-slider_size)){
    slider_pos_o=(x2-x1-slider_size);
  }

  //výmaz slideru
  LCD_FillRect(x1+slider_pos_o,y1,x1+slider_pos_o+slider_size,y2+1,c->background_color);

  if (c->pscgElements[id].grayout==0){
    if (slider_pos>=slider_pos_o){
      LCD_FillRect(x1+slider_pos_o,y1+sirka/4,x1+slider_pos,y2-sirka/4,c->active_color); //pozadí horní active_color
    }else{
      LCD_FillRect(x1+slider_pos,y1+sirka/4,x1+slider_pos_o+slider_size,y2-sirka/4,c->fill_color); //pozadí spodní
    }
    LCD_DrawRectangle(x1,y1+sirka/4,x2,y2-sirka/4,c->border_color); //orámování
    //slider
    LCD_FillRect(x1+slider_pos,y1,x1+slider_pos+slider_size,y2,c->active_color);
    LCD_DrawRectangle(x1+slider_pos,y1,x1+slider_pos+slider_size,y2,c->border_color);
  }else{
    if (slider_pos>=slider_pos_o){
      LCD_FillRect(x1+slider_pos_o,y1+sirka/4,x1+slider_pos,y2-sirka/4,LCD_get_gray16(c->active_color)); //pozadí horní active_color
    }else{
      LCD_FillRect(x1+slider_pos,y1+sirka/4,x1+slider_pos_o+slider_size,y2-sirka/4,LCD_get_gray16(c->fill_color)); //pozadí spodní
    }
    LCD_DrawRectangle(x1,y1+sirka/4,x2,y2-sirka/4,LCD_get_gray16(c->border_color)); //orámování
    //slider
    LCD_FillRect(x1+slider_pos,y1,x1+slider_pos+slider_size,y2,LCD_get_gray16(c->active_color));
    LCD_DrawRectangle(x1+slider_pos,y1,x1+slider_pos+slider_size,y2,LCD_get_gray16(c->border_color));
  }

}

void pscg_draw_progbar_v(int16_t x1,int16_t y1,int16_t x2,int16_t y2,int32_t param, int32_t value, gr2context * c){
  uint16_t slider_pos;
  LCD_setSubDrawArea(x1,y1,x2,y2);

  slider_pos=(uint16_t)(((float)value/(float)param)*((float)(y2-y1)));

  if (slider_pos>(y2-y1)){
    slider_pos=(y2-y1);
  }
  //pozadí
  LCD_FillRect(x1,y1,x2,y1+slider_pos,c->fill_color);

  //slider
  LCD_FillRect(x1,y1+slider_pos,x2,y2,c->active_color);
  LCD_DrawLine(x1,y1+slider_pos,x2,y1+slider_pos, c->border_color);

  //orámování
  LCD_DrawRectangle(x1,y1,x2,y2,c->border_color);
  LCD_DrawRectangle(x1+1,y1+1,x2-1,y2-1,c->border_color);
}


void pscg_draw_progbar_h(int16_t x1,int16_t y1,int16_t x2,int16_t y2,int32_t param, int32_t value, gr2context * c){
  uint16_t slider_pos;
  LCD_setSubDrawArea(x1,y1,x2,y2);

  slider_pos=(int32_t)(((float)value/(float)param)*((float)(x2-x1)));

  if (slider_pos>(x2-x1)){
    slider_pos=(x2-x1);
  }
  //pozadí
  LCD_FillRect(x1 + slider_pos,y1 ,x2 ,y2 ,c->fill_color);


  //slider
  LCD_FillRect(x1, y1, x1 + slider_pos, y2, c->active_color);
  LCD_DrawLine(x1 + slider_pos, y1, x1 + slider_pos, y2, c->border_color);

  //orámování
  LCD_DrawRectangle(x1,y1,x2,y2,c->border_color);
  LCD_DrawRectangle(x1+1,y1+1,x2-1,y2-1,c->border_color);
}

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
    uint16_t id,
    gr2context * c
) {
  //uint16_t strPrac = 0;
  LCD_setSubDrawArea(x1, y1, x2, y2);
  background_color = c->background_color;
#ifndef PSCG_STYLE2
  if (active == 1) {
    LCD_FillRect(x1, y1, x2, y2, fill_color);
    LCD_FillRect(x1 + 10 + ((y2 - y1 - 10) / 8) * 8 * cursor, y1 + 5 , \
                x1 + 10 + ((y2 - y1 - 10) / 8) * 8 * (cursor + 1), \
                y1 + 5 + (( y2 - y1 - 10) / 8) * 8, active_color);
  } else {
    LCD_FillRect(x1, y1, x2, y2, background_color);
  }

  if (editable){
    LCD_DrawRectangle(x1, y1, x2, y2, border_color);
  }

  LCD_DrawText(x1 + 10, y1 + 5, text_color, 0, str, (y2 - y1 - 10) / 8);
#else
  uint8_t curr_font;

  //printf("DBG font size: %u\n", font_size);
  curr_font = LCD_Get_Font_Size();
  LCD_Set_Sys_Font(font_size);

  if (c->pscgElements[id].grayout == 0) {
    if (active == 1) {
      LCD_FillRect(x1, y1, x2, y2, c->active_color); //pozadí
      //strPrac = LCD_Text_Get_Width(str, 0);
      LCD_Text_Draw_Cursor(x1 + 10, y1 + 5, str, cursor, c->text_color);
    } else {
      LCD_FillRect(x1, y1, x2, y2, c->background_color);
    }

    if (editable) {
      LCD_DrawRectangle(x1, y1, x2, y2, c->border_color);
    }

    LCD_set_fitText(fit, x2);
    LCD_DrawText_ext(x1 + 10, y1 + PSCG_TEXT_Y_GAP, c->text_color, str);
    LCD_set_fitText(0, 0);
  } else {
    if (active == 1) {
      LCD_FillRect(x1, y1, x2, y2, LCD_get_gray16(c->active_color)); //pozadí
      //strPrac = LCD_Text_Get_Width(str, 0);
      LCD_Text_Draw_Cursor(x1 + 10, y1 + 5, str, cursor, LCD_get_gray16(c->text_color));
    } else {
      LCD_FillRect(x1, y1, x2, y2, LCD_get_gray16(c->background_color));
    }

    if (editable) {
      LCD_DrawRectangle(x1, y1, x2, y2, LCD_get_gray16(c->border_color));
    }

    LCD_set_fitText(fit, x2);
    LCD_DrawText_ext(x1 + 10, y1 + PSCG_TEXT_Y_GAP, LCD_get_gray16(c->text_color), str);
    LCD_set_fitText(0, 0);
  }

  LCD_Set_Sys_Font(curr_font);
#endif
}
