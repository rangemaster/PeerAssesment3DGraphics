#pragma once
#include "Messager.h"
class Brick
{
public:
	float x, y, z;
	double width, height, depth;
	Brick();
	Brick(double, double, double, double, double, double);
	~Brick();
	double size(void);

	static void TestBrickClass(void)
	{
		Brick brick(10, 10, 10, 10, 10, 10);
		bool succes = brick.test();
		Messager::Message("Test Brick class");
		if (succes)
			Messager::Succes("Succesfull");
		else 
			Messager::Error("Not Succesfull");
	}
	bool test(void);
	void draw(void);
};

