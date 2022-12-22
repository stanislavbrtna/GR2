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
#include "lcd_canvas.h"

extern volatile int16_t draw_area_x1;
extern volatile int16_t draw_area_x2;
extern volatile int16_t draw_area_y1;
extern volatile int16_t draw_area_y2;

extern uint16_t lcd_x_size;
extern uint16_t lcd_y_size;

int16_t canvas_drawAreaX1;
int16_t canvas_drawAreaY1;
int16_t canvas_drawAreaX2;
int16_t canvas_drawAreaY2;

uint16_t canvas_hardX1;
uint16_t canvas_hardY1;
uint16_t canvas_hardX2;
uint16_t canvas_hardY2;

int16_t canvas_width;
int16_t canvas_height;
int16_t canvas_x;
int16_t canvas_y;

uint32_t canvas_pos;

void LCD_canvas_set(int16_t x1, int16_t y1, int16_t x2, int16_t y2) {
  uint16_t prac;

  if (x2 < x1){
    prac = x1;
    x1 = x2;
    x2 = prac;
  }

  if (y2 < y1){
    prac = y1;
    y1 = y2;
    y2 = prac;
  }

  canvas_drawAreaX1 = x1;
  canvas_drawAreaY1 = y1;
  canvas_drawAreaX2 = x2;
  canvas_drawAreaY2 = y2;

  // originální pozice
  canvas_x = x1;
  canvas_y = y1;

  // velikost arey
  canvas_width = x2 - x1;
  canvas_height = y2 - y1;

  canvas_pos = 0;

  //vytvoření draw arey
  if (x1 < draw_area_x1){
    canvas_hardX1 = draw_area_x1;
  } else {
    if (y2 < 0) {
      canvas_hardX1 = 0;
    } else if (x1 > lcd_x_size) {
      canvas_hardX1 = lcd_x_size;
    } else {
      canvas_hardX1 = x1;
    }
  }

  if (x2 > draw_area_x2){
    canvas_hardX2 = draw_area_x2;
  } else {
    if (x2 < 0) {
      canvas_hardX2 = 0;
    } else if (x2 > lcd_x_size) {
      canvas_hardX2 = lcd_x_size;
    } else {
      canvas_hardX2 = x2;
    }
  }

  if (y1 < draw_area_y1){
    canvas_hardY1 = draw_area_y1;
  } else {
    if (y2 < 0) {
      canvas_hardY1 = 0;
    } else if (y1 > lcd_y_size) {
      canvas_hardY1 = lcd_y_size;
    } else {
      canvas_hardY1 = y1;
    }
  }

  if (y2 > draw_area_y2){
    canvas_hardY2 = draw_area_y2;
  } else {
    if (y2 < 0) {
      canvas_hardY2 = 0;
    } else if (y2 > lcd_y_size) {
      canvas_hardY2 = lcd_y_size;
    } else {
      canvas_hardY2 = y2;
    }
  }

  LCD_set_XY(canvas_hardX1, canvas_hardY1, canvas_hardX2, canvas_hardY2);
}

void LCD_canvas_zero() {
  canvas_pos = 0;
}

void LCD_canvas_putcol(uint16_t color) {
  uint16_t current_x, current_y;

  current_x = canvas_x + (canvas_pos % (canvas_width + 1));
  current_y = canvas_y + (canvas_pos / (canvas_width + 1));

  if ((current_x >= canvas_hardX1)
      && (current_x <= canvas_hardX2)
      && (current_y >= canvas_hardY1)
      && (current_y <= canvas_hardY2)
     ) {
    lcd_hw_Draw_Point(color);
  }

  canvas_pos++;
}
