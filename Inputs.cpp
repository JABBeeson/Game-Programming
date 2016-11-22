#pragma once
#include "Inputs.h"

Inputs::Inputs()
{
	W = false;
	A = false;
	S = false;
	D = false;
	P = false;

	horizontal = 0;
	vertical = 0;
}
void Inputs::Process() // processes direction 
{
	if ((W && S) || (!W && !S)) {
		vertical = 0;
	}
	else {
		if (W) {
			vertical = -1;
		}
		else {
			vertical = 1;
		}
	}

	if ((A && D) || (!A && !D)) {
		horizontal = 0;
	}
	else {
		if (A) {
			horizontal = -1;
		}
		else {
			horizontal = 1;
		}
	}
}