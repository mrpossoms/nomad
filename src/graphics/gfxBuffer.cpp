#include "gfxBuffer.h"

using namespace gfx;

Buffer_t CUR_BUF;

Buffer_t BufferAlloc(int width, int height)
{
	Buffer_t buf = {};
	buf.width = width, buf.height = height;

	buf.data = (glyph_t**)malloc(sizeof(glyph_t*) * width);

	if(!buf.data) return buf;

	for(int i = width; i--;){
		buf.data[i] = (glyph_t*)malloc(sizeof(glyph_t) * height);
		if(!buf.data[i]) return buf;
	}

	return buf;
}
//-------------------------------------------------------------------------
void BufferFree(Buffer_t* buf)
{
	if(!buf) return;

	for(int i = width; i--;){
		free(buf.data[i]);
	}

	free(buf.data);
}
