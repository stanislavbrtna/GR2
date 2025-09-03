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

#include "GR2.h"

uint32_t sda_strlen(uint8_t * str);

void gr2_set_grid_size(uint16_t size, gr2context * c) {
	c->defaultGridSize = size;
}

uint8_t gr2_get_valid(uint16_t id, gr2context * c) {
  PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
  return c->pscgElements[id].valid;
}

// color getters and setters
void gr2_set_border_color(uint16_t col, gr2context * c) {
	c->borderColor = col;
}

uint16_t gr2_get_border_color(gr2context * c) {
	return c->borderColor;
}

void gr2_set_text_color(uint16_t col, gr2context * c) {
	c->textColor = col;
}

uint16_t gr2_get_text_color(gr2context * c) {
	return c->textColor;
}

void gr2_set_background_color(uint16_t col, gr2context * c) {
	c->backgroundColor = col;
}

uint16_t gr2_get_background_color(gr2context * c) {
	return c->backgroundColor;
}

void gr2_set_fill_color(uint16_t col, gr2context * c) {
	c->fillColor = col;
}

uint16_t gr2_get_fill_color(gr2context * c) {
	return c->fillColor;
}

void gr2_set_active_color(uint16_t col, gr2context * c) {
	c->activeColor = col;
}

uint16_t gr2_get_active_color(gr2context * c) {
	return c->activeColor;
}

int32_t gr2_get_value(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	return c->pscgElements[id].value;
}

void gr2_set_value(uint16_t id, int32_t val, gr2context * c) {
  PSCG_BOUNDARY_CHECK_AND_RETURN();

  if (c->pscgElements[id].type == GR2_TYPE_SCREEN) {
    return;
  }

  if ((val != c->pscgElements[id].value) && (c->pscgElements[id].modified == 0)) {
    if (c->pscgElements[id].modified == 0) {
      // Store value before item was modified
      c->pscgElements[id].prev_val = c->pscgElements[id].value;
    }
    c->pscgElements[id].modified = 1; // redraw modified
  }
  c->pscgElements[id].value = val;
}

uint16_t gr2_get_element_count(gr2context * c) {
	return c->elementsUsed;
}

uint8_t gr2_get_visible(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	return c->pscgElements[id].visible;
}

void gr2_set_visible(uint16_t id, uint16_t vis, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (vis != c->pscgElements[id].visible) {
		c->pscgElements[id].modified = 1;
	}

	if ((vis == 0) && (c->pscgElements[id].visible == 1)) {
	  c->invisibleFlag = 1;
	}

	c->pscgElements[id].visible = vis;
}

void gr2_set_relative_init(uint8_t val, gr2context * c) {
  c->relativeInit = val;
}

uint8_t gr2_get_relative_init(gr2context * c) {
  return c->relativeInit;
}

void gr2_set_grayout(uint16_t id, uint8_t val, gr2context * c) {
  PSCG_BOUNDARY_CHECK_AND_RETURN();
  if (val != c->pscgElements[id].grayout) {
		c->pscgElements[id].modified = 1;
	}
	c->pscgElements[id].grayout = val;
}

uint8_t gr2_get_grayout(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	return c->pscgElements[id].grayout;
}

int32_t gr2_get_param(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	return c->pscgElements[id].param;
}

uint16_t gr2_get_param2(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	return c->pscgElements[id].param2;
}

void gr2_set_param(uint16_t id, int32_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (val != c->pscgElements[id].param) {
		c->pscgElements[id].modified = 1;
	}
	c->pscgElements[id].param = val;
}

void gr2_set_param2(uint16_t id, int32_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (val != c->pscgElements[id].param2) {
		c->pscgElements[id].modified = 1;
	}
	c->pscgElements[id].param2 = val;
}

void gr2_set_modified(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	c->pscgElements[id].modified = 1;
}

void gr2_set_slider_size(uint16_t id, uint16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();

	if (c->pscgElements[id].type == GR2_TYPE_SLIDER_H) {
		if (val < gr2_get_element_width(id, c)) {
			c->pscgElements[id].param2 = val;
		} else {
			c->pscgElements[id].param2 = gr2_get_element_width(id, c);
		}
		c->pscgElements[id].modified = 1;
		return;
	}

	if (c->pscgElements[id].type == GR2_TYPE_SLIDER_V) {
		if (val < gr2_get_element_height(id, c)) {
			c->pscgElements[id].param2 = val;
		} else {
			c->pscgElements[id].param2 = gr2_get_element_height(id, c);
		}
		c->pscgElements[id].modified = 1;
		return;
	}
}

