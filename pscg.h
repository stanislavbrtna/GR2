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

#ifndef PSCG_PSCG_H_
#define PSCG_PSCG_H_

#include "GR2.h"
#include "GR2_types.h"
#include "GR2_gui_draw.h"

#include "GR2_config.h"

// GR2 context setup
void gr2_reset_context(gr2context *c);
void gr2_init_context(
                     gr2context *c,
                     gr2Element *pscgElementsArray,
                     uint16_t elementsCount,
                     gr2Screen *pscgScreens,
                     uint16_t screensCount
                    );

// screen touch input
uint8_t gr2_touch_input(
                     int16_t x1,
                     int16_t y1,
                     int16_t x2,
                     int16_t y2,
                     uint16_t touch_x,
                     uint16_t touch_y,
                     gr2EventType event,
                     uint16_t screen,
                     gr2context *con
                    );

// screen redraw
void gr2_draw_screen(
                     int16_t x1,
                     int16_t y1,
                     int16_t x2,
                     int16_t y2,
                     uint16_t screen,
                     uint8_t all,
                     gr2context *con
                    );

// after the root screen redraw, this function does a cleanup
void gr2_draw_end(gr2context * c);

// dumps screen contents to the console
void gr2_dump_screen(uint16_t id, gr2context * con);

// setting up various context defaults
void gr2_set_grid_size(uint16_t size, gr2context * c); // sets up default grid size [px]
void gr2_set_relative_init(uint8_t relativeInitEnabled, gr2context * c); // switches x1 y1 x2 y2 and x y w h coordinates
uint8_t gr2_get_relative_init(gr2context * c);

//======================== GUI element constructors ============================
uint16_t gr2_add_screen(gr2context * c);
uint16_t gr2_add_screen_ext(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t screen, gr2context * c);
uint16_t gr2_add_button(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t *str, uint16_t screen, gr2context * c);
uint16_t gr2_add_slider_v(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, int32_t param, int32_t value, uint16_t screen, gr2context * c);
uint16_t gr2_add_slider_h(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, int32_t param, int32_t value, uint16_t screen, gr2context * c);
uint16_t gr2_add_text(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t *str, uint16_t screen, gr2context * c);
uint16_t gr2_add_progbar_v(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, int32_t param, int32_t value, uint16_t screen, gr2context * c);
uint16_t gr2_add_icon(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t *str, uint8_t *icon, uint16_t screen, gr2context * c);
uint16_t gr2_add_frame(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, int32_t val, uint16_t screen, gr2context * c);
uint16_t gr2_add_cbutton(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t *str, uint16_t screen, gr2context * c);
uint16_t gr2_add_checkbox(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t *str, uint16_t screen, gr2context * c);
uint16_t gr2_add_image(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t *str, uint16_t screen, gr2context * c);

// destructors
void gr2_destroy(uint16_t id, gr2context * c);

//===================== GUI element Getters & Setters ==========================
// value
int32_t gr2_get_value(uint16_t id, gr2context * c);
void gr2_set_value(uint16_t id, int32_t val, gr2context * c);
// param
int32_t gr2_get_param(uint16_t id, gr2context * c);
void gr2_set_param(uint16_t id, int32_t val, gr2context * c);
uint16_t gr2_get_param2(uint16_t id, gr2context * c);
// screen
void gr2_set_screen(uint16_t id, uint16_t val, gr2context * c);
uint16_t gr2_get_screen(uint16_t id, gr2context *c);

// coordinates
uint16_t gr2_get_x1(uint16_t id, gr2context * c);
uint16_t gr2_get_x2(uint16_t id, gr2context * c);
uint16_t gr2_get_y1(uint16_t id, gr2context * c);
uint16_t gr2_get_y2(uint16_t id, gr2context * c);

void gr2_set_x1(uint16_t id, uint16_t val, gr2context * c);
void gr2_set_x2(uint16_t id, uint16_t val, gr2context * c);
void gr2_set_y1(uint16_t id, uint16_t val, gr2context * c);
void gr2_set_y2(uint16_t id, uint16_t val, gr2context * c);

void gr2_set_x1y1x2y2(uint16_t id, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, gr2context * c);

void gr2_set_x1y1wh(uint16_t id, uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, gr2context * c);

// string
void gr2_set_str(uint16_t id, uint8_t *str, gr2context * c);
uint8_t * gr2_get_str(uint16_t id, gr2context * c);
void gr2_set_str2(uint16_t id, uint8_t *str, gr2context * c);

// string alignment
uint8_t gr2_text_get_align(uint16_t id, gr2context * c);
void gr2_text_set_align(uint16_t id, uint16_t val, gr2context * c);

// modified flag
void gr2_set_modified(uint16_t id, gr2context * c);

// slider size
void gr2_set_slider_size(uint16_t id, uint16_t val, gr2context * c);

// visibility
void gr2_set_visible(uint16_t id, uint16_t vis, gr2context * c);
uint8_t gr2_get_visible(uint16_t id, gr2context * c);

// grayout
void gr2_set_grayout(uint16_t id, uint8_t val, gr2context * c);
uint8_t gr2_get_grayout(uint16_t id, gr2context * c);

// enable block text selection
void gr2_set_block_enable(uint16_t id, uint16_t val, gr2context * c);
uint8_t gr2_get_block_enable(uint16_t id, gr2context * c);

