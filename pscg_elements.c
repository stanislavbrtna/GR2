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
#include "pscg.h"

/*
 * V tomto souboru se nachází konstruktory elementů grafického rozhraní.
 */

void pscg_set_max_id(uint16_t id, gr2context * c){

  if (id > c->maxElementsId) {
    c->maxElementsId = id;
  }
}

void pscg_error(uint8_t *str, gr2context * c);

void pscg_indent(uint16_t val){
	uint16_t x;
	for(x = 0; x < val; x++){
		printf("  ");
	}
}

void pscg_dump_element(uint16_t id, uint16_t val, gr2context * c){
	pscg_indent(val);
	printf("pscgElements[%u].valid = %u \n", id, c->pscgElements[id].valid);
	pscg_indent(val);
	printf("pscgElements[%u].type = %u \n", id, c->pscgElements[id].type);
	pscg_indent(val);
	printf("pscgElements[%u] position: x1:%d y1:%d x2:%d y2:%u \n",
			id,
			c->pscgElements[id].x1,
			c->pscgElements[id].y1,
			c->pscgElements[id].x2,
			c->pscgElements[id].y2
		);
	pscg_indent(val);
	printf("pscgElements[%u].value = %d \n", id, (int)c->pscgElements[id].value);
	pscg_indent(val);
	printf("pscgElements[%u].param = %d \n", id, (int)c->pscgElements[id].param);
	pscg_indent(val);
	printf("pscgElements[%u].param2 = %u \n", id, c->pscgElements[id].param2);
	pscg_indent(val);
	printf("pscgElements[%u].str_value = %s \n", id, c->pscgElements[id].str_value);
	pscg_indent(val);
	printf("pscgElements[%u].str_value2 = %s \n", id, c->pscgElements[id].str_value2);
	pscg_indent(val);
	printf("pscgElements[%u].screen_id = %u \n", id, c->pscgElements[id].screen_id);
	pscg_indent(val);
	printf("pscgElements[%u].event = %u \n", id, c->pscgElements[id].event);
	pscg_indent(val);
	printf("pscgElements[%u].visible = %u \n", id, c->pscgElements[id].visible);
	pscg_indent(val);
	printf("pscgElements[%u].grayout = %u \n", id, c->pscgElements[id].grayout);
}

void pscg_dump_screen_values(uint16_t id, uint16_t val, gr2context * c){
	uint16_t scrID;

	if (c->pscgElements[id].type == 0){
		scrID = c->pscgElements[id].value;
	} else {
		printf("pscgElement %u: NOT a screen\n", id);
		return;
	}
	pscg_indent(val);
	printf("pscgElement %u, screenID %u x_scroll = %u \n", id, scrID, c->pscgScreens[scrID].x_scroll);
	pscg_indent(val);
	printf("pscgElement %u, screenID %u y_scroll = %u \n", id, scrID, c->pscgScreens[scrID].y_scroll);
	pscg_indent(val);
	printf("pscgElement %u, screenID %u x_cell = %u \n", id, scrID, c->pscgScreens[scrID].x_cell);
	pscg_indent(val);
	printf("pscgElement %u, screenID %u y_cell = %u \n", id, scrID, c->pscgScreens[scrID].y_cell);
	pscg_indent(val);
	printf("pscgElement %u, screenID %u default_font = %u \n", id, scrID, c->pscgScreens[scrID].default_font);

}

void pscg_dump_screen_ind(uint16_t id, uint16_t val, gr2context * c) {
  uint16_t x;

  pscg_indent(val);
  pscg_dump_screen_values(id, val, c);
  pscg_indent(val);
  pscg_dump_element(id, val, c);
  for(x = 0; x <= c->elementsMax; x++) {
    if ((c->pscgElements[x].screen_id == id) && (c->pscgElements[x].valid == 1)) {
      if ((c->pscgElements[x].type == 0) && (x != id)) {
        pscg_dump_screen_ind(x, val++, c);

      }
      pscg_dump_element(x, val, c);
    }
	}
}

