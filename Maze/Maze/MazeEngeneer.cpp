
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

	Messager::Succes("Maze Succesfully created");
}

void MazeEngeneer::ConverMaze(std::vector<Road> *maze_map)
{
	maze_map->push_back(*new Road(*new Brick(0, 0, 0, 5, 0.1, 5), ROAD_STRAIGHT, ROAD_RIGHT_FACING));
	maze_map->push_back(*new Road(*new Brick(0, 0, 0, 5, 0.1, 5), ROAD_CORNER, ROAD_RIGHT_FACING));
	maze_map->push_back(*new Road(*new Brick(0, 0, 0, 5, 0.1, 5), ROAD_EMPTY_SPOT, ROAD_FRONT_FACING));
	maze_map->push_back(*new Road(*new Brick(0, 0, 0, 5, 0.1, 5), ROAD_CORNER, ROAD_BACK_FACING));
}