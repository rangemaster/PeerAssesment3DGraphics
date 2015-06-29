#include "stdafx.h"
#include "triangle.h"
#include <GL\freeglut.h>
#include <cmath>

void drawTriangle()
{
	double width = 1, height = 0.5;
	glBegin(GL_TRIANGLES);

	glColor3f(1, 0, 0); glVertex3f(((double)width / 2), -height, ((double)width / 2));
	glColor3f(1, 0, 0); glVertex3f(((double)width / 2), -height, -((double)width / 2));
	glColor3f(1, 1, 0); glVertex3f(0, height, 0);

	glColor3f(1, 0, 0); glVertex3f(-(sqrt(pow((double)width / 2, 2) + pow((double)width / 2, 2))), -height, 0);// 
	glColor3f(1, 0, 0); glVertex3f(((double)width / 2), -height, -((double)width / 2));
	glColor3f(1, 1, 0); glVertex3f(0, height, 0);

	glColor3f(1, 0, 0); glVertex3f(((double)width / 2), -height, ((double)width / 2));
	glColor3f(1, 0, 0); glVertex3f(-(sqrt(pow((double)width / 2, 2) + pow((double)width / 2, 2))), -height, 0);//
	glColor3f(1, 1, 0); glVertex3f(0, height, 0);

	glColor3f(1, 0, 0); glVertex3f(-(sqrt(pow((double)width/2, 2) + pow((double)width/2, 2))), -height, 0);  //
	glColor3f(1, 0, 0); glVertex3f(((double)width / 2), -height, -((double)width / 2));
	glColor3f(1, 0, 0); glVertex3f(((double)width / 2), -height, ((double)width / 2));


	glEnd();
}