#include "text.h"

#define GLYPH_WIDTH 8
#define GLYPH_HEIGHT 8

texture_t N_GlyphToTex(u8 glyph[GLYPH_HEIGHT])
{
    u8 buffer[GLYPH_WIDTH * GLYPH_HEIGHT] = {};
    for (i32 i = 0; i < GLYPH_HEIGHT; i++)
    {
        for (i32 j = 0; j < GLYPH_WIDTH; j++)
        {
            buffer[GLYPH_WIDTH * (GLYPH_HEIGHT - (i + 1)) + j] = 255 * ((glyph[i] >> j) & 1);
        }
    }
    return N_LoadTextureFromMemory(buffer, GLYPH_WIDTH, GLYPH_HEIGHT, GL_TEXTURE_2D, GL_LUMINANCE, GL_LUMINANCE);
}

texture_t N_PackGlyphs(i32 count, u8 *glyphs)
{
    u8 buffer[GLYPH_WIDTH * GLYPH_HEIGHT * count];
    for (i32 k = 0; k < count; k++)
    {
        for (i32 i = 0; i < GLYPH_HEIGHT; i++)
        {
            for (i32 j = 0; j < GLYPH_WIDTH; j++)
            {
                i32 idx = count * GLYPH_WIDTH * (GLYPH_HEIGHT - (i+1)) + j + GLYPH_WIDTH * k;
                buffer[idx] = 255 * ((glyphs[k * GLYPH_WIDTH + i] >> j) & 1);
            }
        }
    }
    return N_LoadTextureFromMemory(buffer, count * GLYPH_WIDTH, GLYPH_HEIGHT, GL_TEXTURE_2D, GL_LUMINANCE, GL_LUMINANCE);
}

void N_GenerateGlyphQuad(r32 x, r32 y, r32 w, r32 h, i32 glyphIndex, i32 glyphCount, nquad_t *outbuffer)
{
    r32 mult = 1.f / (r32)glyphCount;
    nquad_t quad = {
        x, y, 0, mult * glyphIndex, 0,
        x, y + h, 0, mult * glyphIndex, 1,
        x + w, y + h, 0, mult * (glyphIndex + 1), 1,
        x + w, y, 0, mult * (glyphIndex + 1), 0};
    memcpy(outbuffer, &quad, sizeof(nquad_t));
}

void N_GenerateStringQuads(const char *string, i32 glyphCount, nquad_t *outbuffer)
{
    i32 x = 0, y = 0;
    for (i32 i = 0; i < strlen(string); i++)
    {
        if (string[i] == '\n')
        {
            x = 0;
            y++;
            continue;
        }
        N_GenerateGlyphQuad(x, -y, 1, 1, string[i], glyphCount, outbuffer + i);
        x++;
    }
}
