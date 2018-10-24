#include "lcd_basics.h"
#include "fonts/font_8x8.h"

volatile int16_t draw_area_x1;
volatile int16_t draw_area_x2;
volatile int16_t draw_area_y1;
volatile int16_t draw_area_y2;
uint16_t lcd_x_size;
uint16_t lcd_y_size;

lcdOrientationType lcd_orientation;

// Headers of main callbacks needed for the library to work

// Draw point on LCD on LCDs current adress
void lcd_hw_Draw_Point(uint16_t color);

// Set adress for lcd
void lcd_hw_set_xy(uint16_t px1, uint16_t py1,uint16_t px2,uint16_t py2);

// Initialize the lcd hardware
uint8_t lcd_hw_init();


// setters of LCD orientation

void LCD_set_XY(uint16_t x1, uint16_t y1,uint16_t x2,uint16_t y2) {
	if (lcd_orientation == OR_NORMAL) {
		lcd_hw_set_xy(x1, y1, x2, y2);
	}

	if (lcd_orientation == OR_ROT_LEFT) {
		lcd_hw_set_xy(y1, lcd_y_size - x2, y2, lcd_y_size - x1);
	}

	if (lcd_orientation == OR_ROT_RIGHT) {
		lcd_hw_set_xy(lcd_x_size - y2, x1, lcd_x_size - y1, x2);
	}

	if (lcd_orientation == OR_UPSIDE_DOWN) {
		lcd_hw_set_xy(lcd_x_size - x2, lcd_y_size - y2, lcd_x_size - x1, lcd_y_size - y1);
	}
}

// Misc functions to get the right touch coordinates according to screen orientation

uint16_t LCD_rotr_x(uint16_t x1, uint16_t y1) {
	if (lcd_orientation == OR_NORMAL) {
		return x1;
	}

	if (lcd_orientation == OR_ROT_LEFT) {
		return y1;
	}

	if (lcd_orientation == OR_ROT_RIGHT) {
		return lcd_x_size - y1;
	}

	if (lcd_orientation == OR_UPSIDE_DOWN) {
		return lcd_x_size - x1;
	}

	return x1;
}

uint16_t LCD_rotr_y(uint16_t x1, uint16_t y1) {
	if (lcd_orientation == OR_NORMAL) {
		return y1;
	}

	if (lcd_orientation == OR_ROT_LEFT) {
		return lcd_y_size - x1;
	}

	if (lcd_orientation == OR_ROT_RIGHT) {
		return x1;
	}

	if (lcd_orientation == OR_UPSIDE_DOWN) {
		return lcd_y_size - y1;
	}

	return y1;
}

void LCD_set_orientation(lcdOrientationType orient) {
	lcd_orientation = orient;
}

void LCD_draw_point_wrp(uint16_t color) {
	lcd_hw_Draw_Point(color);
}

uint16_t LCD_get_x_size() {
	return lcd_x_size;
}

uint16_t LCD_get_y_size() {
	return lcd_y_size;
}

uint8_t LCD_init(uint16_t x_size, uint16_t y_size, lcdOrientationType orient) {

	lcd_hw_init();
	lcd_x_size = x_size;
	lcd_y_size = y_size;
	lcd_orientation = orient;
	LCD_Set_Sys_Font(18);

	return 0;
}


void LCD_setDrawArea(int16_t x1, int16_t y1, int16_t x2, int16_t y2) {
	if (x1 > 0) {
		draw_area_x1 = x1;
	} else {
		draw_area_x1 = 0;
	}

	if (x2 > 0) {
		draw_area_x2 = x2;
	} else {
		draw_area_x2 = 0;
	}

	if (y1 > 0) {
		draw_area_y1 = y1;
	} else {
		draw_area_y1 = 0;
	}

	if (y2 > 0) {
		draw_area_y2 = y2;
	} else {
		draw_area_y2 = 0;
	}
}


