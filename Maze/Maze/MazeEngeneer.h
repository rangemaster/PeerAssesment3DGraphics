#define MAZE_WIDTH 10
#define MAZE_HEIGHT 10
#define DIFFICULTY_EASY 1
#define DIFFICULTY_MEDIUM 2
#define DIFFICULTY_HARD 3
#define DIFFICULTY_EXTREEM 4

#define TILE_WIDTH 11
#define TILE_HEIGHT 0.1
#define TILE_DEPTH 11

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