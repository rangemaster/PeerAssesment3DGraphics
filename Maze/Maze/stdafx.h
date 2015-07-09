// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#define _USE_MATH_DEFINES
#define MUTE_MUSIC 1

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <GL\freeglut.h>
#include <functional>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <gl\GL.h>
#include <playsoundapi.h>
#include <ctime>
#include "Messager.h"
#include "ObjModel.h"
#include "AssetManager.h"
#include "stb_image.h"
#include "Texture.h"
#include "cube.h"
#include "triangle.h"
#include "background.h"
#include "Brick.h"
#include "Road.h"
#include "MazeEngeneer.h"


float ToDegrees(float angle);
float mod(float a, float N);

// TODO: reference additional headers your program requires here
