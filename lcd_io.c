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

#include "lcd_io.h"

void ExtDrawPoint(int x, int y, uint16_t color);
void ExtFillRect(int x,  int y, int w, int h, uint16_t color);

uint16_t hx1;
uint16_t hy1;
uint16_t hx2;
uint16_t hy2;

uint16_t counterX;
uint16_t counterY;

uint8_t lcd_hw_init() {
  return 0;
}

void lcd_hw_set_cursor(uint16_t Xpos, uint16_t Ypos) {
  return;
}

void lcd_hw_set_xy(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
  hx1 = x1;
  hx2 = x2;
  hy1 = y1;
  hy2 = y2;
  counterX = 0;
  counterY = 0;
  return;
}

void lcd_hw_Draw_Point(uint16_t color) {
	// Emulates behavior of LCD driver for SDL or something similar
  ExtDrawPoint(counterX + hx1, counterY + hy1, color);
  
  if (counterX < (hx2 - hx1)) {
	  counterX++;
  }else{
	  counterX=0;
 
    if (counterY < (hy2 - hy1)) {
    	counterY++;
    } else {
    	counterY = 0;
    }
  }
  return;
}
