#include "pfx.h"
#include "gfxDrawable.h"

namespace gfx {

class Sprite : Drawable{
	public:
		Sprite(int art_fd);
		Sprite(char* buf[], int w, int h);
		~Sprite();

		int draw(mat3x3 T);
		int erase(mat3x3 T);
	private:
		uint8_t** buf; // image made of chars
		uint8_t w, h;  // dimensions
};

}
