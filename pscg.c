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

#define COUNT_A_B_C_D_old                                                                          \
  a = x1 + con->pscgElements[i].x1 * con->pscgScreens[scrID].x_cell -                              \
      con->pscgScreens[scrID].x_scroll_old +                                                       \
      con->pscgElements[con->pscgElements[i].screen_id].x_offset +                                 \
      con->pscgScreens[scrID].cell_space_left;                                                     \
  b = y1 + con->pscgElements[i].y1 * con->pscgScreens[scrID].y_cell -                              \
      con->pscgScreens[scrID].y_scroll_old +                                                       \
      con->pscgElements[con->pscgElements[i].screen_id].y_offset - 1 +                             \
      con->pscgScreens[scrID].cell_space_top;                                                      \
  c = x1 + con->pscgElements[i].x2 * con->pscgScreens[scrID].x_cell -                              \
      con->pscgScreens[scrID].x_scroll_old - 1 +                                                   \
      con->pscgElements[con->pscgElements[i].screen_id].x_offset -                                 \
      con->pscgScreens[scrID].cell_space_right;                                                    \
  d = y1 + con->pscgElements[i].y2 * con->pscgScreens[scrID].y_cell -                              \
      con->pscgScreens[scrID].y_scroll_old - 1 +                                                   \
      con->pscgElements[con->pscgElements[i].screen_id].y_offset - 1 -                             \
      con->pscgScreens[scrID].cell_space_bottom;

#define COUNT_A_B_C_D                                                                              \
  a = x1 + con->pscgElements[i].x1 * con->pscgScreens[scrID].x_cell -                              \
      con->pscgScreens[scrID].x_scroll +                                                           \
      con->pscgElements[con->pscgElements[i].screen_id].x_offset +                                 \
      con->pscgScreens[scrID].cell_space_left;                                                     \
  b = y1 + con->pscgElements[i].y1 * con->pscgScreens[scrID].y_cell -                              \
      con->pscgScreens[scrID].y_scroll +                                                           \
      con->pscgElements[con->pscgElements[i].screen_id].y_offset - 1 +                             \
      con->pscgScreens[scrID].cell_space_top;                                                      \
  c = x1 + con->pscgElements[i].x2 * con->pscgScreens[scrID].x_cell -                              \
      con->pscgScreens[scrID].x_scroll - 1 +                                                       \
      con->pscgElements[con->pscgElements[i].screen_id].x_offset -                                 \
      con->pscgScreens[scrID].cell_space_right;                                                    \
  d = y1 + con->pscgElements[i].y2 * con->pscgScreens[scrID].y_cell -                              \
      con->pscgScreens[scrID].y_scroll - 1 +                                                       \
      con->pscgElements[con->pscgElements[i].screen_id].y_offset - 1 -                             \
      con->pscgScreens[scrID].cell_space_bottom;

uint16_t gr2_get_element_width(uint16_t id, gr2context *con) {
  uint16_t scrID = con->pscgElements[con->pscgElements[id].screen_id].value;
  int16_t a, b, c, d;
  int16_t x1 = 0;
  int16_t y1 = 0;
  uint16_t i = id;

  COUNT_A_B_C_D
  return (uint16_t)(c - a);
}

uint16_t gr2_get_element_height(uint16_t id, gr2context *con) {
  uint16_t scrID = con->pscgElements[con->pscgElements[id].screen_id].value;
  int16_t a, b, c, d;
  int16_t x1 = 0;
  int16_t y1 = 0;
  uint16_t i = id;

  COUNT_A_B_C_D
  return (uint16_t)(d - b);
}

#ifdef PPM_SUPPORT_ENABLED
uint8_t svp_fexists(uint8_t *fname);
uint8_t
sda_draw_p16_scaled(uint16_t x, uint16_t y, int16_t scale_w, int16_t scale_h, uint8_t *filename);
#endif

