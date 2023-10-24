#include"RedPoRed.h"
#include"WriteToFile.h"
#include "tbb/tick_count.h"

int** matrica;
Matrix *mat1;
Matrix *mat2;

void EmptyTask(Matrix mat1_, Matrix mat2_,int n)
{
	WriteToFile outputFile("RedPoRedMatrica.txt", "VrijemeRedPoRed.txt");

	mat1 = &mat1_;
	mat2 = &mat2_;
	matrica = new int*[mat1->x];
	for (int i = 0; i < mat1->x; ++i)
		matrica[i] = new int[mat2->y];

	for (int ii = 0; ii < n; ii++)
	{
		/*for (int i = 0; i < mat1->x; i++)
			for (int j = 0; j < mat2->y; j++)
				matrica[i][j] = 0;*/

		tbb::empty_task* parent = new(tbb::task::allocate_root()) tbb::empty_task;
		parent->set_ref_count(mat1->x + 1);

		DagTask **t = new DagTask*[mat1->x];
		task_list tl;
		for (int i = 0; i < mat1->x; i++)
		{
			t[i] = new(parent->allocate_child()) DagTask(i);
			tl.push_back(*t[i]);
		}

		tick_count startTime = tick_count::now();
		parent->spawn_and_wait_for_all(tl);
		tick_count endTime = tick_count::now();
		double timeInMS = (endTime - startTime).seconds() * 1000;

		//cout << "Execution time: " << timeInMS << "ms." << endl;
		outputFile.Time(timeInMS);

		parent->destroy(*parent);
	}
	outputFile.Run(matrica, mat1->x, mat2->y);
}

task * DagTask::execute()
{
	
	for (int k = 0; k < mat2->y; k++)
	{
		matrica[n][k] = 0;
		for (int p = 0; p < mat1->x; p++)
		{
			matrica[n][k] += mat1->mat[n][p] * mat2->mat[p][k];
		}
	}
	return NULL;
}
