

class MazePuzzelPart{
public:
	MazePuzzelPart();
	MazePuzzelPart(double x1, double y1, double z1, double w1, double h1, double d1, double s2, double d2, double s3);
	~MazePuzzelPart();
	double x, y, z;
	double w, h, d;
	int state;
	int dir;
	int special;
};