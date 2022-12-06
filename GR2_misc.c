/*
Copyright (c) 2022 Stanislav Brtna

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

// init, reset, destroy

void gr2_init_context(gr2context * c, gr2Element *pscgElementsArray, uint16_t elementsCount, gr2Screen *pscgScreens, uint16_t screensCount) {

  c->elementsMax  = elementsCount;
  c->screensMax   = screensCount;
  c->pscgElements = pscgElementsArray;
  c->pscgScreens  = pscgScreens;

  gr2_reset_context(c);
}


void gr2_reset_context(gr2context * c) {

  gr2_reset_all(c);

  c->textActive                = 0;
  c->textActiveId              = 0;
  c->invisible_flag            = 0;
  c->reset_active_element_flag = 0;
  c->textMouseX                = 0;
  c->textMouseY                = 0;
  c->default_grid_size         = 32;
  c->default_grid_spacing      = 0;
  c->pscg_active_element       = 0;
  c->relative_init             = 0;

  c->border_color     = 0x0000; // black
  c->text_color       = 0x0000; // black
  c->background_color = 0xF800; // red
  c->fill_color       = 0x07E0; // green
  c->active_color     = 0xFFFF; // white
}


// this function is here so elements_used is not decremented twice when recursion occurs
void gr2_destroy_screen_lvl2(uint16_t id, gr2context * c) {
  uint16_t x;
  PSCG_BOUNDARY_CHECK_AND_RETURN();

  c->pscgElements[id].valid = 0;
  c->pscgScreens[c->pscgElements[id].value].valid = 0;
  c->screensUsed--;

  for(x = 1; x <= c->elementsMax; x++) {
    if ((c->pscgElements[x].screen_id == id) && (c->pscgElements[x].valid == 1)) {
      if (c->pscgElements[x].valid == 1) {
        if (c->pscgElements[x].type == 0) {
          gr2_destroy_screen_lvl2(x, c);
        }
        c->elementsUsed--;
        c->pscgElements[x].valid = 0;
      }
    }
  }
}


void gr2_destroy_screen(uint16_t id, gr2context * c) {
  PSCG_BOUNDARY_CHECK_AND_RETURN();
  if (c->pscgElements[id].valid != 1) {
    return;
  }
  c->elementsUsed--;

  gr2_destroy_screen_lvl2(id, c);
}


void gr2_destroy(uint16_t id, gr2context * c) {
  PSCG_BOUNDARY_CHECK_AND_RETURN();
  if (c->pscgElements[id].valid) {
    if (c->pscgElements[id].type == GR2_TYPE_SCREEN) {
      gr2_destroy_screen(id, c);
    } else {
      c->pscgElements[id].valid = 0;
      c->elementsUsed--;
    }
  }
  if (c->pscgElements[c->pscgElements[id].screen_id].valid) {
    c->pscgElements[c->pscgElements[id].screen_id].modified = 1;
  }
}

// Errors

void gr2_error_callback_default(uint8_t *str, gr2context * c) {
  printf("PSCG Error: %s\n", str);
  (void)(c);
}

void gr2_error_callback (uint8_t *str, gr2context * c) __attribute__ ((weak, alias ("gr2_error_callback_default")));


void gr2_error(uint8_t *str, gr2context * c) {
  gr2_error_callback(str, c);
}


// events clearing

void gr2_cleanup(gr2context * c) {
  uint16_t x;
  for(x = 1; x <= c->elementsMax; x++) {
    if (c->pscgElements[x].valid == 1) {
      c->maxElementsId = x;
    }
  }
}

void gr2_clear_screen_ev(uint16_t id, gr2context * c) {
  uint16_t x;
  PSCG_BOUNDARY_CHECK_AND_RETURN();
  for(x = 1; x <= c->maxElementsId; x++) {
    if ((c->pscgElements[x].screen_id == id) && (c->pscgElements[x].valid == 1)) {
      gr2_set_event(x, EV_NONE, c);
    }
  }
}

void gr2_clear_event(uint16_t id, gr2context * c) {
  PSCG_BOUNDARY_CHECK_AND_RETURN();
  if (c->pscgElements[id].type != 0) {
    gr2_set_event(id, EV_NONE, c);
  } else {
    gr2_clear_screen_ev(id, c);
  }
}


void gr2_reset_all(gr2context * c) {
  uint16_t x = 0;

  for(x = 1; x <= c->elementsMax; x++) {
    c->pscgElements[x].valid = 0;
  }
  for(x = 1; x <= c->screensMax; x++) {
    c->pscgScreens[x].valid = 0;
  }
  c->screensUsed   = 0;
  c->elementsUsed  = 0;
  c->maxElementsId = 0;

  gr2_set_global_grayout_flag(0);
}

// misc

uint8_t gr2_clicked(uint16_t id, gr2context * c) {
  PSCG_BOUNDARY_CHECK_AND_RETURN_ZERO();
  if ((c->pscgElements[id].event == EV_RELEASED)) {
    gr2_set_event(id, EV_NONE, c);
    return 1;
  } else {
    gr2_set_event(id, EV_NONE, c);
    return 0;
  }
}


// Sets redraw flag to all valid elements
void gr2_redraw_all(gr2context * c) {
  uint16_t x;
  for(x = 1; x <= c->elementsMax; x++) {
      if (c->pscgElements[x].valid == 1) {
        c->pscgElements[x].modified = 1;
      }
  }
}


uint16_t gr2_get_tmx(gr2context * c) {
  return c->textMouseX;
}


uint16_t gr2_get_tmy(gr2context * c) {
  return c->textMouseY;
}
