#pragma once
#include "Input.h"

Input::Input()
{
	W = false;
	A = false;
	S = false;
	D = false;
	P = false;

	horizontal = 0;
	vertical = 0;
}
void Input::Process() // processes direction 
{
	if (W) {
		vertical = -1;
		horizontal = 0;
	}
	else if(S){
		vertical = 1;
		horizontal = 0;
	}
	else if (A) {
		horizontal = -1;
		vertical = 0;
	}
	else if(D){horizontal = 1;
		vertical = 0;
	}	
}