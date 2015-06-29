#include "stdafx.h"
#include "cube.h"
#include <GL/freeglut.h>


void drawCube()
{
	glBegin(GL_QUADS);

	glColor3f(1, 0, 0);	glVertex3f(-1, -1, -1);
	glColor3f(1, 1, 0);	glVertex3f(-1, 1, -1);
	glColor3f(1, 1, 0);	glVertex3f(-1, 1, 1);
	glColor3f(1, 0, 0);	glVertex3f(-1, -1, 1);

	glColor3f(1, 0, 0);	glVertex3f(1, -1, -1);
	glColor3f(1, 1, 0);	glVertex3f(1, 1, -1);
	glColor3f(1, 1, 0);	glVertex3f(1, 1, 1);
	glColor3f(1, 0, 0);	glVertex3f(1, -1, 1);

	glColor3f(1, 0, 0);	glVertex3f(-1, -1, -1);
	glColor3f(1, 0, 0);	glVertex3f(1, -1, -1);
	glColor3f(1, 0, 0);	glVertex3f(1, -1, 1);
	glColor3f(1, 0, 0);	glVertex3f(-1, -1, 1);

	glColor3f(1, 1, 0);	glVertex3f(-1, 1, -1);
	glColor3f(1, 1, 0);	glVertex3f(1, 1, -1);
	glColor3f(1, 1, 0);	glVertex3f(1, 1, 1);
	glColor3f(1, 1, 0);	glVertex3f(-1, 1, 1);

	glColor3f(1, 0, 0);	glVertex3f(-1, -1, -1);
	glColor3f(1, 0, 0);	glVertex3f(1, -1, -1);
	glColor3f(1, 1, 0);	glVertex3f(1, 1, -1);
	glColor3f(1, 1, 0);	glVertex3f(-1, 1, -1);

	glColor3f(1, 0, 0);	glVertex3f(-1, -1, 1);
	glColor3f(1, 0, 0);	glVertex3f(1, -1, 1);
	glColor3f(1, 1, 0);	glVertex3f(1, 1, 1);
	glColor3f(1, 1, 0);	glVertex3f(-1, 1, 1);
	glEnd();
}


void drawCube(double x, double y, double z, double width, double height, double depth)
{
	double wwidth = (width / 2), hheight = (height / 2), ddepth = (depth / 2);
	glBegin(GL_QUADS);

	glColor3f(1, 0, 0);	glVertex3f(x - wwidth, y - hheight, z - ddepth);
	glColor3f(1, 1, 0);	glVertex3f(x - wwidth, y + hheight, z - ddepth);
	glColor3f(1, 1, 0);	glVertex3f(x - wwidth, y + hheight, z + ddepth);
	glColor3f(1, 0, 0);	glVertex3f(x - wwidth, y - hheight, z + ddepth);

	glColor3f(1, 0, 0);	glVertex3f(x + wwidth, y - hheight, z - ddepth);
	glColor3f(1, 1, 0);	glVertex3f(x + wwidth, y + hheight, z - ddepth);
	glColor3f(1, 1, 0);	glVertex3f(x + wwidth, y + hheight, z + ddepth);
	glColor3f(1, 0, 0);	glVertex3f(x + wwidth, y - hheight, z + ddepth);

	glColor3f(1, 0, 0);	glVertex3f(x - wwidth, y - hheight, z - ddepth);
	glColor3f(1, 0, 0);	glVertex3f(x + wwidth, y - hheight, z - ddepth);
	glColor3f(1, 0, 0);	glVertex3f(x + wwidth, y - hheight, z + ddepth);
	glColor3f(1, 0, 0);	glVertex3f(x - wwidth, y - hheight, z + ddepth);

	glColor3f(1, 1, 0);	glVertex3f(x - wwidth, y + hheight, z - ddepth);
	glColor3f(1, 1, 0);	glVertex3f(x + wwidth, y + hheight, z - ddepth);
	glColor3f(1, 1, 0);	glVertex3f(x + wwidth, y + hheight, z + ddepth);
	glColor3f(1, 1, 0);	glVertex3f(x - wwidth, y + hheight, z + ddepth);

	glColor3f(1, 0, 0);	glVertex3f(x - wwidth, y - hheight, z - ddepth);
	glColor3f(1, 0, 0);	glVertex3f(x + wwidth, y - hheight, z - ddepth);
	glColor3f(1, 1, 0);	glVertex3f(x + wwidth, y + hheight, z - ddepth);
	glColor3f(1, 1, 0);	glVertex3f(x - wwidth, y + hheight, z - ddepth);

	glColor3f(1, 0, 0);	glVertex3f(x - wwidth, y - hheight, z + ddepth);
	glColor3f(1, 0, 0);	glVertex3f(x + wwidth, y - hheight, z + ddepth);
	glColor3f(1, 1, 0);	glVertex3f(x + wwidth, y + hheight, z + ddepth);
	glColor3f(1, 1, 0);	glVertex3f(x - wwidth, y + hheight, z + ddepth);
	glEnd();
}