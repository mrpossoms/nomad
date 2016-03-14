#include "pfx.h"

int RAND_FD = open("/dev/random", O_RDONLY);