// display only element outline
void gr2_set_ghost(uint16_t id, uint16_t val, gr2context * c);
uint8_t gr2_get_ghost(uint16_t id, gr2context * c);

// element select parameter
void gr2_set_select(uint16_t id, uint16_t val, gr2context * c);
uint8_t gr2_get_select(uint16_t id, gr2context * c);

// Rounded modificator
void gr2_set_rounded(uint16_t id, uint16_t val, gr2context * c);
uint8_t gr2_get_rounded(uint16_t id, gr2context * c);

// misc text field functions
void gr2_text_set_size(uint16_t id, uint16_t size, gr2context * c);
uint16_t gr2_text_get_size(uint16_t id, gr2context * c);

void gr2_text_set_editable(uint16_t id, uint16_t val, gr2context * c);
uint8_t gr2_text_get_editable(uint16_t id, gr2context * c);

void gr2_text_set_fit(uint16_t id, uint16_t val, gr2context * c);
uint8_t gr2_text_get_fit(uint16_t id, gr2context * c);

void gr2_text_set_pwd(uint16_t id, uint16_t val, gr2context * c);
uint8_t gr2_text_get_pwd(uint16_t id, gr2context * c);

void gr2_activate_text(uint16_t id, gr2context * c);
void gr2_text_deactivate(gr2context * c);
uint8_t gr2_get_text_active(uint16_t id, gr2context * c);

// events
gr2EventType gr2_get_event(uint16_t id, gr2context * c);
void gr2_set_event(uint16_t id, gr2EventType val, gr2context * c);
void gr2_clear_event(uint16_t id, gr2context * c); //works both for elements and screens
void gr2_clear_screen_ev(uint16_t id, gr2context * c);
uint8_t gr2_clicked(uint16_t id, gr2context * c); // short for get event released & clear event

// misc handlers
uint8_t gr2_cursor_handler(uint16_t id, uint32_t ms_counter, gr2context * con);

//=================== GUI Getters & Setters for screens ========================
int16_t gr2_get_xscroll(uint16_t id, gr2context * c);
int16_t gr2_get_yscroll(uint16_t id, gr2context * c);
void gr2_set_xscroll(uint16_t id, int16_t val, gr2context * c);
void gr2_set_yscroll(uint16_t id, int16_t val, gr2context * c);

// overrides also x_scroll_old, prevents scrolling artifacts
void gr2_set_xscroll_initial(uint16_t id, int16_t val, gr2context * c);
void gr2_set_yscroll_initial(uint16_t id, int16_t val, gr2context * c);

void gr2_set_x_cell(uint16_t id, uint16_t val, gr2context * c);
void gr2_set_y_cell(uint16_t id, uint16_t val, gr2context * c);
uint16_t gr2_get_x_cell(uint16_t id, gr2context * c);
uint16_t gr2_get_y_cell(uint16_t id, gr2context * c);
void gr2_set_default_font(uint16_t id, uint8_t val, gr2context * c);
void gr2_set_cell_space_left(uint16_t id, uint16_t val, gr2context * c);
void gr2_set_cell_space_right(uint16_t id, uint16_t val, gr2context * c);
void gr2_set_cell_space_top(uint16_t id, uint16_t val, gr2context * c);
void gr2_set_cell_space_bottom(uint16_t id, uint16_t val, gr2context * c);
void gr2_set_cell_spacing(uint16_t id, uint16_t left, uint16_t right, uint16_t top, uint16_t bottom, gr2context * c);

// context color getters & setters
void gr2_set_border_color(uint16_t col, gr2context * c);
uint16_t gr2_get_border_color(gr2context * c);
void gr2_set_text_color(uint16_t col, gr2context * c);
uint16_t gr2_get_text_color(gr2context * c);
void gr2_set_background_color(uint16_t col, gr2context * c);
uint16_t gr2_get_background_color(gr2context * c);
void gr2_set_fill_color(uint16_t col, gr2context * c);
uint16_t gr2_get_fill_color(gr2context * c);
void gr2_set_active_color(uint16_t col, gr2context * c);
uint16_t gr2_get_active_color(gr2context * c);

//=================== misc and internaly used functions ========================

uint16_t gr2_get_element_count(gr2context * c);
void gr2_reset_all(gr2context * c);

uint16_t gr2_get_element_width(uint16_t id, gr2context * con);
uint16_t gr2_get_element_height(uint16_t id, gr2context * con);

void gr2_set_global_grayout_flag(uint8_t val);
uint8_t gr2_get_global_grayout_flag();

void gr2_cleanup(gr2context * c); //sets correct maxElementId
void set_gr2_workaround_context(gr2context * c);

uint16_t gr2_get_tmx(gr2context * c);
uint16_t gr2_get_tmy(gr2context * c);

void gr2_error(uint8_t *str, gr2context * c);
void gr2_destroy_screen(uint16_t id, gr2context * c); 

void gr2_error(uint8_t *str, gr2context * c);

uint8_t gr2_strcmp(uint8_t *a, uint8_t *b);

#define PSCG_BOUNDARY_CHECK_AND_RETURN() do{if (id > c->elementsMax) {gr2_error((uint8_t *)"id out of bounds.", c);printf("%s: id out of bounds.\n", __FUNCTION__);return;} }while(0)
#define PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO() do{if (id > c->elementsMax) {gr2_error((uint8_t *)"id out of bounds.", c);printf("%s: id out of bounds.\n", __FUNCTION__);return 0;} }while(0)


#endif /* PSCG_PSCG_H_ */
