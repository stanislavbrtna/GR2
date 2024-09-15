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

#define H_OFFSET 8
#define V_OFFSET 4

static void draw_text_box(int32_t x1, int32_t y1, int32_t x2, uint8_t state, uint16_t id, uint8_t align, gr2context *c) {
  uint16_t bc, fc, ac, tc, ba;

  int16_t text_start;
  int16_t text_stop;

  uint8_t curr_font;
  curr_font = LCD_Get_Font_Size();

  if (state == 2) { //grayout
    bc = LCD_get_gray16(c->border_color);
    fc = LCD_get_gray16(c->fill_color);
    ac = LCD_get_gray16(c->active_color);
    tc = LCD_get_gray16(c->text_color);
    ba = LCD_get_gray16(c->background_color);
  } else {
    bc = c->border_color;
    fc = c->fill_color;
    ac = c->active_color;
    tc = c->text_color;
    ba = c->background_color;
  }

  LCD_Set_Sys_Font(c->pscgElements[id].param2);

  LCD_setSubDrawArea(x1, y1, x2, y1 + LCD_Draw_Get_Font_Height() + V_OFFSET); 

  text_start = gr2_get_text_align_x(id, x1 + H_OFFSET, x2 - H_OFFSET, 0, c);
  text_stop = text_start + LCD_Text_Get_Width(c->pscgElements[id].str_value, 0) + H_OFFSET*2 - 3;

  if(x1 + text_start < x1) {
    text_start = 0;
  }

  if(x1 + text_stop > x2) {
    text_stop = x2 - x1;
  }

  if (state == 1) {
    LCD_FillRect(
      x1 + text_start,
      y1,
      x1 + text_stop,
      y1 + LCD_Draw_Get_Font_Height() + V_OFFSET,
      ac
    );
  } else {
    LCD_FillRect(
      x1 + text_start,
      y1,
      x1 + text_stop,
      y1 + LCD_Draw_Get_Font_Height() + V_OFFSET,
      ba
    );
  }
  
  LCD_DrawText_ext(
    x1 + text_start + H_OFFSET,
    y1 + 3,
    tc,
    c->pscgElements[id].str_value
  );

  LCD_DrawRectangle(
    x1 + text_start,
    y1,
    x1 + text_stop,
    y1 + LCD_Draw_Get_Font_Height() + V_OFFSET,
    bc
  );

  LCD_Set_Sys_Font(curr_font);
}


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
  uint16_t bc, fc, ac, tc, bac;
  
  int32_t box_ystart;
  int32_t box_xstart = x1;

  int32_t img_x1 = x1;

  if ((c->pscgElements[id].grayout == 0) && (global_grayout_flag == 0)) {
    bc  = c->border_color;
    fc  = c->fill_color;
    ac  = c->active_color;
    tc  = c->text_color;
    bac = c->background_color; 
  } else {
    bc  = LCD_get_gray16(c->border_color);
    fc  = LCD_get_gray16(c->fill_color);
    ac  = LCD_get_gray16(c->active_color);
    tc  = LCD_get_gray16(c->text_color);
    bac = LCD_get_gray16(c->background_color); 
  }

  // get the image info
  int32_t img_w = 64, img_h = 64;

  if (svp_fexists(c->pscgElements[id].str_value2)) {
    img_w = sda_img_get_width(c->pscgElements[id].str_value2);
    img_h = sda_img_get_height(c->pscgElements[id].str_value2);
  }

  // compute the required icon scale width
  if(((x2 - x1 + 1) / img_w) < ((y2 - y1  + 1) / img_h)) {
    size = (x2 - x1 + 1) / img_w;
  } else {
    size = (y2 - y1  + 1) / img_h;
  }
  
  LCD_setSubDrawArea(x1, y1, x2 + 1, y2); // set sub-draw area
  LCD_getDrawArea(&area); // store the area

  //printf("size: %d, txt: %s\n", size, c->pscgElements[id].str_value);

  if(size != 0) {
    box_ystart = y1 + img_h*size + 2;
  }

  if(box_ystart > y2 && c->pscgElements[id].str_value[0] != 0) {
    printf("%s: element too small!\n", __FUNCTION__);
  }

  if(size != 0) { // center the icon
    img_x1 = x1 + (x2 - x1)/2 - (img_w*size)/2;
  }

  // special case for desription behind icon...
  if(size == 0) {
    box_ystart = y1 - c->pscgElements[id].param2/2 + img_h/4 - 3;
    box_xstart = x1 + img_w/2 + 5;
  }

  if ((active == 1) && (c->pscgElements[id].pre_active == 0)) {
#ifdef PPM_SUPPORT_ENABLED
    if (svp_fexists(c->pscgElements[id].str_value2)) {
      svp_ppm_set_pmc(1, ac);
      if (c->pscgElements[id].param != 0) {
        sda_p16_set_alpha(1, c->pscgElements[id].param - 1, bac);
      }
      sda_img_set_mix_color(1, ac);
      sda_img_draw(img_x1, y1, size, size, c->pscgElements[id].str_value2);

      sda_p16_set_alpha(0, 0, bac);
      sda_img_set_mix_color(0, ac);
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

    draw_text_box(box_xstart, box_ystart, x2, 1, id, 0, c);

  } else if (active == 0) {
#ifdef PPM_SUPPORT_ENABLED
    if (svp_fexists(c->pscgElements[id].str_value2)) {
      if (c->pscgElements[id].param != 0) {
        sda_p16_set_alpha(1, c->pscgElements[id].param - 1, bac);
      }

      if(c->pscgElements[id].grayout == 1 || global_grayout_flag) {
        sda_img_set_mix_color(1, ac);
      }
      
      sda_img_draw(img_x1, y1, size, size, c->pscgElements[id].str_value2);

      sda_img_set_mix_color(0, ac);
      sda_p16_set_alpha(0, 0, bac);
    } else {
      if (c->pscgElements[id].status_reg & GR2_SELECT_B) {
        LCD_FillRect(x1, y1, x1 + 64 * size, y1 + 64 * size, ac);
      } else {
        LCD_FillRect(x1, y1, x1 + 64 * size, y1 + 64 * size, fc);
      }

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
    
    if (c->pscgElements[id].grayout == 1 || global_grayout_flag) {
      draw_text_box(box_xstart, box_ystart, x2, 2, id, 0, c);
    } else if (c->pscgElements[id].status_reg & GR2_SELECT_B) {
      draw_text_box(box_xstart, box_ystart, x2, 1, id, 0, c);
    } else {
      draw_text_box(box_xstart, box_ystart, x2, 0, id, 0, c);
    }
  }
}