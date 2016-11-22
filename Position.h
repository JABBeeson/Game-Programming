#pragma once

class Position
{
public:
	Position();
	Position(double, double);
	double x;
	double y;


	void setXY(double, double);
	void moveXY(double, double);
	double getX();
	double getY();
private:
};

