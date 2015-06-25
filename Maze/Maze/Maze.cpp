// Maze.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Brick.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	string line;
	cout << "Start Program" << endl;
	
	Brick::TestBrickClass();

	cout << "\nHit Enter to exit" << endl;
	getline(cin, line);
	return 0;
}