void pscg_dump_screen(uint16_t id, gr2context * c) {
	pscg_dump_screen_ind(id, 0, c);
}

static void pscg_add_fill_xy(uint16_t i, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, gr2context * c) {
	c->pscgElements[i].x1 = x1;
	c->pscgElements[i].y1 = y1;

	if (c->relative_init) {
		c->pscgElements[i].x2 = x1 + x2;
		c->pscgElements[i].y2 = y1 + y2;
	} else {

		c->pscgElements[i].x2 = x2;
		c->pscgElements[i].y2 = y2;
	}
}

static void pscg_fill_zero_defaults(uint16_t i, uint16_t screen_id, gr2context * c) {
	c->pscgElements[i].event = EV_NONE;
	c->pscgElements[i].status_reg = 0;
	c->pscgElements[i].pre_active = 0;
	c->pscgElements[i].valid = 1;
	c->pscgElements[i].value = 0;
	c->pscgElements[i].visible = 1;
	c->pscgElements[i].grayout = 0;
	c->pscgElements[i].param = 0;
	c->pscgElements[i].param2 = 0;
	c->pscgElements[i].screen_id = screen_id;
	c->pscgElements[i].modified = 0;
}

uint16_t pscg_add_button(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t *str, uint16_t screen, gr2context * c){
	uint16_t i = 1;
	while (1) {
	  if (c->pscgElements[i].valid == 0) {
	    break;
	  }
	  if (i >= c->elementsMax) {
		  pscg_error((uint8_t *)"Maximum number of elements reached!", c);
		  return 0;
	  }
	  i++;
	}
	pscg_fill_zero_defaults(i, screen, c);
	c->pscgElements[i].type = GR2_TYPE_BUTTON;
	pscg_add_fill_xy(i, x1, y1, x2, y2, c);
	c->pscgElements[i].str_value = str;
		c->pscgElements[i].param = 5; // text x1 is stored in param
	c->pscgElements[i].param2 = c->pscgScreens[c->pscgElements[screen].value].default_font; //číslo fontu
	pscg_set_max_id(i, c);
	c->elementsUsed++;
	return i;
}

uint16_t pscg_add_cbutton(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t *str, uint16_t screen, gr2context * c){
	uint16_t i = 1;
	while(1){
	  if (c->pscgElements[i].valid == 0) {
	    break;
	  }
	  if (i>= c->elementsMax){
		  pscg_error((uint8_t *) "Maximum number of elements reached!", c);
		  return 0;
	  }
	  i++;
	}

	pscg_fill_zero_defaults(i, screen, c);
	c->pscgElements[i].type = GR2_TYPE_COLOR_BUTTON;
	pscg_add_fill_xy(i, x1, y1, x2, y2, c);
	c->pscgElements[i].str_value = str;
	c->pscgElements[i].value = 0; // color is stored in value
	c->pscgElements[i].param2 = c->pscgScreens[c->pscgElements[screen].value].default_font; //číslo fontu
	pscg_set_max_id(i, c);
	c->elementsUsed++;

	return i;
}


uint16_t pscg_add_checkbox(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t *str, uint16_t screen, gr2context * c) {
	uint16_t i = 1;
	while(1) {
	  if (c->pscgElements[i].valid == 0) {
	    break;
	  }
	  if (i >= c->elementsMax) {
		  pscg_error((uint8_t *) "Maximum number of elements reached!", c);
		  return 0;
	  }
	  i++;
	}

	pscg_fill_zero_defaults(i, screen, c);
	c->pscgElements[i].type = GR2_TYPE_CHECKBOX;
	pscg_add_fill_xy(i, x1, y1, x2, y2, c);
	c->pscgElements[i].str_value = str;
	c->pscgElements[i].value = 0; //tutady je pokud je checked
	c->pscgElements[i].param2 = c->pscgScreens[c->pscgElements[screen].value].default_font; //číslo fontu
	pscg_set_max_id(i, c);
	c->elementsUsed++;

	return i;
}

