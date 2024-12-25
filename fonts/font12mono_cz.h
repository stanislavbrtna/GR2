

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
 * File Name           : font12mono_cz.h
 * Date                : 28.10.2024
 * Font size in bytes  : 16164
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


#define NEW_FONT_WIDTH 10
#define NEW_FONT_HEIGHT 16

const uint8_t font12mono_cz[] = {
    0x3F, 0x24, // size
    0x0A, // width
    0x10, // height
    0xC1, // first char
    0xBE, // char count
    
    // char widths
    0x07, 0x07, 0x07, 0x07, 0x07, 0x06, 0x05, 0x05, 0x05, 0x05, 
    0x05, 0x05, 0x05, 0x05, 0x05, 0x06, 0x05, 0x05, 0x05, 0x05, 
    0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x07, 0x05, 
    0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x07, 0x05, 0x05, 
    0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 
    0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 
    0x05, 0x05, 0x05, 0x07, 0x05, 0x07, 0x05, 0x07, 0x05, 0x05, 
    0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x06, 
    0x06, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 
    0x05, 0x05, 0x06, 0x05, 0x06, 0x05, 0x06, 0x05, 0x06, 0x05, 
    0x05, 0x07, 0x06, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 
    0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x04, 0x06, 0x06, 0x05, 
    0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x06, 0x05, 
    0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x06, 0x05, 0x05, 0x05, 
    0x05, 0x05, 0x05, 0x05, 0x05, 0x06, 0x07, 0x06, 0x04, 0x06, 
    0x04, 0x06, 0x04, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 
    0x05, 0x06, 0x05, 0x06, 0x05, 0x06, 0x05, 0x05, 0x05, 0x05, 
    0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x07, 
    0x07, 0x07, 0x05, 0x07, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 
    
    
    // font data
    0x00, 0x00, 0xE0, 0x14, 0xE2, 0x00, 0x00, 0x18, 0x0F, 0x02, 0x02, 0x02, 0x0F, 0x18, // 193
    0x00, 0x00, 0xE4, 0x12, 0xE4, 0x00, 0x00, 0x18, 0x0F, 0x02, 0x02, 0x02, 0x0F, 0x18, // 194
    0x00, 0x00, 0xE6, 0x12, 0xE4, 0x06, 0x00, 0x18, 0x0F, 0x02, 0x02, 0x02, 0x0F, 0x18, // 195
    0x00, 0x00, 0xE4, 0x10, 0xE4, 0x00, 0x00, 0x18, 0x0F, 0x02, 0x02, 0x02, 0x0F, 0x18, // 196
    0x00, 0x00, 0xE8, 0x14, 0xE8, 0x00, 0x00, 0x18, 0x0F, 0x02, 0x02, 0x02, 0x0F, 0x18, // 197
    0x00, 0xC0, 0x30, 0xF0, 0x10, 0x10, 0x18, 0x07, 0x02, 0x1F, 0x11, 0x11, // 198
    0xC0, 0x20, 0x10, 0x10, 0x10, 0x07, 0x18, 0x90, 0x50, 0x10, // 199
    0xF0, 0x12, 0x14, 0x10, 0x10, 0x1F, 0x11, 0x11, 0x11, 0x11, // 200
    0xF0, 0x10, 0x14, 0x12, 0x10, 0x1F, 0x11, 0x11, 0x11, 0x11, // 201
    0xF0, 0x14, 0x12, 0x14, 0x10, 0x1F, 0x11, 0x11, 0x11, 0x11, // 202
    0xF0, 0x14, 0x10, 0x14, 0x10, 0x1F, 0x11, 0x11, 0x11, 0x11, // 203
    0x10, 0x12, 0xF4, 0x10, 0x10, 0x10, 0x10, 0x1F, 0x10, 0x10, // 204
    0x10, 0x10, 0xF4, 0x12, 0x10, 0x10, 0x10, 0x1F, 0x10, 0x10, // 205
    0x10, 0x14, 0xF2, 0x14, 0x10, 0x10, 0x10, 0x1F, 0x10, 0x10, // 206
    0x10, 0x14, 0xF0, 0x14, 0x10, 0x10, 0x10, 0x1F, 0x10, 0x10, // 207
    0x00, 0xF0, 0x10, 0x10, 0x20, 0xC0, 0x01, 0x1F, 0x11, 0x11, 0x08, 0x07, // 208
    0xF0, 0x46, 0x82, 0x04, 0xF6, 0x1F, 0x00, 0x03, 0x04, 0x1F, // 209
    0xE0, 0x32, 0x14, 0x30, 0xE0, 0x0F, 0x18, 0x10, 0x18, 0x0F, // 210
    0xE0, 0x30, 0x14, 0x32, 0xE0, 0x0F, 0x18, 0x10, 0x18, 0x0F, // 211
    0xE0, 0x34, 0x12, 0x34, 0xE0, 0x0F, 0x18, 0x10, 0x18, 0x0F, // 212
    0xE0, 0x36, 0x12, 0x34, 0xE6, 0x0F, 0x18, 0x10, 0x18, 0x0F, // 213
    0xE0, 0x34, 0x10, 0x34, 0xE0, 0x0F, 0x18, 0x10, 0x18, 0x0F, // 214
    0x40, 0x80, 0x00, 0x80, 0x40, 0x04, 0x02, 0x01, 0x02, 0x04, // 215
    0xE0, 0x30, 0x90, 0x70, 0xF0, 0x1F, 0x1C, 0x13, 0x18, 0x0F, // 216
    0xF0, 0x02, 0x04, 0x00, 0xF0, 0x0F, 0x18, 0x10, 0x18, 0x0F, // 217
    0xF0, 0x00, 0x04, 0x02, 0xF0, 0x0F, 0x18, 0x10, 0x18, 0x0F, // 218
    0xF0, 0x04, 0x02, 0x04, 0xF0, 0x0F, 0x18, 0x10, 0x18, 0x0F, // 219
    0xF0, 0x04, 0x00, 0x04, 0xF0, 0x0F, 0x18, 0x10, 0x18, 0x0F, // 220
    0x10, 0x60, 0x80, 0x04, 0x82, 0x60, 0x10, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, // 221
    0xF0, 0x40, 0x40, 0x40, 0x80, 0x1F, 0x04, 0x04, 0x04, 0x03, // 222
    0xE0, 0x10, 0x90, 0x70, 0x00, 0x1F, 0x00, 0x11, 0x12, 0x1C, // 223
    0x00, 0x90, 0xA0, 0x80, 0x00, 0x0C, 0x12, 0x12, 0x12, 0x1F, // 224
    0x00, 0x80, 0xA0, 0x90, 0x00, 0x0C, 0x12, 0x12, 0x12, 0x1F, // 225
    0x00, 0x80, 0xA0, 0x90, 0x20, 0x0C, 0x12, 0x12, 0x12, 0x1F, // 226
    0x00, 0xB0, 0x90, 0xA0, 0x30, 0x0C, 0x12, 0x12, 0x12, 0x1F, // 227
    0x00, 0xA0, 0x80, 0xA0, 0x00, 0x0C, 0x12, 0x12, 0x12, 0x1F, // 228
    0x00, 0x90, 0xA8, 0x90, 0x00, 0x0C, 0x12, 0x12, 0x12, 0x1F, // 229
    0x00, 0x80, 0x80, 0x00, 0x80, 0x80, 0x00, 0x1C, 0x12, 0x12, 0x0F, 0x12, 0x12, 0x13, // 230
    0x00, 0x80, 0x80, 0x80, 0x80, 0x0F, 0x19, 0x90, 0x50, 0x10, // 231
    0x00, 0x90, 0xA0, 0x80, 0x00, 0x0F, 0x1A, 0x12, 0x12, 0x13, // 232
    0x00, 0x80, 0xA0, 0x90, 0x00, 0x0F, 0x1A, 0x12, 0x12, 0x13, // 233
    0x00, 0xA0, 0x90, 0xA0, 0x00, 0x0F, 0x1A, 0x12, 0x12, 0x13, // 234
    0x00, 0xA0, 0x80, 0xA0, 0x00, 0x0F, 0x1A, 0x12, 0x12, 0x13, // 235
    0x80, 0x90, 0xA0, 0x00, 0x00, 0x10, 0x10, 0x1F, 0x10, 0x10, // 236
    0x80, 0x80, 0xA0, 0x10, 0x00, 0x10, 0x10, 0x1F, 0x10, 0x10, // 237
    0x80, 0xA0, 0x90, 0x20, 0x00, 0x10, 0x10, 0x1F, 0x10, 0x10, // 238
    0x80, 0xA0, 0x80, 0x20, 0x00, 0x10, 0x10, 0x1F, 0x10, 0x10, // 239
    0x00, 0x50, 0x20, 0xD0, 0x80, 0x0E, 0x11, 0x11, 0x11, 0x0F, // 240
    0x80, 0xB0, 0x90, 0xA0, 0x30, 0x1F, 0x00, 0x00, 0x00, 0x1F, // 241
    0x00, 0x90, 0xA0, 0x80, 0x00, 0x0F, 0x10, 0x10, 0x10, 0x0F, // 242
    0x00, 0x80, 0xA0, 0x90, 0x00, 0x0F, 0x10, 0x10, 0x10, 0x0F, // 243
    0x00, 0xA0, 0x90, 0xA0, 0x00, 0x0F, 0x10, 0x10, 0x10, 0x0F, // 244
    0x00, 0xB0, 0x90, 0xA0, 0x30, 0x0F, 0x10, 0x10, 0x10, 0x0F, // 245
    0x00, 0xA0, 0x80, 0xA0, 0x00, 0x0F, 0x10, 0x10, 0x10, 0x0F, // 246
    0x00, 0x00, 0x40, 0x00, 0x00, 0x01, 0x01, 0x05, 0x01, 0x01, // 247
    0x00, 0x80, 0x80, 0x80, 0x00, 0x0F, 0x18, 0x16, 0x11, 0x0F, // 248
    0x80, 0x10, 0x20, 0x00, 0x80, 0x0F, 0x10, 0x10, 0x10, 0x1F, // 249
    0x80, 0x00, 0x20, 0x10, 0x80, 0x0F, 0x10, 0x10, 0x10, 0x1F, // 250
    0x80, 0x20, 0x10, 0x20, 0x80, 0x0F, 0x10, 0x10, 0x10, 0x1F, // 251
    0x80, 0x20, 0x00, 0x20, 0x80, 0x0F, 0x10, 0x10, 0x10, 0x1F, // 252
    0x80, 0x00, 0x20, 0x10, 0x80, 0x81, 0x86, 0x78, 0x0E, 0x01, // 253
    0xF0, 0x80, 0x80, 0x80, 0x00, 0xFF, 0x10, 0x10, 0x10, 0x0F, // 254
    0x80, 0x20, 0x00, 0x20, 0x80, 0x81, 0x86, 0x78, 0x0E, 0x01, // 255
    0x00, 0x00, 0xE4, 0x14, 0xE4, 0x04, 0x00, 0x18, 0x0F, 0x02, 0x02, 0x02, 0x0F, 0x18, // 256
    0x00, 0xA0, 0xA0, 0xA0, 0x20, 0x0C, 0x12, 0x12, 0x12, 0x1F, // 257
    0x00, 0x00, 0xE2, 0x14, 0xE4, 0x02, 0x00, 0x18, 0x0F, 0x02, 0x02, 0x02, 0x0F, 0x18, // 258
    0x00, 0x90, 0xA0, 0xA0, 0x10, 0x0C, 0x12, 0x12, 0x12, 0x1F, // 259
    0x00, 0x00, 0xE0, 0x10, 0xE0, 0x00, 0x00, 0x18, 0x0F, 0x02, 0x02, 0x02, 0x4F, 0x98, // 260
    0x00, 0x80, 0x80, 0x80, 0x00, 0x0C, 0x12, 0x12, 0x52, 0x9F, // 261
    0xC0, 0x20, 0x10, 0x14, 0x12, 0x07, 0x18, 0x10, 0x10, 0x10, // 262
    0x00, 0x80, 0x80, 0xA0, 0x90, 0x0F, 0x19, 0x10, 0x10, 0x10, // 263
    0xC0, 0x20, 0x14, 0x12, 0x14, 0x07, 0x18, 0x10, 0x10, 0x10, // 264
    0x00, 0x80, 0xA0, 0x90, 0xA0, 0x0F, 0x19, 0x10, 0x10, 0x10, // 265
    0xC0, 0x20, 0x10, 0x14, 0x10, 0x07, 0x18, 0x10, 0x10, 0x10, // 266
    0x00, 0x80, 0x80, 0xA0, 0x80, 0x0F, 0x19, 0x10, 0x10, 0x10, // 267
    0xC0, 0x20, 0x12, 0x14, 0x12, 0x07, 0x18, 0x10, 0x10, 0x10, // 268
    0x00, 0x80, 0x90, 0xA0, 0x90, 0x0F, 0x19, 0x10, 0x10, 0x10, // 269
    0xF0, 0x12, 0x14, 0x22, 0xC0, 0x1F, 0x10, 0x10, 0x08, 0x07, // 270
    0x00, 0x80, 0x80, 0x80, 0xF0, 0x0F, 0x10, 0x10, 0x10, 0x1F, // 271
    0x00, 0xF0, 0x10, 0x10, 0x20, 0xC0, 0x01, 0x1F, 0x11, 0x11, 0x08, 0x07, // 272
    0x00, 0x80, 0xA0, 0xA0, 0xF0, 0x20, 0x0F, 0x10, 0x10, 0x10, 0x1F, 0x00, // 273
    0xF0, 0x14, 0x14, 0x14, 0x14, 0x1F, 0x11, 0x11, 0x11, 0x11, // 274
    0x00, 0xA0, 0xA0, 0xA0, 0x20, 0x0F, 0x1A, 0x12, 0x12, 0x13, // 275
    0xF0, 0x12, 0x14, 0x14, 0x12, 0x1F, 0x11, 0x11, 0x11, 0x11, // 276
    0x00, 0x90, 0xA0, 0xA0, 0x10, 0x0F, 0x1A, 0x12, 0x12, 0x13, // 277
    0xF0, 0x10, 0x14, 0x10, 0x10, 0x1F, 0x11, 0x11, 0x11, 0x11, // 278
    0x00, 0x80, 0xA0, 0x80, 0x00, 0x0F, 0x1A, 0x12, 0x12, 0x13, // 279
    0xF0, 0x10, 0x10, 0x10, 0x10, 0x1F, 0x11, 0x11, 0x51, 0x91, // 280
    0x00, 0x80, 0x80, 0x80, 0x00, 0x0F, 0x1A, 0x12, 0x52, 0x93, // 281
    0xF0, 0x12, 0x14, 0x12, 0x10, 0x1F, 0x11, 0x11, 0x11, 0x11, // 282
    0x00, 0x90, 0xA0, 0x90, 0x00, 0x0F, 0x1A, 0x12, 0x12, 0x13, // 283
    0xC0, 0x30, 0x14, 0x12, 0x14, 0x07, 0x18, 0x10, 0x11, 0x1F, // 284
    0x00, 0x80, 0xA0, 0x90, 0xA0, 0x80, 0x6B, 0x94, 0x94, 0x94, 0x93, 0x60, // 285
    0xC0, 0x32, 0x14, 0x14, 0x12, 0x07, 0x18, 0x10, 0x11, 0x1F, // 286
    0x00, 0x90, 0xA0, 0xA0, 0x90, 0x80, 0x6B, 0x94, 0x94, 0x94, 0x93, 0x60, // 287
    0xC0, 0x30, 0x10, 0x14, 0x10, 0x07, 0x18, 0x10, 0x11, 0x1F, // 288
    0x00, 0x80, 0x80, 0xA0, 0x80, 0x80, 0x6B, 0x94, 0x94, 0x94, 0x93, 0x60, // 289
    0xC0, 0x30, 0x10, 0x10, 0x10, 0x07, 0x18, 0x90, 0x51, 0x1F, // 290
    0x00, 0x80, 0xA0, 0x90, 0x80, 0x80, 0x6B, 0x94, 0x94, 0x94, 0x93, 0x60, // 291
    0xF0, 0x04, 0x02, 0x04, 0xF0, 0x1F, 0x01, 0x01, 0x01, 0x1F, // 292
    0xF0, 0x84, 0x82, 0x84, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x1F, // 293
    0x20, 0xF0, 0x20, 0x20, 0x20, 0xF0, 0x20, 0x00, 0x1F, 0x01, 0x01, 0x01, 0x1F, 0x00, // 294
    0x20, 0xF0, 0xA0, 0xA0, 0x80, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x1F, // 295
    0x10, 0x16, 0xF2, 0x14, 0x16, 0x10, 0x10, 0x1F, 0x10, 0x10, // 296
    0x80, 0xB0, 0x90, 0x20, 0x30, 0x10, 0x10, 0x1F, 0x10, 0x10, // 297
    0x10, 0x14, 0xF4, 0x14, 0x14, 0x10, 0x10, 0x1F, 0x10, 0x10, // 298
    0x80, 0xA0, 0xA0, 0x20, 0x20, 0x10, 0x10, 0x1F, 0x10, 0x10, // 299
    0x10, 0x12, 0xF4, 0x14, 0x12, 0x10, 0x10, 0x1F, 0x10, 0x10, // 300
    0x80, 0x90, 0xA0, 0x20, 0x10, 0x10, 0x10, 0x1F, 0x10, 0x10, // 301
    0x10, 0x10, 0xF0, 0x10, 0x10, 0x10, 0x10, 0x5F, 0x90, 0x10, // 302
    0x80, 0x80, 0x90, 0x00, 0x00, 0x10, 0x10, 0x5F, 0x90, 0x10, // 303
    0x10, 0x10, 0xF4, 0x10, 0x10, 0x10, 0x10, 0x1F, 0x10, 0x10, // 304
    0x80, 0x80, 0x80, 0x00, 0x00, 0x10, 0x10, 0x1F, 0x10, 0x10, // 305
    0xF0, 0x00, 0x00, 0x00, 0xF0, 0x1F, 0x00, 0x10, 0x10, 0x0F, // 306
    0x90, 0x00, 0x00, 0x80, 0x90, 0x1F, 0x00, 0x80, 0x80, 0x7F, // 307
    0x00, 0x00, 0x04, 0xF2, 0x04, 0x10, 0x10, 0x10, 0x0F, 0x00, // 308
    0x00, 0xA0, 0x90, 0xA0, 0x80, 0x80, 0x80, 0x7F, // 309
    0xF0, 0x00, 0x80, 0x40, 0x20, 0x10, 0x1F, 0x01, 0x81, 0x46, 0x08, 0x10, // 310
    0xF0, 0x00, 0x00, 0x00, 0x80, 0x00, 0x1F, 0x02, 0x82, 0x45, 0x08, 0x10, // 311
    0x80, 0x00, 0x00, 0x00, 0x80, 0x1F, 0x04, 0x06, 0x09, 0x10, // 312
    0xF0, 0x04, 0x02, 0x00, 0x00, 0x1F, 0x10, 0x10, 0x10, 0x10, // 313
    0x10, 0x10, 0xF4, 0x02, 0x00, 0x10, 0x10, 0x1F, 0x10, 0x10, // 314
    0xF0, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x10, 0x90, 0x50, 0x10, // 315
    0x10, 0x10, 0xF0, 0x00, 0x00, 0x10, 0x10, 0x9F, 0x50, 0x10, // 316
    0xF0, 0x00, 0x00, 0x00, 0x60, 0x1F, 0x10, 0x10, 0x10, 0x10, // 317
    0x10, 0x10, 0xF0, 0x00, 0x30, 0x10, 0x10, 0x1F, 0x10, 0x10, // 318
    0xF0, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x10, 0x10, 0x10, 0x11, // 319
    0x10, 0x10, 0xF0, 0x00, 0x00, 0x10, 0x10, 0x1F, 0x10, 0x11, // 320
    0x00, 0xF0, 0x00, 0x80, 0x00, 0x00, 0x02, 0x1F, 0x11, 0x10, 0x10, 0x10, // 321
    0x10, 0x10, 0xF0, 0x00, 0x80, 0x10, 0x12, 0x1F, 0x11, 0x10, // 322
    0xF0, 0x40, 0x84, 0x02, 0xF0, 0x1F, 0x00, 0x03, 0x04, 0x1F, // 323
    0x80, 0x80, 0xA0, 0x90, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x1F, // 324
    0xF0, 0x40, 0x80, 0x00, 0xF0, 0x1F, 0x80, 0x43, 0x04, 0x1F, // 325
    0x80, 0x80, 0x80, 0x80, 0x00, 0x1F, 0x00, 0x80, 0x40, 0x1F, // 326
    0xF0, 0x42, 0x84, 0x02, 0xF0, 0x1F, 0x00, 0x03, 0x04, 0x1F, // 327
    0x80, 0x90, 0xA0, 0x90, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x1F, // 328
    0x40, 0x20, 0x90, 0x80, 0x80, 0x80, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x1F, // 329
    0xF0, 0x60, 0x80, 0x00, 0xF0, 0x1F, 0x00, 0x43, 0x4C, 0x3F, // 330
    0x80, 0x80, 0x80, 0x80, 0x00, 0x1F, 0x00, 0x00, 0x80, 0xFF, // 331
    0xE0, 0x34, 0x14, 0x34, 0xE4, 0x0F, 0x18, 0x10, 0x18, 0x0F, // 332
    0x00, 0xA0, 0xA0, 0xA0, 0x20, 0x0F, 0x10, 0x10, 0x10, 0x0F, // 333
    0xE0, 0x32, 0x14, 0x34, 0xE2, 0x0F, 0x18, 0x10, 0x18, 0x0F, // 334
    0x00, 0x90, 0xA0, 0xA0, 0x10, 0x0F, 0x10, 0x10, 0x10, 0x0F, // 335
    0xE0, 0x34, 0x12, 0x34, 0xE2, 0x0F, 0x18, 0x10, 0x18, 0x0F, // 336
    0x00, 0xA0, 0x90, 0xA0, 0x10, 0x0F, 0x10, 0x10, 0x10, 0x0F, // 337
    0xE0, 0x30, 0x10, 0xF0, 0x10, 0x10, 0x0F, 0x18, 0x10, 0x1F, 0x11, 0x11, // 338
    0x00, 0x80, 0x80, 0x00, 0x80, 0x80, 0x00, 0x0F, 0x10, 0x10, 0x0F, 0x12, 0x12, 0x13, // 339
    0xF0, 0x10, 0x14, 0x12, 0xE0, 0x00, 0x1F, 0x01, 0x01, 0x07, 0x0C, 0x10, // 340
    0x80, 0x20, 0x90, 0x80, 0x1F, 0x01, 0x00, 0x00, // 341
    0xF0, 0x10, 0x10, 0x10, 0xE0, 0x00, 0x1F, 0x01, 0x81, 0x47, 0x0C, 0x10, // 342
    0x80, 0x00, 0x80, 0x80, 0x9F, 0x41, 0x00, 0x00, // 343
    0xF0, 0x12, 0x14, 0x12, 0xE0, 0x00, 0x1F, 0x01, 0x01, 0x07, 0x0C, 0x10, // 344
    0x80, 0x10, 0xA0, 0x90, 0x1F, 0x01, 0x00, 0x00, // 345
    0xE0, 0x90, 0x14, 0x12, 0x10, 0x10, 0x11, 0x11, 0x13, 0x0E, // 346
    0x00, 0x80, 0xA0, 0x90, 0x80, 0x13, 0x12, 0x12, 0x14, 0x0C, // 347
    0xE0, 0x94, 0x12, 0x14, 0x10, 0x10, 0x11, 0x11, 0x13, 0x0E, // 348
    0x00, 0xA0, 0x90, 0xA0, 0x80, 0x13, 0x12, 0x12, 0x14, 0x0C, // 349
    0xE0, 0x90, 0x10, 0x10, 0x10, 0x10, 0x11, 0x91, 0x53, 0x0E, // 350
    0x00, 0x80, 0x80, 0x80, 0x80, 0x13, 0x12, 0x92, 0x54, 0x0C, // 351
    0xE0, 0x92, 0x14, 0x12, 0x10, 0x10, 0x11, 0x11, 0x13, 0x0E, // 352
    0x00, 0x90, 0xA0, 0x90, 0x80, 0x13, 0x12, 0x12, 0x14, 0x0C, // 353
    0x10, 0x10, 0xF0, 0x10, 0x10, 0x10, 0x00, 0x00, 0x9F, 0x40, 0x00, 0x00, // 354
    0x80, 0x80, 0xE0, 0x80, 0x80, 0x00, 0x00, 0x9F, 0x50, 0x10, // 355
    0x10, 0x10, 0xF2, 0x14, 0x12, 0x10, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, // 356
    0x80, 0x80, 0xE0, 0x80, 0xB0, 0x00, 0x00, 0x1F, 0x10, 0x10, // 357
    0x10, 0x10, 0xF0, 0x10, 0x10, 0x10, 0x00, 0x01, 0x1F, 0x01, 0x01, 0x00, // 358
    0x80, 0x80, 0xE0, 0x80, 0x80, 0x00, 0x02, 0x1F, 0x12, 0x10, // 359
    0xF0, 0x06, 0x02, 0x04, 0xF6, 0x0F, 0x18, 0x10, 0x18, 0x0F, // 360
    0x80, 0x30, 0x10, 0x20, 0xB0, 0x0F, 0x10, 0x10, 0x10, 0x1F, // 361
    0xF0, 0x04, 0x04, 0x04, 0xF4, 0x0F, 0x18, 0x10, 0x18, 0x0F, // 362
    0x80, 0x20, 0x20, 0x20, 0xA0, 0x0F, 0x10, 0x10, 0x10, 0x1F, // 363
    0xF0, 0x02, 0x04, 0x04, 0xF2, 0x0F, 0x18, 0x10, 0x18, 0x0F, // 364
    0x80, 0x10, 0x20, 0x20, 0x90, 0x0F, 0x10, 0x10, 0x10, 0x1F, // 365
    0xF0, 0x02, 0x05, 0x02, 0xF0, 0x0F, 0x18, 0x10, 0x18, 0x0F, // 366
    0x80, 0x10, 0x28, 0x10, 0x80, 0x0F, 0x10, 0x10, 0x10, 0x1F, // 367
    0xF0, 0x04, 0x02, 0x04, 0xF2, 0x0F, 0x18, 0x10, 0x18, 0x0F, // 368
    0x80, 0x20, 0x10, 0x20, 0x90, 0x0F, 0x10, 0x10, 0x10, 0x1F, // 369
    0xF0, 0x00, 0x00, 0x00, 0xF0, 0x0F, 0x18, 0x50, 0x98, 0x0F, // 370
    0x80, 0x00, 0x00, 0x00, 0x80, 0x0F, 0x10, 0x10, 0x50, 0x9F, // 371
    0xF0, 0x00, 0x04, 0x82, 0x04, 0x00, 0xF0, 0x01, 0x1E, 0x06, 0x01, 0x06, 0x1E, 0x01, // 372
    0x80, 0x00, 0x20, 0x90, 0x20, 0x00, 0x80, 0x07, 0x18, 0x07, 0x00, 0x0F, 0x18, 0x07, // 373
    0x10, 0x60, 0x84, 0x02, 0x84, 0x60, 0x10, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, // 374
    0x80, 0x20, 0x10, 0x20, 0x80, 0x81, 0x86, 0x78, 0x0E, 0x01, // 375
    0x10, 0x60, 0x84, 0x00, 0x84, 0x60, 0x10, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, // 376
    0x10, 0x10, 0x94, 0xD2, 0x30, 0x18, 0x1E, 0x13, 0x10, 0x10, // 377
    0x80, 0x80, 0xA0, 0x90, 0x80, 0x10, 0x18, 0x14, 0x13, 0x10, // 378
    0x10, 0x10, 0x94, 0xD0, 0x30, 0x18, 0x1E, 0x13, 0x10, 0x10, // 379
    0x80, 0x80, 0xA0, 0x80, 0x80, 0x10, 0x18, 0x14, 0x13, 0x10, // 380
    0x10, 0x12, 0x94, 0xD2, 0x30, 0x18, 0x1E, 0x13, 0x10, 0x10, // 381
    0x80, 0x90, 0xA0, 0x90, 0x80, 0x10, 0x18, 0x14, 0x13, 0x10 // 382
    
};