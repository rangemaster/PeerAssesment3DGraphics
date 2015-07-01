// Maze.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace std;

int previousMouseX, previousMouseY;
int width, height;
float rotation = M_PI / 2;
float cameraAngle = 0;
double posx, posy, posz;
bool p_forward, p_backward, p_left, p_right, p_zoomout, p_zoomin;

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
	glTranslatef(-posx, -posy, -posz);
	drawTriangle();
	glTranslatef(posx, posy, posz);
	cout << "CameraAngle: " << ToDegrees(cameraAngle) << endl;
}
void MoveXP(){ posx += 0.1; }
void MoveXM(){ posx -= 0.1; }
void MoveZP(){ posz += 0.1; }
void MoveZM(){ posz -= 0.1; }
void UpdatePlayerPos()
{
	float angle = ToDegrees(cameraAngle);
	if (p_zoomout)
		posy -= 0.1;
	else if (p_zoomin)
		posy += 0.1;

	if (p_left || p_right)
	{
		if (angle < 45 || angle >= 315)
			(p_left ? MoveZM() : MoveZP());
		else if (angle >= 45 && angle < 135)
			(p_left ? MoveXP() : MoveXM());
		else if (angle >= 135 && angle < 225)
			(p_left ? MoveZP() : MoveZM());
		else if (angle >= 225 && angle < 315)
			(p_left ? MoveXM() : MoveXP());
	}
	if (p_forward || p_backward)
	{
		if (angle < 45 || angle >= 315)
			(p_forward ? MoveXP() : MoveXM());
		else if (angle >= 45 && angle < 135)
			(p_forward ? MoveZP() : MoveZM());
		else if (angle >= 135 && angle < 225)
			(p_forward ? MoveXM() : MoveXP());
		else if (angle >= 225 && angle < 315)
			(p_forward ? MoveZM() : MoveZP());
	}
}
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
		p_zoomout = pressed;
		break;
	case '8':
		p_zoomin = pressed;
		break;
	case 'a':
		p_left = pressed;
		break;
	case 'd':
		p_right = pressed;
		break;
	case 'w':
		p_forward = pressed;
		break;
	case 's':
		p_backward = pressed;
		break;
	}
}
void KeyPressed(unsigned char key, int x, int y){ SetKeyboard(key, true); }
void KeyReleased(unsigned char key, int x, int y){ SetKeyboard(key, false); }
void MouseButton(int button, int state, int x, int y)
{
	//cout << "Mouse pressed: " << state << ", " << x << ", " << y << endl;
	if (state == 0)
	{
		previousMouseX = x;
		previousMouseY = y;
	}
}
void MouseMotion(int x, int y)
{
	//cout << "Mouse moved: " << x << ", " << y << endl;
	int difX = sqrt(pow(x - previousMouseX, 2));
	if (x > previousMouseX)
	{
		cout << "Moving right [" << difX << "]" << endl;
		cameraAngle += (double)((double)difX / 20);
	}
	else if (x < previousMouseX)
	{
		cout << "Moving left [" << difX << "]" << endl;
		cameraAngle -= (double)((double)difX / 20);
	}
	cameraAngle = mod(cameraAngle, M_PI * 2);

	previousMouseX = x;
	previousMouseY = y;
}
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

