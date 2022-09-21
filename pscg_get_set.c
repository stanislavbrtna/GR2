/*
Copyright (c) 2018 Stanislav Brtna

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

uint32_t sda_strlen(uint8_t * str);

void pscg_set_grid_size(uint16_t size, gr2context * c){
	c->default_grid_size = size;
}

// color getters and setters
void pscg_set_border_color(uint16_t col, gr2context * c) {
	c->border_color = col;
}

uint16_t pscg_get_border_color(gr2context * c) {
	return c->border_color;
}

void pscg_set_text_color(uint16_t col, gr2context * c) {
	c->text_color = col;
}

uint16_t pscg_get_text_color(gr2context * c) {
	return c->text_color;
}

void pscg_set_background_color(uint16_t col, gr2context * c) {
	c->background_color = col;
}

uint16_t pscg_get_background_color(gr2context * c) {
	return c->background_color;
}

void pscg_set_fill_color(uint16_t col, gr2context * c) {
	c->fill_color = col;
}

uint16_t pscg_get_fill_color(gr2context * c) {
	return c->fill_color;
}

void pscg_set_active_color(uint16_t col, gr2context * c) {
	c->active_color = col;
}

uint16_t pscg_get_active_color(gr2context * c) {
	return c->active_color;
}

int32_t pscg_get_value(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	return c->pscgElements[id].value;
}

uint16_t pscg_get_element_count(gr2context * c) {
	return c->elementsUsed;
}

uint8_t pscg_get_visible(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	return c->pscgElements[id].visible;
}

void pscg_set_visible(uint16_t id, uint16_t vis, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (vis != c->pscgElements[id].visible) {
		c->pscgElements[id].modified = 1;
	}

	if ((vis == 0) && (c->pscgElements[id].visible == 1)) {
	  c->invisible_flag = 1;
	}

	c->pscgElements[id].visible = vis;
}

void pscg_set_grayout(uint16_t id, uint8_t val, gr2context * c) {
  PSCG_BOUNDARY_CHECK_AND_RETURN();
  if (val != c->pscgElements[id].grayout) {
		c->pscgElements[id].modified = 1;
	}
	c->pscgElements[id].grayout = val;
}

uint8_t pscg_get_grayout(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	return c->pscgElements[id].grayout;
}

int32_t pscg_get_param(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	return c->pscgElements[id].param;
}

uint16_t pscg_get_param2(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	return c->pscgElements[id].param2;
}

void pscg_set_param(uint16_t id, int32_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (val != c->pscgElements[id].param) {
		c->pscgElements[id].modified = 1;
	}
	c->pscgElements[id].param = val;
}

void pscg_set_modified(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	c->pscgElements[id].modified = 1;
}

void pscg_text_set_editable(uint16_t id, uint16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (c->pscgElements[id].type == GR2_TYPE_TEXT) {
		if (val == 1) {
			c->pscgElements[id].status_reg |= GR2_TEXT_EDITABLE_B;
		} else {
			c->pscgElements[id].status_reg &= ~GR2_TEXT_EDITABLE_B;
		}
		pscg_set_modified(id, c);
	}
}

uint8_t pscg_text_get_editable(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	if (c->pscgElements[id].status_reg & GR2_TEXT_EDITABLE_B) {
		return 1;
	} else {
		return 0;
	}
}

void pscg_text_set_fit(uint16_t id, uint16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (c->pscgElements[id].type == GR2_TYPE_TEXT) {
		if (val == 1) {
			c->pscgElements[id].status_reg |= GR2_TEXT_FIT_B;
		} else {
			c->pscgElements[id].status_reg &= ~GR2_TEXT_FIT_B;
		}
		pscg_set_modified(id, c);
	}
}

uint8_t pscg_text_get_fit(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	if (c->pscgElements[id].status_reg & GR2_TEXT_FIT_B) {
		return 1;
	} else {
		return 0;
	}
}

uint8_t pscg_text_get_align(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	if (!(c->pscgElements[id].status_reg & GR2_T_ALIGN_B1) && !(c->pscgElements[id].status_reg & GR2_T_ALIGN_B2)) {
		return GR2_ALIGN_LEFT;
	}
	if (c->pscgElements[id].status_reg & GR2_T_ALIGN_B1 && !(c->pscgElements[id].status_reg & GR2_T_ALIGN_B2)) {
		return GR2_ALIGN_RIGHT;
	}
	if (!(c->pscgElements[id].status_reg & GR2_T_ALIGN_B1) && c->pscgElements[id].status_reg & GR2_T_ALIGN_B2) {
		return GR2_ALIGN_CENTER;
	}
}


void pscg_text_set_align(uint16_t id, uint16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (val == GR2_ALIGN_LEFT) {
		c->pscgElements[id].status_reg &= ~GR2_T_ALIGN_B1;
		c->pscgElements[id].status_reg &= ~GR2_T_ALIGN_B2;
	}
	if (val == GR2_ALIGN_RIGHT) {
		c->pscgElements[id].status_reg |= GR2_T_ALIGN_B1;
		c->pscgElements[id].status_reg &= ~GR2_T_ALIGN_B2;
	}
	if (val == GR2_ALIGN_CENTER) {
		c->pscgElements[id].status_reg &= ~GR2_T_ALIGN_B1;
		c->pscgElements[id].status_reg |= GR2_T_ALIGN_B2;
	}
	pscg_set_modified(id, c);
}


void pscg_text_set_pwd(uint16_t id, uint16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (c->pscgElements[id].type == GR2_TYPE_TEXT) {
		if (val == 1) {
			c->pscgElements[id].status_reg |= GR2_TEXT_PWD_B;
			// Set cursor position on the last char
			c->pscgElements[id].param = sda_strlen(c->pscgElements[id].str_value);
		} else {
			c->pscgElements[id].status_reg &= ~GR2_TEXT_PWD_B;
		}
		pscg_set_modified(id, c);
	}
}

uint8_t pscg_text_get_pwd(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	if (c->pscgElements[id].status_reg & GR2_TEXT_PWD_B) {
		return 1;
	} else {
		return 0;
	}
}

void pscg_set_ghost(uint16_t id, uint16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (val == 1) {
		c->pscgElements[id].status_reg |= GR2_GHOST_B;
	} else {
		c->pscgElements[id].status_reg &= ~GR2_GHOST_B;
	}
	c->pscgElements[id].modified = 1;
}

uint8_t pscg_get_ghost(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	if (c->pscgElements[id].status_reg & GR2_GHOST_B) {
		return 1;
	} else {
		return 0;
	}
}

void pscg_set_select(uint16_t id, uint16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (val == 1) {
		c->pscgElements[id].status_reg |= GR2_SELECT_B;
	} else {
		c->pscgElements[id].status_reg &= ~GR2_SELECT_B;
	}
	c->pscgElements[id].modified = 1;
}

uint8_t pscg_get_select(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	if (c->pscgElements[id].status_reg & GR2_SELECT_B) {
		return 1;
	} else {
		return 0;
	}
}

void pscg_text_set_size(uint16_t id, uint16_t size, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (size != c->pscgElements[id].param2) {
		c->pscgElements[id].modified = 1;
	}
	c->pscgElements[id].param2 = size;
}

void pscg_set_str(uint16_t id, uint8_t *str, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
 	// always redraw
	c->pscgElements[id].modified = 1;
	c->pscgElements[id].str_value = str;
}

void pscg_set_str2(uint16_t id, uint8_t *str, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
 	// always redraw
	c->pscgElements[id].modified = 1;
	c->pscgElements[id].str_value2 = str;
}

uint8_t * pscg_get_str(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	return c->pscgElements[id].str_value;
}

uint16_t pscg_get_x1(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	return c->pscgElements[id].x1;
}

uint16_t pscg_get_x2(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	if (c->relative_init) {
		return c->pscgElements[id].x2 - c->pscgElements[id].x1;
	} else {
		return c->pscgElements[id].x2;
	}
}

uint16_t pscg_get_y1(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	return c->pscgElements[id].y1;
}

uint16_t pscg_get_y2(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	if (c->relative_init) {
		return c->pscgElements[id].y2 - c->pscgElements[id].y1;
	} else {
		return c->pscgElements[id].y2;
	}
}

void pscg_set_x1(uint16_t id, uint16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (val != c->pscgElements[id].x1) {
		c->pscgElements[id].modified = 1;
		c->pscgElements[c->pscgElements[id].screen_id].modified = 1;
	}
	c->pscgElements[id].x1 = val;
}

void pscg_set_x2(uint16_t id, uint16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (c->relative_init) {
		if (val + c->pscgElements[id].x1 != c->pscgElements[id].x2) {
			c->pscgElements[id].modified = 1;
			c->pscgElements[c->pscgElements[id].screen_id].modified = 1;
		}
		c->pscgElements[id].x2 = c->pscgElements[id].x1 + val;
	} else {
		if (val != c->pscgElements[id].x2) {
			c->pscgElements[id].modified = 1;
			c->pscgElements[c->pscgElements[id].screen_id].modified = 1;
		}
		c->pscgElements[id].x2 = val;
	}
}

void pscg_set_y1(uint16_t id, uint16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (val != c->pscgElements[id].y1) {
		c->pscgElements[id].modified = 1;
		c->pscgElements[c->pscgElements[id].screen_id].modified = 1;
	}
	c->pscgElements[id].y1 = val;
}

void pscg_set_y2(uint16_t id, uint16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (c->relative_init) {
		if (c->pscgElements[id].y1 + val != c->pscgElements[id].y2) {
			c->pscgElements[id].modified = 1;
			c->pscgElements[c->pscgElements[id].screen_id].modified = 1;
		}
		c->pscgElements[id].y2 = c->pscgElements[id].y1 + val;
	} else {
		if (val != c->pscgElements[id].y2) {
			c->pscgElements[id].modified = 1;
			c->pscgElements[c->pscgElements[id].screen_id].modified = 1;
		}
		c->pscgElements[id].y2 = val;
	}
}

void pscg_set_x1y1x2y2(
		uint16_t id,
		uint16_t x1,
		uint16_t y1,
		uint16_t x2,
		uint16_t y2,
		gr2context * c
		) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	c->pscgElements[id].modified = 1;
	c->pscgElements[c->pscgElements[id].screen_id].modified = 1;
	c->pscgElements[id].x1 = x1;
	c->pscgElements[id].y1 = y1;

	if (c->relative_init) {
		c->pscgElements[id].x2 = x2 + x1;
		c->pscgElements[id].y2 = y2 + y1;
	} else {
		c->pscgElements[id].x2 = x2;
		c->pscgElements[id].y2 = y2;
	}
}

void pscg_set_screen(uint16_t id, uint16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	pscg_set_modified(id, c); // redraw flag for inner screen
	c->pscgElements[id].screen_id = val;
}

uint16_t pscg_get_xscroll(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	return c->pscgScreens[c->pscgElements[id].value].x_scroll;
}

uint16_t pscg_get_yscroll(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	return c->pscgScreens[c->pscgElements[id].value].y_scroll;
}

void pscg_set_xscroll(uint16_t id, int16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if ((val != c->pscgScreens[c->pscgElements[id].value].x_scroll) && (c->pscgElements[id].modified == 0)) {
		c->pscgElements[id].modified = 2;
	}
	c->pscgScreens[c->pscgElements[id].value].x_scroll_old
		= c->pscgScreens[c->pscgElements[id].value].x_scroll;
	c->pscgScreens[c->pscgElements[id].value].x_scroll = val;
}

void pscg_set_default_font(uint16_t id, uint8_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	c->pscgScreens[c->pscgElements[id].value].default_font = val;
	//printf("setting def font: %u\n", pscgScreens[pscgElements[id].value].default_font);
}

void pscg_set_yscroll(uint16_t id, int16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if ((val != c->pscgScreens[c->pscgElements[id].value].y_scroll) && (c->pscgElements[id].modified == 0)) {
		c->pscgElements[id].modified = 2;
	}
	c->pscgScreens[c->pscgElements[id].value].y_scroll_old
		= c->pscgScreens[c->pscgElements[id].value].y_scroll;
	c->pscgScreens[c->pscgElements[id].value].y_scroll = val;
}

void pscg_set_cell_space_left(uint16_t id, uint16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (val != c->pscgScreens[c->pscgElements[id].value].cell_space_left) {
		c->pscgElements[id].modified = 1;
	}
	c->pscgScreens[c->pscgElements[id].value].cell_space_left = val;
}

void pscg_set_cell_space_right(uint16_t id, uint16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (val != c->pscgScreens[c->pscgElements[id].value].cell_space_right) {
		c->pscgElements[id].modified = 1;
	}
	c->pscgScreens[c->pscgElements[id].value].cell_space_right = val;
}

void pscg_set_cell_space_top(uint16_t id, uint16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (val != c->pscgScreens[c->pscgElements[id].value].cell_space_top) {
		c->pscgElements[id].modified = 1;
	}
	c->pscgScreens[c->pscgElements[id].value].cell_space_top = val;
}

void pscg_set_cell_space_bottom(uint16_t id, uint16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (val != c->pscgScreens[c->pscgElements[id].value].cell_space_bottom) {
		c->pscgElements[id].modified = 1;
	}
	c->pscgScreens[c->pscgElements[id].value].cell_space_bottom = val;
}

void pscg_set_x_cell(uint16_t id, uint16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (val != c->pscgScreens[c->pscgElements[id].value].x_cell) {
		c->pscgElements[id].modified = 1;
	}
	c->pscgScreens[c->pscgElements[id].value].x_cell = val;
}

void pscg_set_y_cell(uint16_t id, uint16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (val != c->pscgScreens[c->pscgElements[id].value].y_cell) {
		c->pscgElements[id].modified = 1;
	}
	c->pscgScreens[c->pscgElements[id].value].y_cell = val;
}

uint16_t pscg_get_x_cell(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	return c->pscgScreens[c->pscgElements[id].value].x_cell;
}

uint16_t pscg_get_y_cell(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	return c->pscgScreens[c->pscgElements[id].value].y_cell;
}

gr2EventType pscg_get_event(uint16_t id, gr2context * c) {
  PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
  if (c->pscgElements[id].valid == 1) {
  	return c->pscgElements[id].event;
  } else {
  	if (id != 0) {
  		pscg_error((uint8_t *)"pscg_get_event: element not valid", c);
  	} else {
  		printf("WARN: pscg_get_event on id Zero!\n");
  	}
  }
  return EV_NONE;
}

void pscg_set_event(uint16_t id, gr2EventType val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (val != c->pscgElements[id].event) {
		c->pscgElements[id].modified = 1;
	}
	c->pscgElements[id].event = val;
}

void pscg_activate_text(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (c->textActive == 1){
		pscg_text_deactivate(c);
	}
	c->pscgElements[id].value = 1;
	c->textActive = 1;
	c->textActiveId = id;
}

uint8_t pscg_get_text_active(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	if ((c->textActive == 1) && (c->textActiveId == id)) {
		return 1;
	} else {
		return 0;
	}
}
