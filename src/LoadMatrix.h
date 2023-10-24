#pragma once
#include <iostream>
#include "fstream"      
#include <vector>

using namespace std;

class Matrix
{
public:
	int x, y;
	std::vector< std::vector<int> > mat;

	Matrix(string MatrixFileName);
	~Matrix();

	int* getRow(int x);
	int* getCol(int y);

};