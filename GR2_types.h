/*
Copyright (c) 2019 Stanislav Brtna

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

#ifndef GR2_TYPES_H_
#define GR2_TYPES_H_

#define GR2_TEXT_EDITABLE_B 1
#define GR2_TEXT_FIT_B      2
#define GR2_SELECT_INV      4
#define GR2_BLOCK_TEXT_B  256
#define GR2_GHOST_B       512
#define GR2_SELECT_B     1024
#define GR2_TEXT_PWD_B   2048
#define GR2_T_ALIGN_B1   4096
#define GR2_T_ALIGN_B2   8192
#define GR2_ROUNDED_B   16384

#define GR2_TYPE_SCREEN        0
#define GR2_TYPE_BUTTON        1
#define GR2_TYPE_SLIDER_V      2
#define GR2_TYPE_TEXT          3
#define GR2_TYPE_PROGBAR       4
#define GR2_TYPE_ICON          5
#define GR2_TYPE_SLIDER_H      6
#define GR2_TYPE_FRAME         8
#define GR2_TYPE_COLOR_BUTTON  9
#define GR2_TYPE_CHECKBOX     10
#define GR2_TYPE_IMAGE        11

#define GR2_ALIGN_LEFT   0
#define GR2_ALIGN_RIGHT  1
#define GR2_ALIGN_CENTER 2


typedef struct {
  uint16_t type;            // use enum in the future
  int16_t  x1;              // grid coordinates
  int16_t  y1;
  int16_t  x2;
  int16_t  y2;
  volatile int32_t  value;
  volatile int32_t  prev_val; // previous value, used for redraw
  volatile int32_t  param;
  volatile uint16_t param2;   //param 2, mostly for storing font sizes
  volatile uint8_t  modified; // modified flag, modified elements are redrawn
  
  volatile uint16_t status_reg;
  // text:
  // bit0 - editable 1
  // bit1 - fit 2
  // bit2 - text select invert 4
  // bit3 8
  // bit4 16
  // bit5 32
  // bit6 64
  // bit7 128
  // bit8 - text copy/paste enabled
  // bit9 - ghost
  // bit10 - select
  // bit11 - pwd
  // bit12 - text align bit 1
  // bit13 - text align bit 2
  // bit14 - rounded mode
  // TODO: move visibility and grayout to position 7, 8
  uint8_t  *str_value;    // text value
  uint8_t  *str_value2;   // image value for button or icon
  uint16_t screen_id;     // id of the parent screen
  uint8_t  visible;
  uint8_t  grayout;
  uint8_t  valid;
  uint8_t  pre_active;    // previous active state, used for redraw
  gr2EventType event;     // last event
} gr2Element;


typedef struct {
  int16_t x_scroll;
  int16_t y_scroll;

  int16_t x_scroll_old;
  int16_t y_scroll_old;

  uint16_t x_cell;
  uint16_t y_cell;

  uint16_t cell_space_left;
  uint16_t cell_space_right;
  uint16_t cell_space_top;
  uint16_t cell_space_bottom;

  uint8_t  default_font;
  uint8_t  textAutoScroll;

  uint16_t kbd_selected;

  uint8_t  valid;

} gr2Screen;


typedef struct {
  uint16_t elementsUsed;
  uint16_t screensUsed;

  uint16_t elementsMax;
  uint16_t screensMax;

  gr2Element *pscgElements;
  gr2Screen  *pscgScreens;

  uint16_t maxElementsId;

  uint32_t textBlockStart;
  uint32_t textBlockEnd;

  uint8_t  textActive;
  uint16_t textActiveId;

  uint8_t  invisibleFlag;
  uint8_t  resetActiveElementFlag;

  int16_t  textMouseX;
  int16_t  textMouseY;
  uint16_t textMaxWidth;

  uint16_t defaultGridSize;
  uint16_t defaultGridSpacing;

  uint16_t defaultSliderSize;

  uint8_t  activeElement;

  int16_t  textXScroll;
  int16_t  textYScroll;

  uint8_t  relativeInit;
  uint8_t  roundedInit;

  uint16_t borderColor;
  uint16_t textColor;
  uint16_t backgroundColor;
  uint16_t fillColor;
  uint16_t activeColor;
} gr2context;

#endif
