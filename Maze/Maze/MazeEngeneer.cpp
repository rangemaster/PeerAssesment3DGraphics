
#include "stdafx.h"

MazeEngeneer::MazeEngeneer()
{
	Messager::Succes("Engeneer Created");
}

MazeEngeneer::~MazeEngeneer()
{
	Messager::Succes("Engeneer Deleted");
}

void MazeEngeneer::CreateMaze(int dif)
{
	MazeEngeneer::maze[0][0] = MazePuzzelPart(0, 0, 0, 5, 0.1, 5, ROAD_STRAIGHT, ROAD_RIGHT_FACING, 0);

	Messager::Succes("Maze Succesfully created");
}

void MazeEngeneer::ConverMaze(std::vector<Road> *maze_map)
{
	int index = 0;
	for (int x = 0; x < MAZE_HEIGHT; x++)
	{
		for (int y = 0; y < MAZE_WIDTH; y++)
		{
			maze_map->push_back(*new Road(*new Brick(maze[x][y].x, maze[x][y].y, index, 5, 0.1, 5), maze[x][y].state, maze[x][y].dir));
			index += 2.5;
		}
	}

	//maze_map->push_back(*new Road(*new Brick(0, 0, 0, 5, 0.1, 5), ROAD_STRAIGHT, ROAD_RIGHT_FACING));
	//maze_map->push_back(*new Road(*new Brick(0, 0, 0, 5, 0.1, 5), ROAD_CORNER, ROAD_RIGHT_FACING));
	//maze_map->push_back(*new Road(*new Brick(0, 0, 0, 5, 0.1, 5), ROAD_EMPTY_SPOT, ROAD_FRONT_FACING));
	//maze_map->push_back(*new Road(*new Brick(0, 0, 0, 5, 0.1, 5), ROAD_CORNER, ROAD_BACK_FACING));
	//maze_map->push_back(*new Road(*new Brick(0, 0.25, 0, 5, 0.5, 5), ROAD_STRAIGHT, ROAD_RIGHT_FACING));
}

MazePuzzelPart MazeEngeneer::at(int x, int y)
{
	return maze[x][y];
}