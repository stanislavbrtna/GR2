/*
 * lcd_hw.h
 *
 *  Created on: 31. 10. 2016
 *      Author: stanislaw
 */

#ifndef LCD_IO_H_
#define LCD_IO_H_

#include "GR2.h"

//funkce co se hodí z venku:
void lcd_Init();
void lcd_hw_set_xy(uint16_t x1, uint16_t y1,uint16_t x2,uint16_t y2);
void lcd_hw_Draw_Point(uint16_t color);
#endif /* LCD_IO_H_ */
