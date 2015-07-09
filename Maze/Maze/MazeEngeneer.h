#define MAZE_WIDTH 15
#define MAZE_HEIGHT 15
#define DIFFICULTY_EASY 1
#define DIFFICULTY_MEDIUM 2
#define DIFFICULTY_HARD 3
#define DIFFICULTY_EXTREEM 4

#define TILE_WIDTH 5
#define TILE_HEIGHT 0.1
#define TILE_DEPTH 5
#define TILE_WALL_HEIGHT 1
#define TILE_WALL_DEPTH 0.1

#include "Messager.h"
#include "MazePuzzelPart.h"
#include <string>

class MazeEngeneer
{
public:
	MazeEngeneer();
	~MazeEngeneer();
	bool CreateMaze(int);
	bool ConverMaze(std::vector<Road> *maze_map);
	MazePuzzelPart at(int, int);
private:
	MazePuzzelPart maze[MAZE_WIDTH][MAZE_HEIGHT];
};