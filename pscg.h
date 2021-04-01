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

#ifndef PSCG_TEXT_Y_GAP
#define PSCG_TEXT_Y_GAP 8
#endif

#ifndef PSCG_CHECKBOX_HSPACE_UP
#define PSCG_CHECKBOX_HSPACE_UP 5
#endif

#ifndef PSCG_CHECKBOX_VSPACE_UP
#define PSCG_CHECKBOX_VSPACE_UP 5
#endif

#ifndef PSCG_CHECKBOX_HSPACE_DN
#define PSCG_CHECKBOX_HSPACE_DN 5
#endif

#ifndef PSCG_CHECKBOX_VSPACE_DN
#define PSCG_CHECKBOX_VSPACE_DN 5
#endif

#ifndef PSCG_CHECKBOX_IN_HSPACE
#define PSCG_CHECKBOX_IN_HSPACE 5
#endif

#ifndef PSCG_CHECKBOX_IN_VSPACE
#define PSCG_CHECKBOX_IN_VSPACE 5
#endif

#ifndef PSCG_CHECKBOX_TEXT_GAP
#define PSCG_CHECKBOX_TEXT_GAP 5
#endif

// GR2 context setup
void gr2_ResetContext(gr2context *c);
void gr2_InitContext(
                     gr2context *c,
                     pscgElement *pscgElementsArray,
                     uint16_t elementsCount,
                     pscgScreen *pscgScreens,
                     uint16_t screensCount
                    );