void gr2_text_set_editable(uint16_t id, uint16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (c->pscgElements[id].type == GR2_TYPE_TEXT) {
		if (val == 1) {
			c->pscgElements[id].status_reg |= GR2_TEXT_EDITABLE_B;
		} else {
			c->pscgElements[id].status_reg &= ~GR2_TEXT_EDITABLE_B;
		}
		gr2_set_modified(id, c);
	}
}

void gr2_text_set_x_scroll(int16_t val, gr2context * c) {
	if(c->textActive && c->textXScroll != val) {
		gr2_set_modified(c->textActiveId, c);
	}
	c->textXScroll = val;
}

void gr2_text_set_y_scroll(int16_t val, gr2context * c) {
	if(c->textActive && c->textYScroll != val) {
		gr2_set_modified(c->textActiveId, c);
	}
	c->textYScroll = val;
}

void gr2_set_text_scr_auto_scroll(uint16_t id, uint16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	c->pscgScreens[c->pscgElements[id].value].textAutoScroll = val;
}

uint8_t gr2_text_get_editable(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	if (c->pscgElements[id].status_reg & GR2_TEXT_EDITABLE_B) {
		return 1;
	} else {
		return 0;
	}
}

void gr2_text_set_invert_select(uint16_t id, uint16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (val == 1) {
		c->pscgElements[id].status_reg |= GR2_SELECT_INV;
	} else {
		c->pscgElements[id].status_reg &= ~GR2_SELECT_INV;
	}
	c->pscgElements[id].modified = 1;
}

uint8_t gr2_text_get_invert_select(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	if (c->pscgElements[id].status_reg & GR2_SELECT_INV) {
		return 1;
	} else {
		return 0;
	}
}

void gr2_text_set_fit(uint16_t id, uint16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (c->pscgElements[id].type == GR2_TYPE_TEXT) {
		if (val == 1) {
			c->pscgElements[id].status_reg |= GR2_TEXT_FIT_B;
		} else {
			c->pscgElements[id].status_reg &= ~GR2_TEXT_FIT_B;
		}
		gr2_set_modified(id, c);
	}
}

uint8_t gr2_text_get_fit(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	if (c->pscgElements[id].status_reg & GR2_TEXT_FIT_B) {
		return 1;
	} else {
		return 0;
	}
}

uint8_t gr2_text_get_align(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	if (!(c->pscgElements[id].status_reg & GR2_T_ALIGN_B1) && !(c->pscgElements[id].status_reg & GR2_T_ALIGN_B2)) {
		return GR2_ALIGN_LEFT;
	}
	if ((c->pscgElements[id].status_reg & GR2_T_ALIGN_B1) && !(c->pscgElements[id].status_reg & GR2_T_ALIGN_B2)) {
		return GR2_ALIGN_RIGHT;
	}
	if (!(c->pscgElements[id].status_reg & GR2_T_ALIGN_B1) && (c->pscgElements[id].status_reg & GR2_T_ALIGN_B2)) {
		return GR2_ALIGN_CENTER;
	}
	return GR2_ALIGN_LEFT;
}


void gr2_text_set_align(uint16_t id, uint16_t val, gr2context * c) {
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
	gr2_set_modified(id, c);
}


void gr2_text_set_pwd(uint16_t id, uint16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (c->pscgElements[id].type == GR2_TYPE_TEXT) {
		if (val == 1) {
			c->pscgElements[id].status_reg |= GR2_TEXT_PWD_B;
			// Set cursor position on the last char
			c->pscgElements[id].param = sda_strlen(c->pscgElements[id].str_value);
		} else {
			c->pscgElements[id].status_reg &= ~GR2_TEXT_PWD_B;
		}
		gr2_set_modified(id, c);
	}
}

uint8_t gr2_text_get_pwd(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	if (c->pscgElements[id].status_reg & GR2_TEXT_PWD_B) {
		return 1;
	} else {
		return 0;
	}
}

