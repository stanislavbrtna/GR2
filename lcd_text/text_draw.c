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

#include "text_draw.h"

#define LCD_BLOCK_SELECT_SPACER 3*(yLineCnt == 0) // make the first line of the block taller

extern uint8_t * CurrentFont;
extern uint8_t * CurrentFont_cz;

extern uint8_t  CurrentSize;
extern int32_t  fontCorector_cz;

uint16_t fitTextMax;
uint8_t  fitText;

uint32_t blockStart;
uint32_t blockEnd;
uint16_t blockColor;

uint8_t  textBgFill;
int16_t  textBgWidth;
int16_t  textBgHeight;
uint16_t textBgColor;


void LCD_Text_Draw_Cursor_Ext(int16_t x, int16_t y, uint8_t *text, uint16_t pos, uint16_t max_w, uint16_t Color);


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


void LCD_set_text_block(uint32_t start, uint32_t end, uint16_t color) {
  blockStart = start;
  blockEnd = end;
  blockColor = color;
}


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
          x + xLineCnt + LCD_Char_Get_Width(LCD_get_ext_char_num(text[i], text[i+1]), CurrentFont_cz) - 1,
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
            x + xLineCnt + CurrentFont[2] - 1,
            y + (yLineCnt + 1) * CurrentFont[3],
            color
          );
        } else if(textBgFill == 1) {
          LCD_FillRect(
            x + xLineCnt,
            y + yLineCnt * CurrentFont[3],
            x + xLineCnt + CurrentFont[2] - 1,
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
            x + xLineCnt + LCD_Char_Get_Width(outChar, CurrentFont) - 1,
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
