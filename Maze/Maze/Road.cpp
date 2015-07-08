#include "stdafx.h"
#include "Brick.h"
#include <vector>


using namespace std;


void Road::Init()
{
	Road::list = new vector < Brick > ;
}
Road::Road(Brick &b1, int state, int dir)
{
	Init();
	Road::list->push_back(b1);
	switch (state)
	{
	case ROAD_EMPTY_SPOT:
		makeEmptySpot(dir);
		break;
	case ROAD_DEADEND:
		makeDeadEndRoad(dir);
		break;
	case ROAD_STRAIGHT:
		makeStraightRoad(dir);
		break;
	case ROAD_CORNER:
		makeCornerRoad(dir);
		break;
	case ROAD_TCROSS:
		makeTCrossRoad(dir);
		break;
	case ROAD_CROSS:
		makeCrossRoad(dir);
	}
}
Road::~Road()
{
}
void Road::drawRoad()
{
	for (int i = 0; i < list->size(); i++)
	{
		list->at(i).draw();
	}
}

void Road::makeEmptySpot(int dir)
{
	Brick brick = list->at(0);
	list->push_back(*new Brick(brick.x - (brick.width / 2 - ((double)TILE_WALL_DEPTH /2)), brick.y + brick.height / 2 + ((double)TILE_WALL_HEIGHT /2), brick.z, TILE_WALL_DEPTH, TILE_WALL_HEIGHT, brick.depth));
	list->push_back(*new Brick(brick.x + (brick.width / 2 - ((double)TILE_WALL_DEPTH /2)), brick.y + brick.height / 2 + ((double)TILE_WALL_HEIGHT /2), brick.z, TILE_WALL_DEPTH, TILE_WALL_HEIGHT, brick.depth));
	list->push_back(*new Brick(brick.x, brick.y + brick.height / 2 + ((double)TILE_WALL_HEIGHT /2), brick.z - (brick.width / 2 - ((double)TILE_WALL_DEPTH /2)), brick.depth, TILE_WALL_HEIGHT, TILE_WALL_DEPTH));
	list->push_back(*new Brick(brick.x, brick.y + brick.height / 2 + ((double)TILE_WALL_HEIGHT /2), brick.z + (brick.width / 2 - ((double)TILE_WALL_DEPTH /2)), brick.depth, TILE_WALL_HEIGHT, TILE_WALL_DEPTH));
}
void Road::makeDeadEndRoad(int dir)
{
	Brick brick = list->at(0);
	if (dir != ROAD_BACK_FACING)
		list->push_back(*new Brick(brick.x - (brick.width / 2 - ((double)TILE_WALL_DEPTH /2)), brick.y + brick.height / 2 + ((double)TILE_WALL_HEIGHT /2), brick.z, TILE_WALL_DEPTH, TILE_WALL_HEIGHT, brick.depth));
	if (dir != ROAD_FRONT_FACING)
		list->push_back(*new Brick(brick.x + (brick.width / 2 - ((double)TILE_WALL_DEPTH /2)), brick.y + brick.height / 2 + ((double)TILE_WALL_HEIGHT /2), brick.z, TILE_WALL_DEPTH, TILE_WALL_HEIGHT, brick.depth));
	if (dir != ROAD_RIGHT_FACING)
		list->push_back(*new Brick(brick.x, brick.y + brick.height / 2 + ((double)TILE_WALL_HEIGHT /2), brick.z - (brick.width / 2 - ((double)TILE_WALL_DEPTH /2)), brick.depth, TILE_WALL_HEIGHT, TILE_WALL_DEPTH));
	if (dir != ROAD_LEFT_FACING)
		list->push_back(*new Brick(brick.x, brick.y + brick.height / 2 + ((double)TILE_WALL_HEIGHT /2), brick.z + (brick.width / 2 - ((double)TILE_WALL_DEPTH /2)), brick.depth, TILE_WALL_HEIGHT, TILE_WALL_DEPTH));
}
void Road::makeStraightRoad(int dir)
{
	Brick brick = list->at(0);
	if (dir != ROAD_BACK_FACING && dir != ROAD_FRONT_FACING)
	{
		list->push_back(*new Brick(brick.x - (brick.width / 2 - ((double)TILE_WALL_DEPTH /2)), brick.y + brick.height / 2 + ((double)TILE_WALL_HEIGHT /2), brick.z, TILE_WALL_DEPTH, TILE_WALL_HEIGHT, brick.depth));
		list->push_back(*new Brick(brick.x + (brick.width / 2 - ((double)TILE_WALL_DEPTH /2)), brick.y + brick.height / 2 + ((double)TILE_WALL_HEIGHT /2), brick.z, TILE_WALL_DEPTH, TILE_WALL_HEIGHT, brick.depth));
	}
	if (dir != ROAD_RIGHT_FACING && dir != ROAD_LEFT_FACING)
	{
		list->push_back(*new Brick(brick.x, brick.y + brick.height / 2 + ((double)TILE_WALL_HEIGHT /2), brick.z - (brick.width / 2 - ((double)TILE_WALL_DEPTH /2)), brick.depth, TILE_WALL_HEIGHT, TILE_WALL_DEPTH));
		list->push_back(*new Brick(brick.x, brick.y + brick.height / 2 + ((double)TILE_WALL_HEIGHT /2), brick.z + (brick.width / 2 - ((double)TILE_WALL_DEPTH /2)), brick.depth, TILE_WALL_HEIGHT, TILE_WALL_DEPTH));
	}
}
void Road::makeCornerRoad(int dir)
{
	Brick brick = list->at(0);
	switch (dir)
	{
	case ROAD_FRONT_FACING:
		list->push_back(*new Brick(brick.x - (brick.width / 2 - ((double)TILE_WALL_DEPTH /2)), brick.y + brick.height / 2 + ((double)TILE_WALL_HEIGHT /2), brick.z, TILE_WALL_DEPTH, TILE_WALL_HEIGHT, brick.depth)); // Back
		list->push_back(*new Brick(brick.x, brick.y + brick.height / 2 + ((double)TILE_WALL_HEIGHT /2), brick.z - (brick.width / 2 - ((double)TILE_WALL_DEPTH /2)), brick.depth, TILE_WALL_HEIGHT, TILE_WALL_DEPTH)); // Right
		break;
	case ROAD_LEFT_FACING:
		list->push_back(*new Brick(brick.x, brick.y + brick.height / 2 + ((double)TILE_WALL_HEIGHT /2), brick.z - (brick.width / 2 - ((double)TILE_WALL_DEPTH /2)), brick.depth, TILE_WALL_HEIGHT, TILE_WALL_DEPTH)); // Right
		list->push_back(*new Brick(brick.x + (brick.width / 2 - ((double)TILE_WALL_DEPTH /2)), brick.y + brick.height / 2 + ((double)TILE_WALL_HEIGHT /2), brick.z, TILE_WALL_DEPTH, TILE_WALL_HEIGHT, brick.depth)); // Front
		break;
	case ROAD_BACK_FACING:
		list->push_back(*new Brick(brick.x + (brick.width / 2 - ((double)TILE_WALL_DEPTH /2)), brick.y + brick.height / 2 + ((double)TILE_WALL_HEIGHT /2), brick.z, TILE_WALL_DEPTH, TILE_WALL_HEIGHT, brick.depth)); // Front
		list->push_back(*new Brick(brick.x, brick.y + brick.height / 2 + ((double)TILE_WALL_HEIGHT /2), brick.z + (brick.width / 2 - ((double)TILE_WALL_DEPTH /2)), brick.depth, TILE_WALL_HEIGHT, TILE_WALL_DEPTH)); // Left
		break;
	case ROAD_RIGHT_FACING:
		list->push_back(*new Brick(brick.x, brick.y + brick.height / 2 + ((double)TILE_WALL_HEIGHT /2), brick.z + (brick.width / 2 - ((double)TILE_WALL_DEPTH /2)), brick.depth, TILE_WALL_HEIGHT, TILE_WALL_DEPTH)); // Left
		list->push_back(*new Brick(brick.x - (brick.width / 2 - ((double)TILE_WALL_DEPTH /2)), brick.y + brick.height / 2 + ((double)TILE_WALL_HEIGHT /2), brick.z, TILE_WALL_DEPTH, TILE_WALL_HEIGHT, brick.depth)); // Back
		break;
	}
}
void Road::makeTCrossRoad(int dir)
{
	Brick brick = list->at(0);
	if (dir == ROAD_FRONT_FACING)
		list->push_back(*new Brick(brick.x - (brick.width / 2 - ((double)TILE_WALL_DEPTH /2)), brick.y + brick.height / 2 + ((double)TILE_WALL_HEIGHT /2), brick.z, TILE_WALL_DEPTH, TILE_WALL_HEIGHT, brick.depth));
	if (dir == ROAD_BACK_FACING)
		list->push_back(*new Brick(brick.x + (brick.width / 2 - ((double)TILE_WALL_DEPTH /2)), brick.y + brick.height / 2 + ((double)TILE_WALL_HEIGHT /2), brick.z, TILE_WALL_DEPTH, TILE_WALL_HEIGHT, brick.depth));
	if (dir == ROAD_LEFT_FACING)
		list->push_back(*new Brick(brick.x, brick.y + brick.height / 2 + ((double)TILE_WALL_HEIGHT /2), brick.z - (brick.width / 2 - ((double)TILE_WALL_DEPTH /2)), brick.depth, TILE_WALL_HEIGHT, TILE_WALL_DEPTH));
	if (dir == ROAD_RIGHT_FACING)
		list->push_back(*new Brick(brick.x, brick.y + brick.height / 2 + ((double)TILE_WALL_HEIGHT /2), brick.z + (brick.width / 2 - ((double)TILE_WALL_DEPTH /2)), brick.depth, TILE_WALL_HEIGHT, TILE_WALL_DEPTH));
}
void Road::makeCrossRoad(int dir){}

Brick Road::at(int index)
{
	return list->at(index);
}