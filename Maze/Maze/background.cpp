#include "stdafx.h"
#include "background.h"
#include <GL\freeglut.h>

void drawBackground()
{
	glColor3f(1, 1, 0);
	glBegin(GL_QUADS);
	glVertex2f(-1, -1);
	glVertex2f(1, -1);
	glVertex2f(1, -0.9f);
	glVertex2f(-1, -0.9f);

	glVertex2f(-1, 1);
	glVertex2f(1, 1);
	glVertex2f(1, 0.9f);
	glVertex2f(-1, 0.9f);

	glVertex2f(-1, -1);
	glVertex2f(-0.9f, -1);
	glVertex2f(-0.9f, 1);
	glVertex2f(-1, 1);

	glVertex2f(1, -1);
	glVertex2f(0.9f, -1);
	glVertex2f(0.9f, 1);
	glVertex2f(1, 1);

}