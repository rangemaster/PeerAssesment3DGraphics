
#include "stdafx.h"

MazeEngeneer::MazeEngeneer()
{
	Messager::Succes("Engeneer Created");
}

MazeEngeneer::~MazeEngeneer()
{
	Messager::Succes("Engeneer Deleted");
}

bool MazeEngeneer::CreateMaze(int dif)
{
	try
	{
	float indexX = 0, indexY = 0;
		for (int y = 0; y < MAZE_HEIGHT; y++)
		{
			indexX = 0;
			for (int x = 0; x < MAZE_WIDTH; x++)
			{
				MazeEngeneer::maze[y][x] = MazePuzzelPart(indexY, 0, indexX, TILE_WIDTH, TILE_HEIGHT, TILE_DEPTH, ROAD_TCROSS, ROAD_RIGHT_FACING, 0);
				indexX += maze[0][0].d / 2;
			}
			indexY += maze[0][0].w / 2;
		}
		MazeEngeneer::maze[0][0] = MazePuzzelPart(maze[0][0].x, maze[0][0].y, maze[0][0].z, maze[0][0].w, maze[0][0].h, maze[0][0].d, ROAD_CORNER, ROAD_FRONT_FACING, 0);
		MazeEngeneer::maze[0][1] = MazePuzzelPart(maze[0][1].x, maze[0][1].y, maze[0][1].z, maze[0][1].w, maze[0][1].h, maze[0][1].d, ROAD_TCROSS, ROAD_FRONT_FACING, 0);
		throw exception();
	}
	catch (...)
	{
		Messager::Error("Maze could not be created");
		return false;
	}
	Messager::Succes("Maze Succesfully created");
	return true;
}

bool MazeEngeneer::ConverMaze(std::vector<Road> *maze_map)
{
	try
	{
	float index = 0;
		for (int y = 0; y < MAZE_WIDTH; y++)
		{
			for (int x = 0; x < MAZE_HEIGHT; x++)
			{
				maze_map->push_back(*new Road(*new Brick(maze[y][x].x, maze[y][x].y, maze[y][x].z, maze[y][x].w, maze[y][x].h, maze[y][x].d), maze[y][x].state, maze[y][x].dir));
			}
		}
	}
	catch (exception)
	{
		Messager::Error("Maze could not be converted");
		return false;
	}
	Messager::Succes("Maze Succesfully converted");
	return true;
}

MazePuzzelPart MazeEngeneer::at(int x, int y)
{
	return maze[x][y];
}