// screen touch input
uint8_t pscg_touch_input(
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
void pscg_draw_screen(
                     int16_t x1,
                     int16_t y1,
                     int16_t x2,
                     int16_t y2,
                     uint16_t screen,
                     uint8_t all,
                     gr2context *con
                    );

// after the root screen redraw, this function does a cleanup
void pscg_draw_end(gr2context * c);

// dumps screen contents to the console
void pscg_dump_screen(uint16_t id, gr2context * con);

// setting up various context defaults
void pscg_set_grid_size(uint16_t size, gr2context * c); // sets up default grid size [px]
void pscg_set_relative_init(uint8_t relativeInitEnabled, gr2context * c); // switches x1 y1 x2 y2 and x y w h coordinates

//======================== GUI element constructors ============================
uint16_t pscg_add_screen(gr2context * c);
uint16_t pscg_add_screen_ext(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t screen, gr2context * c);
uint16_t pscg_add_button(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t *str, uint16_t screen, gr2context * c);
uint16_t pscg_add_slider_v(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, int32_t param, int32_t value, uint16_t screen, gr2context * c);
uint16_t pscg_add_slider_h(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, int32_t param, int32_t value, uint16_t screen, gr2context * c);
uint16_t pscg_add_text(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t *str, uint16_t screen, gr2context * c);
uint16_t pscg_add_progbar_v(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, int32_t param, int32_t value, uint16_t screen, gr2context * c);
uint16_t pscg_add_icon(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t *str, uint8_t *str2, uint16_t screen, gr2context * c);
uint16_t pscg_add_frame(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, int32_t val, uint16_t screen, gr2context * c);
uint16_t pscg_add_cbutton(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t *str, uint16_t screen, gr2context * c);
uint16_t pscg_add_checkbox(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t *str, uint16_t screen, gr2context * c);
uint16_t pscg_add_image(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t *str, uint16_t screen, gr2context * c);

// destructors
void pscg_destroy(uint16_t id, gr2context * c);

//===================== GUI element Getters & Setters ==========================
// value
int32_t pscg_get_value(uint16_t id, gr2context * c);
void pscg_set_value(uint16_t id, int32_t val, gr2context * c);
// param
int32_t pscg_get_param(uint16_t id, gr2context * c);
void pscg_set_param(uint16_t id, int32_t val, gr2context * c);
// screen
void pscg_set_screen(uint16_t id, uint16_t val, gr2context * c);

// coordinates
uint16_t pscg_get_x1(uint16_t id, gr2context * c);
uint16_t pscg_get_x2(uint16_t id, gr2context * c);
uint16_t pscg_get_y1(uint16_t id, gr2context * c);
uint16_t pscg_get_y2(uint16_t id, gr2context * c);

void pscg_set_x1(uint16_t id, uint16_t val, gr2context * c);
void pscg_set_x2(uint16_t id, uint16_t val, gr2context * c);
void pscg_set_y1(uint16_t id, uint16_t val, gr2context * c);
void pscg_set_y2(uint16_t id, uint16_t val, gr2context * c);

void pscg_set_x1y1x2y2(uint16_t id, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, gr2context * c);

// string
void pscg_set_str(uint16_t id, uint8_t *str, gr2context * c);
uint8_t * pscg_get_str(uint16_t id, gr2context * c);

// string alignment
uint8_t pscg_text_get_align(uint16_t id, gr2context * c);
void pscg_text_set_align(uint16_t id, uint16_t val, gr2context * c);

// modified flag
void pscg_set_modified(uint16_t id, gr2context * c);

// visibility
void pscg_set_visible(uint16_t id, uint16_t vis, gr2context * c);
uint8_t pscg_get_visible(uint16_t id, gr2context * c);

// grayout
void pscg_set_grayout(uint16_t id, uint8_t val, gr2context * c);
uint8_t pscg_get_grayout(uint16_t id, gr2context * c);

// display only element outline
void pscg_set_ghost(uint16_t id, uint16_t val, gr2context * c);
uint8_t pscg_get_ghost(uint16_t id, gr2context * c);

// element select parameter
void pscg_set_select(uint16_t id, uint16_t val, gr2context * c);
uint8_t pscg_get_select(uint16_t id, gr2context * c);

// misc text field functions
void pscg_text_set_size(uint16_t id, uint16_t size, gr2context * c);

void pscg_text_set_editable(uint16_t id, uint16_t val, gr2context * c);
uint8_t pscg_text_get_editable(uint16_t id, gr2context * c);

void pscg_text_set_fit(uint16_t id, uint16_t val, gr2context * c);
uint8_t pscg_text_get_fit(uint16_t id, gr2context * c);

void pscg_text_set_pwd(uint16_t id, uint16_t val, gr2context * c);
uint8_t pscg_text_get_pwd(uint16_t id, gr2context * c);

void pscg_activate_text(uint16_t id, gr2context * c);
void pscg_text_deactivate(gr2context * c);
uint8_t pscg_get_text_active(uint16_t id, gr2context * c);

// events
gr2EventType pscg_get_event(uint16_t id, gr2context * c);
void pscg_set_event(uint16_t id, gr2EventType val, gr2context * c);
void pscg_clear_event(uint16_t id, gr2context * c); //works both for elements and screens
void pscg_clear_screen_ev(uint16_t id, gr2context * c);
uint8_t gr2_clicked(uint16_t id, gr2context * c); // short for get event released & clear event

//=================== GUI Getters & Setters for screens ========================
uint16_t pscg_get_xscroll(uint16_t id, gr2context * c);
uint16_t pscg_get_yscroll(uint16_t id, gr2context * c);
void pscg_set_xscroll(uint16_t id, int16_t val, gr2context * c);
void pscg_set_yscroll(uint16_t id, int16_t val, gr2context * c);
void pscg_set_x_cell(uint16_t id, uint16_t val, gr2context * c);
void pscg_set_y_cell(uint16_t id, uint16_t val, gr2context * c);
uint16_t pscg_get_x_cell(uint16_t id, gr2context * c);
uint16_t pscg_get_y_cell(uint16_t id, gr2context * c);
void pscg_set_default_font(uint16_t id, uint8_t val, gr2context * c);
void pscg_set_cell_space_left(uint16_t id, uint16_t val, gr2context * c);
void pscg_set_cell_space_right(uint16_t id, uint16_t val, gr2context * c);
void pscg_set_cell_space_top(uint16_t id, uint16_t val, gr2context * c);
void pscg_set_cell_space_bottom(uint16_t id, uint16_t val, gr2context * c);

// context color getters & setters
void pscg_set_border_color(uint16_t col, gr2context * c);
uint16_t pscg_get_border_color(gr2context * c);
void pscg_set_text_color(uint16_t col, gr2context * c);
uint16_t pscg_get_text_color(gr2context * c);
void pscg_set_background_color(uint16_t col, gr2context * c);
uint16_t pscg_get_background_color(gr2context * c);
void pscg_set_fill_color(uint16_t col, gr2context * c);
uint16_t pscg_get_fill_color(gr2context * c);
void pscg_set_active_color(uint16_t col, gr2context * c);
uint16_t pscg_get_active_color(gr2context * c);

//=================== misc and internaly used functions ========================

uint16_t pscg_get_element_count(gr2context * c);
void pscg_reset_all(gr2context * c);

void set_global_grayout_flag(uint8_t val);
uint8_t get_global_grayout_flag();

void pscg_cleanup(gr2context * c); //sets correct maxElementId
void set_pscg_workaround_context(gr2context * c);

uint16_t pscg_get_tmx(gr2context * c);
uint16_t pscg_get_tmy(gr2context * c);

void pscg_error(uint8_t *str, gr2context * c);
void pscg_destroy_screen(uint16_t id, gr2context * c); // deprecated

#endif /* PSCG_PSCG_H_ */
