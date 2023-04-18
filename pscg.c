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

#include "GR2.h"

#define COUNT_A_B_C_D_old a=x1+con->pscgElements[i].x1*con->pscgScreens[scrID].x_cell-con->pscgScreens[scrID].x_scroll_old + con->pscgScreens[scrID].cell_space_left;; \
b=y1+con->pscgElements[i].y1*con->pscgScreens[scrID].y_cell-con->pscgScreens[scrID].y_scroll_old + con->pscgScreens[scrID].cell_space_top; \
c=x1+con->pscgElements[i].x2*con->pscgScreens[scrID].x_cell-con->pscgScreens[scrID].x_scroll_old-1 - con->pscgScreens[scrID].cell_space_right; \
d=y1+con->pscgElements[i].y2*con->pscgScreens[scrID].y_cell-con->pscgScreens[scrID].y_scroll_old-1 - con->pscgScreens[scrID].cell_space_bottom; \

#define COUNT_A_B_C_D a=x1+con->pscgElements[i].x1*con->pscgScreens[scrID].x_cell-con->pscgScreens[scrID].x_scroll + con->pscgScreens[scrID].cell_space_left; \
b=y1+con->pscgElements[i].y1*con->pscgScreens[scrID].y_cell-con->pscgScreens[scrID].y_scroll + con->pscgScreens[scrID].cell_space_top; \
c=x1+con->pscgElements[i].x2*con->pscgScreens[scrID].x_cell-con->pscgScreens[scrID].x_scroll-1 - con->pscgScreens[scrID].cell_space_right; \
d=y1+con->pscgElements[i].y2*con->pscgScreens[scrID].y_cell-con->pscgScreens[scrID].y_scroll-1 - con->pscgScreens[scrID].cell_space_bottom; \


uint16_t gr2_get_element_width(uint16_t id, gr2context * con) {
  uint16_t scrID = con->pscgElements[con->pscgElements[id].screen_id].value;
  int16_t a, b, c, d;
  int16_t x1 = 0;
  int16_t y1 = 0;
  uint16_t i = id;

  COUNT_A_B_C_D

  return (uint16_t)(c - a);
}

uint16_t gr2_get_element_height(uint16_t id, gr2context * con) {
  uint16_t scrID = con->pscgElements[con->pscgElements[id].screen_id].value;
  int16_t a, b, c, d;
  int16_t x1 = 0;
  int16_t y1 = 0;
  uint16_t i = id;

  COUNT_A_B_C_D

  return (uint16_t)(d - b);
}


void gr2_draw_screen_bg(int16_t x1,
                        int16_t y1,
                        int16_t x2,
                        int16_t y2,
                        int16_t imgX1,
                        int16_t imgY1,
                        uint16_t id,
                        gr2context * c) {
  LCD_drawArea area;
  LCD_getDrawArea(&area);
  LCD_setSubDrawArea(x1, y1, x2, y2);
  

#ifdef PPM_SUPPORT_ENABLED
  if (svp_fexists(c->pscgElements[id].str_value)) {
    sda_draw_p16_scaled(imgX1, imgY1, c->pscgElements[id].param, c->pscgElements[id].param, c->pscgElements[id].str_value);
  }  else {
    LCD_FillRect(x1, y1, x2, y2, c->active_color);
    LCD_DrawRectangle(x1, y1, x2, y2, c->border_color);
    LCD_DrawLine(x1, y1, x2, y2, c->border_color);
    LCD_DrawLine(x1, y2, x2, y1, c->border_color);
  }
#else
  LCD_FillRect(x1, y1, x2, y2, c->background_color);
#endif
  LCD_setDrawAreaS(&area); //draw_ppm changes subdraw area, so it must be restored
}


