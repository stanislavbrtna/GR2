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


uint8_t gr2_ki_get_selectable(uint16_t id, gr2context * con) {

  if(con->pscgElements[id].valid == 0)
    return 0;
  
  if(con->pscgElements[id].visible == 0)
    return 0;

  if(gr2_get_grayout(id, con) == 1)
    return 0;

  switch (con->pscgElements[id].type) {
  case GR2_TYPE_BUTTON:
    return 1;
    break;

  case GR2_TYPE_SLIDER_V:
    return 1;
    break;

  case GR2_TYPE_TEXT:
    if(gr2_text_get_editable(id, con)) 
      return 1;
    else
      return 0;
    break;
  
  case GR2_TYPE_ICON:
    return 1;
    break;

  case GR2_TYPE_SLIDER_H:
    return 1;
    break;

  case GR2_TYPE_COLOR_BUTTON:
    return 1;
    break;

  case GR2_TYPE_CHECKBOX:
    return 1;
    break;

  default:
    return 0;
  }
}


uint8_t gr2_ki_select(uint16_t id, gr2context * con) {
  if (gr2_ki_get_selectable(id, con) == 0) {
    return 0;
  }

  if (con->pscgScreens[con->pscgElements[con->pscgElements[id].screen_id].value].kbd_selected != 0) {
    gr2_set_select(con->pscgScreens[con->pscgElements[con->pscgElements[id].screen_id].value].kbd_selected, 0, con);
  }
  con->pscgScreens[con->pscgElements[con->pscgElements[id].screen_id].value].kbd_selected = id;
  gr2_set_select(id, 1, con);

  return 1;
}


void gr2_ki_unselect(uint16_t screen, gr2context * con) {
  if (con->pscgScreens[con->pscgElements[screen].value].kbd_selected != 0) {
    gr2_set_select(con->pscgScreens[con->pscgElements[screen].value].kbd_selected, 0, con);
    con->pscgScreens[con->pscgElements[screen].value].kbd_selected = 0;
  }
}