void gr2_draw_screen_bg(int16_t x1,
                        int16_t y1,
                        int16_t x2,
                        int16_t y2,
                        int16_t imgX1,
                        int16_t imgY1,
                        uint16_t id,
                        gr2context *c) {
  LCD_drawArea area;
  LCD_getDrawArea(&area);
  LCD_setSubDrawArea(x1, y1, x2, y2 + 1);

#ifdef PPM_SUPPORT_ENABLED
  if (svp_fexists(c->pscgElements[id].str_value)) {
    sda_draw_p16_scaled(imgX1,
                        imgY1,
                        c->pscgElements[id].param,
                        c->pscgElements[id].param,
                        c->pscgElements[id].str_value);
  } else {
    LCD_FillRect(x1, y1, x2, y2, c->fillColor);
    LCD_DrawRectangle(x1, y1, x2, y2, c->borderColor);
    LCD_DrawLine(x1, y1, x2, y2, c->borderColor);
    LCD_DrawLine(x1, y2, x2, y1, c->borderColor);
  }
#else
  LCD_FillRect(x1, y1, x2, y2, c->backgroundColor);
#endif
  LCD_setDrawAreaS(&area); // draw_ppm changes subdraw area, so it must be restored
}

void gr2_draw_screen(
    int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t screen, uint8_t all, gr2context *con) {
  LCD_drawArea area;
  uint16_t i, scrID;
  int16_t a, b, c, d;
  uint8_t draw_frame_flag = 0;
  uint16_t global_grayout_flag;
  uint16_t backgroundColor;

  if (screen > con->elementsMax) {
    gr2_error((uint8_t *)"id out of bounds.", con);
    printf("%s: id out of bounds.\n", __FUNCTION__);
    return;
  }

  LCD_setSubDrawArea(x1, y1, x2, y2);

  if (con->pscgElements[screen].modified) {
    all = con->pscgElements[screen].modified; // override draw mode
    draw_frame_flag = 1;                      // redraw frame
  }

  if (gr2_get_global_grayout_flag() || (con->pscgElements[screen].grayout == 1)) {
    backgroundColor = LCD_get_gray16(con->backgroundColor);
  } else {
    backgroundColor = con->backgroundColor;
  }

  global_grayout_flag = gr2_get_global_grayout_flag();
  if ((global_grayout_flag == 0) && (con->pscgElements[screen].grayout == 1)) {
    gr2_set_global_grayout_flag(1);
  }

  LCD_getDrawArea(&area);
  scrID = con->pscgElements[screen].value;

  if (all == GR2_REDRAW_ALL) {
    draw_frame_flag = 1;
    if (con->pscgElements[screen].str_value != 0 &&
        gr2_strcmp(con->pscgElements[screen].str_value, (uint8_t *)"") != 1) {
      gr2_draw_screen_bg(x1, y1, x2, y2, x1, y1, screen, con);
    } else {
      LCD_FillRect(x1, y1, x2, y2, backgroundColor);
    }
  } else if (all == GR2_REDRAW_SCROLLED) {
    for (i = 1; i <= con->maxElementsId; i++) {
      if ((con->pscgElements[i].screen_id == screen) && (i != screen) &&
          (con->pscgElements[i].valid == 1)) {

        if ((x1 > 480) && (x1 > x2)) {
          x1 = 0;
        }

        if ((y1 > 480) && (y1 > y2)) {
          y1 = 0;
        }

        COUNT_A_B_C_D_old if (con->pscgElements[screen].param2 == 0) {
          if (con->pscgElements[screen].str_value != 0 &&
              !gr2_strcmp(con->pscgElements[screen].str_value, (uint8_t *)"")) {
            gr2_draw_screen_bg(a, b, c + 1, d, x1, y1, screen, con);
          } else {
            LCD_FillRect(a, b, c + 1, d, backgroundColor);
          }
        }
      }
    }
    con->pscgScreens[scrID].x_scroll_old = con->pscgScreens[scrID].x_scroll;
    con->pscgScreens[scrID].y_scroll_old = con->pscgScreens[scrID].y_scroll;

    all = 1; // redraw all elements again
  }

  // handle elements previously marked as invisible
  if (con->invisibleFlag == 1) {
    for (i = 1; i <= con->maxElementsId; i++) {
      if (con->pscgElements[i].screen_id == screen && i != screen &&
          con->pscgElements[i].valid == 1 && con->pscgElements[i].visible == 0 &&
          con->pscgElements[i].modified == 1) {
        COUNT_A_B_C_D
        if (con->pscgElements[screen].str_value != 0 &&
            gr2_strcmp(con->pscgElements[screen].str_value, (uint8_t *)"") != 1) {
          gr2_draw_screen_bg(a, b, c, d, x1, y1, screen, con);
        } else {
          LCD_FillRect(a, b, c, d, backgroundColor);
        }
        con->pscgElements[i].modified = 0;
      }
    }
  }

  for (i = 1; i <= con->maxElementsId; i++) {
    if (!(con->pscgElements[i].screen_id == screen && i != screen &&
          con->pscgElements[i].valid == 1 && con->pscgElements[i].visible == 1)) {
      if (con->pscgElements[i].screen_id == screen && i != screen &&
          con->pscgElements[i].valid == 1 && con->pscgElements[i].visible == 0) {
        // clear flag for the modified invisible element
        con->pscgElements[i].modified = 0;
      }

      LCD_setDrawAreaS(&area);
      continue;
    }

    // skip drawing elements outside the screen
    COUNT_A_B_C_D
    if ((a > x2 + 1) || (b > y2 + 1) || (c < x1 - 1) || (d < y1 - 1)) {
      continue;
    }

    if (con->pscgElements[i].modified == 1) {
      draw_frame_flag = 1;
    }

    // Screen
    if (con->pscgElements[i].type == GR2_TYPE_SCREEN) {
      COUNT_A_B_C_D
      // printf("PSCGdbg: DrawScreen a:%u b:%u c:%u d:%u id:%u mode: ", a,b,c,d,
      // i);
      if (all == GR2_REDRAW_ALL) {
        gr2_draw_screen(a, b, c, d, i, 1, con);
      } else if (con->pscgElements[i].modified) {
        // printf("modified\n");
        gr2_draw_screen(a, b, c, d, i, con->pscgElements[i].modified, con);
        con->pscgElements[i].modified = 0;
      } else {
        // printf("basic redraw\n");
        gr2_draw_screen(a, b, c, d, i, 0, con);
      }
    }
    // Button
    if (con->pscgElements[i].type == GR2_TYPE_BUTTON) {
      COUNT_A_B_C_D
      if ((all == 1) || (con->pscgElements[i].modified == 1)) {
        if ((i == con->activeElement) || (con->pscgElements[i].value == 1)) {
          gr2_draw_button(a, b, c, d, con->pscgElements[i].str_value, 1, i, con);
        } else {
          gr2_draw_button(a, b, c, d, con->pscgElements[i].str_value, 0, i, con);
        }
        // printf("drawing button %s\n", con->pscgElements[i].str_value);
        con->pscgElements[i].modified = 0;
      }
    }
    // Text
    if (con->pscgElements[i].type == GR2_TYPE_TEXT) {
      COUNT_A_B_C_D
      if ((all == 1) || (con->pscgElements[i].modified == 1)) {
        if (con->pscgElements[screen].str_value != 0 && all == 0 &&
            gr2_strcmp(con->pscgElements[screen].str_value, (uint8_t *)"") != 1) {
          gr2_draw_screen_bg(a, b, c + 1, d, x1, y1, screen, con);
        }
        gr2_draw_text(a, b, c, d, i, con);
        con->pscgElements[i].modified = 0;
      }
    }
    // Progbar
    if (con->pscgElements[i].type == GR2_TYPE_PROGBAR) {
      COUNT_A_B_C_D
      if ((all == 1) || (con->pscgElements[i].modified == 1)) {
        if ((c - a) < (d - b)) {
          gr2_draw_progbar_v(
              a, b, c, d, con->pscgElements[i].param, con->pscgElements[i].value, i, con);
        } else {
          gr2_draw_progbar_h(
              a, b, c, d, con->pscgElements[i].param, con->pscgElements[i].value, i, con);
        }
        con->pscgElements[i].modified = 0;
      }
    }
    // Icon
    if (con->pscgElements[i].type == GR2_TYPE_ICON) {
      COUNT_A_B_C_D
      if ((all == 1) || (con->pscgElements[i].modified == 1)) {
        if ((i == con->activeElement) || (con->pscgElements[i].value == 1)) {
          gr2_draw_icon(a, b, c, d, 1, i, con);
        } else {
          gr2_draw_icon(a, b, c, d, 0, i, con);
        }
        con->pscgElements[i].modified = 0;
      }
    }
    // Slider V
    if (con->pscgElements[i].type == GR2_TYPE_SLIDER_V) {
      COUNT_A_B_C_D
      if (all == 1 ||
          (con->pscgElements[i].modified == 1 &&
           con->pscgElements[i].value == con->pscgElements[i].prev_val)) {
        gr2_draw_slider_v(a,
                          b,
                          c,
                          d,
                          con->pscgElements[i].param2,
                          con->pscgElements[i].param,
                          con->pscgElements[i].value,
                          i,
                          con);
      } else if (con->pscgElements[i].modified != 0) {
        gr2_draw_slider_v_f(a,
                            b,
                            c,
                            d,
                            con->pscgElements[i].param2,
                            con->pscgElements[i].param,
                            con->pscgElements[i].value,
                            con->pscgElements[i].prev_val,
                            i,
                            con);
      }
      con->pscgElements[i].modified = 0;
    }
    // Slider H
    if (con->pscgElements[i].type == GR2_TYPE_SLIDER_H) {
      COUNT_A_B_C_D
      if (all == 1 ||
          (con->pscgElements[i].modified == 1 &&
           con->pscgElements[i].value == con->pscgElements[i].prev_val)) {
        gr2_draw_slider_h(a,
                          b,
                          c,
                          d,
                          con->pscgElements[i].param2,
                          con->pscgElements[i].param,
                          con->pscgElements[i].value,
                          i,
                          con);
      } else if (con->pscgElements[i].modified != 0) {
        gr2_draw_slider_h_f(a,
                            b,
                            c,
                            d,
                            con->pscgElements[i].param2,
                            con->pscgElements[i].param,
                            con->pscgElements[i].value,
                            con->pscgElements[i].prev_val,
                            i,
                            con);
      }
      con->pscgElements[i].modified = 0;
    }
    // Frame
    if (con->pscgElements[i].type == GR2_TYPE_FRAME) {
      COUNT_A_B_C_D
      uint16_t global_grayout_flag;

      global_grayout_flag = gr2_get_global_grayout_flag();
      if ((global_grayout_flag == 0) && (con->pscgElements[i].grayout == 1)) {
        gr2_set_global_grayout_flag(1);
      }

      uint8_t modified =
          con->pscgElements[i].modified || con->pscgElements[con->pscgElements[i].value].modified;

      if (all == 1) {
        gr2_draw_screen(a, b, c, d, con->pscgElements[i].value, GR2_REDRAW_ALL, con);
      } else if (modified) {
        gr2_draw_screen(a, b, c, d, con->pscgElements[i].value, modified, con);
        con->pscgElements[i].modified = 0;
        con->pscgElements[con->pscgElements[i].value].modified = 0;
      } else {
        gr2_draw_screen(a, b, c, d, con->pscgElements[i].value, GR2_REDRAW_MODIFIED, con);
      }

      gr2_set_global_grayout_flag(global_grayout_flag);
    }
    // ColorButton
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
    // Checkbox
    if (con->pscgElements[i].type == GR2_TYPE_CHECKBOX) {
      COUNT_A_B_C_D
      if ((all == 1) || (con->pscgElements[i].modified == 1)) {
        gr2_draw_checkbox(a,
                          b,
                          c,
                          d,
                          con->pscgElements[i].str_value,
                          (uint8_t)con->pscgElements[i].value,
                          i,
                          con);
        con->pscgElements[i].modified = 0;
      }
    }
    // Image
    if (con->pscgElements[i].type == GR2_TYPE_IMAGE) {
      COUNT_A_B_C_D
      if (all == 1 || con->pscgElements[i].modified == 1) {
        gr2_draw_image(a, b, c, d, i, con);
        con->pscgElements[i].modified = 0;
      }
    }

    LCD_setDrawAreaS(&area);
  }

  if (draw_frame_flag == 1) {
    LCD_DrawRectangle(x1, y1, x2, y2, con->borderColor);
  }

  con->pscgElements[screen].modified = 0;

  gr2_set_global_grayout_flag(global_grayout_flag);
}

