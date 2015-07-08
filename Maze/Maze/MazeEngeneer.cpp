
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
				int state = ROAD_EMPTY_SPOT;
				int dir = ROAD_RIGHT_FACING;
				if (x == 0 || y == 0 || x == MAZE_WIDTH - 1 || y == MAZE_HEIGHT - 1)
				{
					if (x == 0 && y == 0 || x == 0 && y == MAZE_HEIGHT - 1 || y == 0 && x == MAZE_WIDTH - 1 || x == MAZE_WIDTH - 1 && y == MAZE_HEIGHT - 1)
					{
						state = ROAD_CORNER;
						dir = (x == 0 && y == 0 ? ROAD_FRONT_FACING : x == 0 && y == MAZE_HEIGHT - 1 ? ROAD_LEFT_FACING : y == 0 && x == MAZE_WIDTH - 1 ? ROAD_RIGHT_FACING : ROAD_BACK_FACING);
					}
					else
					{
						state = ROAD_TCROSS;
						dir = (x == 0 ? ROAD_LEFT_FACING : y == 0 ? ROAD_FRONT_FACING : x == MAZE_WIDTH - 1 ? ROAD_RIGHT_FACING : ROAD_BACK_FACING);
					}
				}
				MazeEngeneer::maze[y][x] = MazePuzzelPart(indexY, 0, indexX, TILE_WIDTH, TILE_HEIGHT, TILE_DEPTH, state, dir, 0);
				indexX += maze[0][0].d / 2;
			}
			indexY += maze[0][0].w / 2;
		}
		for (int y = MAZE_HEIGHT / 2-1; y < MAZE_HEIGHT / 2 + 2; y++)
		{
			for (int x = MAZE_WIDTH / 2-1; x < MAZE_WIDTH / 2 + 2; x++)
			{
				MazeEngeneer::maze[y][x] = MazePuzzelPart(maze[y][x].x, maze[y][x].y, maze[y][x].z, maze[y][x].w, maze[y][x].h, maze[y][x].d, ROAD_CROSS, maze[y][x].dir, maze[y][x].special);
			}
		}
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