void LCD_getDrawArea(LCD_drawArea *a) {
	a->x1 = draw_area_x1;
	a->x2 = draw_area_x2;
	a->y1 = draw_area_y1;
	a->y2 = draw_area_y2;
}

void LCD_setDrawAreaS(LCD_drawArea *a) {
	draw_area_x1 = a->x1;
	draw_area_x2 = a->x2;
	draw_area_y1 = a->y1;
	draw_area_y2 = a->y2;
}

void LCD_setSubDrawArea(int16_t x1, int16_t y1, int16_t x2, int16_t y2) {
	if (x1 >= draw_area_x1) {
		draw_area_x1 = x1;
	}
	if (x2 <= draw_area_x2) {
		draw_area_x2 = x2;
	}
	if (y1 >= draw_area_y1) {
		draw_area_y1 = y1;
	}
	if (y2 <= draw_area_y2) {
		draw_area_y2 = y2;
	}
}

void LCD_DrawPoint(int16_t x, int16_t y, int16_t color) {
	if ((x > (int16_t)lcd_x_size) || (x < draw_area_x1) || (x > draw_area_x2))
		return;

	if ((y > (int16_t)lcd_y_size) || (y < draw_area_y1) || (y > draw_area_y2))
		return;

	LCD_set_XY((uint16_t)x, (uint16_t)y, (uint16_t)x, (uint16_t)y);
	LCD_draw_point_wrp(color);
}


#ifdef STM_BSP_FILL
void BSP_LCD_FillRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
void BSP_LCD_SetTextColor(uint32_t c);
#endif

#ifdef LCD_IO_FILL
void ExtFillRect(int x,	int y, int w, int h, uint16_t color);
#endif

void LCD_FillRect(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t Color) {
	int16_t X1, X2, Y1, Y2;
	int32_t i, j;

	if (x1 >= (lcd_x_size )) {
		x1 = lcd_x_size ;
	}
	if (x2 >= (lcd_x_size )) {
		x2 = lcd_x_size ;
	}
	if (y1 >= (lcd_y_size)) {
		y1 = lcd_y_size;
	}
	if (y2 >= (lcd_y_size)) {
		y2 = lcd_y_size;
	}

	if (x1 <= draw_area_x1) {
		X1 = draw_area_x1;
	} else {
		X1 = x1;
	}
	if (y1 <= draw_area_y1) {
		Y1 = draw_area_y1;
	} else {
		Y1 = y1;
	}
	if (x2 >= draw_area_x2) {
		X2 = draw_area_x2;
	} else {
		X2 = x2;
	}
	if (y2 >= draw_area_y2) {
		Y2 = draw_area_y2;
	} else {
		Y2 = y2;
	}

// We might use optimised functions for rectangle fill

#if !(STM_BSP_FILL || LCD_IO_FILL)

	LCD_set_XY((uint16_t)X1, (uint16_t)Y1, (uint16_t)X2, (uint16_t)Y2);
	for(i = X1; i <= X2; i++) {
		for (j = Y1; j <= Y2; j++) {
			LCD_draw_point_wrp(Color);
		}
	}
	LCD_set_XY(0, 0, lcd_x_size, lcd_y_size);
#endif

#ifdef STM_BSP_FILL
	uint8_t r, g, b;
	r = (uint8_t)(((float)((Color >> 11) & 0x1F) / 32) * 256);
	g = (uint8_t)(((float)(((Color & 0x07E0) >> 5) & 0x3F) / 64) * 256);
	b = (uint8_t)(((float)(Color & 0x1F) / 32) * 256);

	if ((X1 < X2) && (Y1 < Y2)) {
		BSP_LCD_SetTextColor(0xff << 24 | r << 16 | g << 8 | b);
		BSP_LCD_FillRect((uint16_t)X1, (uint16_t)Y1, (uint16_t)(X2 - X1 + 1), (uint16_t)(Y2 - Y1));
	}
#endif

#ifdef LCD_IO_FILL
	if ((X1 < X2) && (Y1 < Y2)) {
		ExtFillRect((uint16_t)X1, (uint16_t)Y1, (uint16_t)(X2 - X1 + 1), (uint16_t)(Y2 - Y1 + 1), Color);
	}
#endif

}