uint8_t touch_in_screen(
    uint16_t touch_x, uint16_t touch_y, int16_t x1, int16_t y1, int16_t x2, int16_t y2) {
  if ((touch_x > x1) && (touch_y > y1) && (touch_x < x2) && (touch_y < y2)) {
    return 1;
  } else {
    return 0;
  }
}

uint8_t touch_in_element(uint16_t touch_x,
                         uint16_t touch_y,
                         int16_t x1,
                         int16_t y1,
                         int16_t x2,
                         int16_t y2,
                         uint16_t i,
                         uint16_t screen,
                         gr2EventType event,
                         gr2context *con) {
  int16_t a, b, c, d;
  uint16_t scrID;
  (void)(x2);
  (void)(y2);

  scrID = con->pscgElements[screen].value;

  COUNT_A_B_C_D

  if (con->pscgElements[i].grayout == 0 && touch_x > a && touch_x < c && touch_y > b &&
      touch_y < d) {
    if ((con->pscgElements[i].type == GR2_TYPE_SCREEN) ||
        (con->pscgElements[i].type == GR2_TYPE_FRAME)) {
      return 1;
    } else {
      if ((con->activeElement == 0 && event == EV_PRESSED) ||
          (con->activeElement == i && event != EV_PRESSED)) {
        return 1;
      } else {
        return 0;
      }
    }
  } else {
    return 0;
  }
}

