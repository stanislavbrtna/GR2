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

#define GR2_GHOST_B 512
#define GR2_SELECT_B 1024

#define GR2_TYPE_SCREEN 0
#define GR2_TYPE_BUTTON 1
#define GR2_TYPE_SLIDER_V 2
#define GR2_TYPE_TEXT 3
#define GR2_TYPE_PROGBAR 4
#define GR2_TYPE_ICON 5
#define GR2_TYPE_SLIDER_H 6

#define GR2_TYPE_FRAME 8
#define GR2_TYPE_COLOR_BUTTON 9
#define GR2_TYPE_CHECKBOX 10
#define GR2_TYPE_IMAGE 11

typedef struct {
  uint16_t type;            // use enum in the future
  int16_t x1;               // grid coordinates
  int16_t y1;
  int16_t x2;
  int16_t y2;
  volatile int32_t value;
  volatile int32_t param;
  volatile uint16_t param2; //param 2, mostly for storing font sizes
  uint8_t *str_value;
  uint8_t *str_value2;
  volatile uint16_t status_reg;
  // text:
  // bit0 - editable
  // bit1 - fit
  // TODO: move visibility and graiout to position 7, 8, also add ghost option 9 and selected 10
  uint16_t screen_id;         // id of the parent screen
  volatile uint16_t modified; // modified flag, modified elements are redrawn
  volatile int32_t prev_val;  // previous value, used for redraw
  uint8_t visible;
  uint8_t grayout;
  uint8_t valid;
  gr2EventType event;         // last event
  uint8_t pre_active;         // previous active state, used for redraw
} pscgElement;

/*
 * Element types:
 *  0 - screen - value matches its screen structure
 *  1 - button
 *  2 - slider_v
 *  3 - text
 *  4 - progbar_v
 *  5 - icon
 *  6 - slider_h
 *  7 - 2D slider - nehotovo
 *  8 - frame
 *  9 - color button
 * 10 - checkBox
 * 11 - image (ppm)
 *
 */

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

	uint8_t default_font;

	uint8_t valid;

	volatile uint16_t modified;

} pscgScreen;

typedef struct {
	uint16_t elementsUsed;
	uint16_t screensUsed;

	uint16_t elementsMax;
	uint16_t screensMax;

	pscgElement *pscgElements;

	pscgScreen *pscgScreens;

	uint16_t maxElementsId;

	uint8_t textActive;
	uint16_t textActiveId;

	uint8_t invisible_flag;

	uint16_t textMouseX;
	uint16_t textMouseY;

	uint16_t default_grid_size;
	uint16_t default_grid_spacing;

	uint8_t pscg_active_element;

	uint8_t sliderRedrawHotfix;

	uint8_t relative_init;

	uint16_t border_color;     // black
	uint16_t text_color;       // black
	uint16_t background_color; // red;
	uint16_t fill_color;       // green
	uint16_t active_color;     // white
} gr2context;

#endif