void gr2_draw_screen(
                    int16_t x1,
                    int16_t y1,
                    int16_t x2,
                    int16_t y2,
                    uint16_t screen,
                    uint8_t allx,
                    gr2context * con) {
  LCD_drawArea area;
  uint16_t i, scrID;
  int16_t a, b, c, d;
  uint8_t all;
  uint8_t draw_frame_flag = 0;
  uint16_t global_grayout_flag;
  uint16_t background_color;

  if (screen > con->elementsMax) {
    gr2_error("id out of bounds.", con);
    printf("%s: id out of bounds.\n", __FUNCTION__);
    return;
  }

  LCD_setSubDrawArea(x1, y1, x2, y2);

  all = allx;
  if (con->pscgElements[screen].modified == 1) {
    all = 1;
    con->pscgElements[screen].modified = 0;
  }

  if (con->pscgElements[screen].modified) {
    draw_frame_flag = 1;
  }

  if (gr2_get_global_grayout_flag() || (con->pscgElements[screen].grayout == 1)) {
    background_color = LCD_get_gray16(con->background_color);
  } else {
    background_color = con->background_color;
  }

  global_grayout_flag = gr2_get_global_grayout_flag();
  if ((global_grayout_flag == 0) && (con->pscgElements[screen].grayout == 1)) {
    gr2_set_global_grayout_flag(1);
  }

  LCD_getDrawArea(&area);
  scrID = con->pscgElements[screen].value;

  if (all == 1) {
    draw_frame_flag = 1;
    if (con->pscgElements[screen].str_value != 0) {
      gr2_draw_screen_bg(x1, y1, x2, y2, x1, y1, screen, con);
    } else {
      LCD_FillRect(x1, y1, x2, y2, background_color);
    }
  } else if (all == 2) {
    for (i = 1; i <= con->maxElementsId; i++) {
      if ((con->pscgElements[i].screen_id == screen) && (i != screen) && (con->pscgElements[i].valid == 1)) {

        if ((x1 > 480) && (x1 > x2)) {
          x1 = 0;
        }

        if ((y1 > 480) && (y1 > y2)) {
          y1 = 0;
        }

        COUNT_A_B_C_D_old
        if (con->pscgElements[screen].str_value != 0) {
          gr2_draw_screen_bg(a, b, c + 1, d, x1, y1, screen, con);
        } else {
          LCD_FillRect(a, b, c + 1, d, background_color);
        }
      }
    }
    all = 1; //aby se znovu překreslily prvky
  }

  //zneviditelnění invisible prvků
  //set visible nastaví flag
  //flag je shozen voláním gr2_draw_end(), které by se mělo zavolat jakmile je vše potřebné vykresleno
  if (con->invisible_flag == 1) {
    for (i = 1; i <= con->maxElementsId; i++){
      if ((con->pscgElements[i].screen_id == screen)
          && (i != screen)
          && (con->pscgElements[i].valid == 1)
          && (con->pscgElements[i].visible == 0)
          && (con->pscgElements[i].modified == 1)) {

        COUNT_A_B_C_D
        if (con->pscgElements[screen].str_value != 0) {
          gr2_draw_screen_bg(a, b, c, d, x1, y1, screen, con);
        } else {
          LCD_FillRect(a, b, c, d, background_color);
        }
        con->pscgElements[i].modified = 0;
      }
    }
  }

  for (i = 1; i <= con->maxElementsId; i++) {
    if((con->pscgElements[i].screen_id == screen)
        && (i != screen)
        && (con->pscgElements[i].valid == 1)
        && (con->pscgElements[i].visible == 1)
        && (con->pscgElements[i].modified)) {
      draw_frame_flag = 1;
    }

    if ((con->pscgElements[i].screen_id == screen)
        && (i != screen)
        && (con->pscgElements[i].valid == 1)
        && (con->pscgElements[i].visible == 1)) {
      if (con->pscgElements[i].type == GR2_TYPE_SCREEN) {
        COUNT_A_B_C_D
        //printf("PSCGdbg: DrawScreen a:%u b:%u c:%u d:%u id:%u mode: ", a,b,c,d, i);
        if (all == 1) {
          //printf("all\n");
          gr2_draw_screen(a, b, c, d, i, 1, con);
        } else if (con->pscgElements[i].modified){
          //printf("modified\n");
          gr2_draw_screen(a,b,c,d,i,con->pscgElements[i].modified, con); //tohle je ok
          con->pscgElements[i].modified=0;
        } else {
          //printf("basic redraw\n");
          gr2_draw_screen(a,b,c,d,i,0, con);
        }
      }
      if (con->pscgElements[i].type == GR2_TYPE_BUTTON) {
        COUNT_A_B_C_D
        if ((all == 1) || (con->pscgElements[i].modified == 1)) {
          if ((i == con->pscg_active_element)||(con->pscgElements[i].value == 1)) {
            gr2_draw_button(a, b, c, d, con->pscgElements[i].str_value, 1, i, con);
          } else {
            gr2_draw_button(a, b, c, d, con->pscgElements[i].str_value, 0, i, con);
          }
          //printf("drawing button %s\n", con->pscgElements[i].str_value);
          con->pscgElements[i].modified = 0;
        }
      }
      if (con->pscgElements[i].type == GR2_TYPE_SLIDER_V) {
        COUNT_A_B_C_D
        if (all == 1 ||
            (con->pscgElements[i].modified == 1 && con->pscgElements[i].value == con->pscgElements[i].prev_val)
        ) {
          gr2_draw_slider_v(a,b,c,d, con->pscgElements[i].param2, con->pscgElements[i].param,con->pscgElements[i].value,i, con);
        } else if(con->pscgElements[i].modified != 0) {
          gr2_draw_slider_v_f(a,b,c,d, con->pscgElements[i].param2, con->pscgElements[i].param, con->pscgElements[i].value,con->pscgElements[i].prev_val,i,con);
        }
        con->pscgElements[i].modified = 0;
      }
      if (con->pscgElements[i].type == GR2_TYPE_TEXT) {
        COUNT_A_B_C_D
        if ((all == 1) || (con->pscgElements[i].modified == 1)) {
          //DBG
          //static uint32_t ix;
          //printf("%u redrawing: %s\n", ix, con->pscgElements[i].str_value);
          //ix++;
          if (con->pscgElements[screen].str_value != 0 && all == 0) {
            gr2_draw_screen_bg(a, b, c + 1, d, x1, y1, screen, con);
          }
          gr2_draw_text(a, b, c, d, i, con);
          con->pscgElements[i].modified = 0;
        }
      }
      if (con->pscgElements[i].type == GR2_TYPE_PROGBAR) {
        COUNT_A_B_C_D
        if ((all == 1) || (con->pscgElements[i].modified == 1)) {
          if ((c - a) < (d - b)) {
            gr2_draw_progbar_v(a,b,c,d, con->pscgElements[i].param,con->pscgElements[i].value, i, con);
          } else {
            gr2_draw_progbar_h(a,b,c,d, con->pscgElements[i].param,con->pscgElements[i].value, i, con);
          }
          con->pscgElements[i].modified = 0;
        }
      }
      if (con->pscgElements[i].type == GR2_TYPE_ICON) {
        COUNT_A_B_C_D
        if ((all == 1) || (con->pscgElements[i].modified == 1)) {
          if ((i == con->pscg_active_element) || (con->pscgElements[i].value == 1)) {
            gr2_draw_icon(a, b, c, d, 1, i, con);
          }else{
            gr2_draw_icon(a, b, c, d, 0, i, con);
          }
          con->pscgElements[i].modified = 0;
        }
      }
      if (con->pscgElements[i].type == GR2_TYPE_SLIDER_H) {
        COUNT_A_B_C_D
        if (all == 1 ||
            (con->pscgElements[i].modified == 1 && con->pscgElements[i].value == con->pscgElements[i].prev_val)
        ) {
          gr2_draw_slider_h(a, b, c, d, con->pscgElements[i].param2, con->pscgElements[i].param, con->pscgElements[i].value, i, con);
        } else if(con->pscgElements[i].modified != 0) {
          gr2_draw_slider_h_f(a,b,c,d, con->pscgElements[i].param2, con->pscgElements[i].param,con->pscgElements[i].value, con->pscgElements[i].prev_val,i, con);
        }
        con->pscgElements[i].modified = 0;
      }
      if (con->pscgElements[i].type == GR2_TYPE_FRAME) {
        COUNT_A_B_C_D
        uint16_t global_grayout_flag;

        global_grayout_flag = gr2_get_global_grayout_flag();
        if ((global_grayout_flag == 0) && (con->pscgElements[i].grayout == 1)) {
          gr2_set_global_grayout_flag(1);
        }

        if (all == 1) {
          gr2_draw_screen(a, b, c, d, con->pscgElements[i].value, 1, con);
        } else if (con->pscgElements[i].modified) {
          gr2_draw_screen(a, b, c, d, con->pscgElements[i].value, con->pscgElements[i].modified, con);
          con->pscgElements[i].modified = 0;
        } else {
          gr2_draw_screen(a, b, c, d, con->pscgElements[i].value, 0, con);
        }

        gr2_set_global_grayout_flag(global_grayout_flag);
      }
      if (con->pscgElements[i].type == GR2_TYPE_COLOR_BUTTON) {
        COUNT_A_B_C_D
        if ((all == 1) || (con->pscgElements[i].modified == 1)) {
          if ((con->pscgElements[i].event != EV_NONE)) {
            gr2_draw_cbutton(a, b, c, d, con->pscgElements[i].str_value, 1, i, con);
          } else {
            gr2_draw_cbutton(a, b, c, d, con->pscgElements[i].str_value, 0, i, con);
          }
          con->pscgElements[i].modified = 0;
        }
      }
      if (con->pscgElements[i].type == GR2_TYPE_CHECKBOX) {
        COUNT_A_B_C_D
        if ((all == 1) || (con->pscgElements[i].modified == 1)) {
          gr2_draw_checkbox(a, b, c, d, con->pscgElements[i].str_value, (uint8_t) con->pscgElements[i].value, i, con);
          con->pscgElements[i].modified = 0;
        }
      }
      if (con->pscgElements[i].type == GR2_TYPE_IMAGE) {
        COUNT_A_B_C_D
        if ((all == 1) || (con->pscgElements[i].modified == 1)) {
          gr2_draw_image(a, b, c, d, i, con);
          con->pscgElements[i].modified = 0;
        }
      }
    } else if((con->pscgElements[i].screen_id == screen)
              && (i != screen)
              && (con->pscgElements[i].valid == 1)
              && (con->pscgElements[i].visible == 0)) {
      // clear flag for the modified invisible elements
      con->pscgElements[i].modified = 0;
    }
    LCD_setDrawAreaS(&area);
  }

  if(draw_frame_flag == 1) {
    LCD_DrawRectangle(x1, y1, x2, y2, con->border_color);
  }

  gr2_set_global_grayout_flag(global_grayout_flag);
}

