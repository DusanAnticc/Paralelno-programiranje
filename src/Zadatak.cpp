#include"Zadatak.h"
#include"WriteToFile.h"
#include "tbb/tick_count.h"

int** mat;
Matrix *matA;
Matrix *matB;

void EmptyTaskZadatak(Matrix matA_, Matrix matB_, int n)
{
	WriteToFile outputFile("ZadatakMatrica.txt", "VrijemeZadatak.txt");

	matA = &matA_;
	matB = &matB_;
	mat = new int*[matA->x];
	for (int i = 0; i < matA->x; ++i)
		mat[i] = new int[matB->y];

	for (int ii = 0; ii < n; ii++)
	{
	/*	for (int i = 0; i < matA->x; i++)
			for (int j = 0; j < matB->y; j++)
				mat[i][j] = 0;*/

		tbb::empty_task* parent = new(tbb::task::allocate_root()) tbb::empty_task;
		parent->set_ref_count(matA->x*matB->y + 1);

		int brojac = 0;
		Task **t = new Task*[matA->x*matB->y];
		task_list tl;
		for (int i = 0; i < matA->x; i++)
		{
			for (int j = 0; j < matB->y; j++)
			{
				t[brojac] = new(parent->allocate_child()) Task(i,j);
				tl.push_back(*t[brojac++]);
			}			
		}

		tick_count startTime = tick_count::now();
		parent->spawn_and_wait_for_all(tl);
		tick_count endTime = tick_count::now();
		double timeInMS = (endTime - startTime).seconds() * 1000;

		//cout << "Execution time: " << timeInMS << "ms." << endl;
		outputFile.Time(timeInMS);

		parent->destroy(*parent);
	}
	outputFile.Run(mat, matA->x, matB->y);
}

task * Task::execute()
{
	mat[i][j] = 0;
	for (int k = 0; k < matB->y; k++)
	{
			mat[i][j] += matA->mat[i][k] * matB->mat[k][j];
	}
	return NULL;
}
