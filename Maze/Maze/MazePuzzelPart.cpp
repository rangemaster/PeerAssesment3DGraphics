#include "stdafx.h"
//#include "MazePuzzelPart.h"

MazePuzzelPart::MazePuzzelPart()
{
	x = 0;
	y = 0;
	z = 0;
	w = 0;
	h = 0;
	d = 0;
	state = 0;
	dir = 0;
	special = 0;
}
MazePuzzelPart::MazePuzzelPart(double x1, double y1, double z1, double w1, double h1, double d1, double s2, double d2, double s3)
{
	x = x1;
	y = y1;
	z = z1;
	w = w1;
	h = h1;
	d = d1;
	state = s2;
	dir = d2;
	special = s3;
}
MazePuzzelPart::~MazePuzzelPart()
{

}