static int16_t gr2_abs(int16_t a, int16_t b) {
  if (a < 0)
    a *= -1;
  if (b < 0)
    b *= -1;

  if (a > b)
    return a - b;
  else
    return b - a;
}

static void gr2_update_scrollbars(uint16_t screen, gr2context *con) {
  uint16_t scrID = con->pscgElements[screen].value;
  if (con->pscgScreens[scrID].y_scroll_bar) {
    if (gr2_get_yscroll(screen, con) != gr2_get_value(con->pscgScreens[scrID].y_scroll_bar, con)) {
      gr2_set_value(con->pscgScreens[scrID].y_scroll_bar, gr2_get_yscroll(screen, con), con);
    }
  }

  if (con->pscgScreens[scrID].x_scroll_bar) {
    if (gr2_get_yscroll(screen, con) != gr2_get_value(con->pscgScreens[scrID].x_scroll_bar, con)) {
      gr2_set_value(con->pscgScreens[scrID].x_scroll_bar, gr2_get_xscroll(screen, con), con);
    }
  }
}

static void gr2_handle_scrollbars(uint16_t screen, gr2context *con) {
  uint16_t scrID = con->pscgElements[screen].value;
  if (con->pscgScreens[scrID].y_scroll_bar) {
    if (gr2_get_param(con->pscgScreens[scrID].y_scroll_bar, con) !=
        con->pscgScreens[scrID].y_scroll_max) {
      gr2_set_param(
          con->pscgScreens[scrID].y_scroll_bar, con->pscgScreens[scrID].y_scroll_max, con);
    }

    if (gr2_get_event(con->pscgScreens[scrID].y_scroll_bar, con)) {
      if (gr2_get_value(con->pscgScreens[scrID].y_scroll_bar, con) !=
          con->pscgScreens[scrID].y_scroll) {
        gr2_set_yscroll(screen, gr2_get_value(con->pscgScreens[scrID].y_scroll_bar, con), con);
      }
    }
    gr2_clear_event(con->pscgScreens[scrID].y_scroll_bar, con);
  }

  if (con->pscgScreens[scrID].x_scroll_bar) {
    if (gr2_get_param(con->pscgScreens[scrID].x_scroll_bar, con) !=
        con->pscgScreens[scrID].x_scroll_max) {
      gr2_set_param(
          con->pscgScreens[scrID].x_scroll_bar, con->pscgScreens[scrID].x_scroll_max, con);
    }

    if (gr2_get_event(con->pscgScreens[scrID].x_scroll_bar, con)) {
      if (gr2_get_value(con->pscgScreens[scrID].x_scroll_bar, con) !=
          con->pscgScreens[scrID].x_scroll) {
        gr2_set_xscroll(screen, gr2_get_value(con->pscgScreens[scrID].x_scroll_bar, con), con);
      }
    }

    gr2_clear_event(con->pscgScreens[scrID].x_scroll_bar, con);
  }
}

