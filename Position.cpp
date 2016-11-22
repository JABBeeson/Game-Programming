#include "Position.h"

Position::Position()
{
	x = 0;
	y = 0;
}
Position::Position(double _x, double _y) // used to set up the functions  - the constructor
{
	x = _x;
	y = _y;
}

void Position::setXY(double _x, double _y)
{
	x = _x;
	y = _y;
}

void Position::moveXY(double _x, double _y)		//adds the movment 
{
	x += _x;
	y += _y;

}


double Position::getX()
{
	return x;
}


double Position::getY()
{
	return y;
}
