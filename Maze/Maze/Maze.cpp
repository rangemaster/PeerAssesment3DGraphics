// Maze.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace std;

int width, height;
float rotation = M_PI / 2;
float cameraAngle = 0;

double posx, posy, posz;


vector<Road> *maze_map;

MazeEngeneer *engeneer;


void PopRoad(Road &road)
{
	glPushMatrix();
	glTranslatef(road.at(0).x, road.at(0).y, road.at(0).z);
	road.drawRoad();
	glTranslatef(-road.at(0).x, -road.at(0).y, -road.at(0).z);
	glPopMatrix();
}
void PopBrick(double x, double y, double z, double w, double h, double d)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	drawCube(x, y, z, w, h, d);
	glTranslatef(-x, -y, -z);
	glPopMatrix();
}
void DrawToDisplay()
{
	int index = 0;
	for (int x = 0; x < MAZE_WIDTH; x++)
	{
		for (int y = 0; y < MAZE_HEIGHT; y++)
		{
			PopRoad(maze_map->at(index++));
		}
	}
	//PopRoad(maze_map->at(0));
	//glTranslatef(0, 0, 5);
	//PopRoad(maze_map->at(1));
	//glTranslatef(0, 0, -10);
	//PopRoad(maze_map->at(2));
	//glTranslatef(5, 0, 10);
	//PopRoad(maze_map->at(3));
	//glTranslatef(0, 0, -5);
	//PopRoad(maze_map->at(4));

	//PopRoad(*road1);
	//glTranslatef(0, 0, 5);
	//PopRoad(*road2);
	//glTranslatef(0, 0, -10);
	//PopRoad(*road3);

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

	glTranslatef(posx, posy, posz);

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
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case '4':
		cameraAngle -= 0.1;
		break;
	case '6':
		cameraAngle += 0.1;
		break;
	case '2':
		posy -= 0.1;
		break;
	case '8':
		posy += 0.1;
		break;
	case 'a':
		posz -= 0.1;
		break;
	case 'd':
		posz += 0.1;
		break;
	case 'w':
		posx -= 0.1;
		break;
	case 's':
		posx += 0.1;
		break;
	}
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
}

void Init(int argc, char* argv[])
{
	cout << "Init" << endl;
	engeneer = new MazeEngeneer();
	maze_map = new vector < Road > ;

	engeneer->CreateMaze(DIFFICULTY_EASY);
	engeneer->ConverMaze(maze_map);

	GlutInit(argc, argv);

}
int _tmain(int argc, char* argv[])
{
	string line;
	cout << "Start Program" << endl;

	Init(argc, argv);

	glutMainLoop();

	cout << "\nHit Enter to exit" << endl;
	getline(cin, line);
	return 0;
}