void gr2_set_ghost(uint16_t id, uint16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (val == 1) {
		c->pscgElements[id].status_reg |= GR2_GHOST_B;
	} else {
		c->pscgElements[id].status_reg &= ~GR2_GHOST_B;
	}
	c->pscgElements[id].modified = 1;
}

uint8_t gr2_get_ghost(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	if (c->pscgElements[id].status_reg & GR2_GHOST_B) {
		return 1;
	} else {
		return 0;
	}
}


void gr2_set_block_enable(uint16_t id, uint16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (val == 1) {
		c->pscgElements[id].status_reg |= GR2_BLOCK_TEXT_B;
	} else {
		c->pscgElements[id].status_reg &= ~GR2_BLOCK_TEXT_B;
	}
}

uint8_t gr2_get_block_enable(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	if (c->pscgElements[id].status_reg & GR2_BLOCK_TEXT_B) {
		return 1;
	} else {
		return 0;
	}
}


void gr2_set_select(uint16_t id, uint16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (val == 1) {
		c->pscgElements[id].status_reg |= GR2_SELECT_B;
	} else {
		c->pscgElements[id].status_reg &= ~GR2_SELECT_B;
	}
	c->pscgElements[id].modified = 1;
}

uint8_t gr2_get_select(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	if (c->pscgElements[id].status_reg & GR2_SELECT_B) {
		return 1;
	} else {
		return 0;
	}
}


void gr2_set_rounded(uint16_t id, uint16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (val == 1) {
		c->pscgElements[id].status_reg |= GR2_ROUNDED_B;
	} else {
		c->pscgElements[id].status_reg &= ~GR2_ROUNDED_B;
	}
	c->pscgElements[id].modified = 1;
}

uint8_t gr2_get_rounded(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	if (c->pscgElements[id].status_reg & GR2_ROUNDED_B) {
		return 1;
	} else {
		return 0;
	}
}


// sets sizes 12, 18 (default), 32, 70, 87
void gr2_text_set_size(uint16_t id, uint16_t size, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (size != c->pscgElements[id].param2) {
		c->pscgElements[id].modified = 1;
	}
	c->pscgElements[id].param2 = size;
}

uint16_t gr2_text_get_size(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	return c->pscgElements[id].param2;
}

void gr2_set_str(uint16_t id, uint8_t *str, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
 	// always redraw
	c->pscgElements[id].modified = 1;
	c->pscgElements[id].str_value = str;
}

void gr2_set_str2(uint16_t id, uint8_t *str, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
 	// always redraw
	c->pscgElements[id].modified = 1;
	c->pscgElements[id].str_value2 = str;
}

uint8_t * gr2_get_str(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();

	if (c->pscgElements[id].str_value == 0) {
		printf("%s: string value out of bounds! Empty string returned. (element id: %u)\n", __FUNCTION__, id);
		gr2_error((uint8_t *)"gr2_get_str: pointer out of bounds!", c);
		return "";
	}

	return c->pscgElements[id].str_value;
}

uint16_t gr2_get_x1(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	return c->pscgElements[id].x1;
}

uint16_t gr2_get_x2(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	if (c->relativeInit) {
		return c->pscgElements[id].x2 - c->pscgElements[id].x1;
	} else {
		return c->pscgElements[id].x2;
	}
}

uint16_t gr2_get_y1(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	return c->pscgElements[id].y1;
}

uint16_t gr2_get_y2(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	if (c->relativeInit) {
		return c->pscgElements[id].y2 - c->pscgElements[id].y1;
	} else {
		return c->pscgElements[id].y2;
	}
}

void gr2_set_x1(uint16_t id, uint16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (val != c->pscgElements[id].x1) {
		c->pscgElements[id].modified = 1;
		c->pscgElements[c->pscgElements[id].screen_id].modified = 1;
	}
	if (c->relativeInit) {
		c->pscgElements[id].x2 = c->pscgElements[id].x2 - c->pscgElements[id].x1 + val;
	}

	c->pscgElements[id].x1 = val;	
}

