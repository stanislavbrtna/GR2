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

#include "lcd_text.h"
#include "fonts/font18.h"
#include "fonts/font32.h"
#include "fonts/font18_cz.h"
#include "fonts/font32_cz.h"
#include "fonts/mono70.h"

#include "fonts/roboto87.h"
#include "fonts/roboto87_cz.h"

uint16_t fitTextMax;
uint8_t fitText;
const uint8_t * CurrentFont;
const uint8_t * CurrentFont_cz;
uint8_t CurrentSize; // current font size
int32_t fontCorector_cz;

// background color of the text field, ugly hack for fitting text
extern uint16_t background_color;

void LCD_set_fitText(uint8_t enable, uint16_t max) {
  fitTextMax = max;
  fitText = enable;
}

void LCD_Draw_Set_Font(uint8_t *font) {

  if (font == font18) {
    fontCorector_cz = -3;
    CurrentFont_cz  = font18_cz;
    CurrentSize     = 18;
  }

  if (font == font32) {
    fontCorector_cz = 0;
    CurrentFont_cz  = font32_cz;
    CurrentSize     = 32;
  }

  CurrentFont = font;
}

uint16_t LCD_Draw_Get_Font_Height() {
  return (uint16_t)CurrentFont[3];
}

uint16_t LCD_Draw_Get_Font_Width() {
  return (uint16_t)CurrentFont[2];
}