uint16_t pscg_add_frame(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, int32_t val, uint16_t screen, gr2context * c){
	uint16_t i = 1;
	while(1){
	  if (c->pscgElements[i].valid==0){
	    break;
	  }
	  if (i>= c->elementsMax){
		  pscg_error((uint8_t *) "Maximum number of elements reached!", c);
		  return 0;
	  }
	  i++;
	}

	pscg_fill_zero_defaults(i, screen, c);
	c->pscgElements[i].type = GR2_TYPE_FRAME;
	pscg_add_fill_xy(i, x1, y1, x2, y2, c);
	c->pscgElements[i].value = val; //id of the screen inside the frame

	pscg_set_max_id(i, c);
	c->elementsUsed++;

	return i;
}

uint16_t pscg_add_icon(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t *str, uint8_t *str2, uint16_t screen, gr2context * c){
	uint16_t i = 1;
	while(1){
	  if (c->pscgElements[i].valid==0){
	    break;
	  }
	  if (i>= c->elementsMax){
		  pscg_error((uint8_t *) "Maximum number of elements reached!", c);
		  return 0;
	  }
	  i++;
	}

	pscg_fill_zero_defaults(i, screen, c);
	c->pscgElements[i].type = GR2_TYPE_ICON;
	pscg_add_fill_xy(i, x1, y1, x2, y2, c);
	c->pscgElements[i].str_value = str;
	c->pscgElements[i].str_value2 = str2; //name of .ppm file with size 32x32 or 64x64
	//param:
	//0 pokud není vykreslena
	//1 pokud je vykreslena jako neaktivní
	//2 pokud je vykreslena jako aktivní

	pscg_set_max_id(i, c);
	c->elementsUsed++;

	return i;
}

uint16_t pscg_add_text(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t *str, uint16_t screen, gr2context * c){
	uint16_t i = 1;
	while(1){
	  if (c->pscgElements[i].valid==0){
	    break;
	  }
	  if (i >= c->elementsMax){
		  pscg_error((uint8_t *) "Maximum number of elements reached!", c);
		  return 0;
	  }
	  i++;
	}

	pscg_fill_zero_defaults(i, screen, c);
	c->pscgElements[i].type = GR2_TYPE_TEXT;
	pscg_add_fill_xy(i, x1, y1, x2, y2, c);
	c->pscgElements[i].str_value = str;
	//value: marks active textbox
	//param: stores cursor position
	//status_reg: bit0 - editable
	c->pscgElements[i].param2 = c->pscgScreens[c->pscgElements[screen].value].default_font; //font

	pscg_set_max_id(i, c);
	c->elementsUsed++;

	return i;
}

uint16_t pscg_add_slider_v(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, int32_t param, int32_t value, uint16_t screen, gr2context * c){
	uint16_t i = 1;
	while(1){
	  if (c->pscgElements[i].valid==0){
	    break;
	  }
	  if (i>=c->elementsMax){
		  pscg_error((uint8_t *) "Maximum number of elements reached!", c);
		  return 0;
	  }
	  i++;
	}

	pscg_fill_zero_defaults(i, screen, c);
	c->pscgElements[i].type = GR2_TYPE_SLIDER_V;
	pscg_add_fill_xy(i, x1, y1, x2, y2, c);
	c->pscgElements[i].param = param; //pozici slideru ovlivňuje value/param
	c->pscgElements[i].value = value;
	c->pscgElements[i].prev_val = value;
	pscg_set_max_id(i, c);
	c->elementsUsed++;

	return i;
}