uint8_t touch_in_screen(
                      uint16_t touch_x,
                      uint16_t touch_y,
                      int16_t x1,
                      int16_t y1,
                      int16_t x2,
                      int16_t y2
                      ) {

  if ((touch_x > x1) && (touch_y > y1) && (touch_x < x2) && (touch_y < y2)) {
    return 1;
  } else {
    return 0;
  }
}


int16_t get_a(
            uint16_t touch_x,
            int16_t touch_y,
            int16_t x1,
            int16_t y1,
            int16_t x2,
            int16_t y2,
            uint16_t i,
            uint16_t screen,
            gr2context * con
            ) {
  uint16_t scrID;

  (void)(touch_x);
  (void)(touch_y);
  (void)(x1);
  (void)(y1);
  (void)(x2);
  (void)(y2);

  scrID = con->pscgElements[screen].value;

  return x1 + con->pscgElements[i].x1 * con->pscgScreens[scrID].x_cell
         - con->pscgScreens[scrID].x_scroll + con->pscgScreens[scrID].cell_space_left;
}

int16_t get_b(
            uint16_t touch_x,
            int16_t touch_y,
            int16_t x1,
            int16_t y1,
            int16_t x2,
            int16_t y2,
            uint16_t i,
            uint16_t screen,
            gr2context * con
            ) {
  uint16_t scrID;
  (void)(touch_x);
  (void)(touch_y);
  (void)(x1);
  (void)(y1);
  (void)(x2);
  (void)(y2);
  scrID = con->pscgElements[screen].value;

  return y1 + con->pscgElements[i].y1 * con->pscgScreens[scrID].y_cell
         - con->pscgScreens[scrID].y_scroll + con->pscgScreens[scrID].cell_space_top;
}

