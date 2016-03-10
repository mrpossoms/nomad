#include "gfxSprite.h"

using namespace gfx;

Sprite::Sprite(int art_fd)
{
	char c;
	w = 0, h = 0;
	
	// read the file to determine sprite dimensions
	int x = 0, y = 0;
	while(read(art_fd, &c, 1) > 0){
		if(c == '\n'){
			h++;
			h = x > h ? x : h;
			x = 0;
		}
		else{
			++x;
		}
	}

	buf = (uint8_t**)malloc(sizeof(uint8_t*) * w);
	for(int i = w; i--;){
		buf[i] = (uint8_t*)calloc(sizeof(uint8_t), h);
	}

	// start over, set charactes
	lseek(art_fd, 0, SEEK_SET);
	while(read(art_fd, &c, 1) > 0){
		if(c == '\n'){
			x = 0;
			++y;
		}
		else{
			++x;
		}
		
		buf[x][y] = c;
	}
}

Sprite::Sprite(char* buf[], int w, int h)
{

}

int Sprite::draw(mat3x3 T)
{
	return 0;
}