uint8_t gr2_touch_input(int16_t x1,
                        int16_t y1,
                        int16_t x2,
                        int16_t y2,
                        uint16_t touch_x,
                        uint16_t touch_y,
                        gr2EventType event,
                        uint16_t screen,
                        gr2context *con) {
  uint16_t i, scrID;
  int16_t a, b, c, d;
  uint8_t retval = 0;

  if (screen > con->elementsMax) {
    gr2_error((uint8_t *)"id out of bounds.", con);
    printf("%s: id out of bounds.\n", __FUNCTION__);
    return 0;
  }

  if (event == EV_NONE) {
    con->pscgElements[con->activeElement].modified = 1;
    con->activeElement = 0;
    return 0;
  } else if (event == EV_RELEASED) {
    con->pscgElements[con->activeElement].modified = 1;
    con->resetActiveElementFlag = 1;
  } else if ((event == EV_HOLD) && (con->activeElement != 0)) {
    i = con->activeElement;
    if (touch_in_screen(touch_x, touch_y, x1, y1, x2, y2)) { // touch in screen
      if (1 !=
          (touch_in_element(
              touch_x, touch_y, x1, y1, x2, y2, i, screen, event, con))) { // but out of element
        con->pscgElements[i].event = EV_DRAGOUT; // event dragout is not really used here
      }
    }
  }

  scrID = con->pscgElements[screen].value;

  if (touch_in_screen(touch_x, touch_y, x1, y1, x2, y2) &&
      (con->activeElement == 0 ||
       (con->pscgElements[con->activeElement].type != GR2_TYPE_SLIDER_H &&
        con->pscgElements[con->activeElement].type != GR2_TYPE_SLIDER_V &&
        !(con->pscgElements[con->activeElement].type == GR2_TYPE_TEXT &&
          gr2_get_text_active(con->activeElement, con))))) {
    if (event == EV_PRESSED) {
      con->pscgScreens[scrID].x_scroll_origin = touch_x;
      con->pscgScreens[scrID].y_scroll_origin = touch_y;
      con->pscgScreens[scrID].slideScroll = 0;
    }

    if (event == EV_HOLD) {
      int16_t val_x = gr2_abs(con->pscgScreens[scrID].x_scroll_origin, (int16_t)touch_x);
      int16_t val_y = gr2_abs(con->pscgScreens[scrID].y_scroll_origin, (int16_t)touch_y);

      if ((val_x > GR2_DRAG_TRESHOLD || val_y > GR2_DRAG_TRESHOLD) &&
          !con->pscgScreens[scrID].slideScroll) {
        con->pscgScreens[scrID].slideScroll = 1;
      }

      if (con->pscgScreens[scrID].slideScroll == 1) {
        if (con->pscgScreens[scrID].y_scroll_origin > touch_y) {
          con->pscgScreens[scrID].y_scroll_origin -= GR2_DRAG_TRESHOLD;
        } else {
          con->pscgScreens[scrID].y_scroll_origin += GR2_DRAG_TRESHOLD;
        }

        if (con->pscgScreens[scrID].x_scroll_origin > touch_x) {
          con->pscgScreens[scrID].x_scroll_origin -= GR2_DRAG_TRESHOLD;
        } else {
          con->pscgScreens[scrID].x_scroll_origin += GR2_DRAG_TRESHOLD;
        }
        con->pscgScreens[scrID].slideScroll = 2;
      }
    }

    if (event == EV_HOLD) {
      if (con->pscgScreens[scrID].slideScroll) {
        uint8_t scrolled = 0;
        // x axis
        if (con->pscgScreens[scrID].x_scroll_max != 0 ||
            con->pscgScreens[scrID].x_scroll_min != 0) {
          int16_t val = gr2_get_xscroll(screen, con) +
              ((int16_t)touch_x - con->pscgScreens[scrID].x_scroll_origin) * -1;

          if (val < con->pscgScreens[scrID].x_scroll_min) {
            gr2_set_xscroll(screen, con->pscgScreens[scrID].x_scroll_min, con);
          } else if (val > con->pscgScreens[scrID].x_scroll_max) {
            gr2_set_xscroll(screen, con->pscgScreens[scrID].x_scroll_max, con);
          } else {
            gr2_set_xscroll(screen, val, con);
          }

          con->pscgScreens[scrID].x_scroll_origin = touch_x;
          scrolled = 1;
        }

        // y axis
        if (con->pscgScreens[scrID].y_scroll_max != 0 ||
            con->pscgScreens[scrID].y_scroll_min != 0) {
          int16_t val = gr2_get_yscroll(screen, con) +
              ((int16_t)touch_y - con->pscgScreens[scrID].y_scroll_origin) * -1;
          if (val < con->pscgScreens[scrID].y_scroll_min) {
            gr2_set_yscroll(screen, con->pscgScreens[scrID].y_scroll_min, con);
          } else if (val > con->pscgScreens[scrID].y_scroll_max) {
            gr2_set_yscroll(screen, con->pscgScreens[scrID].y_scroll_max, con);
          } else {
            gr2_set_yscroll(screen, val, con);
          }
          con->pscgScreens[scrID].y_scroll_origin = touch_y;
          scrolled = 1;
        }

        if (scrolled) {
          gr2_update_scrollbars(screen, con);
          con->activeElement = 0;
          return 0;
        }
      }
    }

    if (event == EV_RELEASED) {
      con->pscgScreens[scrID].x_scroll_origin = 0;
      con->pscgScreens[scrID].y_scroll_origin = 0;

      if (con->pscgScreens[scrID].slideScroll) {
        con->pscgScreens[scrID].slideScroll = 0;
        return 0;
      }
    }
  }

  if (con->pscgScreens[scrID].x_scroll_bar || con->pscgScreens[scrID].y_scroll_bar) {
    gr2_handle_scrollbars(screen, con);
    gr2_update_scrollbars(screen, con);
  }

  for (i = 1; i <= con->maxElementsId; i++) {
    if (!(con->pscgElements[i].screen_id == screen && i != screen &&
          con->pscgElements[i].valid == 1 && con->pscgElements[i].visible == 1)) {
      continue;
    }

    if (!touch_in_screen(touch_x, touch_y, x1, y1, x2, y2)) {
      continue;
    }

    if (con->pscgElements[i].type == GR2_TYPE_SLIDER_V) {
      COUNT_A_B_C_D
      if ((touch_in_element(touch_x, touch_y, x1, y1, x2, y2, i, screen, event, con) &&
           con->activeElement == 0) ||
          (con->activeElement == i)) {
        con->pscgElements[i].event = event;
        con->pscgElements[i].prev_val = con->pscgElements[i].value;
        d -= con->pscgElements[i].param2 / 2;
        b += con->pscgElements[i].param2 / 2;

        if ((touch_y > b) && (touch_y < d)) {
          gr2_set_value(i,
                        (int32_t)(((float)(touch_y - b) * (float)con->pscgElements[i].param) /
                                  (float)(d - b)),
                        con);
        } else if ((touch_y < b) && (con->pscgElements[i].value != 0)) {
          gr2_set_value(i, 0, con);
        } else if ((touch_y > d) && con->pscgElements[i].value != con->pscgElements[i].param) {
          gr2_set_value(i, con->pscgElements[i].param, con);
        }
        if (event == EV_PRESSED) {
          con->activeElement = i;
        }
        if (event == EV_RELEASED) {
          con->activeElement = 0;
        }
        retval = 1;
      }
    }

    if (con->pscgElements[i].type == GR2_TYPE_SLIDER_H) {
      COUNT_A_B_C_D
      if ((touch_in_element(touch_x, touch_y, x1, y1, x2, y2, i, screen, event, con) &&
           con->activeElement == 0) ||
          (con->activeElement == i)) {
        con->pscgElements[i].event = event;
        con->pscgElements[i].prev_val = con->pscgElements[i].value;
        a += con->pscgElements[i].param2 / 2;
        c -= con->pscgElements[i].param2 / 2;
        if ((touch_x > a) && (touch_x < c)) {
          gr2_set_value(i,
                        (int32_t)((float)con->pscgElements[i].param) *
                            ((float)(touch_x - a) / (float)(c - a)),
                        con);
        } else if ((touch_x < a) && (con->pscgElements[i].value != 0)) {
          gr2_set_value(i, 0, con);
        } else if ((touch_x > c) && (con->pscgElements[i].value != con->pscgElements[i].param)) {
          gr2_set_value(i, con->pscgElements[i].param, con);
        }

        retval = 1;
        if (event == EV_PRESSED) {
          con->activeElement = i;
        }
        if (event == EV_RELEASED) {
          con->activeElement = 0;
        }
      }
    }

    if (con->pscgElements[i].type == GR2_TYPE_SCREEN) {
      COUNT_A_B_C_D
      retval = gr2_touch_input(a, b, c, d, touch_x, touch_y, event, i, con);
    }

    // We can skip rest of the elements on outside click
    if (!touch_in_element(touch_x, touch_y, x1, y1, x2, y2, i, screen, event, con)) {
      continue;
    }

    if (con->pscgElements[i].type == GR2_TYPE_FRAME) {
      COUNT_A_B_C_D
      retval =
          gr2_touch_input(a, b, c, d, touch_x, touch_y, event, con->pscgElements[i].value, con);
    }

    if (con->pscgElements[i].type == GR2_TYPE_BUTTON ||
        con->pscgElements[i].type == GR2_TYPE_IMAGE) {
      con->pscgElements[i].event = event;
      con->pscgElements[i].modified = 1;
      if (event == EV_PRESSED) {
        con->activeElement = i;
      }

      if (event == EV_RELEASED) {
        con->activeElement = 0;
      }
      retval = 1;
    }

    if (con->pscgElements[i].type == GR2_TYPE_ICON) {
      con->pscgElements[i].event = event;
      con->pscgElements[i].modified = 1;
      retval = 1;
      if (event == EV_PRESSED) {
        con->activeElement = i;
      }
      if (event == EV_RELEASED) {
        con->activeElement = 0;
      }
    }

    if (con->pscgElements[i].type == GR2_TYPE_CHECKBOX) {
      con->pscgElements[i].event = event;
      con->pscgElements[i].modified = 1;

      if (event == EV_PRESSED) {
        con->activeElement = i;
      }

      if (event == EV_RELEASED) {
        if (con->pscgElements[i].value) {
          con->pscgElements[i].value = 0;
        } else {
          con->pscgElements[i].value = 1;
        }
        con->activeElement = 0;
      }
      retval = 1;
    }

    if (con->pscgElements[i].type == GR2_TYPE_TEXT) {
      COUNT_A_B_C_D
      if (event == EV_PRESSED) {
        con->activeElement = i;
      }

      if (gr2_text_get_editable(i, con)) {
        if (event == EV_RELEASED) {
          if (con->textActive == 0) {
            retval = 2; // magic return value for opening the sw keyboard
          }
          gr2_activate_text(i, con);
          con->activeElement = 0;
        }
      }

      // store current absolute touch coordinates for cursor positioning
      if (con->pscgElements[i].value == 1) {
        if (gr2_text_get_align(i, con) == GR2_ALIGN_LEFT) {
          con->textMouseX = touch_x - a - con->pscgElements[i].x_offset;
        } else if (gr2_text_get_align(i, con) == GR2_ALIGN_RIGHT) {
          con->textMouseX =
              touch_x - a - (gr2_get_text_align_x(i, a, c, con->pscgElements[i].x_offset, con));
        } else if (gr2_text_get_align(i, con) == GR2_ALIGN_CENTER) {
          con->textMouseX =
              touch_x - a - (gr2_get_text_align_x(i, a, c, con->pscgElements[i].x_offset, con));
        }
        if (gr2_text_get_fit(i, con)) {
          con->textMaxWidth = c - a;
        } else {
          con->textMaxWidth = 0;
        }
        con->textMouseY = touch_y - b - 5 - con->pscgElements[i].y_offset;
      }
      con->pscgElements[i].event = event;
    }

    if (con->pscgElements[i].type == GR2_TYPE_COLOR_BUTTON) {
      con->pscgElements[i].event = event;
      con->pscgElements[i].modified = 1;
      retval = 1;
      if (event == EV_PRESSED) {
        con->activeElement = i;
      }
      if (event == EV_RELEASED) {
        con->activeElement = 0;
      }
    }
  }

  // unselect the keyboard-selected
  gr2_ki_unselect(screen, con);

  return retval;
}
