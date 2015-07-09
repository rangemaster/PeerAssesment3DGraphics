// Maze.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
using namespace std;

int previousMouseX, previousMouseY;
int width, height;
float rotation = M_PI / 2;
float cameraAngle = 0;
double posx, posy, posz;
double trofee_pos_x, trofee_pos_y, trofee_pos_z;
bool p_forward, p_backward, p_left, p_right, p_zoomout, p_zoomin;
bool moveable = 1, trofeeCollected = 0;
clock_t pastTime = -1, countdownTime = -1;

GLfloat lAmbient[] = { 0.7, 0.7, 0.7, 1.0 };
vector<pair<int, ObjModel*>>models;
vector<Road> *maze_map;
MazeEngeneer *engeneer;

void PlayBackgroundMusic(){ if (!MUTE_MUSIC)PlaySound(TEXT("..\\res\\Theme_afgekort.wav"), NULL, SND_ASYNC | SND_LOOP); }
void ErrorUnableToMove(){ Messager::Error("You are not able to move right now!"); }
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
	//DrawTrofee();

	int index = 0;
	double pre_x = -1, pre_y = -1, pre_z = -1;
	Brick brick;
	for (int x = 0; x < MAZE_WIDTH; x++)
	{
		for (int y = 0; y < MAZE_HEIGHT; y++)
		{
			PopRoad(maze_map->at(index++));
		}
	}
	//cout << index << " object(s) drawn - cur pos: " << posx << ", " << posy << ", " << posz << endl;

	glTranslatef(-posx, -posy, -posz);
	drawTriangle();
	glTranslatef(posx, posy, posz);

}

double stepSize = TILE_WIDTH;
void MoveXP(){ if (posx < 0)posx += stepSize; }
void MoveXM(){ if (posx > -TILE_WIDTH * (MAZE_WIDTH - 1))  posx -= stepSize; }
void MoveZP(){ if (posz < 0) posz += stepSize; }
void MoveZM(){ if (posz > -TILE_DEPTH * (MAZE_HEIGHT - 1)) posz -= stepSize; }

