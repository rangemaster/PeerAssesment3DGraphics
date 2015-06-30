#define DIFFICULTY_EASY 1
#define DIFFICULTY_MEDIUM 2
#define DIFFICULTY_HARD 3
#define DIFFICULTY_EXTREEM 4

#include "Messager.h"

class MazeEngeneer
{
public:
	MazeEngeneer();
	~MazeEngeneer();
	void CreateMaze(int);
	void ConverMaze(std::vector<Road> *maze_map);

	struct MazePuzzelPart{
	public:
		int state;
		int dir;
		int special;
	};

};