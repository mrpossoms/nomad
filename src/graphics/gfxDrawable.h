#include "pfx.h"

namespace gfx {

class Drawable {
	public:
		virtual int draw(mat3x3 T);
};

}
