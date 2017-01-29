#include "Position.h"
#include <iostream>

Position::Position(){
	x = 0;
	y = 0;
}
Position::Position(double _x, double _y){
	x = _x;
	y = _y;
}
void Position::setXY(double _x, double _y){
	x = _x;
	y = _y;
}
void Position::moveXY(double _x, double _y){
	x += _x;
	y += _y;
}