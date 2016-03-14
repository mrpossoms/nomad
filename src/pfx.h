// This acts a easy means to include nearly
// universal libraries into a file
#pragma once

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <dirent.h>
#include <math.h>
#include <fcntl.h>
#include <assert.h>
#include <errno.h>

#include "linmath.h"

#define UUID_LEN 16

extern int RAND_FD;

//    _   _          __      _   __  __
//   | | | |___ ___ / _|_  _| | |  \/  |__ _ __ _ _ ___ ___
//   | |_| (_-</ -_)  _| || | | | |\/| / _` / _| '_/ _ (_-<
//    \___//__/\___|_|  \_,_|_| |_|  |_\__,_\__|_| \___/__/
//
#define BIT_SET(field, flag) ((field) & (flag))

#define NEW_UUID(arr) { read(RAND_FD, (arr), UUID_LEN); }