bool CloseEnough(double des, double pos)
{
	return true;
}
void UpdatePlayerPos()
{
	//for (pair<int, ObjModel*> model : models)
	//{
	if (posx == -trofee_pos_x  && posz == -trofee_pos_z && !trofeeCollected)
	{
		Messager::Succes("You reached the trofee");
		trofeeCollected = true;
		models.clear();
		posy = 0;
	}
	//}

	if (p_zoomout)
		posy -= 0.05;
	else if (p_zoomin)
		posy += 0.05;

	float angle = ToDegrees(cameraAngle);
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
		p_left = false;
		p_right = false;
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
		p_forward = false;
		p_backward = false;
	}
	//cout << "pos: " << posx << ", " << posy << ", " << posz << "angle: " << 7 * cos(cameraAngle) << "," << 4 << ", " << 7 * sin(cameraAngle) << endl;
}
bool InitGraphics(){
	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	try{
		models.push_back(pair<int, ObjModel*>(1, new ObjModel("models/bloemetje/PrimRoseP.obj")));
	}
	catch (...){
		Messager::Error("Could not load model trofee");
		return false;
	}
	Messager::Succes("Trofee succesfull loaded");
	return true;
}
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
	if (moveable)
		gluLookAt(7 * cos(cameraAngle), 5, 7 * sin(cameraAngle), 0, 0, 0, 0, 1, 0);

	glLightfv(GL_LIGHT0, GL_AMBIENT, lAmbient);
	glEnable(GL_DEPTH_TEST);

	glTranslatef(posx, posy, posz);

	DrawToDisplay();

	//glTranslatef(-posx, -posy, -posz);

	if (!trofeeCollected){
		glTranslatef(trofee_pos_x, trofee_pos_y, trofee_pos_z);
		glRotatef(rotation, 0, 1, 0);
		models[0].second->draw();
	}

	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -5, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	drawBackground();

	glEnd();

	glutSwapBuffers();
}
void SetKeyboard(unsigned char key, bool pressed)
{
	if (pressed)
		switch (key){
		case 27:
			exit(0);
			break;
		case 'm':
			moveable = !moveable;
			break;
	}
	if (moveable)
	{
		switch (key)
		{
		case '4':
			cameraAngle -= 0.1;
			break;
		case '6':
			cameraAngle += 0.1;
			break;
		case '8':
			p_zoomout = pressed;
			break;
		case '2':
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
	else{ ErrorUnableToMove(); }
}
void KeyPressed(unsigned char key, int x, int y){ SetKeyboard(key, true); }
void KeyReleased(unsigned char key, int x, int y){ SetKeyboard(key, false); }
void MouseButton(int button, int state, int x, int y)
{
	if (moveable)
	{
		if (state == 0)
		{
			previousMouseX = x;
			previousMouseY = y;
		}
	}
	else{ ErrorUnableToMove(); }
}
void MouseMotion(int x, int y)
{
	if (moveable)
	{
		int difX = sqrt(pow(x - previousMouseX, 2));
		if (x > previousMouseX)
		{
			cameraAngle += (double)((double)difX / 20);
		}
		else if (x < previousMouseX)
		{
			cameraAngle -= (double)((double)difX / 20);
		}
		cameraAngle = mod(cameraAngle, M_PI * 2);

		previousMouseX = x;
		previousMouseY = y;
	}
	else{ ErrorUnableToMove(); }
}
void IdleFunc()
{
	if (trofeeCollected)
	{
		clock_t currentTime = clock();
		if (pastTime + 100 < currentTime)
		{
			pastTime = currentTime;
			posy -= 0.5;
			std::stringstream ss;
			ss << (posy == -15 ? "Almost there" : posy == -10 ? "Were out of here" : posy == -5 ? "Let's go!" : "");
			if (ss.str() != "")
				Messager::Message(ss.str());
			if (posy < -20)
				exit(1);
		}
	}
	if (!moveable)
	{
		clock_t currentTime = clock();
		if (pastTime + 1000 < currentTime)
		{
			pastTime = currentTime;
			posx += 0.1;

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(70, width / (float)height, 0.1f, 15.0f);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt(-4.6, 4, -0.7, 0, 0, 0, 0, 1, 0);

			glLightfv(GL_LIGHT0, GL_AMBIENT, lAmbient);
			glEnable(GL_DEPTH_TEST);
		}
	}
	rotation = glutGet(GLUT_ELAPSED_TIME) / 50.0f;
	glutPostRedisplay();
}
void Reshape(GLint width, GLint height)
{
	::width = width;
	::height = height;
	glViewport(0, 0, width, height);
}
bool GlutInit(int argc, char* argv[])
{
	bool succes = true;
	glutInit(&argc, argv);
	glutInitWindowSize(1024, 768);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Remake Demo");
	succes &= InitGraphics();
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	//glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(KeyPressed);
	glutKeyboardUpFunc(KeyReleased);
	glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMotion);
	glutIdleFunc(IdleFunc);
	return succes;
}

void Init(int argc, char* argv[])
{
	cout << "Init" << endl;
	bool succes = true;
	engeneer = new MazeEngeneer();
	maze_map = new vector < Road > ;

	posx = 0;
	posy = -TILE_HEIGHT;
	posz = 0;

	trofee_pos_x = (((double)MAZE_WIDTH - 1)*TILE_WIDTH) / 2;
	trofee_pos_y = TILE_HEIGHT * 5;
	trofee_pos_z = (((double)MAZE_HEIGHT - 1)*TILE_DEPTH) / 2;

	succes &= engeneer->CreateMaze(DIFFICULTY_EASY);
	succes &= engeneer->ConverMaze(maze_map);
	succes &= GlutInit(argc, argv);

	PlayBackgroundMusic();

	succes == true ? Messager::Succes("Init succesfull") : Messager::Error("Init failed");
}
int _tmain(int argc, char* argv[])
{
	string line;
	cout << "Start Program" << endl;

	Init(argc, argv);

	glutMainLoop();

	return 0;
}