void LCD_Set_Sys_Font(uint8_t size) {
  if (size == 18) {
    CurrentSize     = 18;
    fontCorector_cz = -3;
    CurrentFont     = font18;
    CurrentFont_cz  = font18_cz;
  }

  if (size == 32) {
    CurrentSize     = 32;
    fontCorector_cz = 0;
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

void LCD_DrawText_ext(int16_t x, int16_t y, uint16_t color, uint8_t *text) {
  uint32_t i         = 0;
  uint32_t lw_det    = 0;
  uint32_t lastspace = 0;
  uint16_t lastX     = 0;
  uint16_t xLineCnt  = 0;
  uint16_t yLineCnt  = 0;
  uint8_t outChar    = 0;
  uint16_t yprac;

  while (0 != text[i]) {
    //bitbang utf8
    if (text[i] > 128) {
      yprac = y + yLineCnt * CurrentFont[3] + fontCorector_cz;
      xLineCnt += LCD_DrawChar(x + xLineCnt, yprac, color,  LCD_get_ext_char_num(text[i], text[i+1]), CurrentFont_cz);
      i++;
    } else {
      if (text[i] != '\n') {
        if (fitText == 1) {
          if (x + xLineCnt > fitTextMax - CurrentFont[2]) {
            if (lw_det != lastspace) {
              LCD_FillRect(
                           x + lastX,
                           y + yLineCnt*CurrentFont[3],
                           fitTextMax,
                           y + (yLineCnt + 1)*CurrentFont[3],
                           background_color
              );
              i = lastspace;
            }

            xLineCnt = 0;
            lw_det = lastspace;
            i++; // skip the space

            yLineCnt++;
            continue;
          }
        }

        if (text[i] == ' ') {
          lastspace = i;
          lastX = xLineCnt;
          xLineCnt += CurrentFont[2];
        } else if (text[i] == 9) { // tab
          lastspace = i;
          lastX = xLineCnt;
          xLineCnt =  (xLineCnt/(CurrentFont[2] * 4) + 1) * (CurrentFont[2] * 4);
        } else {
          outChar = text[i];
          xLineCnt += LCD_DrawChar(x + xLineCnt, y + yLineCnt * CurrentFont[3], color, outChar, CurrentFont);
        }

      } else {
        xLineCnt = 0;
        yLineCnt++;
      }
    }
    i++;
  }
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

uint16_t LCD_Text_Get_Width(uint8_t *text, uint16_t count) {
  uint32_t i        = 0;
  uint16_t xLineCnt = 0;
  uint16_t yLineCnt = 0;
  uint8_t outChar   = 0;
  uint16_t maxW     = 0;

  while (0 != text[i]) {
      if (text[i] > 128){
        xLineCnt += LCD_Char_Get_Width(LCD_get_ext_char_num(text[i], text[i+1]), CurrentFont_cz);
        i++;
      }else if (text[i] != '\n') {
        if (text[i] == ' ') {
          xLineCnt += CurrentFont[2];
        } else if (text[i] == 9) { // tab
          xLineCnt = (xLineCnt/(CurrentFont[2] * 4) + 1) * (CurrentFont[2] * 4);
        } else {
          outChar = text[i];
          xLineCnt += LCD_Char_Get_Width(outChar, CurrentFont);
        }
    } else {
      if (xLineCnt > maxW) {
        maxW = xLineCnt;
      }
      xLineCnt = 0;
      yLineCnt++;
    }
    i++;
    if((count != 0) && (i == count)) {
      return xLineCnt;
    }
  }

  if (xLineCnt > maxW) {
    maxW = xLineCnt;
  }

  return maxW;
}

uint16_t LCD_Text_Get_Height(uint8_t *text, uint16_t count) {
  uint32_t i = 0;
  uint16_t yLineCnt = 0;

  while (0 != text[i]) {
    if (text[i] == '\n') {
       // abychom nepřičetli, pokud je znakem enter, dělá to pak bordel
       // we wont count last carriage return
      if (i != count) {
        yLineCnt++;
      }
    }

    if((count != 0) && (i == count)) {
      break;
    }
    i++;
  }

  return yLineCnt*CurrentFont[3];
}

// předám x a y, ono to vrátí polohu kurzoru
// text and touch coordinates are passed, cursor position is returned
uint16_t LCD_Text_Get_Cursor_Pos(uint8_t *text, uint16_t touch_x, uint16_t touch_y) {
  uint32_t i        = 0;
  uint16_t xLineCnt = 0;
  uint16_t yLineCnt = 0;
  uint8_t outChar   = 0;
  uint8_t entFlg    = 0;
  uint8_t czFlag    = 0;
  uint16_t xstart   = 0;
  uint16_t ystart   = 0;
  uint16_t xstop    = 0;
  uint16_t ystop    = 0;

  while (0 != text[i]) {
      czFlag = 0;

      xstart = xLineCnt;
      ystart = yLineCnt*CurrentFont[3];

      if (text[i] > 128) {
        czFlag = 1;
        xLineCnt += LCD_Char_Get_Width(LCD_get_ext_char_num(text[i], text[i+1]), CurrentFont_cz);
        i++;

        xstop = xLineCnt;
        ystop = (yLineCnt+1) * CurrentFont[3];
    }else if (text[i] != '\n') {
      if (text[i] == ' ') {
        xLineCnt += CurrentFont[2];
      } else if (text[i] == 9) { // tab
        xLineCnt =  (xLineCnt/(CurrentFont[2] * 4) + 1) * (CurrentFont[2] * 4);
      } else {
        outChar = text[i];
        xLineCnt += LCD_Char_Get_Width(outChar, CurrentFont);
      }
      xstop = xLineCnt;
      ystop = (yLineCnt + 1)*CurrentFont[3];
    } else {

      xstop = 0xffff;
      ystop = (yLineCnt + 1) * CurrentFont[3];
      entFlg = 1;

      xLineCnt = 0;
      yLineCnt++;
    }

    if(entFlg == 0) {
      xstop = xLineCnt;
      ystop = (yLineCnt + 1)*CurrentFont[3];
    } else {
      entFlg = 0;
    }

    if ((touch_x > xstart) && (touch_x < xstop) && (touch_y > ystart) && (touch_y < ystop)) {
      return i - czFlag;
    }
    i++;
  }

  xstop = 0xffff;
  ystop = 0xffff;
  if ((touch_x > xstart) && (touch_x < xstop) && (touch_y > ystart) && (touch_y < ystop)) {
    return i;
  }
  return 0;
}

void LCD_Text_Draw_Cursor(int16_t x, int16_t y, uint8_t *text, uint16_t pos, uint16_t Color) {
  uint16_t xplus = 0;
  uint16_t yplus = 0;

  if(pos != 0) {
    xplus = LCD_Text_Get_Width(text, pos);
    yplus = LCD_Text_Get_Height(text, pos);
  }

  LCD_DrawLine(x + xplus, y + yplus, x + xplus, y + yplus + CurrentFont[3], Color);
}


// returns char width
uint16_t LCD_DrawChar(int16_t x, int16_t y, uint16_t color, uint16_t znak, const uint8_t *font) {
  uint32_t a, b, d;
  uint16_t xLineCnt = 0;
  uint16_t yLineCnt = 0;
  uint16_t cv;
  uint32_t cpos;
  uint32_t cposIncr = 0;
  uint16_t FontSize;
  uint8_t liche = 0;

  xLineCnt = x;

  if (((font[3] / 8) * 8) == font[3]) {
    FontSize = font[3]/8;
  } else {
    FontSize = font[3]/8 + 1;
    liche = font[3]%8;
  }

  if ((znak >= 32 && znak <= 128) || (znak >= 193 && znak <= 383)) {
    cposIncr = 0;
    cv = font[znak + 6 - font[4]];
    cpos = font[5] + 6; //96+6 - první znak

    for (a = 6; a < (uint32_t)(znak - font[4] + 6); a++) { //napočítáme pozici znaku
      cpos += font[a] * FontSize;
    }

    for (a = 0; a < FontSize; a++) { //je to po deseti bitech na sloupeček
      for (b = 0; b < cv; b++) {
        for(d = 0; d < 8; d++) {
          if (font[cpos + cposIncr] & (1 << d)) {
            if (liche == 0) {
              LCD_DrawPoint(xLineCnt + b, y + yLineCnt * font[3] + a*8 + d, color);
            } else {
              if (a < (uint32_t)(FontSize - 1)) {
                LCD_DrawPoint(xLineCnt + b, y + yLineCnt*font[3] + a*8 + d, color);
              } else {
                LCD_DrawPoint(xLineCnt + b, y + yLineCnt*font[3] + (a - 1)*8 + liche + d, color);
              }
            }
          }
        }
        cposIncr++;
      }
    }
    return cv + font[2]/9 + font[2]%9;
  } else {
    if (znak != 0) {
      LCD_DrawRectangle(x + 1, y + 1, x + font[2] - 2 , y + font[3] - 2, color);
      return font[2];
    }
  }
  return 0;
}

uint16_t LCD_Char_Get_Width(uint16_t znak, const uint8_t *font) {
  uint16_t cv;

  if (znak != 0) {
    cv = font[znak + 6 - font[4]];
    return cv + font[2]/9 + font[2]%9;
  }
  return 0;
}
