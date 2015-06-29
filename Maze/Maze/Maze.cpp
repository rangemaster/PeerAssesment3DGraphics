// Maze.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

int width, height;
float rotation = M_PI / 2;
float cameraAngle = 0;

void PopMatrix(void (*function)(void))
{
	glPushMatrix();
	function();
	//drawCube();
	glPopMatrix();
}
void DrawToDisplay()
{
	//PopMatrix(drawCube);
	PopMatrix(drawTriangle);
}
void UpdatePlayerPos()
{}
void InitGraphics(){}
void Display()
{
	UpdatePlayerPos();
	glClearColor(0.2, 0.3, 0.1, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, width / (float)height, 0.1f, 15.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(7 * cos(cameraAngle), 2, 7 * sin(cameraAngle), 0, 0, 0, 0, 1, 0);

	glEnable(GL_DEPTH_TEST);

	DrawToDisplay();

	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	drawBackground();

	glEnd();

	glutSwapBuffers();
}
void SetKeyboard(unsigned char key, bool pressed)
{
}
void KeyPressed(unsigned char key, int x, int y){ SetKeyboard(key, true); }
void KeyReleased(unsigned char key, int x, int y){ SetKeyboard(key, false); }
void MouseButton(int button, int state, int x, int y)
{}
void MouseMotion(int x, int y)
{}
void IdleFunc()
{
	rotation = glutGet(GLUT_ELAPSED_TIME) / 50.0f;
	glutPostRedisplay();
}
void Reshape(GLint width, GLint height)
{
	::width = width;
	::height = height;
	glViewport(0, 0, width, height);
}
void GlutInit(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(1024, 768);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Remake Demo");
	InitGraphics();
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	//glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(KeyPressed);
	glutKeyboardUpFunc(KeyReleased);
	glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMotion);
	glutIdleFunc(IdleFunc);
	glutMainLoop();
}

int _tmain(int argc, char* argv[])
{
	string line;
	cout << "Start Program" << endl;

	GlutInit(argc, argv);

	cout << "\nHit Enter to exit" << endl;
	getline(cin, line);
	return 0;
}

