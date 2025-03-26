

/*
 *
 * new Font
 *
 * created with FontCreator
 * written by F. Maximilian Thiele
 *
 * http://www.apetech.de/fontCreator
 * me@apetech.de
 *
 * File Name           : roboto12_cz_exp
 * Date                : 24.03.2021
 * Font size in bytes  : 35957
 * Font width          : 10
 * Font height         : 16
 * Font first char     : 193
 * Font last char      : 383
 * Font used chars     : 190
 *
 * The font data are defined as
 *
 * struct _FONT_ {
 *     uint16_t   font_Size_in_Bytes_over_all_included_Size_it_self;
 *     uint8_t    font_Width_in_Pixel_for_fixed_drawing;
 *     uint8_t    font_Height_in_Pixel_for_all_characters;
 *     unit8_t    font_First_Char;
 *     uint8_t    font_Char_Count;
 *
 *     uint8_t    font_Char_Widths[font_Last_Char - font_First_Char +1];
 *                  // for each character the separate width in pixels,
 *                  // characters < 128 have an implicit virtual right empty row
 *
 *     uint8_t    font_data[];
 *                  // bit field of all characters
 */

#ifndef ROBOTO12_CZ_H
#define ROBOTO12_CZ_H

#define ROBOTO12_CZ_WIDTH 10
#define ROBOTO12_CZ_HEIGHT 16

