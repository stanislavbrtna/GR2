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
  uint16_t type;            // typ, id typu, hodilo by se udělat enum
  int16_t x1;              // souřadnice vzhledem ke gridu
  int16_t y1;
  int16_t x2;
  int16_t y2;
  volatile int32_t value;  // hodnota, závislé od typu
  volatile int32_t param;  // parametr, závislé od typu
  volatile uint16_t param2; //param 2, mostly for storing font sizes
  uint8_t *str_value;       // textová hodnota
  uint8_t *str_value2;      // druhá textová hodnota
  volatile uint16_t status_reg;
  // text:
  // bit0 - editable
  // bit1 - fit
  // TODO: move visibility and graiout to position 7, 8, also add ghost option 9 and selected 10
  uint16_t screen_id;       // id elementu screenu, na kterém se prvek nachází
  volatile uint16_t modified; //modified hodnota
  volatile int32_t prev_val; //předchozí value
  uint8_t visible;            // viditelnost
  uint8_t grayout;            // šeďivost
  uint8_t valid;              // validita
  gr2EventType event;         // poslední event
  uint8_t pre_active;         // aktivita předchozího kroku, pomocná hodnota pro pscg_draw
} pscgElement;

/*
 * Element type:
 *  0 - screen - screen id určuje odpovídající screeen strukturu
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

	uint8_t pscg_active_element;

	uint8_t sliderRedrawHotfix; //flag pro korektní překreslení 2x modifikovaného slideru

	uint8_t relative_init;

	uint16_t border_color; //black
	uint16_t text_color; //black
	uint16_t background_color; //red;
	uint16_t fill_color; //green
	uint16_t active_color; //white
} gr2context;

void gr2_ResetContext(gr2context * c);
void gr2_InitContext(gr2context * c, pscgElement *pscgElementsArray, uint16_t elementsCount, pscgScreen *pscgScreens, uint16_t screensCount);

//touch input screenu
uint8_t pscg_touch_input(int16_t x1, int16_t y1,int16_t x2, int16_t y2,uint16_t touch_x,uint16_t touch_y,gr2EventType event, uint16_t screen, gr2context * con);

//draw funkce screenu
void pscg_draw_screen(int16_t x1, int16_t y1,int16_t x2, int16_t y2, uint16_t screen, uint8_t all, gr2context * con);
//po vykreslení kořenového screenu zavolat tuhle funkci
void pscg_draw_end(gr2context * c);

//debug
void pscg_dump_screen(uint16_t id, gr2context * con);

//konstruktory elementů
uint16_t pscg_add_screen(gr2context * c);
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

//draw funkce elementů
void pscg_draw_button(int16_t x1,int16_t y1,int16_t x2,int16_t y2, uint8_t *str, uint8_t active, uint16_t id, gr2context * c);
void pscg_draw_cbutton(int16_t x1,int16_t y1,int16_t x2,int16_t y2, uint8_t *str, uint8_t active, uint16_t id,  gr2context * c);
void pscg_draw_text(int16_t x1,int16_t y1,int16_t x2,int16_t y2, uint8_t *str, uint8_t active, uint8_t editable , uint16_t cursor, uint16_t font_size, uint8_t fit, uint16_t id, gr2context * c);
void pscg_draw_slider_v(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t slider_size, int32_t param, int32_t value, uint16_t id, gr2context * c);
void pscg_draw_slider_h(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t slider_size, int32_t param, int32_t value, uint16_t id, gr2context * c);
void pscg_draw_checkbox(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t *str, uint8_t active, uint16_t id, gr2context * c);

void pscg_draw_progbar_v(int16_t x1,int16_t y1,int16_t x2,int16_t y2,int32_t param, int32_t value, gr2context * c);
void pscg_draw_progbar_h(int16_t x1,int16_t y1,int16_t x2,int16_t y2,int32_t param, int32_t value, gr2context * c);
void pscg_draw_icon(int16_t x1,int16_t y1,int16_t x2,int16_t y2, uint8_t active, uint16_t id, gr2context * c);
void pscg_draw_image(int16_t x1,int16_t y1,int16_t x2,int16_t y2, uint16_t id, gr2context * c);

void pscg_draw_slider_v_f(int16_t x1,int16_t y1,int16_t x2,int16_t y2, uint16_t slider_size,int32_t param, int32_t value, int32_t oldval, uint16_t id, gr2context * c);
void pscg_draw_slider_h_f(int16_t x1,int16_t y1,int16_t x2,int16_t y2, uint16_t slider_size,int32_t param, int32_t value, int32_t oldval, uint16_t id, gr2context * c);

//všeobecné funkce pro práci s elementy
int32_t pscg_get_value(uint16_t id, gr2context * c);
void pscg_set_value(uint16_t id, int32_t val, gr2context * c);
void pscg_set_screen(uint16_t id, uint16_t val, gr2context * c);
int32_t pscg_get_param(uint16_t id, gr2context * c);
void pscg_set_param(uint16_t id, int32_t val, gr2context * c);


uint16_t pscg_get_x1(uint16_t id, gr2context * c);
uint16_t pscg_get_x2(uint16_t id, gr2context * c);
uint16_t pscg_get_y1(uint16_t id, gr2context * c);
uint16_t pscg_get_y2(uint16_t id, gr2context * c);

void pscg_set_x1(uint16_t id, uint16_t val, gr2context * c);
void pscg_set_x2(uint16_t id, uint16_t val, gr2context * c);
void pscg_set_y1(uint16_t id, uint16_t val, gr2context * c);
void pscg_set_y2(uint16_t id, uint16_t val, gr2context * c);

void pscg_set_str(uint16_t id, uint8_t *str, gr2context * c);
uint8_t * pscg_get_str(uint16_t id, gr2context * c);
void pscg_set_modified(uint16_t id, gr2context * c);
void pscg_set_visible(uint16_t id, uint16_t vis, gr2context * c);

void pscg_set_grayout(uint16_t id, uint8_t val, gr2context * c);
uint8_t pscg_get_grayout(uint16_t id, gr2context * c);

void pscg_text_set_size(uint16_t id, uint16_t size, gr2context * c);
void pscg_text_deactivate(gr2context * c);
void pscg_text_set_editable(uint16_t id, uint16_t val, gr2context * c);
uint8_t pscg_text_get_editable(uint16_t id, gr2context * c);
void pscg_text_set_fit(uint16_t id, uint16_t val, gr2context * c);
void pscg_activate_text(uint16_t id, gr2context * c);
uint8_t pscg_get_text_active(uint16_t id, gr2context * c);

void pscg_set_x1y1x2y2(uint16_t id, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, gr2context * c);

gr2EventType pscg_get_event(uint16_t id, gr2context * c);
void pscg_set_event(uint16_t id, gr2EventType val, gr2context * c);
void pscg_clear_event(uint16_t id, gr2context * c); //works both for elements and screens
void pscg_clear_screen_ev(uint16_t id, gr2context * c);

//pro práci s obrazovkami
uint16_t pscg_get_xscroll(uint16_t id, gr2context * c);
uint16_t pscg_get_yscroll(uint16_t id, gr2context * c);
void pscg_set_xscroll(uint16_t id, int16_t val, gr2context * c);
void pscg_set_yscroll(uint16_t id, int16_t val, gr2context * c);
void pscg_set_x_cell(uint16_t id, uint16_t val, gr2context * c);
void pscg_set_y_cell(uint16_t id, uint16_t val, gr2context * c);
uint16_t pscg_get_x_cell(uint16_t id, gr2context * c);
uint16_t pscg_get_y_cell(uint16_t id, gr2context * c);
void pscg_set_default_font(uint16_t id, uint8_t val, gr2context * c);

//ostatní
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

uint8_t pscg_text_get_fit(uint16_t id, gr2context * c);
uint16_t pscg_get_element_count(gr2context * c);
uint8_t pscg_get_visible(uint16_t id, gr2context * c);

void pscg_reset_all(gr2context * c);

void pscg_set_grid_size(uint16_t size, gr2context * c); //není v dokumentaci, nastaví defaultní grid size
void pscg_cleanup(gr2context * c); //není v dokumentaci, nastavuje korektní maxElementId
void set_pscg_workaround_context(gr2context * c);
void pscg_set_relative_init(uint8_t val, gr2context * c);

void pscg_set_ghost(uint16_t id, uint16_t val, gr2context * c);
uint8_t pscg_get_ghost(uint16_t id, gr2context * c);
void pscg_set_select(uint16_t id, uint16_t val, gr2context * c);
uint8_t pscg_get_select(uint16_t id, gr2context * c);

uint16_t pscg_get_tmx(gr2context * c);
uint16_t pscg_get_tmy(gr2context * c);

void pscg_destroy(uint16_t id, gr2context * c); // odstraňuje i obrazovky
void pscg_destroy_screen(uint16_t id, gr2context * c); //odstraní screen a všechny jeho prvky

void pscg_error(uint8_t *str, gr2context * c);

uint8_t gr2_clicked(uint16_t id, gr2context * c); // short for get event released & clear event

#endif /* PSCG_PSCG_H_ */
