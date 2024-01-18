#pragma once
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "MapStruct.h"
#include "ArrayFunctions.h"
#include "CheckInput.h"

#define MAX_VERTICAL_SIZE 100
#define MIN_VERTICAL_SIZE 10
#define MAX_HORIZONTAL_SIZE 100
#define MIN_HORIZONTAL_SIZE 10
#define TIMER_GAME 60
