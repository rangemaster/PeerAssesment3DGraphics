// stdafx.cpp : source file that includes just the standard includes
// Maze.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

float ToDegrees(float angle){ return angle * 180 / M_PI; }
float mod(float a, float N){ return a - N*floor(a / N); }

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
