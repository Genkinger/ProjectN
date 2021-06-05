#pragma once
#include "types.h"
#include "texture.h"
#include "vertex_spec.h"


ntexture_t N_GlyphToTex(u8 glyph[8]);
ntexture_t N_PackGlyphs(i32 count, u8 *glyphs);
void N_GenerateGlyphQuad(r32 x, r32 y, r32 w, r32 h, i32 glyphIndex, i32 glyphCount, nquad_t* outbuffer);
void N_GenerateStringQuads(const char* string,i32 glyphCount, nquad_t* outbuffer);