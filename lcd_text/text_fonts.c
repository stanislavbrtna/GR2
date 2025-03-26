/*
Copyright (c) 2025 Stanislav Brtna

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

#include "text_fonts.h"
#include "../fonts/fonts.h"

uint8_t * CurrentFont;
uint8_t * CurrentFont_cz;

uint8_t  CurrentSize;
int32_t  fontCorector_cz;


uint16_t LCD_Draw_Get_Font_Height() {
  return (uint16_t)CurrentFont[3];
}
  

uint16_t LCD_Draw_Get_Font_Width() {
  return (uint16_t)CurrentFont[2];
}
  

void LCD_Set_Sys_Font(uint8_t size) {
  if (size == 12) {
    CurrentSize     = 12;
    fontCorector_cz = -2;
    CurrentFont     = roboto12;
    CurrentFont_cz  = roboto12_cz;
  }

  if (size == 13) {
    CurrentSize     = 13;
    fontCorector_cz = -3;
    CurrentFont     = font12mono;
    CurrentFont_cz  = font12mono_cz;
  }

  if (size == 18) {
    CurrentSize     = 18;
    fontCorector_cz = -3;
    CurrentFont     = font18;
    CurrentFont_cz  = font18_cz;
  }

  if (size == 32) {
    CurrentSize     = 32;
    fontCorector_cz = -5;
    CurrentFont     = font32;
    CurrentFont_cz  = font32_cz;
  }

  if (size == 70) {
    CurrentSize = 70;
    CurrentFont = mono70;
  }

  if (size == 87) {
    CurrentSize     = 87;
    fontCorector_cz = -10;
    CurrentFont     = roboto87;
    CurrentFont_cz  = roboto87_cz;
  }
}
  