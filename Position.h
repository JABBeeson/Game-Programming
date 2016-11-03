class Position
{
public:
	Position();
	Position(double, double);
	void setXY(double, double);
	void moveXY(double, double);
	double getX();
	double getY();
private:
	double x;
	double y;
};

