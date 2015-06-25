#pragma once
#include "Messager.h"
class Brick
{
public:
	int x, y, z, width, height, depth;
	Brick(int, int, int, int, int, int);
	~Brick();
	double size(void);

	static void TestBrickClass(void)
	{
		Brick brick(10, 10, 10, 10, 10, 10);
		bool succes = brick.test();
		if (succes)
			Messager::Message("Succesfull");
		else 
			Messager::Error("Not Succesfull");
	}
	bool test(void);
};