uint8_t gr2_keypad_input(gr2ButtonType button, gr2EventType ev, uint16_t screen, gr2context * con) {
  uint16_t current_element;
  uint16_t closest_element = 0;

  if (con->pscgScreens[con->pscgElements[screen].value].kbd_selected == 0 && ev == EV_PRESSED) {
    for (uint16_t i = 1; i <= con->maxElementsId; i++) {
      if ((con->pscgElements[i].screen_id == screen) && (i != screen) && (con->pscgElements[i].valid == 1) && gr2_ki_get_selectable(i, con)) {
        current_element = i;
        gr2_ki_select(i, con);
        return 0;
      }
    }
  } else {
    current_element = con->pscgScreens[con->pscgElements[screen].value].kbd_selected;
  }

  // handling sliders
  if (con->pscgElements[current_element].type == GR2_TYPE_SLIDER_H || con->pscgElements[current_element].type == GR2_TYPE_SLIDER_V) {

    if (con->pscgElements[current_element].type == GR2_TYPE_SLIDER_H) {
      if (button == GR2_BUTTON_RIGHT && ev == EV_PRESSED) {
        if (gr2_get_value(current_element, con) + gr2_get_param(current_element, con)/10 < gr2_get_param(current_element, con)) {
          gr2_set_value(current_element, gr2_get_value(current_element, con) + gr2_get_param(current_element, con)/10, con);
        } else {
          gr2_set_value(current_element, gr2_get_param(current_element, con), con);
        }
        gr2_set_event(current_element, EV_PRESSED, con);
        return 1; 
      }

      if (button == GR2_BUTTON_LEFT && ev == EV_PRESSED) {
        if (gr2_get_value(current_element, con) - gr2_get_param(current_element, con)/10 > 0) {
          gr2_set_value(current_element, gr2_get_value(current_element, con) - gr2_get_param(current_element, con)/10, con);
        } else {
          gr2_set_value(current_element, 0, con);
        }
        gr2_set_event(current_element, EV_PRESSED, con);
        return 1;
      }
    }

    if (con->pscgElements[current_element].type == GR2_TYPE_SLIDER_V) {
      if (button == GR2_BUTTON_DOWN && ev == EV_PRESSED) {
        if (gr2_get_value(current_element, con) + gr2_get_param(current_element, con)/10 < gr2_get_param(current_element, con)) {
          gr2_set_value(current_element, gr2_get_value(current_element, con) + gr2_get_param(current_element, con)/10, con);
        } else {
          gr2_set_value(current_element, gr2_get_param(current_element, con), con);
        }
        gr2_set_event(current_element, EV_PRESSED, con);
        return 1; 
      }

      if (button == GR2_BUTTON_UP && ev == EV_PRESSED) {
        if (gr2_get_value(current_element, con) - gr2_get_param(current_element, con)/10 > 0) {
          gr2_set_value(current_element, gr2_get_value(current_element, con) - gr2_get_param(current_element, con)/10, con);
        } else {
          gr2_set_value(current_element, 0, con);
        }
        gr2_set_event(current_element, EV_PRESSED, con);
        return 1;
      }
    }
  }

  if (button == GR2_BUTTON_RIGHT && ev == EV_PRESSED) {
    for (uint16_t i = 1; i <= con->maxElementsId; i++) {
      if ((con->pscgElements[i].screen_id == screen) && (i != screen) && (con->pscgElements[i].valid == 1) && gr2_ki_get_selectable(i, con)) {
        if (con->pscgElements[i].x1 >= con->pscgElements[current_element].x2 && con->pscgElements[i].y1 == con->pscgElements[current_element].y1 && closest_element == 0) {
          closest_element = i;
        } else if (con->pscgElements[i].x1 <= con->pscgElements[closest_element].x1 && con->pscgElements[current_element].x2 <= con->pscgElements[i].x1 && con->pscgElements[i].y1 == con->pscgElements[current_element].y1 && i != current_element) {
          closest_element = i;
        }
      }
    }
    if (closest_element == 0) {
      for (uint16_t i = 1; i <= con->maxElementsId; i++) {
        if ((con->pscgElements[i].screen_id == screen) && (i != screen) && (con->pscgElements[i].valid == 1) && gr2_ki_get_selectable(i, con)) {
          if (con->pscgElements[i].x1 >= con->pscgElements[current_element].x2 && closest_element == 0) {
            closest_element = i;
          } else if (con->pscgElements[i].x1 <= con->pscgElements[closest_element].x1 && con->pscgElements[current_element].x2 <= con->pscgElements[i].x1 && i != current_element) {
            closest_element = i;
          }
        }
      } 
    }
  }

  if (button == GR2_BUTTON_LEFT && ev == EV_PRESSED) {
    for (uint16_t i = 1; i <= con->maxElementsId; i++) {
      if ((con->pscgElements[i].screen_id == screen) && (i != screen) && (con->pscgElements[i].valid == 1) && gr2_ki_get_selectable(i, con)) {
        if (con->pscgElements[i].x2 <= con->pscgElements[current_element].x1 && con->pscgElements[i].y1 == con->pscgElements[current_element].y1 && closest_element == 0) {
          closest_element = i;
        } else if (con->pscgElements[i].x2 >= con->pscgElements[closest_element].x2 && con->pscgElements[i].x2 <= con->pscgElements[current_element].x1 && con->pscgElements[i].y1 == con->pscgElements[current_element].y1 && i != current_element) {
          closest_element = i;
        }
      }
    }
    if (closest_element == 0) {
      for (uint16_t i = 1; i <= con->maxElementsId; i++) {
        if ((con->pscgElements[i].screen_id == screen) && (i != screen) && (con->pscgElements[i].valid == 1) && gr2_ki_get_selectable(i, con)) {
          if (con->pscgElements[i].x2 <= con->pscgElements[current_element].x1 && closest_element == 0) {
            closest_element = i;
          } else if (con->pscgElements[i].x2 >= con->pscgElements[closest_element].x2 && con->pscgElements[i].x2 <= con->pscgElements[current_element].x1 && i != current_element) {
            closest_element = i;
          }
        }
      }
    }
  }

  if (button == GR2_BUTTON_UP && ev == EV_PRESSED) {
    for (uint16_t i = 1; i <= con->maxElementsId; i++) {
      if ((con->pscgElements[i].screen_id == screen) && (i != screen) && (con->pscgElements[i].valid == 1) && gr2_ki_get_selectable(i, con)) {
        if (con->pscgElements[i].y2 <= con->pscgElements[current_element].y1 && con->pscgElements[i].x1 == con->pscgElements[current_element].x1 && closest_element == 0) {
          closest_element = i;
        } else if (con->pscgElements[i].y2 >= con->pscgElements[closest_element].y2 && con->pscgElements[i].y2 <= con->pscgElements[current_element].y1 && i != current_element) {
          closest_element = i;
        }
      }
    }
    if (closest_element == 0) {
      for (uint16_t i = 1; i <= con->maxElementsId; i++) {
        if ((con->pscgElements[i].screen_id == screen) && (i != screen) && (con->pscgElements[i].valid == 1) && gr2_ki_get_selectable(i, con)) {
          if (con->pscgElements[i].y2 <= con->pscgElements[current_element].y1 && con->pscgElements[i].x1 == con->pscgElements[current_element].x1 && closest_element == 0) {
            closest_element = i;
          } else if (con->pscgElements[i].y2 >= con->pscgElements[closest_element].y2 && con->pscgElements[i].y2 <= con->pscgElements[current_element].y1 && i != current_element) {
            closest_element = i;
          }
        }
      }
    }
    
  }

  if (button == GR2_BUTTON_DOWN && ev == EV_PRESSED) {
    for (uint16_t i = 1; i <= con->maxElementsId; i++) {
      if ((con->pscgElements[i].screen_id == screen) && (i != screen) && (con->pscgElements[i].valid == 1) && gr2_ki_get_selectable(i, con)) {
        if (con->pscgElements[i].y1 >= con->pscgElements[current_element].y2 && con->pscgElements[i].x1 == con->pscgElements[current_element].x1 && closest_element == 0) {
          closest_element = i;
        } else if (con->pscgElements[i].y1 <= con->pscgElements[closest_element].y1 && con->pscgElements[i].y1 >= con->pscgElements[current_element].y2 && con->pscgElements[i].x1 == con->pscgElements[current_element].x1 && i != current_element) {
          closest_element = i;
        }
      }
    }

    if (closest_element == 0) {
      for (uint16_t i = 1; i <= con->maxElementsId; i++) {
        if ((con->pscgElements[i].screen_id == screen) && (i != screen) && (con->pscgElements[i].valid == 1) && gr2_ki_get_selectable(i, con)) {
          if (con->pscgElements[i].y1 >= con->pscgElements[current_element].y2 && closest_element == 0) {
            closest_element = i;
          } else if (con->pscgElements[i].y1 <= con->pscgElements[closest_element].y1 && con->pscgElements[i].y1 >= con->pscgElements[current_element].y2 && i != current_element) {
            closest_element = i;
          }
        }
      }
    }
  }

  if(closest_element != 0) {
    gr2_ki_select(closest_element,con);
    current_element = closest_element;
  }

  if (button == GR2_BUTTON_OK && ev != EV_NONE && gr2_get_event(current_element, con) != ev) {
    if (con->pscgElements[current_element].type == GR2_TYPE_TEXT && gr2_text_get_editable(current_element, con)) {
      gr2_activate_text(current_element, con);
      return 2;
    }
    gr2_set_event(current_element, ev, con);
    return 1;
  }
  return 0;
}