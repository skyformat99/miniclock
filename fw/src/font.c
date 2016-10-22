
#include "font.h"

font_t font_4x7_led[] = {
        ' ', 1, 1, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        '0',  4, 7, 0xF0,0x90,0x90,0x90,0x90,0x90,0xF0,
        '1',  4, 7, 0x10,0x10,0x10,0x10,0x10,0x10,0x10,
        '2',  4, 7, 0xF0,0x10,0x10,0xF0,0x80,0x80,0xF0,
        '3',  4, 7, 0xF0,0x10,0x10,0xF0,0x10,0x10,0xF0,
        '4',  4, 7, 0x90,0x90,0x90,0xF0,0x10,0x10,0x10,
        '5',  4, 7, 0xF0,0x80,0x80,0xF0,0x10,0x10,0xF0,
        '6',  4, 7, 0xF0,0x80,0x80,0xF0,0x90,0x90,0xF0,
        '7',  4, 7, 0xF0,0x10,0x10,0x10,0x10,0x10,0x10,
        '8',  4, 7, 0xF0,0x90,0x90,0xF0,0x90,0x90,0xF0,
        '9',  4, 7, 0xF0,0x90,0x90,0xF0,0x10,0x10,0xF0,
        ':',  1, 7, 0x00,0x00,0x80,0x00,0x80,0x00,0x00,
        '%',  4, 7, 0xC0,0xC0,0x10,0x20,0x40,0xB0,0x30,
        0xE0, 4, 7, 0x80,0x60,0x90,0x80,0x80,0x90,0x60 // ℃
};

uint8_t font_get_glyph(font_t* font, char encoding, glyph_t* glyph){
        glyph_t* pos =(glyph_t *) font;
        glyph_t* end = (glyph_t*) (font + sizeof(font_4x7_led));
        while(pos != end) {
                if(pos->ch == encoding) {
                        memcpy(glyph, pos, sizeof(glyph_t));
                        return 0;
                }
                pos++;
        }
        return ERR_GLYPH_NOT_FOUND;
}