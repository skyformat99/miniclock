#ifndef FONT_H
#define FONT_H

#include "base.h"

#define ERR_GLYPH_NOT_FOUND 1

// font defines
// format: 8bytes = encoding(1byte) + bitmap (7bytes)
typedef uint8_t font_t;

// a single char encoding
typedef struct _glyph_{
  char ch;    //encoding char
  uint8_t w;  // width
  uint8_t h;  // height
  byte_t bitmap[7]; //7x8bit
} glyph_t;

// font type
enum _font_type {
        FT_LED,
        FT_ARIA
};


///////////////////////////////////////////////////////////////////////////////
// public functions
///////////////////////////////////////////////////////////////////////////////
uint8_t font_get_glyph(const font_t* font, char encoding, glyph_t* glyph);
font_t* font_get_font(uint8_t font_type);



#endif
