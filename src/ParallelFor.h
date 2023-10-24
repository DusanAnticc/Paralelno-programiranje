#pragma once
#include"LoadMatrix.h"
#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"
#include "tbb/tick_count.h"
#include"WriteToFile.h"

using namespace std;
using namespace tbb;

void ParallelFun(Matrix* mat1_, Matrix* mat2_, int n);

struct ParallelFor
{
	int x;
	int y;
	Matrix *mat1;
	Matrix *mat2;
	int **matrica;
public:
	ParallelFor(int x, int y);
	void Run(Matrix mat1, Matrix mat2, int n);
	int Multiply(int row[], int col[], int size);

	void operator()(const blocked_range<int>& range) const {
		for (int i = range.begin(); i < range.end(); ++i)
		{
			for (int j = 0; j < y; ++j)
			{
				matrica[i][j] = 0;
				for (int k = 0; k < y; k++)
					matrica[i][j] += mat1->mat[i][k] * mat2->mat[k][j];
			}
		}
	}
};


