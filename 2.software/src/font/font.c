/*******************************************************************************
 * Size: 16 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl.h"
#endif

#ifndef FONT
#define FONT 1
#endif

#if FONT

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0025 "%" */
    0x60, 0x89, 0x8, 0x91, 0x9, 0x20, 0x92, 0x6,
    0x46, 0x4, 0x90, 0x89, 0x8, 0x91, 0x9, 0x20,
    0xa2, 0x4,

    /* U+0030 "0" */
    0x33, 0x28, 0x61, 0x86, 0x18, 0x61, 0x85, 0x23,
    0x0,

    /* U+0031 "1" */
    0x26, 0xa2, 0x22, 0x22, 0x22, 0x20,

    /* U+0032 "2" */
    0x39, 0x38, 0x41, 0x4, 0x21, 0x8, 0x41, 0x1f,
    0xc0,

    /* U+0033 "3" */
    0x72, 0x20, 0x84, 0x38, 0x30, 0x41, 0x4, 0x2f,
    0x0,

    /* U+0034 "4" */
    0x8, 0x10, 0x61, 0x44, 0x89, 0x22, 0x7f, 0x8,
    0x10, 0x20,

    /* U+0035 "5" */
    0x79, 0x4, 0x10, 0x79, 0x30, 0x41, 0x4, 0x2f,
    0x0,

    /* U+0036 "6" */
    0x18, 0x84, 0x10, 0x8a, 0x18, 0x61, 0x85, 0x13,
    0x80,

    /* U+0037 "7" */
    0xfc, 0x10, 0x82, 0x8, 0x41, 0x4, 0x20, 0x82,
    0x0,

    /* U+0038 "8" */
    0x72, 0x28, 0xa2, 0x51, 0xc8, 0xe1, 0x86, 0x17,
    0x80,

    /* U+0039 "9" */
    0x72, 0x28, 0x61, 0x86, 0x16, 0x42, 0x8, 0x46,
    0x0,

    /* U+003A ":" */
    0xc6,

    /* U+5149 "光" */
    0x0, 0x0, 0x10, 0x0, 0x88, 0x44, 0x81, 0x24,
    0x1, 0x40, 0x8, 0xff, 0xb8, 0x9, 0x0, 0x48,
    0x2, 0x40, 0x22, 0x11, 0x10, 0x90, 0x85, 0x3,
    0xe0, 0x0,

    /* U+571F "土" */
    0x0, 0x0, 0x4, 0x0, 0x10, 0x0, 0x40, 0x1,
    0x0, 0x4, 0x0, 0x11, 0xf, 0xf8, 0x1, 0x0,
    0x4, 0x0, 0x10, 0x0, 0x40, 0x1, 0x3d, 0xff,
    0xf0,

    /* U+58E4 "壤" */
    0x0, 0x80, 0x42, 0x1, 0x7f, 0x84, 0x3c, 0x13,
    0x51, 0xfd, 0x81, 0x17, 0x4, 0xf4, 0x13, 0xe0,
    0x83, 0xec, 0x39, 0x0, 0xd8, 0xd, 0xa0, 0x44,
    0x70,

    /* U+5EA6 "度" */
    0x1, 0x0, 0x2, 0x1, 0x3f, 0x87, 0x90, 0x12,
    0x58, 0xbf, 0x82, 0x24, 0x8, 0xe0, 0x21, 0xe0,
    0x99, 0x2, 0x28, 0x10, 0x60, 0x43, 0x42, 0x30,
    0xc3, 0x0, 0x80,

    /* U+5F3A "强" */
    0x0, 0x21, 0xdf, 0x14, 0x88, 0x27, 0xc7, 0x28,
    0x20, 0x42, 0xf, 0xde, 0x94, 0x14, 0xa0, 0x9e,
    0x4, 0x20, 0x41, 0x26, 0xf6, 0x90, 0x0,

    /* U+6E7F "湿" */
    0x48, 0xe1, 0x39, 0x1, 0x28, 0x2e, 0x89, 0x44,
    0x33, 0xc0, 0x8a, 0x4, 0x52, 0x2a, 0xa2, 0x36,
    0x10, 0xa1, 0x85, 0x61, 0xff, 0x0, 0x0,

    /* U+7167 "照" */
    0x0, 0x4, 0xbe, 0x79, 0x24, 0x9a, 0x4a, 0x46,
    0x82, 0x4b, 0xe4, 0xa2, 0x72, 0x60, 0x38, 0x42,
    0x5, 0x22, 0xc9, 0x18, 0x1
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 211, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 18, .adv_w = 120, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 27, .adv_w = 120, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 33, .adv_w = 120, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 42, .adv_w = 120, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 51, .adv_w = 120, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 61, .adv_w = 120, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 70, .adv_w = 120, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 79, .adv_w = 120, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 88, .adv_w = 120, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 97, .adv_w = 120, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 106, .adv_w = 56, .box_w = 1, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 107, .adv_w = 256, .box_w = 13, .box_h = 16, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 133, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 158, .adv_w = 256, .box_w = 14, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 183, .adv_w = 256, .box_w = 14, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 210, .adv_w = 256, .box_w = 13, .box_h = 14, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 233, .adv_w = 256, .box_w = 13, .box_h = 14, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 256, .adv_w = 256, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = -2}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0xb, 0xc, 0xd, 0xe, 0xf, 0x10, 0x11,
    0x12, 0x13, 0x14, 0x15, 0x5124, 0x56fa, 0x58bf, 0x5e81,
    0x5f15, 0x6e5a, 0x7142
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 37, .range_length = 28995, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 19, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t font = {
#else
lv_font_t font = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 16,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if FONT*/

