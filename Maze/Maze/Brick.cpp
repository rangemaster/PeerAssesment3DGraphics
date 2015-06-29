#include "stdafx.h"
#include "Brick.h"
#include "cube.h"


Brick::Brick(double xPos, double yPos, double zPos, double widthBrick, double heightBrick, double depthBrick)
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
	return width * height * depth;
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
void Brick::draw(void)
{
	drawCube(x, y, z, width, height, depth);
}