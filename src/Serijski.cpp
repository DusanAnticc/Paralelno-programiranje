#include"Serijski.h"
#include "tbb/tick_count.h"
#include"WriteToFile.h"

using namespace tbb;

Serijski::Serijski(int xx, int yy):x(xx),y(yy)
{}

int Serijski::Multiply(int row[], int col[], int size)
{
	int suma = 0;
	for (int i = 0; i < size; i++)
	{
		suma += row[i] * col[i];
	}
	return suma;
}

void Serijski::Run(Matrix mat1, Matrix mat2,int n)
{
	WriteToFile outputFile("SerijskiMatrica.txt","VrijemeSerijski.txt");
	int **matrica;
	matrica = new int*[x];
	for (int i = 0; i < x; ++i)
		matrica[i] = new int[y];
	for (int i = 0; i < n; i++)
	{
		tick_count startTime = tick_count::now();
		// run program
		for (int i = 0; i < x; ++i){
			for (int j = 0; j < y; ++j)
			{
				//matrica[i][j] = Multiply(mat1.getRow(i), mat2.getCol(j), y);
				matrica[i][j] = 0;
				for (int k = 0; k < y; k++)
					matrica[i][j] += mat1.mat[i][k] * mat2.mat[k][j];
			}}
		tick_count endTime = tick_count::now();
		double timeInMS = (endTime - startTime).seconds() * 1000;
		//cout <<  "Execution time: " << timeInMS << "ms." << endl;
		outputFile.Time(timeInMS);
	}
	outputFile.Run(matrica, mat1.x, mat2.y);
}