const uint8_t roboto12_cz[] = {
    0x49, 0x54, // size
    0x0A, // width
    0x10, // height
    0xC1, // first char
    0xBE, // char count

    // char widths
    0x08, 0x08, 0x08, 0x09, 0x08, 0x0B, 0x07, 0x06, 0x06, 0x06,
    0x06, 0x03, 0x03, 0x04, 0x05, 0x07, 0x07, 0x07, 0x07, 0x07,
    0x07, 0x07, 0x06, 0x07, 0x07, 0x07, 0x07, 0x07, 0x08, 0x06,
    0x07, 0x06, 0x06, 0x06, 0x06, 0x05, 0x06, 0x0A, 0x05, 0x06,
    0x06, 0x06, 0x06, 0x03, 0x03, 0x04, 0x05, 0x06, 0x06, 0x06,
    0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
    0x06, 0x06, 0x07, 0x08, 0x06, 0x08, 0x06, 0x08, 0x06, 0x07,
    0x05, 0x07, 0x05, 0x07, 0x05, 0x07, 0x05, 0x07, 0x08, 0x07,
    0x07, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
    0x06, 0x07, 0x06, 0x07, 0x06, 0x08, 0x06, 0x07, 0x06, 0x07,
    0x06, 0x08, 0x07, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x03,
    0x03, 0x02, 0x02, 0x09, 0x05, 0x07, 0x04, 0x07, 0x06, 0x06,
    0x06, 0x03, 0x06, 0x02, 0x06, 0x04, 0x06, 0x04, 0x07, 0x04,
    0x07, 0x06, 0x07, 0x06, 0x07, 0x06, 0x06, 0x07, 0x06, 0x07,
    0x06, 0x07, 0x06, 0x07, 0x06, 0x0B, 0x0A, 0x06, 0x04, 0x06,
    0x04, 0x06, 0x04, 0x07, 0x05, 0x07, 0x05, 0x07, 0x05, 0x07,
    0x05, 0x07, 0x04, 0x07, 0x04, 0x07, 0x04, 0x07, 0x06, 0x07,
    0x06, 0x07, 0x06, 0x07, 0x06, 0x07, 0x06, 0x07, 0x06, 0x0A,
    0x09, 0x08, 0x06, 0x07, 0x06, 0x05, 0x06, 0x05, 0x06, 0x05,


    // font data
    0x00, 0x00, 0xC0, 0xF0, 0xF6, 0xC2, 0x00, 0x00, 0x10, 0x1E, 0x07, 0x04, 0x04, 0x07, 0x1E, 0x18, // 193
    0x00, 0x00, 0xC4, 0xF4, 0xF6, 0xC4, 0x00, 0x00, 0x10, 0x1E, 0x07, 0x04, 0x04, 0x07, 0x1E, 0x18, // 194
    0x00, 0x00, 0xC6, 0xF2, 0x74, 0xE6, 0x00, 0x00, 0x10, 0x1E, 0x0F, 0x05, 0x04, 0x07, 0x1F, 0x18, // 195
    0x00, 0x00, 0x84, 0xE4, 0x30, 0xE4, 0x84, 0x00, 0x00, 0x10, 0x1C, 0x0F, 0x07, 0x04, 0x07, 0x0F, 0x1C, 0x10, // 196
    0x00, 0x00, 0x80, 0xF6, 0x76, 0xE0, 0x00, 0x00, 0x10, 0x1E, 0x0F, 0x05, 0x04, 0x07, 0x1F, 0x18, // 197
    0x00, 0x00, 0x80, 0xE0, 0x70, 0xF0, 0xF0, 0x10, 0x10, 0x10, 0x00, 0x18, 0x1E, 0x07, 0x05, 0x04, 0x1F, 0x1F, 0x11, 0x11, 0x11, 0x10, // 198
    0xC0, 0xE0, 0x30, 0x10, 0x10, 0x70, 0x60, 0x07, 0x0F, 0x18, 0xB0, 0xF0, 0x1C, 0x0C, // 199
    0xF0, 0xF2, 0x16, 0x14, 0x10, 0x10, 0x1F, 0x1F, 0x11, 0x11, 0x11, 0x10, // 200
    0xF0, 0xF0, 0x10, 0x16, 0x12, 0x10, 0x1F, 0x1F, 0x11, 0x11, 0x11, 0x10, // 201
    0xF0, 0xF4, 0x16, 0x16, 0x14, 0x10, 0x1F, 0x1F, 0x11, 0x11, 0x11, 0x10, // 202
    0xF0, 0xF4, 0x14, 0x14, 0x14, 0x10, 0x1F, 0x1F, 0x11, 0x11, 0x11, 0x10, // 203
    0x02, 0xF6, 0xF4, 0x00, 0x1F, 0x1F, // 204
    0xF4, 0xF6, 0x02, 0x1F, 0x1F, 0x00, // 205
    0x04, 0xF6, 0xF6, 0x04, 0x00, 0x1F, 0x1F, 0x00, // 206
    0x04, 0xF4, 0xF0, 0x04, 0x04, 0x00, 0x1F, 0x1F, 0x00, 0x00, // 207
    0x00, 0xF0, 0xF0, 0x10, 0x30, 0xE0, 0xC0, 0x01, 0x1F, 0x1F, 0x11, 0x18, 0x0F, 0x07, // 208
    0xF0, 0xF4, 0xE2, 0x84, 0x04, 0xF2, 0xF0, 0x1F, 0x1F, 0x00, 0x03, 0x0E, 0x1F, 0x1F, // 209
    0xC0, 0xE0, 0x32, 0x14, 0x30, 0xE0, 0xC0, 0x07, 0x0F, 0x18, 0x10, 0x18, 0x0F, 0x07, // 210
    0xC0, 0xE0, 0x30, 0x14, 0x32, 0xE0, 0xC0, 0x07, 0x0F, 0x18, 0x10, 0x18, 0x0F, 0x07, // 211
    0xC0, 0xE0, 0x34, 0x12, 0x34, 0xE0, 0xC0, 0x07, 0x0F, 0x18, 0x10, 0x18, 0x0F, 0x07, // 212
    0xC0, 0xE0, 0x36, 0x14, 0x36, 0xE0, 0xC0, 0x07, 0x0F, 0x18, 0x10, 0x18, 0x0F, 0x07, // 213
    0xC0, 0xE4, 0x34, 0x10, 0x34, 0xE4, 0xC0, 0x07, 0x0F, 0x18, 0x10, 0x18, 0x0F, 0x07, // 214
    0x00, 0xC0, 0x80, 0x80, 0xC0, 0x40, 0x04, 0x0E, 0x03, 0x03, 0x06, 0x04, // 215
    0xC0, 0xE0, 0x30, 0x90, 0x70, 0xF8, 0xC0, 0x27, 0x3F, 0x1C, 0x13, 0x18, 0x0F, 0x07, // 216
    0xF0, 0xF0, 0x02, 0x04, 0x00, 0xF0, 0xF0, 0x0F, 0x1F, 0x10, 0x10, 0x10, 0x1F, 0x0F, // 217
    0xF0, 0xF0, 0x00, 0x04, 0x02, 0xF0, 0xF0, 0x0F, 0x1F, 0x10, 0x10, 0x10, 0x1F, 0x0F, // 218
    0xF0, 0xF0, 0x06, 0x02, 0x04, 0xF0, 0xF0, 0x0F, 0x1F, 0x10, 0x10, 0x10, 0x1F, 0x0F, // 219
    0xF0, 0xF4, 0x04, 0x00, 0x04, 0xF4, 0xF0, 0x0F, 0x1F, 0x10, 0x10, 0x10, 0x1F, 0x0F, // 220
    0x10, 0x70, 0xE0, 0x84, 0x86, 0xE2, 0x70, 0x10, 0x00, 0x00, 0x01, 0x1F, 0x1F, 0x01, 0x00, 0x00, // 221
    0xF0, 0xF0, 0x40, 0x40, 0xC0, 0x80, 0x1F, 0x1F, 0x04, 0x04, 0x07, 0x03, // 222
    0xF0, 0xF8, 0x08, 0xF8, 0xF0, 0x00, 0x00, 0x1F, 0x1F, 0x10, 0x11, 0x13, 0x1F, 0x0E, // 223
    0x80, 0xC8, 0x58, 0x50, 0xC0, 0x80, 0x0C, 0x1E, 0x12, 0x12, 0x1F, 0x1F, // 224
    0x80, 0xC0, 0x40, 0x58, 0xC8, 0x80, 0x0C, 0x1E, 0x12, 0x12, 0x1F, 0x1F, // 225
    0x80, 0xD0, 0x58, 0x48, 0xD0, 0x80, 0x0C, 0x1E, 0x12, 0x12, 0x1F, 0x1F, // 226
    0x80, 0xD8, 0x48, 0x50, 0xD8, 0x88, 0x0C, 0x1E, 0x12, 0x12, 0x1F, 0x1F, // 227
    0x90, 0xD0, 0x40, 0xD0, 0x90, 0x0C, 0x1E, 0x12, 0x1F, 0x1F, // 228
    0x80, 0xC0, 0x5C, 0x54, 0xC8, 0x80, 0x0C, 0x1E, 0x12, 0x12, 0x1F, 0x1F, // 229
    0x80, 0xC0, 0x40, 0x40, 0xC0, 0xC0, 0x40, 0x40, 0xC0, 0x80, 0x0C, 0x1E, 0x12, 0x12, 0x1F, 0x1F, 0x12, 0x12, 0x13, 0x03, // 230
    0x80, 0xC0, 0x40, 0x40, 0xC0, 0x0F, 0x1F, 0x38, 0xF8, 0x4C, // 231
    0x80, 0xC8, 0x58, 0x40, 0xC0, 0x80, 0x0F, 0x1F, 0x12, 0x12, 0x1B, 0x03, // 232
    0x80, 0xC0, 0x50, 0x58, 0xC8, 0x80, 0x0F, 0x1F, 0x12, 0x12, 0x1B, 0x03, // 233
    0x80, 0xD0, 0x48, 0x58, 0xD0, 0x80, 0x0F, 0x1F, 0x12, 0x12, 0x1B, 0x03, // 234
    0x00, 0x90, 0xD0, 0x40, 0xD0, 0x90, 0x02, 0x0F, 0x1F, 0x12, 0x13, 0x1B, // 235
    0x08, 0xD8, 0xD0, 0x00, 0x1F, 0x1F, // 236
    0xD0, 0xD8, 0x08, 0x1F, 0x1F, 0x00, // 237
    0x10, 0xC8, 0xC8, 0x10, 0x00, 0x1F, 0x1F, 0x00, // 238
    0x10, 0xD0, 0xC0, 0x10, 0x10, 0x00, 0x1F, 0x1F, 0x00, 0x00, // 239
    0x00, 0x98, 0xB8, 0xB0, 0xF0, 0x80, 0x0F, 0x1F, 0x10, 0x10, 0x1F, 0x07, // 240
    0xC0, 0xD8, 0x48, 0x50, 0xD8, 0x80, 0x1F, 0x1F, 0x00, 0x00, 0x1F, 0x1F, // 241
    0x80, 0xC8, 0x58, 0x40, 0xC0, 0x80, 0x0F, 0x1F, 0x10, 0x10, 0x1F, 0x0F, // 242
    0x80, 0xC0, 0x40, 0x58, 0xC8, 0x80, 0x0F, 0x1F, 0x10, 0x10, 0x1F, 0x0F, // 243
    0x80, 0xD0, 0x58, 0x58, 0xD0, 0x80, 0x0F, 0x1F, 0x10, 0x10, 0x1F, 0x0F, // 244
    0x80, 0xD8, 0x48, 0x50, 0xD8, 0x80, 0x0F, 0x1F, 0x10, 0x10, 0x1F, 0x0F, // 245
    0x80, 0xD0, 0x50, 0x50, 0xD0, 0x80, 0x0F, 0x1F, 0x10, 0x10, 0x1F, 0x0F, // 246
    0x00, 0x00, 0x60, 0x60, 0x00, 0x00, 0x01, 0x01, 0x0D, 0x0D, 0x01, 0x01, // 247
    0x80, 0xC0, 0x40, 0xC0, 0xE0, 0x80, 0x0F, 0x3F, 0x1E, 0x11, 0x1F, 0x0F, // 248
    0xC0, 0xC8, 0x18, 0x10, 0xC0, 0xC0, 0x0F, 0x1F, 0x10, 0x10, 0x1F, 0x1F, // 249
    0xC0, 0xC0, 0x00, 0x18, 0xC8, 0xC0, 0x0F, 0x1F, 0x10, 0x10, 0x1F, 0x1F, // 250
    0xC0, 0xD0, 0x18, 0x08, 0xD0, 0xC0, 0x0F, 0x1F, 0x10, 0x10, 0x1F, 0x1F, // 251
    0xD0, 0xD0, 0x00, 0x10, 0xD0, 0xC0, 0x0F, 0x1F, 0x10, 0x10, 0x1F, 0x1F, // 252
    0x40, 0xC0, 0x80, 0x18, 0xC8, 0xC0, 0x00, 0x83, 0xDF, 0x7C, 0x0F, 0x01, // 253
    0xF8, 0xF8, 0x40, 0x40, 0xC0, 0x80, 0xFF, 0xFF, 0x10, 0x10, 0x1F, 0x0F, // 254
    0x40, 0xD0, 0x90, 0x00, 0x90, 0xD0, 0x40, 0x00, 0x83, 0xDF, 0x78, 0x1F, 0x03, 0x00, // 255
    0x00, 0x00, 0xC4, 0xF4, 0xF4, 0xC4, 0x00, 0x00, 0x10, 0x1E, 0x07, 0x04, 0x04, 0x07, 0x1E, 0x10, // 256
    0x80, 0xD0, 0x50, 0x50, 0xD0, 0x80, 0x0C, 0x1E, 0x12, 0x12, 0x1F, 0x1F, // 257
    0x00, 0x00, 0xC2, 0xF4, 0xF4, 0xC2, 0x00, 0x00, 0x10, 0x1E, 0x07, 0x04, 0x04, 0x07, 0x1E, 0x10, // 258
    0x80, 0xC8, 0x50, 0x50, 0xD8, 0x80, 0x0C, 0x1E, 0x12, 0x12, 0x1F, 0x1F, // 259
    0x00, 0x00, 0xE0, 0x70, 0xF0, 0xC0, 0x00, 0x00, 0x18, 0x1F, 0x07, 0x04, 0x05, 0xE7, 0xFE, 0x98, // 260
    0x80, 0xC0, 0x40, 0x40, 0xC0, 0x80, 0x0C, 0x1E, 0x12, 0xF2, 0xFF, 0x9F, // 261
    0xC0, 0xE0, 0x30, 0x14, 0x16, 0x70, 0x60, 0x07, 0x0F, 0x18, 0x10, 0x10, 0x1C, 0x0C, // 262
    0x80, 0xC0, 0x50, 0x58, 0xC8, 0x0F, 0x1F, 0x10, 0x10, 0x18, // 263
    0xC0, 0xE0, 0x34, 0x12, 0x16, 0x70, 0x60, 0x07, 0x0F, 0x18, 0x10, 0x10, 0x1C, 0x0C, // 264
    0x80, 0xD0, 0x58, 0x58, 0xD0, 0x0F, 0x1F, 0x10, 0x10, 0x18, // 265
    0xC0, 0xE0, 0x30, 0x16, 0x16, 0x30, 0x60, 0x07, 0x0F, 0x18, 0x10, 0x10, 0x18, 0x0C, // 266
    0x80, 0xC0, 0x48, 0x48, 0xC0, 0x0F, 0x1F, 0x10, 0x10, 0x18, // 267
    0xC0, 0xE0, 0x32, 0x14, 0x16, 0x32, 0x20, 0x07, 0x0F, 0x18, 0x10, 0x10, 0x1C, 0x0C, // 268
    0x80, 0xC8, 0x58, 0x58, 0xC8, 0x0F, 0x1F, 0x10, 0x10, 0x18, // 269
    0xF0, 0xF2, 0x14, 0x16, 0x32, 0xE0, 0xC0, 0x1F, 0x1F, 0x10, 0x10, 0x18, 0x0F, 0x07, // 270
    0x80, 0xC0, 0x40, 0x40, 0xF8, 0xF8, 0x38, 0x18, 0x0F, 0x1F, 0x10, 0x10, 0x1F, 0x1F, 0x00, 0x00, // 271
    0x00, 0xF0, 0xF0, 0x10, 0x30, 0xE0, 0xC0, 0x01, 0x1F, 0x1F, 0x11, 0x18, 0x0F, 0x07, // 272
    0x80, 0xC0, 0x40, 0x50, 0xF8, 0xF8, 0x10, 0x0F, 0x1F, 0x10, 0x10, 0x1F, 0x1F, 0x00, // 273
    0xF0, 0xF4, 0x14, 0x14, 0x14, 0x10, 0x1F, 0x1F, 0x11, 0x11, 0x11, 0x10, // 274
    0x80, 0xD0, 0x50, 0x50, 0xD0, 0x80, 0x0F, 0x1F, 0x12, 0x12, 0x1B, 0x03, // 275
    0xF0, 0xF2, 0x14, 0x14, 0x12, 0x10, 0x1F, 0x1F, 0x11, 0x11, 0x11, 0x10, // 276
    0x80, 0xD8, 0x50, 0x58, 0xC8, 0x80, 0x0F, 0x1F, 0x12, 0x12, 0x1B, 0x03, // 277
    0xF0, 0xF0, 0x14, 0x14, 0x10, 0x10, 0x1F, 0x1F, 0x11, 0x11, 0x11, 0x10, // 278
    0x80, 0xC0, 0x48, 0x48, 0xC0, 0x80, 0x0F, 0x1F, 0x12, 0x12, 0x1B, 0x03, // 279
    0xF0, 0xF0, 0x10, 0x10, 0x10, 0x10, 0x1F, 0x1F, 0xF1, 0xF1, 0x91, 0x10, // 280
    0x00, 0x80, 0xC0, 0x40, 0x40, 0x80, 0x06, 0x1F, 0x35, 0xF4, 0xF4, 0x17, // 281
    0xF0, 0xF2, 0x16, 0x16, 0x12, 0x10, 0x1F, 0x1F, 0x11, 0x11, 0x11, 0x10, // 282
    0x80, 0xC8, 0x50, 0x58, 0xC8, 0x80, 0x0F, 0x1F, 0x12, 0x12, 0x1B, 0x03, // 283
    0xC0, 0xE0, 0x34, 0x12, 0x14, 0x70, 0x60, 0x07, 0x0F, 0x18, 0x10, 0x11, 0x1F, 0x0F, // 284
    0x80, 0xD0, 0x58, 0x58, 0xD0, 0xC0, 0x0F, 0xDF, 0x90, 0x90, 0xFF, 0x7F, // 285
    0xC0, 0xE0, 0x36, 0x14, 0x16, 0x70, 0x60, 0x07, 0x0F, 0x18, 0x10, 0x11, 0x1F, 0x0F, // 286
    0x80, 0xC8, 0x50, 0x50, 0xC8, 0xC0, 0x0F, 0xDF, 0x90, 0x90, 0xFF, 0x7F, // 287
    0xC0, 0xE0, 0x30, 0x16, 0x16, 0x10, 0x70, 0x60, 0x07, 0x0F, 0x18, 0x10, 0x11, 0x11, 0x1F, 0x0F, // 288
    0x80, 0xC0, 0x48, 0x48, 0xC0, 0xC0, 0x0F, 0xDF, 0x90, 0x90, 0xFF, 0x7F, // 289
    0xC0, 0xE0, 0x30, 0x10, 0x10, 0x70, 0x60, 0x07, 0x0F, 0x18, 0xF1, 0x11, 0x1F, 0x0F, // 290
    0x80, 0xC0, 0x78, 0x78, 0xC0, 0xC0, 0x0F, 0xDF, 0x90, 0x90, 0xFF, 0x7F, // 291
    0xF0, 0xF0, 0x04, 0x02, 0x04, 0xF0, 0xF0, 0x1F, 0x1F, 0x01, 0x01, 0x01, 0x1F, 0x1F, // 292
    0xFC, 0xFC, 0x42, 0x42, 0xC4, 0x80, 0x1F, 0x1F, 0x00, 0x00, 0x1F, 0x1F, // 293
    0x20, 0xF0, 0xF0, 0x20, 0x20, 0x20, 0xF0, 0xF0, 0x00, 0x1F, 0x1F, 0x01, 0x01, 0x01, 0x1F, 0x1F, // 294
    0x10, 0xF8, 0xF8, 0x50, 0x40, 0xC0, 0x80, 0x00, 0x1F, 0x1F, 0x00, 0x00, 0x1F, 0x1F, // 295
    0x06, 0xF2, 0xF4, 0x06, 0x00, 0x1F, 0x1F, 0x00, // 296
    0x18, 0xC8, 0xD0, 0x18, 0x00, 0x1F, 0x1F, 0x00, // 297
    0x04, 0xF4, 0xF4, 0x04, 0x00, 0x1F, 0x1F, 0x00, // 298
    0x10, 0xD0, 0xD0, 0x10, 0x00, 0x1F, 0x1F, 0x00, // 299
    0x02, 0xF4, 0xF4, 0x02, 0x00, 0x1F, 0x1F, 0x00, // 300
    0x08, 0xD0, 0xD0, 0x08, 0x00, 0x1F, 0x1F, 0x00, // 301
    0x00, 0xF0, 0xF0, 0xE0, 0xFF, 0x9F, // 302
    0x00, 0xD8, 0xD8, 0xE0, 0xFF, 0x9F, // 303
    0xF4, 0xF4, 0x1F, 0x1F, // 304
    0xC0, 0xC0, 0x1F, 0x1F, // 305
    0xF0, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xF0, 0x1F, 0x1F, 0x00, 0x08, 0x18, 0x10, 0x10, 0x1F, 0x0F, // 306
    0xD8, 0xD8, 0x00, 0xD8, 0xD8, 0x1F, 0x1F, 0x80, 0xFF, 0x7F, // 307
    0x00, 0x00, 0x00, 0x04, 0xF2, 0xF6, 0x04, 0x08, 0x18, 0x10, 0x10, 0x1F, 0x0F, 0x00, // 308
    0x10, 0xC8, 0xD8, 0x10, 0x80, 0xFF, 0x7F, 0x00, // 309
    0xF0, 0xF0, 0x80, 0xC0, 0xE0, 0x30, 0x10, 0x1F, 0x1F, 0xE3, 0x67, 0x0E, 0x1C, 0x10, // 310
    0xF8, 0xF8, 0x00, 0x80, 0xC0, 0x40, 0x1F, 0x1F, 0xE3, 0x6F, 0x1C, 0x18, // 311
    0xC0, 0xC0, 0x00, 0x80, 0xC0, 0x40, 0x1F, 0x1F, 0x06, 0x0F, 0x1D, 0x10, // 312
    0xF4, 0xF6, 0x02, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0x10, 0x10, 0x10, 0x10, // 313
    0xFC, 0xFE, 0x02, 0x1F, 0x1F, 0x00, // 314
    0xF0, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x1F, 0xF0, 0x70, 0x10, 0x10, // 315
    0xF8, 0xF8, 0xFF, 0x7F, // 316
    0xF0, 0xF0, 0x00, 0x70, 0x30, 0x00, 0x1F, 0x1F, 0x10, 0x10, 0x10, 0x10, // 317
    0xF8, 0xF8, 0x38, 0x18, 0x1F, 0x1F, 0x00, 0x00, // 318
    0xF0, 0xF0, 0x00, 0x80, 0x80, 0x00, 0x1F, 0x1F, 0x10, 0x11, 0x11, 0x10, // 319
    0xF8, 0xF8, 0x00, 0x00, 0x1F, 0x1F, 0x01, 0x01, // 320
    0x00, 0xF0, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1F, 0x1F, 0x11, 0x10, 0x10, 0x10, // 321
    0x00, 0xF8, 0xF8, 0x80, 0x01, 0x1F, 0x1F, 0x00, // 322
    0xF0, 0xF0, 0xE0, 0x84, 0x02, 0xF0, 0xF0, 0x1F, 0x1F, 0x00, 0x03, 0x0E, 0x1F, 0x1F, // 323
    0xC0, 0xC0, 0x40, 0x58, 0xC8, 0x80, 0x1F, 0x1F, 0x00, 0x00, 0x1F, 0x1F, // 324
    0xF0, 0xF0, 0xE0, 0x80, 0x00, 0xF0, 0xF0, 0x1F, 0x1F, 0xE0, 0x63, 0x0E, 0x1F, 0x1F, // 325
    0xC0, 0xC0, 0x40, 0x40, 0xC0, 0x80, 0x1F, 0x1F, 0xE0, 0x00, 0x1F, 0x1F, // 326
    0xF0, 0xF2, 0xE6, 0x84, 0x06, 0xF2, 0xF0, 0x1F, 0x1F, 0x00, 0x03, 0x0E, 0x1F, 0x1F, // 327
    0xC0, 0xC8, 0x58, 0x58, 0xC8, 0x80, 0x1F, 0x1F, 0x00, 0x00, 0x1F, 0x1F, // 328
    0x38, 0xD8, 0xC0, 0x40, 0xC0, 0x80, 0x00, 0x1F, 0x1F, 0x00, 0x1F, 0x1F, // 329
    0xF0, 0xF0, 0xE0, 0x80, 0x00, 0xF0, 0xF0, 0x1F, 0x1F, 0x00, 0x03, 0x8E, 0xFF, 0x7F, // 330
    0xC0, 0xC0, 0x40, 0x40, 0xC0, 0x80, 0x1F, 0x1F, 0x00, 0x80, 0xFF, 0x7F, // 331
    0xC0, 0xE0, 0x34, 0x14, 0x34, 0xE4, 0xC0, 0x07, 0x0F, 0x18, 0x10, 0x18, 0x0F, 0x07, // 332
    0x80, 0xD0, 0x50, 0x50, 0xD0, 0x80, 0x0F, 0x1F, 0x10, 0x10, 0x1F, 0x0F, // 333
    0xC0, 0xE0, 0x36, 0x14, 0x36, 0xE0, 0xC0, 0x07, 0x0F, 0x18, 0x10, 0x18, 0x0F, 0x07, // 334
    0x80, 0xC8, 0x50, 0x50, 0xC8, 0x80, 0x0F, 0x1F, 0x10, 0x10, 0x1F, 0x0F, // 335
    0xC0, 0xE0, 0x34, 0x12, 0x34, 0xE2, 0xC0, 0x07, 0x0F, 0x18, 0x10, 0x18, 0x0F, 0x07, // 336
    0x80, 0xC0, 0x58, 0x50, 0xD8, 0x88, 0x0F, 0x1F, 0x10, 0x10, 0x1F, 0x0F, // 337
    0xC0, 0xE0, 0x30, 0x10, 0x10, 0xF0, 0xF0, 0x10, 0x10, 0x10, 0x10, 0x07, 0x0F, 0x18, 0x10, 0x10, 0x1F, 0x1F, 0x11, 0x11, 0x11, 0x10, // 338
    0x80, 0xC0, 0x40, 0x40, 0xC0, 0xC0, 0x40, 0x40, 0xC0, 0x80, 0x0F, 0x1F, 0x10, 0x10, 0x1F, 0x1F, 0x1A, 0x12, 0x13, 0x03, // 339
    0xF0, 0xF0, 0x14, 0x12, 0xF0, 0xE0, 0x1F, 0x1F, 0x01, 0x07, 0x1F, 0x18, // 340
    0xC0, 0xD0, 0x58, 0x48, 0x1F, 0x1F, 0x00, 0x00, // 341
    0xF0, 0xF0, 0x10, 0x10, 0xF0, 0xE0, 0x1F, 0x1F, 0xE1, 0x61, 0x1F, 0x18, // 342
    0xC0, 0xC0, 0x40, 0x40, 0xFF, 0x7F, 0x00, 0x00, // 343
    0xF2, 0xF2, 0x14, 0x16, 0xF2, 0xE0, 0x1F, 0x1F, 0x01, 0x07, 0x1F, 0x18, // 344
    0xC8, 0xD8, 0x58, 0x48, 0x1F, 0x1F, 0x00, 0x00, // 345
    0xE0, 0xF0, 0x90, 0x94, 0x16, 0x30, 0x20, 0x0C, 0x1D, 0x11, 0x13, 0x13, 0x1F, 0x0E, // 346
    0x80, 0xC0, 0x50, 0xC8, 0x80, 0x0B, 0x1B, 0x17, 0x1E, 0x0E, // 347
    0xE0, 0xF0, 0x96, 0x92, 0x16, 0x30, 0x20, 0x0C, 0x1D, 0x11, 0x13, 0x13, 0x1F, 0x0E, // 348
    0x80, 0xD0, 0x48, 0xD0, 0x80, 0x0B, 0x1B, 0x17, 0x1E, 0x0E, // 349
    0xE0, 0xF0, 0x90, 0x90, 0x10, 0x30, 0x20, 0x0C, 0x1D, 0x11, 0xF3, 0xF3, 0x1F, 0x0E, // 350
    0x80, 0xC0, 0x40, 0xC0, 0x80, 0x0B, 0x1B, 0xB7, 0x5E, 0x0E, // 351
    0xE0, 0xF0, 0x96, 0x94, 0x16, 0x32, 0x20, 0x0C, 0x1D, 0x11, 0x13, 0x13, 0x1F, 0x0E, // 352
    0x80, 0xC8, 0x50, 0xC8, 0x80, 0x0B, 0x1B, 0x17, 0x1E, 0x0E, // 353
    0x10, 0x10, 0xF0, 0xF0, 0x10, 0x10, 0x10, 0x00, 0x00, 0xBF, 0xFF, 0x40, 0x00, 0x00, // 354
    0x40, 0xF0, 0xF0, 0x40, 0x00, 0x0F, 0xBF, 0xF8, // 355
    0x10, 0x12, 0xF4, 0xF4, 0x12, 0x12, 0x10, 0x00, 0x00, 0x1F, 0x1F, 0x00, 0x00, 0x00, // 356
    0x40, 0xF0, 0xF0, 0x5C, 0x00, 0x0F, 0x1F, 0x10, // 357
    0x10, 0x90, 0xF0, 0xF0, 0x90, 0x10, 0x10, 0x00, 0x00, 0x1F, 0x1F, 0x00, 0x00, 0x00, // 358
    0x40, 0xF0, 0xF0, 0x40, 0x01, 0x0F, 0x1F, 0x11, // 359
    0xF0, 0xF4, 0x02, 0x04, 0x04, 0xF2, 0xF0, 0x0F, 0x1F, 0x10, 0x10, 0x10, 0x1F, 0x0F, // 360
    0xC0, 0xD8, 0x08, 0x10, 0xD8, 0xC0, 0x0F, 0x1F, 0x10, 0x10, 0x1F, 0x1F, // 361
    0xF0, 0xF4, 0x04, 0x04, 0x04, 0xF0, 0xF0, 0x0F, 0x1F, 0x10, 0x10, 0x10, 0x1F, 0x0F, // 362
    0xC0, 0xD0, 0x10, 0x10, 0xD0, 0xC0, 0x0F, 0x1F, 0x10, 0x10, 0x1F, 0x1F, // 363
    0xF0, 0xF2, 0x06, 0x04, 0x06, 0xF2, 0xF0, 0x0F, 0x1F, 0x10, 0x10, 0x10, 0x1F, 0x0F, // 364
    0xC0, 0xC8, 0x10, 0x10, 0xC8, 0xC0, 0x0F, 0x1F, 0x10, 0x10, 0x1F, 0x1F, // 365
    0xF0, 0xF2, 0x06, 0x05, 0x02, 0xF0, 0xF0, 0x0F, 0x1F, 0x10, 0x10, 0x10, 0x1F, 0x0F, // 366
    0xC0, 0xC8, 0x14, 0x1C, 0xC0, 0xC0, 0x0F, 0x1F, 0x10, 0x10, 0x1F, 0x1F, // 367
    0xF0, 0xF0, 0x06, 0x02, 0x04, 0xF2, 0xF0, 0x0F, 0x1F, 0x10, 0x10, 0x10, 0x1F, 0x0F, // 368
    0xC0, 0xD0, 0x18, 0x00, 0xD8, 0xC8, 0x0F, 0x1F, 0x10, 0x10, 0x1F, 0x1F, // 369
    0xF0, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0xF0, 0x0F, 0x1F, 0x10, 0x70, 0x70, 0x5F, 0x0F, // 370
    0xC0, 0xC0, 0x00, 0x00, 0xC0, 0xC0, 0x0F, 0x1F, 0x10, 0xF0, 0xFF, 0x9F, // 371
    0x10, 0xF0, 0x80, 0x00, 0xF4, 0xF2, 0xC4, 0x00, 0xF0, 0xF0, 0x00, 0x03, 0x1F, 0x1E, 0x03, 0x00, 0x0F, 0x1C, 0x1F, 0x00, // 372
    0x40, 0xC0, 0x10, 0x98, 0xC8, 0x10, 0x00, 0xC0, 0x40, 0x00, 0x0F, 0x1C, 0x0F, 0x01, 0x1F, 0x1E, 0x07, 0x00, // 373
    0x10, 0x70, 0xE8, 0x84, 0x84, 0xE8, 0x70, 0x10, 0x00, 0x00, 0x01, 0x1F, 0x1F, 0x01, 0x00, 0x00, // 374
    0x40, 0xD0, 0x98, 0x08, 0xD0, 0xC0, 0x00, 0x83, 0xDF, 0x7C, 0x0F, 0x01, // 375
    0x30, 0x74, 0xC4, 0x00, 0xC4, 0xF4, 0x30, 0x00, 0x00, 0x01, 0x1F, 0x1F, 0x01, 0x00, // 376
    0x10, 0x10, 0x10, 0xD6, 0x72, 0x30, 0x18, 0x1E, 0x17, 0x11, 0x10, 0x10, // 377
    0x40, 0x40, 0x50, 0xC8, 0xC0, 0x18, 0x1E, 0x17, 0x11, 0x10, // 378
    0x10, 0x10, 0x14, 0xD4, 0x70, 0x30, 0x18, 0x1C, 0x17, 0x11, 0x10, 0x10, // 379
    0x40, 0x40, 0x48, 0xC8, 0xC0, 0x18, 0x1C, 0x1F, 0x13, 0x10, // 380
    0x10, 0x12, 0x14, 0xD4, 0x72, 0x30, 0x18, 0x1E, 0x17, 0x11, 0x10, 0x10, // 381
    0x40, 0x48, 0x50, 0xC8, 0xC0, 0x18, 0x1E, 0x17, 0x11, 0x10 // 382
};

#endif
