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

#include "char_utils.h"

extern uint8_t * CurrentFont;
extern uint8_t * CurrentFont_cz;

extern uint8_t  CurrentSize;
extern int32_t  fontCorector_cz;

extern volatile int16_t draw_area_x1;
extern volatile int16_t draw_area_x2;
extern volatile int16_t draw_area_y1;
extern volatile int16_t draw_area_y2;

extern uint8_t  textBgFill;
extern uint16_t textBgColor;

uint16_t charLine[8];


static void draw_char_line(int16_t x, int16_t y, uint8_t len) {
  int16_t yTopOffset = 0;
  // set XY with draw area in mind
  if (x > draw_area_x2 || x < draw_area_x1 || y + len < draw_area_y1 || y > draw_area_y2) {
    return;
  }

  if (y < draw_area_y1) {
    yTopOffset = draw_area_y1 - y;
    y = draw_area_y1;
  }

  if (y + len > draw_area_y2) {
    len = draw_area_y2 - y;
  }

  lcdOrientationType or = LCD_get_orientation();

  if (or == OR_NORMAL || or == OR_ROT_LEFT) {
    LCD_set_XY(x, y, x, y + len);
    for(int16_t i = yTopOffset; i < len; i++) {
      lcd_hw_Draw_Point(charLine[i]);
    }
  }
  
  if (or == OR_ROT_RIGHT || or == OR_UPSIDE_DOWN ) {
    LCD_set_XY(x, y - 1, x, y + len - 1);
    for(int16_t i = len - 1; i >= yTopOffset; i--) {
      lcd_hw_Draw_Point(charLine[i]);
    }
  }
}

// returns char width
uint16_t LCD_DrawChar(int16_t x, int16_t y, uint16_t color, uint16_t charIndex, const uint8_t *font) {
  uint32_t a, b, d;
  uint16_t char_width;
  uint32_t cpos;
  uint32_t cposIncr = 0;
  uint16_t FontSize;
  uint8_t liche = 0;

  char_width = font[charIndex + 6 - font[4]];

  if (((font[3] / 8) * 8) == font[3]) {
    FontSize = font[3]/8;
  } else {
    FontSize = font[3]/8 + 1;
    liche = font[3]%8;
  }

  if (!(charIndex >= font[4] && charIndex <= font[4] + font[5])) {
    // unknown char...
    if(textBgFill) {
      LCD_FillRect(x, y, x + font[2], y + font[3], textBgColor);
    }
    LCD_DrawRectangle(x + 1, y + 1, x + font[2] - 2 , y + font[3] - 2, color);
    return font[2];
  }

  if(x + char_width < draw_area_x1 || x > draw_area_x2 || y + font[3] < draw_area_y1 || y > draw_area_y2) {
    return char_width + font[2]/9 + font[2]%9;
  }

  cposIncr = 0;
  cpos = font[5] + 6; //96+6 - první znak

  for (a = 6; a < (uint32_t)(charIndex - font[4] + 6); a++) { // get char position
    cpos += font[a] * FontSize;
  }

  if(textBgFill == 0) {
    for (a = 0; a < FontSize; a++) { // fontSize per column
      for (b = 0; b < char_width; b++) {
        for(d = 0; d < 8; d++) {
          if (font[cpos + cposIncr] & (1 << d)) {
            if (liche == 0) {
              LCD_DrawPoint(x + b, y  + a*8 + d, color);
            } else {
              if (a < (uint32_t)(FontSize - 1)) {
                LCD_DrawPoint(x + b, y + a*8 + d, color);
              } else {
                LCD_DrawPoint(x + b, y + (a - 1)*8 + liche + d, color);
              }
            }
          }
        }
        cposIncr++;
      }
    }
  } else {
    for (a = 0; a < FontSize; a++) {
      for (b = 0; b < char_width; b++) {
        if (a < (uint32_t)(FontSize - 1) || (liche == 0)) {
          for(d = 0; d < 8; d++) {
            if (font[cpos + cposIncr] & (1 << d)) {
              charLine[d] = color;
            } else {
              charLine[d] = textBgColor;
            }
          }
          draw_char_line(x + b, y + a*8, 8);
          cposIncr++;
        } else {
          uint8_t i = 0;
          for(d = 8 - liche; d < 8; d++) {
            if (font[cpos + cposIncr] & (1 << d)) {
              charLine[i] = color;
            } else {
              charLine[i] = textBgColor;
            }
            i++;
          }

          draw_char_line(x + b, y + a*8, liche);
          cposIncr++;
        }
      }
    }
    
    LCD_FillRect(x+char_width, y, x + char_width + font[2]/9 + font[2]%9, y + font[3], textBgColor);
  }
  
  return char_width + font[2]/9 + font[2]%9;
}


