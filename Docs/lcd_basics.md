## Basic functions
GR2 library builds on these basic draw functions, they can be used separately. 

### Coordinates 
GR2 uses 16bit unsigned ints for display hardware coordinates. X is horizontal axis, Y is vertical and zero (x=0 and y=0) is in the upper left corner of the screen.

### Init function
Init LCD and set the orientation.

    uint8_t LCD_init(uint16_t x_size, uint16_t y_size, lcdOrientationType orient);

### Rotation
Does not rotate the canvas functions.
void LCD_set_orientation(lcdOrientationType orient);

### Rotation translators
Used to get rotated x or y coordinates from hw coordinates. Useful for touch input.

    uint16_t LCD_rotr_x(uint16_t x1, uint16_t y1);
    uint16_t LCD_rotr_y(uint16_t x1, uint16_t y1);

### Get LCD size

    uint16_t LCD_get_x_size();
    uint16_t LCD_get_y_size();

### Draw area functions
Library allows you to specify a virtual draw area and then limit it by specifying sub-draw areas. Areas are specified as 16bit signed ints and can go outside the physical display boundary.

    void LCD_setDrawArea(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
    void LCD_setSubDrawArea(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
    void LCD_getDrawArea(LCD_drawArea *a);
    void LCD_setDrawAreaS(LCD_drawArea *a);

### Color handling
GR2 internally uses 16bit GRB565 color space, function to get 16bit color from RGB888 is provided.

    uint16_t LCD_MixColor(uint8_t r, uint8_t g,uint8_t b);
    uint16_t LCD_get_gray16(uint16_t color);

### Basic element draw functions
Fill display with one color:

    void LCD_Fill(uint16_t color);

Point:

    void LCD_DrawPoint(int16_t x, int16_t y, int16_t color);

Line:

    void LCD_DrawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);

Rectangle (outline):

    void LCD_DrawRectangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);

Rectangle(filled):

    void LCD_FillRect(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t Color);
Circle (outline):

    void LCD_DrawCircle(int16_t x0, int16_t y0, uint16_t radius, uint16_t color);

Circle (filled):

    void LCD_FillCircle(int16_t x0, int16_t y0, uint16_t radius, uint16_t color);

### Text draw
Draw text:

    void LCD_DrawText_ext(int16_t x, int16_t y, uint16_t color, uint8_t *text);

Get width of string:
Count: the number of characters used. Zero will give you the length of whole string.

    uint16_t LCD_Text_Get_Width(uint8_t *text, uint16_t count); 

Current font parameters:

    uint16_t LCD_Draw_Get_Font_Height();
    uint16_t LCD_Draw_Get_Font_Width();

Change font:

    void LCD_Set_Sys_Font(uint8_t size);
    uint8_t LCD_Get_Font_Size();

Set text max width of string to be drawn. This will be globally applied 

    void LCD_set_fitText(uint8_t enable, uint16_t max);
### Canvas
Canvas allows to use as direct draw to lcd, but respects drawAreas. Canvas is not persistent, you need to reinit it before each draw cycle.

    void LCD_canvas_set(int16_t x1, int16_t y1, int16_t x2, int16_t y2);

Reset the buffer pointer:

    void LCD_canvas_zero(); 

Put color to the canvas:

    void LCD_canvas_putcol(uint16_t color);