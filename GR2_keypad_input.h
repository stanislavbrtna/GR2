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

#ifndef _GR2_KEYPAD_INPUT_H
#define _GR2_KEYPAD_INPUT_H

#include "GR2.h"

typedef enum {GR2_BUTTON_UP, GR2_BUTTON_DOWN, GR2_BUTTON_LEFT,GR2_BUTTON_RIGHT, GR2_BUTTON_OK, GR2_BUTTON_CANCEL} gr2ButtonType;

void gr2_ki_unselect(uint16_t screen, gr2context * con);
uint8_t gr2_keypad_input(gr2ButtonType button, gr2EventType ev, uint16_t screen, gr2context * con);

#endif