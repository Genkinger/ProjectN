#include "text.h"

texture_t N_GlyphToTex(u8 glyph[8])
{
    u8 buffer[64] = {};
    for (i32 i = 0; i < 8; i++)
    {
        for (i32 j = 0; j < 8; j++)
        {
            buffer[8 * (8 - (i + 1)) + j] = 255 * ((glyph[i] >> j) & 1);
        }
    }
    return N_LoadTextureFromMemory(buffer, 8, 8, GL_TEXTURE_2D, GL_LUMINANCE, GL_LUMINANCE);
}

texture_t N_PackGlyphs(i32 count, u8 *glyphs)
{
    u8 buffer[64 * count];
    for(i32 k = 0; k < count; k++){
        for (i32 i = 0; i < 8; i++)
        {
            for (i32 j = 0; j < 8; j++)
            {
                i32 idx = count*8*(7-i) + j + 8*k;
                buffer[idx] = 255 * ((glyphs[k*8 + i] >> j) & 1);
            }
        }
    }
    return N_LoadTextureFromMemory(buffer, count * 8, 8, GL_TEXTURE_2D, GL_LUMINANCE, GL_LUMINANCE);
}

void N_GenerateGlyphQuad(r32 x, r32 y, r32 w, r32 h, i32 glyphIndex, i32 glyphCount, r32* outbuffer){
    r32 mult =  1.f/(r32)glyphCount;
    r32 quad[20] = {
        x, y, 0, mult*glyphIndex, 0,
        x, y+h, 0, mult*glyphIndex, 1,
        x+w, y+h, 0, mult*(glyphIndex+1), 1,
        x+w, y, 0, mult*(glyphIndex+1), 0
    };
    memcpy(outbuffer,quad,sizeof(r32)*20);
}

void N_GenerateStringQuads(const char* string,i32 glyphCount, r32* outbuffer){
    i32 x = 0, y = 0;
    for(i32 i = 0; i < strlen(string); i++){
        if(string[i] == '\n'){
            x = 0;
            y++;
            continue;
        }
        N_GenerateGlyphQuad(x,-y,1,1,string[i],glyphCount,outbuffer+i*20);
        x++;
    }
}
