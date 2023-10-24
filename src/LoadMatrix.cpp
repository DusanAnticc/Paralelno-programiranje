#include "LoadMatrix.h"

Matrix::Matrix(string MatrixFileName)
{
	ifstream MatrixFile;
	MatrixFile.open(MatrixFileName, ios::in);
	if (!MatrixFile.is_open()) //check is file has been opened
	{
		cout << "Failed to open input file" << endl;
		exit(EXIT_FAILURE);  //abort program
	}

	int i, j;
	MatrixFile >> x;
	MatrixFile >> y;

	mat.resize(x);
	for (int i = 0; i < x; ++i)
	{
		mat[i].resize(y);
	}

	for (i = 0; i < x; i++) 
	{
		for (j = 0; j < y; j++) {
			MatrixFile >> mat[i][j];
		}
	}
}

Matrix::~Matrix()
{
	for (int i = 0; i < x; i++) //load matrix
	{
		mat[i].clear();
	}
	mat.clear();
}

int* Matrix::getRow(int xx)
{
	int *row;
	row = new int[y];
	for (int i = 0; i < y; i++)
	{
		row[i] = mat[xx][i];
	}
	return row;
}

int* Matrix::getCol(int yy)
{
	int *col;
	col = new int[x];
	for (int i = 0; i < x; i++)
		col[i] = mat[i][yy];
	return col;
}