void gr2_set_x2(uint16_t id, uint16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (c->relativeInit) {
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

void gr2_set_y1(uint16_t id, uint16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (val != c->pscgElements[id].y1) {
		c->pscgElements[id].modified = 1;
		c->pscgElements[c->pscgElements[id].screen_id].modified = 1;
	}
	if (c->relativeInit) {
		c->pscgElements[id].y2 = c->pscgElements[id].y2 - c->pscgElements[id].y1 + val;
	}

	c->pscgElements[id].y1 = val;
}

void gr2_set_y2(uint16_t id, uint16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (c->relativeInit) {
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

void gr2_set_x1y1x2y2(
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

	if (c->relativeInit) {
		c->pscgElements[id].x2 = x2 + x1;
		c->pscgElements[id].y2 = y2 + y1;
	} else {
		c->pscgElements[id].x2 = x2;
		c->pscgElements[id].y2 = y2;
	}
}

void gr2_set_x1y1wh(
		uint16_t id,
		uint16_t x1,
		uint16_t y1,
		uint16_t w,
		uint16_t h,
		gr2context * c
		) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	c->pscgElements[id].modified = 1;
	c->pscgElements[c->pscgElements[id].screen_id].modified = 1;
	c->pscgElements[id].x1 = x1;
	c->pscgElements[id].y1 = y1;

    c->pscgElements[id].x2 = x1 + w;
	c->pscgElements[id].y2 = y1 + h;
}

void gr2_set_screen(uint16_t id, uint16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	gr2_set_modified(id, c); // redraw flag for inner screen
	c->pscgElements[id].screen_id = val;
}

uint16_t gr2_get_screen(uint16_t id, gr2context *c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	return c->pscgElements[id].screen_id;
}

int16_t gr2_get_xscroll(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	return c->pscgScreens[c->pscgElements[id].value].x_scroll;
}

int16_t gr2_get_yscroll(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	return c->pscgScreens[c->pscgElements[id].value].y_scroll;
}

void gr2_set_xscroll(uint16_t id, int16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if ((val != c->pscgScreens[c->pscgElements[id].value].x_scroll) && (c->pscgElements[id].modified == 0)) {
		c->pscgElements[id].modified = 2;
	}
	c->pscgScreens[c->pscgElements[id].value].x_scroll_old
		= c->pscgScreens[c->pscgElements[id].value].x_scroll;
	c->pscgScreens[c->pscgElements[id].value].x_scroll = val;
}

// overrides also x_scroll_old, prevents scrolling artifacts
void gr2_set_xscroll_initial(uint16_t id, int16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if ((val != c->pscgScreens[c->pscgElements[id].value].x_scroll) && (c->pscgElements[id].modified == 0)) {
		c->pscgElements[id].modified = 2;
	}

	c->pscgScreens[c->pscgElements[id].value].x_scroll_old = val;
	c->pscgScreens[c->pscgElements[id].value].x_scroll = val;
}

void gr2_set_default_font(uint16_t id, uint8_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	c->pscgScreens[c->pscgElements[id].value].default_font = val;
	//printf("setting def font: %u\n", pscgScreens[pscgElements[id].value].default_font);
}

void gr2_set_yscroll(uint16_t id, int16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if ((val != c->pscgScreens[c->pscgElements[id].value].y_scroll) && (c->pscgElements[id].modified == 0)) {
		c->pscgElements[id].modified = 2;
	}
	c->pscgScreens[c->pscgElements[id].value].y_scroll_old
		= c->pscgScreens[c->pscgElements[id].value].y_scroll;
	c->pscgScreens[c->pscgElements[id].value].y_scroll = val;
}

void gr2_set_yscroll_initial(uint16_t id, int16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if ((val != c->pscgScreens[c->pscgElements[id].value].y_scroll) && (c->pscgElements[id].modified == 0)) {
		c->pscgElements[id].modified = 2;
	}
	c->pscgScreens[c->pscgElements[id].value].y_scroll_old = val;
	c->pscgScreens[c->pscgElements[id].value].y_scroll = val;
}

void gr2_set_cell_spacing(uint16_t id, uint16_t left, uint16_t right, uint16_t top, uint16_t bottom, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if(!c->pscgElements[id].valid || !c->pscgScreens[c->pscgElements[id].value].valid) {
		printf("%s: Warn: Element not valid!\n", __FUNCTION__);
		return;
	}
	gr2_set_cell_space_left(id, left, c);
	gr2_set_cell_space_right(id, right, c);
	gr2_set_cell_space_top(id, top, c);
	gr2_set_cell_space_bottom(id, bottom, c);
}

void gr2_set_cell_space_left(uint16_t id, uint16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (val != c->pscgScreens[c->pscgElements[id].value].cell_space_left) {
		c->pscgElements[id].modified = 1;
	}
	c->pscgScreens[c->pscgElements[id].value].cell_space_left = val;
}

void gr2_set_cell_space_right(uint16_t id, uint16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (val != c->pscgScreens[c->pscgElements[id].value].cell_space_right) {
		c->pscgElements[id].modified = 1;
	}
	c->pscgScreens[c->pscgElements[id].value].cell_space_right = val;
}

void gr2_set_cell_space_top(uint16_t id, uint16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (val != c->pscgScreens[c->pscgElements[id].value].cell_space_top) {
		c->pscgElements[id].modified = 1;
	}
	c->pscgScreens[c->pscgElements[id].value].cell_space_top = val;
}

void gr2_set_cell_space_bottom(uint16_t id, uint16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (val != c->pscgScreens[c->pscgElements[id].value].cell_space_bottom) {
		c->pscgElements[id].modified = 1;
	}
	c->pscgScreens[c->pscgElements[id].value].cell_space_bottom = val;
}

void gr2_set_x_cell(uint16_t id, uint16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if(!c->pscgElements[id].valid  || !c->pscgScreens[c->pscgElements[id].value].valid) {
		printf("%s: Warn: Element not valid!\n", __FUNCTION__);
		return;
	}
	if (val != c->pscgScreens[c->pscgElements[id].value].x_cell) {
		c->pscgElements[id].modified = 1;
	}
	c->pscgScreens[c->pscgElements[id].value].x_cell = val;
}

void gr2_set_y_cell(uint16_t id, uint16_t val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if(!c->pscgElements[id].valid  || !c->pscgScreens[c->pscgElements[id].value].valid) {
		printf("%s: Warn: Element not valid!\n", __FUNCTION__);
		return;
	}
	if (val != c->pscgScreens[c->pscgElements[id].value].y_cell) {
		c->pscgElements[id].modified = 1;
	}
	c->pscgScreens[c->pscgElements[id].value].y_cell = val;
}

uint16_t gr2_get_x_cell(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	return c->pscgScreens[c->pscgElements[id].value].x_cell;
}

uint16_t gr2_get_y_cell(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	return c->pscgScreens[c->pscgElements[id].value].y_cell;
}

gr2EventType gr2_get_event(uint16_t id, gr2context * c) {
  PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
  if (c->pscgElements[id].valid == 1) {
  	return c->pscgElements[id].event;
  } else {
  	if (id != 0) {
  		gr2_error((uint8_t *)"gr2_get_event: element not valid", c);
  	} else {
  		printf("WARN: gr2_get_event on id Zero!\n");
  	}
  }
  return EV_NONE;
}

void gr2_set_event(uint16_t id, gr2EventType val, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (val != c->pscgElements[id].event) {
		c->pscgElements[id].modified = 1;
	}
	c->pscgElements[id].event = val;
}

void gr2_activate_text(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN();
	if (c->textActiveId == id && c->textActive == 1) {
		return;
	}
	if (c->textActive == 1) {
		gr2_text_deactivate(c);
	}
	c->pscgElements[id].value    = 1;
	c->pscgElements[id].modified = 1;
	c->textActive     = 1;
	c->textActiveId   = id;
	c->textBlockStart = 0;
    c->textBlockEnd   = 0;
	c->textXScroll    = 0;
	c->textYScroll    = 0;
}

void gr2_text_deactivate(gr2context * c) {
  c->textActive = 0;
  c->pscgElements[c->textActiveId].value = 0;
  c->pscgElements[c->textActiveId].modified = 1;
}

uint8_t gr2_get_text_active(uint16_t id, gr2context * c) {
	PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
	if ((c->textActive == 1) && (c->textActiveId == id)) {
		return 1;
	} else {
		return 0;
	}
}
