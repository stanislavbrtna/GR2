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

#include "fonts/roboto12.h"
#include "fonts/roboto12_cz.h"

#include "fonts/font12mono.h"
#include "fonts/font12mono_cz.h"


const uint8_t * CurrentFont;
const uint8_t * CurrentFont_cz;

uint16_t fitTextMax;
uint8_t  fitText;
uint8_t  CurrentSize; // current font size
int32_t  fontCorector_cz;
uint32_t blockStart;
uint32_t blockEnd;
uint16_t blockColor;

uint8_t  textBgFill;
int16_t  textBgWidth;
int16_t  textBgHeight;
uint16_t textBgColor;

void LCD_set_text_bg(uint8_t enable, uint16_t color, int16_t width, int16_t height) {
  textBgFill = enable;
  textBgColor = color;
  textBgWidth = width;
  textBgHeight = height;
}


void LCD_set_fitText(uint8_t enable, uint16_t max) {
  fitTextMax = max;
  fitText = enable;
}

uint16_t LCD_Draw_Get_Font_Height() {
  return (uint16_t)CurrentFont[3];
}

uint16_t LCD_Draw_Get_Font_Width() {
  return (uint16_t)CurrentFont[2];
}

void LCD_set_text_block(uint32_t start, uint32_t end, uint16_t color) {
  blockStart = start;
  blockEnd = end;
  blockColor = color;
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

#define LCD_BLOCK_SELECT_SPACER 3*(yLineCnt == 0) // make the first line of the block taller

static inline uint16_t LCD_Text_Get_Word_Width(uint8_t *text) {
  uint16_t width = 0;
  uint32_t i = 0;
  while(text[i] != 0) {
    if (text[i] > 128) {
      width += LCD_Char_Get_Width(LCD_get_ext_char_num(text[i], text[i+1]), CurrentFont_cz);
      i += 2;
      continue;

    } else if (text[i] == '\n') {
      return width;
    } else if (text[i] == ' ') {
      return width;
    } else if (text[i] == 9) {
      return width;
    } else {
      width += LCD_Char_Get_Width(text[i], CurrentFont);
    }
    i++;
  }

  return width;
}


void LCD_DrawText_ext(int16_t x, int16_t y, uint16_t color, uint8_t *text) {
  uint32_t i         = 0;
  uint16_t xLineCnt  = 0;
  uint16_t yLineCnt  = 0;
  uint8_t  outChar   = 0;
  uint16_t yprac;

  while (0 != text[i]) {

    //bitbang utf8
    if (text[i] > 128) {
      yprac = y + yLineCnt * CurrentFont[3] + fontCorector_cz;
      if (blockStart != blockEnd && i >= blockStart && i < blockEnd) {
        LCD_FillRect(
          x + xLineCnt,
          y + yLineCnt * CurrentFont[3] - LCD_BLOCK_SELECT_SPACER,
          x + xLineCnt + LCD_Char_Get_Width(LCD_get_ext_char_num(text[i], text[i+1]), CurrentFont_cz),
          y + (yLineCnt + 1) * CurrentFont[3],
          color
        );
        uint16_t col = textBgColor;
        textBgColor = color;
        xLineCnt += LCD_DrawChar(x + xLineCnt, yprac, blockColor,  LCD_get_ext_char_num(text[i], text[i+1]), CurrentFont_cz);
        textBgColor = col;
      } else {
        xLineCnt += LCD_DrawChar(x + xLineCnt, yprac, color,  LCD_get_ext_char_num(text[i], text[i+1]), CurrentFont_cz);
      }
      i++;
    } else {
      if (text[i] == '\n') {
        
        if(textBgFill == 1) {
          LCD_FillRect(
            x + xLineCnt,
            y + yLineCnt * CurrentFont[3],
            x + textBgWidth,
            y + (yLineCnt + 1) * CurrentFont[3],
            textBgColor
          );
        }

        xLineCnt = 0;
        yLineCnt++;
      } else if (text[i] == ' ') {
        if (blockStart != blockEnd && i >= blockStart && i < blockEnd) {
          LCD_FillRect(
            x + xLineCnt,
            y + yLineCnt * CurrentFont[3] - LCD_BLOCK_SELECT_SPACER,
            x + xLineCnt + CurrentFont[2],
            y + (yLineCnt + 1) * CurrentFont[3],
            color
          );
        } else if(textBgFill == 1) {
          LCD_FillRect(
            x + xLineCnt,
            y + yLineCnt * CurrentFont[3],
            x + xLineCnt + CurrentFont[2],
            y + (yLineCnt + 1) * CurrentFont[3],
            textBgColor
          );
        }
        xLineCnt += CurrentFont[2];
        if (fitText == 1) {
          // next word longer than max
          if (x + xLineCnt + LCD_Text_Get_Word_Width(&text[i + 1]) + CurrentFont[2] > fitTextMax) {
            // go to new line
            if(textBgFill == 1) {
              LCD_FillRect(
                x + xLineCnt,
                y + yLineCnt * CurrentFont[3],
                x + textBgWidth,
                y + (yLineCnt + 1) * CurrentFont[3],
                textBgColor
              );
            }
            xLineCnt = 0;
            yLineCnt++;
          }
        }
      } else if (text[i] == 9) { // tab
        xLineCnt =  (xLineCnt/(CurrentFont[2] * 4) + 1) * (CurrentFont[2] * 4);
      } else {
        outChar = text[i];

        if (blockStart != blockEnd && i >= blockStart && i < blockEnd) {
          LCD_FillRect(
            x + xLineCnt,
            y + yLineCnt * CurrentFont[3] - LCD_BLOCK_SELECT_SPACER,
            x + xLineCnt + LCD_Char_Get_Width(outChar, CurrentFont),
            y + (yLineCnt + 1) * CurrentFont[3],
            color
          );
          uint16_t col = textBgColor;
          textBgColor = color;
          xLineCnt += LCD_DrawChar(x + xLineCnt, y + yLineCnt * CurrentFont[3], blockColor, outChar, CurrentFont);
          textBgColor = col;
        } else {
          xLineCnt += LCD_DrawChar(x + xLineCnt, y + yLineCnt * CurrentFont[3], color, outChar, CurrentFont);
        }
        
      } 
    }
    i++;
  }

  if(textBgFill == 1) {
    LCD_FillRect(
      x + xLineCnt,
      y + yLineCnt * CurrentFont[3],
      x + textBgWidth,
      y + (yLineCnt + 1) * CurrentFont[3],
      textBgColor
    );
  
    LCD_FillRect(
      x,
      y + (yLineCnt + 1) * CurrentFont[3],
      x + textBgWidth,
      y + textBgHeight,
      textBgColor
    );
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

// returns width of a string, up to the count argument,
uint16_t LCD_Text_Get_Width(uint8_t *text, uint16_t count) {
  uint16_t w;
  uint16_t h;

  LCD_Text_Get_WH(text, count, fitTextMax, &w, &h);

  return w;
}


uint16_t LCD_Text_Get_Height(uint8_t *text, uint16_t count) {
  uint16_t w;
  uint16_t h;

  LCD_Text_Get_WH(text, count, fitTextMax, &w, &h);

  return h;
}


// text and touch coordinates are passed, cursor position is returned
uint16_t LCD_Text_Get_Cursor_Pos(uint8_t *text, int16_t touch_x, int16_t touch_y, uint16_t max_w) {
  uint32_t i        = 0;
  int16_t  xLineCnt = 0;
  int16_t  yLineCnt = 0;
  uint8_t  czFlag   = 0;
  int16_t  xstart   = 0;
  int16_t  ystart   = 0;
  int16_t  xstop    = 0;
  int16_t  ystop    = 0;
  uint16_t char_w   = 0;

  while (0 != text[i]) {
    uint8_t eol = 0;
    czFlag = 0;
    if (text[i] > 128) {
      czFlag = 1;
      char_w = LCD_Char_Get_Width(LCD_get_ext_char_num(text[i], text[i+1]), CurrentFont_cz);
      xLineCnt += char_w;
      i++;
    } else if (text[i] == '\n') {
      char_w = xLineCnt;
      xLineCnt = 0;
      yLineCnt++;
      eol = 1;
    } else if(text[i] == ' ') {
      xLineCnt += CurrentFont[2];
      char_w = CurrentFont[2];
      if (max_w != 0) {
        // next word longer than max, 10 px is the default text offset
        if (xLineCnt + LCD_Text_Get_Word_Width(&text[i + 1]) + CurrentFont[2] > max_w) {
          // go to new line
          char_w = xLineCnt - CurrentFont[2];
          xLineCnt = 0;
          yLineCnt++;
          eol = 1;
        }
      }
    } else if (text[i] == 9) { // tab
      char_w = (xLineCnt/(CurrentFont[2] * 4) + 1) * (CurrentFont[2] * 4) - xLineCnt; 
      xLineCnt = (xLineCnt/(CurrentFont[2] * 4) + 1) * (CurrentFont[2] * 4);
    } else {
      char_w = LCD_Char_Get_Width(text[i], CurrentFont);
      xLineCnt += char_w;
    }
    
    if(eol) {
      xstart = char_w;
      ystart = (yLineCnt - 1) * CurrentFont[3];
      xstop  = 0x0fff;
      ystop  = yLineCnt * CurrentFont[3];
    } else {
      xstart = xLineCnt - char_w;
      ystart = yLineCnt * CurrentFont[3];
      xstop  = xLineCnt;
      ystop  = (yLineCnt + 1)*CurrentFont[3];
    }

#ifdef LCD_CURSOR_TEST
    LCD_FillRect(xstart + 7, ystart + 40, xstop + 7, ystop + 40, LCD_MixColor(255, 255, 255));
    LCD_DrawRectangle(xstart + 7, ystart + 40, xstop + 7, ystop + 40, 0);
#endif

    if (((touch_x >= xstart) || (touch_x >= xstart - 7 && touch_x < 0))
        && (touch_x < xstop) && (touch_y >= ystart) && (touch_y < ystop)
    ){
#ifdef LCD_CURSOR_TEST
      LCD_FillRect(xstart + 7, ystart + 40, xstop + 7, ystop + 40, LCD_MixColor(255, 0, 0));
#endif
      return i - czFlag;
    }

    i++;
  }
 
  if ((touch_x > 0) && (touch_y > 0)) {
#ifdef LCD_CURSOR_TEST
    LCD_FillRect(xstart + 7, ystart + 40, xstop + 7, ystop + 40, LCD_MixColor(0, 255, 0));
#endif
    return i;
  }

#ifdef LCD_CURSOR_TEST
  LCD_FillRect(7, 40, 7 + CurrentFont[2], 40 + CurrentFont[3], LCD_MixColor(0, 255, 0));
#endif
  return 0;
}

void LCD_Text_Draw_Cursor_Ext(int16_t x, int16_t y, uint8_t *text, uint16_t pos, uint16_t max_w, uint16_t Color);

void LCD_Text_Draw_Cursor(int16_t x, int16_t y, uint8_t *text, uint16_t pos, uint16_t Color) {
  LCD_Text_Draw_Cursor_Ext(x, y, text, pos, (fitTextMax - x) * (int16_t)fitText, Color);
}

// TODO: merge logic in this and in LCD_Text_Get_Cursor_Pos
void LCD_Text_Draw_Cursor_Ext(int16_t x, int16_t y, uint8_t *text, uint16_t pos, uint16_t max_w, uint16_t Color) {
  uint32_t i        = 0;
  uint16_t xLineCnt = 0;
  uint16_t yLineCnt = 0;
  uint8_t  czFlag   = 0;
  uint16_t xstart   = 0;
  uint16_t ystart   = 0;
  uint16_t char_w   = 0;
  uint8_t  eol      = 0;

  while (0 != text[i]) {
    eol = 0;
    czFlag = 0;
    if (text[i] > 128) {
      czFlag = 1;
      char_w = LCD_Char_Get_Width(LCD_get_ext_char_num(text[i], text[i+1]), CurrentFont_cz);
      xLineCnt += char_w;
      i++;
    } else if (text[i] == '\n') {
      char_w = xLineCnt;
      xLineCnt = 0;
      yLineCnt++;
      eol = 1;
    } else if(text[i] == ' ') {
      xLineCnt += CurrentFont[2];
      char_w = CurrentFont[2];
      if (max_w != 0) {
        // next word longer than max
        if (xLineCnt + LCD_Text_Get_Word_Width(&text[i+1]) + CurrentFont[2] > max_w) {
          // go to new line
          char_w = xLineCnt - CurrentFont[2];
          xLineCnt = 0;
          yLineCnt++;
          eol = 1;
        }
      }
    } else if (text[i] == 9) { // tab
      char_w = (xLineCnt/(CurrentFont[2] * 4) + 1) * (CurrentFont[2] * 4) - xLineCnt; 
      xLineCnt = (xLineCnt/(CurrentFont[2] * 4) + 1) * (CurrentFont[2] * 4);
    } else {
      char_w = LCD_Char_Get_Width(text[i], CurrentFont);
      xLineCnt += char_w;
    }
    
    if(eol) {
      xstart = char_w;
      ystart = (yLineCnt - 1) * CurrentFont[3];
    } else {
      xstart = xLineCnt - char_w;
      ystart = yLineCnt * CurrentFont[3];
    }

    if(i >= pos) {  
      LCD_DrawLine(x + xstart, y + ystart, x + xstart, y + ystart + CurrentFont[3], Color);
      return;
    }

    i++;
  }

  if(eol) {
    xstart = 0;
    ystart = (yLineCnt) * CurrentFont[3];
  } else {
    xstart += char_w;
  }

  LCD_DrawLine(x + xstart, y + ystart, x + xstart, y + ystart + CurrentFont[3], Color);
}


// returns char width
uint16_t LCD_DrawChar(int16_t x, int16_t y, uint16_t color, uint16_t znak, const uint8_t *font) {
  uint32_t a, b, d;
  uint16_t yLineCnt = 0;
  uint16_t char_width;
  uint32_t cpos;
  uint32_t cposIncr = 0;
  uint16_t FontSize;
  uint8_t liche = 0;

  if (((font[3] / 8) * 8) == font[3]) {
    FontSize = font[3]/8;
  } else {
    FontSize = font[3]/8 + 1;
    liche = font[3]%8;
  }

  if ((znak >= 32 && znak <= 128) || (znak >= 193 && znak <= 383)) {
    cposIncr = 0;
    char_width = font[znak + 6 - font[4]];
    cpos = font[5] + 6; //96+6 - první znak

    for (a = 6; a < (uint32_t)(znak - font[4] + 6); a++) { // get char position
      cpos += font[a] * FontSize;
    }

    if(textBgFill == 0) {
      for (a = 0; a < FontSize; a++) { // fontSize per column
        for (b = 0; b < char_width; b++) {
          for(d = 0; d < 8; d++) {
            if (font[cpos + cposIncr] & (1 << d)) {
              if (liche == 0) {
                LCD_DrawPoint(x + b, y + yLineCnt * font[3] + a*8 + d, color);
              } else {
                if (a < (uint32_t)(FontSize - 1)) {
                  LCD_DrawPoint(x + b, y + yLineCnt*font[3] + a*8 + d, color);
                } else {
                  LCD_DrawPoint(x + b, y + yLineCnt*font[3] + (a - 1)*8 + liche + d, color);
                }
              }
            }
          }
          cposIncr++;
        }
      }
    } else {
      //textBgColor = LCD_MixColor(255,0,0);
      for (a = 0; a < FontSize; a++) {
        for (b = 0; b < char_width; b++) {
          if (a < (uint32_t)(FontSize - 1)) {
            LCD_canvas_set(x + b, y + a*8, x + b + 1, y + (a+1)*8 );
            for(d = 0; d < 8; d++) {
              if (font[cpos + cposIncr] & (1 << d)) {
                LCD_canvas_putcol(color);
              } else {
                LCD_canvas_putcol(textBgColor);
              }
            }
            cposIncr++;
          } else {
            LCD_canvas_set(x + b, y + a*8, x + b + 1, y + (a)*8 + liche);
            for(d = 2; d < 8; d++) {
              if (font[cpos + cposIncr] & (1 << d)) {
                LCD_canvas_putcol(color);
              } else {
                LCD_canvas_putcol(textBgColor);
              }
            }
            cposIncr++;
          }
        }
      }
      
      LCD_FillRect(x+char_width, y, x + char_width + font[2]/9 + font[2]%9, y + font[3], textBgColor);
    }
    
    return char_width + font[2]/9 + font[2]%9;
  } else {
    // unknown char...
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


void LCD_Text_Get_WH(uint8_t *text, uint16_t pos, uint16_t max_w, uint16_t *width, uint16_t *height) {
  uint32_t i         = 0;
  uint16_t xLineCnt  = 0;
  uint16_t yLineCnt  = 0;
  uint8_t  czFlag    = 0;
  uint16_t xstart    = 0;
  uint16_t ystart    = 0;
  uint16_t char_w    = 0;
  uint8_t  eol       = 0;
  uint16_t max_width = 0;

  *width  = 0;
  *height = 0;

  while (0 != text[i]) {
    eol = 0;
    czFlag = 0;
    if (text[i] > 128) {
      czFlag = 1;
      char_w = LCD_Char_Get_Width(LCD_get_ext_char_num(text[i], text[i+1]), CurrentFont_cz);
      xLineCnt += char_w;
      i++;
    } else if (text[i] == '\n') {
      char_w = xLineCnt;
      xLineCnt = 0;
      yLineCnt++;
      eol = 1;
    } else if(text[i] == ' ') {
      xLineCnt += CurrentFont[2];
      char_w = CurrentFont[2];
      if (max_w != 0) {
        // next word longer than max
        if (xLineCnt + LCD_Text_Get_Word_Width(&text[i+1]) + CurrentFont[2] > max_w) {
          // go to new line
          char_w = xLineCnt - CurrentFont[2];
          xLineCnt = 0;
          yLineCnt++;
          eol = 1;
        }
      }
    } else if (text[i] == 9) { // tab
      char_w = (xLineCnt/(CurrentFont[2] * 4) + 1) * (CurrentFont[2] * 4) - xLineCnt; 
      xLineCnt = (xLineCnt/(CurrentFont[2] * 4) + 1) * (CurrentFont[2] * 4);
    } else {
      char_w = LCD_Char_Get_Width(text[i], CurrentFont);
      xLineCnt += char_w;
    }

    if(xLineCnt > max_width) {
      max_width = xLineCnt;
    }
    
    if(eol) {
      xstart = char_w;
      ystart = (yLineCnt - 1) * CurrentFont[3];
    } else {
      xstart = xLineCnt - char_w;
      ystart = yLineCnt * CurrentFont[3];
    }

    if(i == pos && pos != 0) {
      *width  = max_width;
      *height = yLineCnt * CurrentFont[3];
      return;
    }
    i++;
  }

  if(eol) {
    xstart = 0;
    ystart = (yLineCnt) * CurrentFont[3];
  } else {
    xstart += char_w;
  }

  *width  = max_width;
  *height = yLineCnt * CurrentFont[3];

  //printf("orig: w:%u h:%u max:%u\n", *width, *height, max_w);
}
