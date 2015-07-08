#define ROAD_EMPTY_SPOT 0
#define ROAD_DEADEND 1
#define ROAD_STRAIGHT 2
#define ROAD_CORNER 3
#define ROAD_TCROSS 4
#define ROAD_CROSS 5

#define ROAD_BACK_FACING 1
#define ROAD_FRONT_FACING 2
#define ROAD_RIGHT_FACING 3
#define ROAD_LEFT_FACING 4

#include "Brick.h"

class Road{
public:
	Road(Brick&, int state, int dir);
	~Road();
	void drawRoad(void);
	Brick at(int index);
private:
	std::vector<Brick> *list;

	void Init(void);
	void makeEmptySpot(int);
	void makeDeadEndRoad(int dir);
	void makeStraightRoad(int dir);
	void makeCornerRoad(int dir);
	void makeTCrossRoad(int dir);
	void makeCrossRoad(int dir);
};
