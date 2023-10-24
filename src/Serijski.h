#pragma once
#include"LoadMatrix.h"

class Serijski
{
	int x;
	int y;
public:
	Serijski(int x, int y);
	void Run(Matrix mat1, Matrix mat2,int n);
	int Multiply(int row[], int col[], int size);
};