uint8_t touch_in_element(
            uint16_t touch_x,
            uint16_t touch_y,
            int16_t x1,
            uint16_t y1,
            int16_t x2,
            int16_t y2,
            uint16_t i,
            uint16_t screen,
            gr2EventType event,
            gr2context * con
            ) {
  int16_t a, b, c, d;
  uint16_t scrID;
  (void)(x2);
  (void)(y2);

  scrID = con->pscgElements[screen].value;

  a=x1+con->pscgElements[i].x1*con->pscgScreens[scrID].x_cell-con->pscgScreens[scrID].x_scroll + con->pscgScreens[scrID].cell_space_left;
  b=y1+con->pscgElements[i].y1*con->pscgScreens[scrID].y_cell-con->pscgScreens[scrID].y_scroll + con->pscgScreens[scrID].cell_space_top;
  c=x1+con->pscgElements[i].x2*con->pscgScreens[scrID].x_cell-con->pscgScreens[scrID].x_scroll-1 - con->pscgScreens[scrID].cell_space_right;
  d=y1+con->pscgElements[i].y2*con->pscgScreens[scrID].y_cell-con->pscgScreens[scrID].y_scroll-1 - con->pscgScreens[scrID].cell_space_bottom;

  if ((con->pscgElements[i].grayout == 0)
        && (touch_x > a)
        && (touch_x < c)
        && (touch_y > b)
        && (touch_y < d)
  ) {
    if ((con->pscgElements[i].type == GR2_TYPE_SCREEN) || (con->pscgElements[i].type == GR2_TYPE_FRAME)) {
      return 1;
    } else {
      if ((con->pscg_active_element == 0 && event == EV_PRESSED) || (con->pscg_active_element == i && event != EV_PRESSED)) {
        return 1;
      } else {
        return 0;
      }
    }
  } else {
    return 0;
  }
}

