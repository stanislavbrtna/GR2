/*
Copyright (c) 2023 Stanislav Brtna

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

#include "GR2.h"

// handles cursor for text field, returns 1 when block is activated, otherwise 0
uint8_t gr2_cursor_handler(uint16_t id, uint32_t ms_counter, gr2context * con) {
  static uint32_t blockEventTimer;
  static uint16_t cursor_pre;

  // not active? return  
  if (!gr2_get_value(id, con)) {
    return 0;
  }

  // touch event handling
  if ((gr2_get_event(id, con) == EV_PRESSED || gr2_get_event(id, con) == EV_RELEASED)
        && (gr2_text_get_pwd(id, con) == 0))
  {
    uint16_t temp;
    uint8_t curr_font;
    curr_font = LCD_Get_Font_Size();
    LCD_Set_Sys_Font(gr2_get_param2(id, con));

    temp = LCD_Text_Get_Cursor_Pos(
      gr2_get_str(id, con),
      gr2_get_tmx(con) - con->textXScroll,
      gr2_get_tmy(con) - con->textYScroll,
      gr2_get_text_max_width(con)
    );
    LCD_Set_Sys_Font(curr_font);

    if ((con->textBlockStart != 0 || con->textBlockEnd != 0)
        && temp > con->textBlockStart - 1
        && temp < con->textBlockEnd - 1
    ) {
      blockEventTimer = 0;
      gr2_set_event(id, EV_NONE, con);
      return 1;
    } else {
        gr2_set_param(id, temp, con);
        if (gr2_get_event(id, con) == EV_PRESSED) {
          blockEventTimer = ms_counter;
          con->textBlockStart = 0;
          con->textBlockEnd = 0;
          cursor_pre = temp;
        }
    }
    //printf("t: %u bs: %u be: %u\n", temp, con->textBlockStart, con->textBlockEnd);
  }
  
  if ((gr2_get_event(id, con) == EV_HOLD)
        && (gr2_text_get_pwd(id, con) == 0))
  {
    uint16_t temp;
    uint8_t curr_font;
    curr_font = LCD_Get_Font_Size();
    LCD_Set_Sys_Font(gr2_get_param2(id, con));

    temp = LCD_Text_Get_Cursor_Pos(
      gr2_get_str(id, con),
      gr2_get_tmx(con) - con->textXScroll,
      gr2_get_tmy(con) - con->textYScroll,
      gr2_get_text_max_width(con)
    );
    
    LCD_Set_Sys_Font(curr_font);

    if (gr2_get_block_enable(id, con)) {
      if (blockEventTimer != 0) {
        
        //printf("t: %u tp: %u\n", temp, cursor_pre);
        if (temp != cursor_pre) {
          blockEventTimer = ms_counter;
          if (temp > gr2_get_param(id, con)) {
            con->textBlockStart = gr2_get_param(id, con) + 1;
            con->textBlockEnd = temp;
          } else {
            con->textBlockStart = temp + 1;
            con->textBlockEnd = gr2_get_param(id, con);
          }
          //printf("param: %u, temp: %u\n", gr2_get_param(id, con), temp);
          //printf("bs: %u, be:%u\n", con->textBlockStart, con->textBlockEnd);
          gr2_set_modified(id, con);
          cursor_pre = temp;
        }
      }
    } else {
      gr2_set_param(id, temp, con);
    }

    if (blockEventTimer + 1200 <= ms_counter && blockEventTimer != 0) {
      blockEventTimer = 0;
      return 1;
    }
  }


  uint16_t scrID = con->pscgElements[con->pscgElements[id].screen_id].value;
  
  // active text auto scroll for given screen 
  if(con->pscgScreens[scrID].textAutoScroll) {
    int16_t x1 = con->pscgElements[id].x1*con->pscgScreens[scrID].x_cell-con->pscgScreens[scrID].x_scroll + con->pscgScreens[scrID].cell_space_left;
    int16_t x2 = con->pscgElements[id].x2*con->pscgScreens[scrID].x_cell-con->pscgScreens[scrID].x_scroll-1 - con->pscgScreens[scrID].cell_space_right;
    int16_t x_add = gr2_get_text_align_x(id, x1, x2, 10, con);
    int16_t width;

    if (gr2_get_param(id, con)) {
      width = (int16_t) gr2_get_text_width(id, gr2_get_param(id, con), con);
    } else {
      width = 0;
    }

    if (width + con->textXScroll + x_add + 15 > x2 - x1) {
      //printf("cursor outside! w: %d, diff: %d\n", width, x2 - x1);
      con->textXScroll -= 10;
      gr2_set_modified(id, con);
      blockEventTimer = 0;
    }

    if (width + con->textXScroll + x_add - 15 < x1 && con->textXScroll < 0) {
      //printf("cursor outside 2! w+xs: %d, x1: %d\n", width + con->textXScroll, x1);
      con->textXScroll += 10;
      gr2_set_modified(id, con);
      blockEventTimer = 0;
    }
  }

  con->pscgElements[id].event = EV_NONE;

  return 0;
}


uint16_t gr2_get_text_width(uint16_t id, uint16_t pos, gr2context * c) {
  uint16_t w;
  uint16_t h;
  uint16_t max_w = 0;

  uint8_t currFont = LCD_Get_Font_Size();
  LCD_Set_Sys_Font(c->pscgElements[id].param2);

  if(gr2_text_get_fit(id, c)) {
    uint16_t scrID = c->pscgElements[c->pscgElements[id].screen_id].value;
    int16_t x1 =c->pscgElements[id].x1*c->pscgScreens[scrID].x_cell-c->pscgScreens[scrID].x_scroll + c->pscgScreens[scrID].cell_space_left;
    int16_t x2 =c->pscgElements[id].x2*c->pscgScreens[scrID].x_cell-c->pscgScreens[scrID].x_scroll-1 - c->pscgScreens[scrID].cell_space_right;
    max_w = x2 - x1; 
  }

  LCD_Text_Get_WH(c->pscgElements[id].str_value, pos, max_w, &w, &h);

  LCD_Set_Sys_Font(currFont);

  return w;
}


uint16_t gr2_get_text_height(uint16_t id, uint16_t pos, gr2context * c) {
  uint16_t w;
  uint16_t h;
  uint16_t max_w = 0;

  uint8_t currFont = LCD_Get_Font_Size();
  LCD_Set_Sys_Font(c->pscgElements[id].param2);

  if(gr2_text_get_fit(id, c)) {

    uint16_t scrID = c->pscgElements[c->pscgElements[id].screen_id].value;
    int16_t x1 =c->pscgElements[id].x1*c->pscgScreens[scrID].x_cell + c->pscgScreens[scrID].cell_space_left;
    int16_t x2 =c->pscgElements[id].x2*c->pscgScreens[scrID].x_cell - c->pscgScreens[scrID].cell_space_right;
    max_w = x2 - x1;
  }

  LCD_Text_Get_WH(c->pscgElements[id].str_value, pos, max_w, &w, &h);

  h += LCD_Draw_Get_Font_Height();

  LCD_Set_Sys_Font(currFont);

  return h;
}