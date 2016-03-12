// This acts a easy means to include nearly
// universal libraries into a file
#pragma once

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/param.h>
#include <math.h>
#include <fcntl.h>
#include <assert.h>

#include "linmath.h"

//    _   _          __      _   __  __                    
//   | | | |___ ___ / _|_  _| | |  \/  |__ _ __ _ _ ___ ___
//   | |_| (_-</ -_)  _| || | | | |\/| / _` / _| '_/ _ (_-<
//    \___//__/\___|_|  \_,_|_| |_|  |_\__,_\__|_| \___/__/
//                                                         
#define BIT_SET(field, flag) ((field) & (flag))
