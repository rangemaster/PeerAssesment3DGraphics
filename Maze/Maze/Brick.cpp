#include "stdafx.h"
#include "Brick.h"


Brick::Brick(int xPos, int yPos, int zPos, int widthBrick, int heightBrick, int depthBrick)
{
	x = xPos;
	y = yPos;
	z = zPos;
	width = widthBrick;
	height = heightBrick;
	depth = depthBrick;
}


Brick::~Brick()
{
}

double Brick::size(void)
{
	double value = 0;
	return value;
}
bool Brick::test(void)
{
	if (x != 10)return false;
	if (y != 10)return false;
	if (z != 10)return false;
	if (width != 10)return false;
	if (height != 10)return false;
	if (depth != 10)return false;
	if (size() != 1000)return false;
	return true;
}