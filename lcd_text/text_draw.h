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

#ifndef LCD_TEXT_DRAW_H
#define LCD_TEXT_DRAW_H
#include "../GR2.h"

void LCD_DrawText_ext(int16_t x, int16_t y, uint16_t color, uint8_t *text);

void LCD_set_text_block(uint32_t start, uint32_t end, uint16_t color);
void LCD_set_fitText(uint8_t enable, uint16_t max);
void LCD_set_text_bg(uint8_t enable, uint16_t color, int16_t width, int16_t height);

uint16_t LCD_Text_Get_Width(uint8_t *text, uint16_t count); //if count == 0 maximum line width is returned
uint16_t LCD_Text_Get_Height(uint8_t *text, uint16_t count); //if count == 0 maximum line height is returned
uint16_t LCD_Text_Get_Cursor_Pos(uint8_t *text, int16_t touch_x, int16_t touch_y, uint16_t max_w);

void LCD_Text_Draw_Cursor(int16_t x, int16_t y, uint8_t *text, uint16_t pos, uint16_t Color);

void LCD_Text_Get_WH(uint8_t *text, uint16_t pos, uint16_t max_w, uint16_t *width, uint16_t *height);

#endif
