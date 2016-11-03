#pragma once
class Inputs
{
public:
	bool W, A, S, D, P;
	Inputs(); //setup function, constructor
	void Process(); // processes the input

	double horizontal;
	double vertical;
};

