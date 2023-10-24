#include"ParallelFor.h"
#include "tbb/tick_count.h"
#include"WriteToFile.h"
#include "tbb/parallel_for.h"

using namespace tbb;

ParallelFor::ParallelFor(int xx, int yy) :x(xx), y(yy)
{
	matrica = new int*[x];
	for (int i = 0; i < x; ++i)
		matrica[i] = new int[y];
}

int ParallelFor::Multiply(int row[], int col[], int size)
{
	int suma = 0;
	for (int i = 0; i < size; i++)
	{
		suma += row[i] * col[i];
	}
	return suma;
}

void ParallelFor::Run(Matrix mat1, Matrix mat2, int n)
{
	WriteToFile outputFile("ParallelForMatrica.txt", "VrijemeParallelFor.txt");
	int **matrica;
	matrica = new int*[x];
	for (int i = 0; i < x; ++i)
		matrica[i] = new int[y];
	for (int i = 0; i < n; i++)
	{
		tick_count startTime = tick_count::now();
		// run program
		for (int i = 0; i < x; ++i)
		{
			for (int j = 0; j < y; ++j)
			{
				matrica[i][j] = Multiply(mat1.getRow(i), mat2.getCol(j), y);
			}
		}
		tick_count endTime = tick_count::now();
		double timeInMS = (endTime - startTime).seconds() * 1000;

		//cout << "Execution time: " << timeInMS << "ms." << endl;
		outputFile.Time(timeInMS);
	}
	outputFile.Run(matrica, mat1.x, mat2.y);
}

void ParallelFun(Matrix* mat1_, Matrix* mat2_, int n)
{
	ParallelFor par(mat1_->x, mat2_->y);
	par.mat1 = mat1_;
	par.mat2 = mat2_;
	WriteToFile outputFile("ParallelForMatrica.txt", "VrijemeParallelFor.txt");
	for (int i = 0; i < n; i++)
	{
		tick_count startTime = tick_count::now();
		parallel_for(blocked_range<int>(0,mat1_->x), par, auto_partitioner());
		tick_count endTime = tick_count::now();

		double timeInMS = (endTime - startTime).seconds() * 1000;
		//cout <<  "Execution time: " << timeInMS << "ms." << endl;
		outputFile.Time(timeInMS);
	}
	outputFile.Run(par.matrica, par.x, par.y);
}