uint16_t LCD_MixColor(uint8_t r, uint8_t g, uint8_t b) {
	r = ( r * 249 + 1014 ) >> 11; //5
	g = ( g * 253 + 505 ) >> 10; //6
	b = ( b * 249 + 1014 ) >> 11; //5

	return r << 11 | (g & 0x3F) << 5 | (b & 0x1F);
}

uint16_t LCD_get_gray16(uint16_t color) {
	uint8_t r = 0;
	uint8_t g = 0;
	uint8_t b = 0;
	uint8_t round;
	r = (uint8_t)(((float)((color >> 11) & 0x1F) / 32) * 256);
	g = (uint8_t)(((float)(((color & 0x07E0) >> 5) & 0x3F) / 64) * 256);
	b = (uint8_t)(((float)(color & 0x1F) / 32) * 256);

	round = (uint8_t)(((uint16_t)r + (uint16_t)g + (uint16_t)b) / 4);

	return LCD_MixColor(round, round, round);
}

uint16_t LCD_color_lighten(uint16_t color, uint8_t val) {
	uint8_t r = 0;
	uint8_t g = 0;
	uint8_t b = 0;
	uint8_t round;
	r = (uint8_t)(((float)((color >> 11) & 0x1F) / 32) * 256);
	g = (uint8_t)(((float)(((color & 0x07E0) >> 5) & 0x3F) / 64) * 256);
	b = (uint8_t)(((float)(color & 0x1F) / 32) * 256);

	if ((uint32_t)r + (uint32_t)val > 255) {
	  r = 255;
	} else {
	  r += val;
	}

	if ((uint32_t)g + (uint32_t)val > 255) {
	  g = 255;
	} else {
	  g += val;
	}

	if ((uint32_t)g + (uint32_t)val > 255) {
	  g = 255;
	} else {
	  g += val;
	}

	if ((uint32_t)b + (uint32_t)val > 255) {
	  b = 255;
	} else {
	  b += val;
	}

	return LCD_MixColor(r, g, b);
}

uint16_t LCD_color_darken(uint16_t color, uint8_t val) {
	uint8_t r = 0;
	uint8_t g = 0;
	uint8_t b = 0;
	uint8_t round;
	r = (uint8_t)(((float)((color >> 11) & 0x1F) / 32) * 256);
	g = (uint8_t)(((float)(((color & 0x07E0) >> 5) & 0x3F) / 64) * 256);
	b = (uint8_t)(((float)(color & 0x1F) / 32) * 256);

	if ((int32_t)r - (int32_t)val < 0) {
	  r = 0;
	} else {
	  r -= val;
	}

	if ((int32_t)g - (int32_t)val < 0) {
	  g = 0;
	} else {
	  g -= val;
	}

	if ((int32_t)g - (int32_t)val < 0) {
	  g = 0;
	} else {
	  g -= val;
	}

	if ((int32_t)b - (int32_t)val < 0) {
	  b = 0;
	} else {
	  b -= val;
	}

	return LCD_MixColor(r, g, b);
}

void LCD_Fill(uint16_t color) {
	uint16_t i, j;
	LCD_set_XY(0, 0, lcd_x_size, lcd_y_size);
	for(i = 0; i < lcd_x_size + 1; i++){
		for (j = 0; j < lcd_y_size + 1; j++) {
			LCD_draw_point_wrp(color);
		}
	}
}



void LCD_DrawCircle(int16_t x0, int16_t y0, uint16_t radius, uint16_t color) {
	int16_t x = radius;
	int16_t y = 0;
	int16_t err = 0;

	while (x >= y) {
		LCD_DrawPoint(x0 + x, y0 + y, color);
		LCD_DrawPoint(x0 + y, y0 + x, color);
		LCD_DrawPoint(x0 - y, y0 + x, color);
		LCD_DrawPoint(x0 - x, y0 + y, color);
		LCD_DrawPoint(x0 - x, y0 - y, color);
		LCD_DrawPoint(x0 - y, y0 - x, color);
		LCD_DrawPoint(x0 + y, y0 - x, color);
		LCD_DrawPoint(x0 + x, y0 - y, color);

		y += 1;
		err += 1 + 2*y;
		if (2*(err-x) + 1 > 0) {
			x -= 1;
			err += 1 - 2 * x;
		}
	}
}