uint16_t pscg_add_slider_h(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, int32_t param, int32_t value, uint16_t screen, gr2context * c){
	uint16_t i=1;
	while(1){
	  if (c->pscgElements[i].valid==0){
	    break;
	  }
	  if (i>=c->elementsMax){
		  pscg_error((uint8_t *) "Maximum number of elements reached!", c);
		  return 0;
	  }
	  i++;
	}

	pscg_fill_zero_defaults(i, screen, c);
	c->pscgElements[i].type = GR2_TYPE_SLIDER_H;
	pscg_add_fill_xy(i, x1, y1, x2, y2, c);
	c->pscgElements[i].param = param; //pozici slideru ovlivňuje value/param
	c->pscgElements[i].value = value;
	c->pscgElements[i].prev_val = value;

	pscg_set_max_id(i, c);
	c->elementsUsed++;

	return i;
}

//vertikální progbar
uint16_t pscg_add_progbar_v(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, int32_t param, int32_t value, uint16_t screen, gr2context * c){
	uint16_t i = 1;
	while(1){
	  if (c->pscgElements[i].valid==0){
	    break;
	  }
	  if (i>=c->elementsMax){
		  pscg_error((uint8_t *) "Maximum number of elements reached!", c);
		  return 0;
	  }
	  i++;
	}

	pscg_fill_zero_defaults(i, screen, c);
	c->pscgElements[i].type = GR2_TYPE_PROGBAR;
	pscg_add_fill_xy(i, x1, y1, x2, y2, c);
	c->pscgElements[i].param = param; //pozici progbaru ovlivňuje value/param
	c->pscgElements[i].value = value;
	c->pscgElements[i].prev_val = value;

	pscg_set_max_id(i, c);
	c->elementsUsed++;

	return i;

}

// image
uint16_t pscg_add_image(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t *str, uint16_t screen, gr2context * c){
	uint16_t i = 1;
	while(1){
	  if (c->pscgElements[i].valid==0){
	    break;
	  }
	  if (i>= c->elementsMax){
		  pscg_error((uint8_t *) "Maximum number of elements reached!", c);
		  return 0;
	  }
	  i++;
	}

	pscg_fill_zero_defaults(i, screen, c);
	c->pscgElements[i].type = GR2_TYPE_IMAGE;
	pscg_add_fill_xy(i, x1, y1, x2, y2, c);
	c->pscgElements[i].str_value = str;
	c->pscgElements[i].value = 1;

	pscg_set_max_id(i, c);
	c->elementsUsed++;

	return i;
}

uint16_t pscg_add_screen(gr2context * c){
	uint16_t i = 1;
	uint16_t scrI = 0;
	while(1){
	  if (c->pscgElements[i].valid==0){
	    break;
	  }
	  if (i>=c->elementsMax){
		  pscg_error((uint8_t *) "Maximum number of elements reached!", c);
		  return 0;
	  }
	  i++;
	}

	while(1){
	  if (c->pscgScreens[scrI].valid==0){
	    break;
	  }
	  if (scrI>=c->screensMax){
		  pscg_error((uint8_t *) "Maximum number of screens reached!", c);
		  return 0;
	  }
	  scrI++;
	}

	c->pscgScreens[scrI].valid = 1;
	c->pscgScreens[scrI].x_scroll = 0;
	c->pscgScreens[scrI].y_scroll = 0;
	c->pscgScreens[scrI].x_cell = c->default_grid_size;
	c->pscgScreens[scrI].y_cell = c->default_grid_size;
	c->pscgScreens[scrI].cell_space_left = c->default_grid_spacing;
	c->pscgScreens[scrI].cell_space_right = c->default_grid_spacing;
	c->pscgScreens[scrI].cell_space_bottom = c->default_grid_spacing;
	c->pscgScreens[scrI].cell_space_top = c->default_grid_spacing;
	c->pscgScreens[scrI].default_font = LCD_Get_Font_Size();

	pscg_fill_zero_defaults(i, i, c);
	c->pscgElements[i].type = GR2_TYPE_SCREEN;
	pscg_add_fill_xy(i, 0, 0, 1, 1, c);
	c->pscgElements[i].modified = 1; // new screen will get redrawn
	c->pscgElements[i].value = (int32_t)scrI;

	pscg_set_max_id(i, c);
	c->elementsUsed++;
	c->screensUsed++;

	return i;

}
