#pragma once

class Position
{
public:
	Position();
	Position(double x, double y);
	double x;
	double y;


	void setXY(double, double);
	void moveXY(double, double);
};