void LCD_FillCircle(int16_t x0, int16_t y0, uint16_t radius, uint16_t color) {
	int16_t x = radius;
	int16_t y = 0;
	int16_t err = 0;
	uint16_t i;

	while (x >= y) {
		for (i = y0 - y; i <= y0 + y; i++) {
			LCD_DrawPoint(x0 + x, i, color);
			LCD_DrawPoint(x0 - x, i, color);
		}
		for (i = y0 - x; i <= y0 + x; i++) {
			LCD_DrawPoint(x0 + y, i, color);
			LCD_DrawPoint(x0 - y, i, color);
		}

		y += 1;
		err += 1 + 2*y;
		if (2 * (err - x) + 1 > 0){
			x -= 1;
			err += 1 - 2*x;
		}
	}
}



void LCD_DrawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
	uint16_t t;
	int32_t xerr = 0, yerr = 0, delta_x, delta_y, distance;
	int32_t incx, incy, uRow, uCol;

	delta_x = x2 - x1;
	delta_y = y2 - y1;

	uRow = x1;
	uCol = y1;
	if(delta_x > 0) {
		incx = 1;
	} else if(delta_x == 0) {
		LCD_FillRect(x1, y1, x1, y2, color);
		return;
	} else {
		incx =- 1;
		delta_x =- delta_x;
	}

	if(delta_y > 0) {
		incy = 1;
	} else if(delta_y == 0) {
		LCD_FillRect(x1, y1, x2, y1, color);
		return;
	} else {
		incy =- 1;
		delta_y =- delta_y;
	}

	if(delta_x > delta_y)
		distance = delta_x;
	else
		distance = delta_y;
	for(t = 0; t <= distance + 1; t++) {
		LCD_DrawPoint(uRow, uCol, color);
		xerr += delta_x;
		yerr += delta_y;
		if (xerr > distance) {
			xerr -= distance;
			uRow += incx;
		}
		if(yerr > distance) {
			yerr -= distance;
			uCol += incy;
		}
	}
}

void LCD_DrawRectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
	LCD_DrawLine(x1, y1, x2, y1, color);
	LCD_DrawLine(x1, y1, x1, y2, color);
	LCD_DrawLine(x1, y2, x2, y2, color);
	LCD_DrawLine(x2, y1, x2, y2, color);
}

// old backup draw text function, does not support czech characters, ASCII only

void LCD_DrawText(int16_t x, int16_t y, uint16_t color, uint16_t bg_color, uint8_t *text, uint8_t scale) {
	uint32_t i = 0;
	uint32_t a, b, c, d;
	uint16_t xLineCnt = 0;
	uint16_t yLineCnt = 0;
	uint8_t outChar = 0;

	(void)(bg_color);

	while (0 != text[i]) {
		if (text[i] != '\n') {
			outChar = text[i];
			if((text[i] == 0xc3) && (text[i + 1] == 0xa1)) {
				i++;
				outChar = 128;
			}

			for(d = 0; d < 8; d++) {
				for(a = 0; a < 8; a++) {
					if (font8x8_basic[(outChar * 8 + d)] & (1 << a)) {
						for(c = 0; c < scale; c++)
							for(b = 0; b < scale; b++)
								LCD_DrawPoint(
									x + xLineCnt * 8 * scale + d * scale + b,
									y + yLineCnt * 8 * scale + a * scale + c,
									color
								);

					}
				}
			}
			xLineCnt++;
		} else {
			xLineCnt = 0;
			yLineCnt++;
		}
		i++;
	}
}

