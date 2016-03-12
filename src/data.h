#pragma once

#include "pfx.h"
#include <vector>

namespace data {

typedef struct {
	virtual size_t write(int fd) = 0;
} Storable_t; 

}
