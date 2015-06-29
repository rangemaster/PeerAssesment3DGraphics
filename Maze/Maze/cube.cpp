#include "stdafx.h"
#include "cube.h"
#include <GL/freeglut.h>


void drawCube()
{
	glBegin(GL_QUADS);

	glColor3f(1, 0, 0);	glVertex3f(-1, -1, -1);
	glColor3f(1, 0, 0);	glVertex3f(-1, 1, -1);
	glColor3f(1, 0, 0);	glVertex3f(-1, 1, 1);
	glColor3f(1, 0, 0);	glVertex3f(-1, -1, 1);

	glColor3f(1, 1, 0);	glVertex3f(1, -1, -1);
	glColor3f(1, 1, 0);	glVertex3f(1, 1, -1);
	glColor3f(1, 1, 0);	glVertex3f(1, 1, 1);
	glColor3f(1, 1, 0);	glVertex3f(1, -1, 1);

	glColor3f(1, 0, 0);	glVertex3f(-1, -1, -1);
	glColor3f(1, 1, 0);	glVertex3f(1, -1, -1);
	glColor3f(1, 1, 0);	glVertex3f(1, -1, 1);
	glColor3f(1, 0, 0);	glVertex3f(-1, -1, 1);

	glColor3f(1, 0, 0);	glVertex3f(-1, 1, -1);
	glColor3f(1, 1, 0);	glVertex3f(1, 1, -1);
	glColor3f(1, 1, 0);	glVertex3f(1, 1, 1);
	glColor3f(1, 0, 0);	glVertex3f(-1, 1, 1);

	glColor3f(1, 0, 0);	glVertex3f(-1, -1, -1);
	glColor3f(1, 1, 0);	glVertex3f(1, -1, -1);
	glColor3f(1, 1, 0);	glVertex3f(1, 1, -1);
	glColor3f(1, 0, 0);	glVertex3f(-1, 1, -1);

	glColor3f(1, 0, 0);	glVertex3f(-1, -1, 1);
	glColor3f(1, 1, 0);	glVertex3f(1, -1, 1);
	glColor3f(1, 1, 0);	glVertex3f(1, 1, 1);
	glColor3f(1, 0, 0);	glVertex3f(-1, 1, 1);
	glEnd();
}