uint8_t gr2_touch_input(
            int16_t x1,
            int16_t y1,
            int16_t x2,
            int16_t y2,
            uint16_t touch_x,
            uint16_t touch_y,
            gr2EventType event,
            uint16_t screen,
            gr2context * con) {
  uint16_t i, scrID;
  int16_t a, b, c, d;
  uint8_t retval = 0;

  if (screen > con->elementsMax) {
    gr2_error("id out of bounds.", con);
    printf("%s: id out of bounds.\n", __FUNCTION__);
    return 0;
  }

  if (event == EV_NONE) {
    con->pscgElements[con->pscg_active_element].modified = 1;
    con->pscg_active_element = 0;
    return 0;
  } else if (event == EV_RELEASED) {
    con->pscgElements[con->pscg_active_element].modified = 1;
    con->reset_active_element_flag = 1;
  } else if ((event == EV_HOLD) && (con->pscg_active_element != 0)) {
    i = con->pscg_active_element;
    if (touch_in_screen(touch_x, touch_y, x1, y1, x2, y2)) { // touch in screen
      if (1 != (touch_in_element(touch_x, touch_y, x1, y1, x2, y2, i, screen, event, con))) { // but out of element
        con->pscgElements[i].event = EV_DRAGOUT; // event dragout is not really used here
      }
    }
  }

  scrID = con->pscgElements[screen].value;

  for (i = 1; i <= con->maxElementsId; i++) {
    if ((con->pscgElements[i].screen_id == screen) && (i != screen) && (con->pscgElements[i].valid == 1) && (con->pscgElements[i].visible == 1)) {
      if (con->pscgElements[i].type == GR2_TYPE_SCREEN) {
        //a musí zvostat pošahaný, aby screen zjistil, že a je pošahaný
        COUNT_A_B_C_D
        if (touch_in_screen(touch_x, touch_y, x1, y1, x2, y2)) {
          if (touch_in_element(touch_x, touch_y, x1, y1, x2, y2, i, screen, event, con)) {
            retval = gr2_touch_input(a, b, c, d, touch_x, touch_y, event, i, con);
          }
        }
      }

      if ((con->pscgElements[i].type == GR2_TYPE_BUTTON) || (con->pscgElements[i].type == GR2_TYPE_IMAGE)) {
        if (touch_in_screen(touch_x, touch_y, x1, y1, x2, y2)) {
          if (touch_in_element(touch_x, touch_y, x1, y1, x2, y2, i, screen, event, con)) {
            con->pscgElements[i].event    = event;
            con->pscgElements[i].modified = 1;
            if (event == EV_PRESSED){
              con->pscg_active_element = i;
            }

            if (event == EV_RELEASED) {
              con->pscg_active_element = 0;
            }
            retval = 1;
          }
        }
      }

      if (con->pscgElements[i].type == GR2_TYPE_CHECKBOX) {
        if (touch_in_screen(touch_x, touch_y, x1, y1, x2, y2)) {
          if (touch_in_element(touch_x, touch_y, x1, y1, x2, y2, i, screen, event, con)) {

            con->pscgElements[i].event = event;
            con->pscgElements[i].modified = 1;

            if (event == EV_PRESSED) {
              con->pscg_active_element = i;
            }

            if (event == EV_RELEASED) {
              if (con->pscgElements[i].value) {
                con->pscgElements[i].value = 0;
              } else {
                con->pscgElements[i].value = 1;
              }
              con->pscg_active_element = 0;
            }
            retval = 1;
          }
        }
      }

      if (con->pscgElements[i].type == GR2_TYPE_SLIDER_V) {
        COUNT_A_B_C_D
        if ( touch_in_screen(touch_x, touch_y, x1, y1, x2, y2)){
          if ((touch_in_element(touch_x, touch_y, x1, y1, x2, y2, i, screen, event, con) && (con->pscg_active_element == 0)) || (con->pscg_active_element == i)) {
            con->pscgElements[i].event = event;
            con->pscgElements[i].prev_val = con->pscgElements[i].value;
            d -= con->pscgElements[i].param2/2;
            b += con->pscgElements[i].param2/2;

            if ((touch_y > b) && (touch_y < d)) {
              gr2_set_value(i,(int32_t)( ((float)(touch_y-b)*(float)con->pscgElements[i].param)/(float)(d-b)), con);
            }else if((touch_y < b) && (con->pscgElements[i].value != 0)) {
              gr2_set_value(i, 0, con);
            }else if((touch_y > d) && con->pscgElements[i].value != con->pscgElements[i].param) {
              gr2_set_value(i, con->pscgElements[i].param, con);
            }
            if (event == EV_PRESSED) {
              con->pscg_active_element = i;
            }
            if (event == EV_RELEASED) {
              con->pscg_active_element = 0;
            }
            retval = 1;
          }
        }
      }

      if (con->pscgElements[i].type == GR2_TYPE_TEXT) {
        if ( touch_in_screen(touch_x, touch_y, x1, y1, x2, y2)) {
          if (touch_in_element(touch_x, touch_y, x1, y1, x2, y2, i, screen, event, con)) {

            if (event == EV_PRESSED) {
              con->pscg_active_element = i;
            }

            a = get_a(touch_x, touch_y, x1, y1, x2, y2, i, screen, con);
            b = y1 + con->pscgElements[i].y1 * con->pscgScreens[scrID].y_cell - con->pscgScreens[scrID].y_scroll;

            
            if (gr2_text_get_editable(i, con)) {
              if (event == EV_RELEASED) {
                if (con->textActive == 0) {
                  retval = 2; //magic return value for opening the sw keyboard
                }
                gr2_activate_text(i, con);
                con->pscg_active_element = 0;
              }
            }
          

            // store current absolute touch coordinates for cursor detection
            if (con->pscgElements[i].value == 1) {
              if (gr2_text_get_align(i, con) == GR2_ALIGN_LEFT) {
                con->textMouseX = touch_x - a - 10;
              } else if (gr2_text_get_align(i, con) == GR2_ALIGN_RIGHT) {
                con->textMouseX = touch_x - a - (gr2_get_text_align_x(i, x1, x2, 10, con) - 52);
              } else if (gr2_text_get_align(i, con) == GR2_ALIGN_CENTER) {
                con->textMouseX = touch_x - a - (gr2_get_text_align_x(i, x1, x2, 10, con) - 26);
              }
              con->textMouseY = touch_y - b - 5;
              con->pscgElements[i].event    = event;
            }
          }
        }
      }

      if (con->pscgElements[i].type == GR2_TYPE_ICON) {
        COUNT_A_B_C_D
        if (touch_in_screen(touch_x, touch_y, x1, y1, x2, y2)) {
          if (touch_in_element(touch_x, touch_y, x1, y1, x2, y2, i, screen, event, con)) {
            con->pscgElements[i].event    = event;
            con->pscgElements[i].modified = 1;
            retval = 1;
            if (event == EV_PRESSED) {
              con->pscg_active_element = i;
            }
            if (event == EV_RELEASED) {
              con->pscg_active_element = 0;
            }
          }
        }
      }

      if (con->pscgElements[i].type == GR2_TYPE_SLIDER_H) {
        COUNT_A_B_C_D
        if (touch_in_screen(touch_x, touch_y, x1, y1, x2, y2)) {
          if ((touch_in_element(touch_x, touch_y, x1, y1, x2, y2, i, screen, event, con) && (con->pscg_active_element == 0)) || (con->pscg_active_element == i)) {
            con->pscgElements[i].event    = event;
            con->pscgElements[i].prev_val = con->pscgElements[i].value;
            a += con->pscgElements[i].param2/2;
            c -= con->pscgElements[i].param2/2;
            if ((touch_x > a) && (touch_x < c)) {
              gr2_set_value(i, (int32_t)((float)con->pscgElements[i].param) * ((float)(touch_x - a) / (float)(c - a)), con);
            } else if((touch_x < a) && (con->pscgElements[i].value != 0)) {
              gr2_set_value(i, 0, con);
            } else if((touch_x > c) && (con->pscgElements[i].value != con->pscgElements[i].param)) {
              gr2_set_value(i, con->pscgElements[i].param, con);
            }

            retval = 1;
            if (event == EV_PRESSED) {
              con->pscg_active_element = i;
            }
            if (event == EV_RELEASED) {
              con->pscg_active_element = 0;
            }
          }
        }
      }

      if (con->pscgElements[i].type == GR2_TYPE_FRAME) {
        COUNT_A_B_C_D
        if ( touch_in_screen( touch_x, touch_y, x1, y1, x2, y2 )){
          if (touch_in_element(touch_x, touch_y, x1, y1, x2, y2, i, screen, event, con)){
            retval = gr2_touch_input(a, b, c, d, touch_x, touch_y, event, con->pscgElements[i].value, con);
          }
        }
      }

      if (con->pscgElements[i].type == GR2_TYPE_COLOR_BUTTON) {
        COUNT_A_B_C_D
        if (touch_in_screen(touch_x, touch_y, x1, y1, x2, y2)) {
          if (touch_in_element(touch_x, touch_y, x1, y1, x2, y2, i, screen, event, con)) {
            con->pscgElements[i].event    = event;
            con->pscgElements[i].modified = 1;
            retval = 1;
            if (event == EV_PRESSED) {
              con->pscg_active_element = i;
            }
            if (event == EV_RELEASED) {
              con->pscg_active_element = 0;
            }
          }
        }
      }
    }
  }

  if (retval != 0) {
    gr2_ki_unselect(screen, con);
  }

  return retval;
}