uint16_t LCD_Char_Get_Width(uint16_t znak, const uint8_t *font) {
  uint16_t cv;

  if (znak != 0) {
    cv = font[znak + 6 - font[4]];
    return cv + font[2]/9 + font[2]%9;
  }
  return 0;
}


uint8_t LCD_Get_Font_Size() {
  return CurrentSize;
}
  
  
uint16_t LCD_get_ext_char_num(uint8_t b1, uint8_t b2) {
  if((b1 == 0xC3) && (b2 == 0x81)){ //Á
    return 193;
  }else if((b1 == 0xC4) && (b2 == 0x8C)){ //Č
    return 268;
  }else if((b1 == 0xC4) && (b2 == 0x8E)){ //Ď
    return 270;
  }else if((b1 == 0xC3) && (b2 == 0x89)){ //É
    return 201;
  }else if((b1 == 0xC4) && (b2 == 0x9a)){ //Ě
    return 201;
  }else if((b1 == 0xC3) && (b2 == 0x8D)){ //Í
    return 205;
  }else if((b1 == 0xC5) && (b2 == 0x87)){ //Ň
    return 327;
  }else if((b1 == 0xC3) && (b2 == 0x93)){ //Ó
    return 211;
  }else if((b1 == 0xC5) && (b2 == 0x98)){ //Ř
    return 344;
  }else if((b1 == 0xC5) && (b2 == 0xa0)){ //Š
    return 352;
  }else if((b1 == 0xC5) && (b2 == 0xa4)){ //Ť
    return 356;
  }else if((b1 == 0xC3) && (b2 == 0x9a)){ //Ú
    return 218;
  }else if((b1 == 0xC5) && (b2 == 0xae)){ //Ů
    return 366;
  }else if((b1 == 0xC3) && (b2 == 0x9d)){ //Ý
    return 221;
  }else if((b1 == 0xC5) && (b2 == 0xbd)){ //Ž
    return 381;
  }else if((b1 == 0xC3) && (b2 == 0xa1)){ //á
    return 225;
  }else if((b1 == 0xC4) && (b2 == 0x8d)){ //č
    return 269;
  }else if((b1 == 0xC4) && (b2 == 0x8f)){ //ď
    return 271;
  }else if((b1 == 0xC3) && (b2 == 0xa9)){ //é
    return 233;
  }else if((b1 == 0xC4) && (b2 == 0x9b)){ //ě
    return 283;
  }else if((b1 == 0xC3) && (b2 == 0xad)){ //í
    return 237;
  }else if((b1 == 0xC5) && (b2 == 0x88)){ //ň
    return 328;
  }else if((b1 == 0xC3) && (b2 == 0xb3)){ //ó
    return 243;
  }else if((b1 == 0xC5) && (b2 == 0x99)){ //ř
    return 345;
  }else if((b1 == 0xC5) && (b2 == 0xa1)){ //š
    return 353;
  }else if((b1 == 0xC5) && (b2 == 0xa5)){ //ť
    return 357;
  }else if((b1 == 0xC3) && (b2 == 0xba)){ //ú
    return 250;
  }else if((b1 == 0xC5) && (b2 == 0xaf)){ //ů
    return 367;
  }else if((b1 == 0xC3) && (b2 == 0xbd)){ //ý
    return 253;
  }else if((b1 == 0xC5) && (b2 == 0xbe)){ //í
    return 382;
  }
  return 0;
}

uint16_t LCD_get_emoji_num(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4) {
  if(b1 == 0xF0 && b2 == 0x9F){
    if(b3 == 0x98 && b4 >= 0x80) return b4 - 0x80 + 1;
    
    if(b3 == 0x99 && b4 >= 0x80) {
      return b4 - 0x80 + 0x3F + 2;
    }
  }

  return 0;
}


void LCD_DrawText_Pwd(int16_t x, int16_t y, uint16_t color, uint8_t *text) {
  uint16_t xLineCnt = 0;
  uint32_t i        = 0;

  while (0 != text[i]) {
    xLineCnt += LCD_DrawChar(x + xLineCnt, y, color, '*', CurrentFont);
    i++;
  }
}


void LCD_Text_Draw_Cursor_Pwd(int16_t x, int16_t y, uint8_t *text, uint16_t Color) {
  uint16_t xplus = 0;
  uint32_t i = 0;

  while (0 != text[i]) {
    xplus += LCD_Char_Get_Width('*', CurrentFont);
    i++;
  }

  LCD_DrawLine(x + xplus, y, x + xplus, y + CurrentFont[3], Color);
}