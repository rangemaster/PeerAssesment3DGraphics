#include "stdafx.h"
#include "Brick.h"
#include <vector>


using namespace std;

 std::vector<Brick> *list;
double wallThickness, wallHeight;

void Road::Init()
{
	wallThickness = 0.1;
	wallHeight = 3;
	list = new vector < Brick > ;
}
Road::Road(Brick &b1, int state, int dir)
{
	Init();
	list->push_back(b1);
	switch (state)
	{
	case 0:
		makeEmptySpot(dir);
		break;
	case 1:
		makeDeadEndRoad(dir);
		break;
	case 2:
		makeStraightRoad(dir);
		break;
	case 3:
		makeTCrossRoad(dir);
		break;
	case 4:
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
	Messager::Message("Making Empty Spot");
	Brick brick = list->at(0);
	list->push_back(*new Brick(brick.x - (brick.width / 2 - wallThickness / 2), brick.y + brick.height / 2 + wallHeight / 2, brick.z, wallThickness, wallHeight, brick.depth));
	list->push_back(*new Brick(brick.x + (brick.width / 2 - wallThickness / 2), brick.y + brick.height / 2 + wallHeight / 2, brick.z, wallThickness, wallHeight, brick.depth));
	list->push_back(*new Brick(brick.x, brick.y + brick.height / 2 + wallHeight / 2, brick.z - (brick.width / 2 - wallThickness / 2), brick.depth, wallHeight, wallThickness));
	list->push_back(*new Brick(brick.x, brick.y + brick.height / 2 + wallHeight / 2, brick.z + (brick.width / 2 - wallThickness / 2), brick.depth, wallHeight, wallThickness));
}
void Road::makeDeadEndRoad(int dir)
{
	Messager::Message("Making DeadEnd Road");
	Brick brick = list->at(0);
	if (dir != ROAD_BACK_FACING)
		list->push_back(*new Brick(brick.x - (brick.width / 2 - wallThickness / 2), brick.y + brick.height / 2 + wallHeight / 2, brick.z, wallThickness, wallHeight, brick.depth));
	if (dir != ROAD_FRONT_FACING)
		list->push_back(*new Brick(brick.x + (brick.width / 2 - wallThickness / 2), brick.y + brick.height / 2 + wallHeight / 2, brick.z, wallThickness, wallHeight, brick.depth));
	if (dir != ROAD_RIGHT_FACING)
		list->push_back(*new Brick(brick.x, brick.y + brick.height / 2 + wallHeight / 2, brick.z - (brick.width / 2 - wallThickness / 2), brick.depth, wallHeight, wallThickness));
	if (dir != ROAD_LEFT_FACING)
		list->push_back(*new Brick(brick.x, brick.y + brick.height / 2 + wallHeight / 2, brick.z + (brick.width / 2 - wallThickness / 2), brick.depth, wallHeight, wallThickness));
}
void Road::makeStraightRoad(int dir)
{
	Messager::Message("Making Straight Road");
	Brick brick = list->at(0);
	if (dir != ROAD_BACK_FACING && dir != ROAD_FRONT_FACING)
	{
		list->push_back(*new Brick(brick.x - (brick.width / 2 - wallThickness / 2), brick.y + brick.height / 2 + wallHeight / 2, brick.z, wallThickness, wallHeight, brick.depth));
		list->push_back(*new Brick(brick.x + (brick.width / 2 - wallThickness / 2), brick.y + brick.height / 2 + wallHeight / 2, brick.z, wallThickness, wallHeight, brick.depth));
	}
	if (dir != ROAD_RIGHT_FACING && dir != ROAD_LEFT_FACING)
	{
		list->push_back(*new Brick(brick.x, brick.y + brick.height / 2 + wallHeight / 2, brick.z - (brick.width / 2 - wallThickness / 2), brick.depth, wallHeight, wallThickness));
		list->push_back(*new Brick(brick.x, brick.y + brick.height / 2 + wallHeight / 2, brick.z + (brick.width / 2 - wallThickness / 2), brick.depth, wallHeight, wallThickness));
	}
}
void Road::makeTCrossRoad(int dir)
{
	Messager::Message("Making T Cross Road");
	Brick brick = list->at(0);
	if (dir == ROAD_FRONT_FACING)
		list->push_back(*new Brick(brick.x - (brick.width / 2 - wallThickness / 2), brick.y + brick.height / 2 + wallHeight / 2, brick.z, wallThickness, wallHeight, brick.depth));
	if (dir == ROAD_BACK_FACING)
		list->push_back(*new Brick(brick.x + (brick.width / 2 - wallThickness / 2), brick.y + brick.height / 2 + wallHeight / 2, brick.z, wallThickness, wallHeight, brick.depth));
	if (dir == ROAD_LEFT_FACING)
		list->push_back(*new Brick(brick.x, brick.y + brick.height / 2 + wallHeight / 2, brick.z - (brick.width / 2 - wallThickness / 2), brick.depth, wallHeight, wallThickness));
	if (dir == ROAD_RIGHT_FACING)
		list->push_back(*new Brick(brick.x, brick.y + brick.height / 2 + wallHeight / 2, brick.z + (brick.width / 2 - wallThickness / 2), brick.depth, wallHeight, wallThickness));
}
void Road::makeCrossRoad(int dir)
{
	Messager::Message("Making Cross Road");
}

Brick Road::at(int index)
{
	return list->at(index);
}