/*
Copyright (c) 2019 Stanislav Brtna

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

#ifndef GR2_GUI_DRAW_H_
#define GR2_GUI_DRAW_H_

// text align helper
int16_t pscg_get_text_align_x(
    uint16_t id,
    int16_t x1,
    int16_t x2,
    gr2context * c
);

// headers for the element draw functions, used only internaly in the GR2
void pscg_draw_button(
           int16_t x1,
           int16_t y1,
           int16_t x2,
           int16_t y2,
           uint8_t *str,
           uint8_t active,
           uint16_t id,
           gr2context * c
          );

void pscg_draw_cbutton(
           int16_t x1,
           int16_t y1,
           int16_t x2,
           int16_t y2,
           uint8_t *str,
           uint8_t active,
           uint16_t id,
           gr2context * c
          );

void pscg_draw_text(
           int16_t x1,
           int16_t y1,
           int16_t x2,
           int16_t y2,
           uint8_t *str,
           uint8_t active,
           uint8_t editable,
           uint16_t cursor,
           uint16_t font_size,
           uint8_t fit,
           uint8_t pwd,
           uint16_t id,
           gr2context * c
          );

void pscg_draw_slider_v(
           int16_t x1,
           int16_t y1,
           int16_t x2,
           int16_t y2,
           uint16_t slider_size,
           int32_t param,
           int32_t value,
           uint16_t id,
           gr2context * c
          );

void pscg_draw_slider_h(
           int16_t x1,
           int16_t y1,
           int16_t x2,
           int16_t y2,
           uint16_t slider_size,
           int32_t param,
           int32_t value,
           uint16_t id,
           gr2context * c
          );

void pscg_draw_checkbox(
           int16_t x1,
           int16_t y1,
           int16_t x2,
           int16_t y2,
           uint8_t *str,
           uint8_t active,
           uint16_t id,
           gr2context * c
          );

void pscg_draw_progbar_v(
           int16_t x1,
           int16_t y1,
           int16_t x2,
           int16_t y2,
           int32_t param,
           int32_t value,
           uint16_t id,
           gr2context * c
          );

void pscg_draw_progbar_h(
           int16_t x1,
           int16_t y1,
           int16_t x2,
           int16_t y2,
           int32_t param,
           int32_t value,
           uint16_t id,
           gr2context * c
          );

void pscg_draw_icon(
           int16_t x1,
           int16_t y1,
           int16_t x2,
           int16_t y2,
           uint8_t active,
           uint16_t id,
           gr2context * c
          );

void pscg_draw_image(
           int16_t x1,
           int16_t y1,
           int16_t x2,
           int16_t y2,
           uint16_t id,
           gr2context * c
          );

void pscg_draw_slider_v_f(
           int16_t x1,
           int16_t y1,
           int16_t x2,
           int16_t y2,
           uint16_t slider_size,
           int32_t param,
           int32_t value,
           int32_t oldval,
           uint16_t id,
           gr2context * c
          );

void pscg_draw_slider_h_f(
           int16_t x1,
           int16_t y1,
           int16_t x2,
           int16_t y2,
           uint16_t slider_size,
           int32_t param,
           int32_t value,
           int32_t oldval,
           uint16_t id,
           gr2context * c
          );

#endif
