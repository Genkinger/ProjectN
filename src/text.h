#pragma once
#include "types.h"
#include "texture.h"


texture_t N_GlyphToTex(u8 glyph[8]);
texture_t N_PackGlyphs(i32 count, u8 *glyphs);
void N_GenerateGlyphQuad(r32 x, r32 y, r32 w, r32 h, i32 glyphIndex, i32 glyphCount, r32* outbuffer);
void N_GenerateStringQuads(const char* string,i32 glyphCount, r32* outbuffer);