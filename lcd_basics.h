/*
 * lcd_basics.h
 *
 *  Created on: 4. 11. 2016
 *      Author: stanislaw
 */

#ifndef LCD_BASICS_LCD_BASICS_H_
#define LCD_BASICS_LCD_BASICS_H_
#include "GR2.h"

typedef enum {OR_NORMAL,OR_ROT_LEFT,OR_ROT_RIGHT,OR_UPSIDE_DOWN} lcdOrientationType;

typedef struct {
  int16_t x1;
  int16_t y1;
  int16_t x2;
  int16_t y2;
} LCD_drawArea;

//lcd init and parameter config functions
uint8_t LCD_init(uint16_t x_size, uint16_t y_size, lcdOrientationType orient);

//rotation functions
void LCD_set_orientation(lcdOrientationType orient);

//rotation translators
uint16_t LCD_rotr_x(uint16_t x1, uint16_t y1);
uint16_t LCD_rotr_y(uint16_t x1, uint16_t y1);

//getters
uint16_t LCD_get_x_size();
uint16_t LCD_get_y_size();

//draw area functions
void LCD_setDrawArea(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
void LCD_setSubDrawArea(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
void LCD_getDrawArea(LCD_drawArea *a);
void LCD_setDrawAreaS(LCD_drawArea *a);

//color functions
uint16_t LCD_MixColor(uint8_t r, uint8_t g,uint8_t b);
uint16_t LCD_get_gray16(uint16_t color);

//draw functions
void LCD_DrawPoint(int16_t x, int16_t y, int16_t color);
void LCD_Fill(uint16_t color);
void LCD_DrawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
void LCD_DrawRectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
void LCD_FillRect(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t Color);

void LCD_DrawCircle(int16_t x0, int16_t y0, uint16_t radius, uint16_t color);
void LCD_FillCircle(int16_t x0, int16_t y0, uint16_t radius, uint16_t color);

// deprecated
void LCD_DrawText(int16_t x, int16_t y, uint16_t color,uint16_t bg_color, uint8_t *text, uint8_t scale);

#endif /* LCD_BASICS_LCD_BASICS_H_ */
