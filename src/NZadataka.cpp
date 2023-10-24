#include"NZadataka.h"
#include"WriteToFile.h"
#include "tbb/tick_count.h"

int** m;
Matrix *m1;
Matrix *m2;
int br;

void EmptyTaskNZadataka(Matrix m1_, Matrix m2_,int count, int n)
{
	WriteToFile outputFile("NZadatakaMatrica.txt", "VrijemeNZadataka.txt");

	m1 = &m1_;
	m2 = &m2_;
	int c = (m1->y*m2->x) / count;
	br = c;
	m = new int*[m1->x];
	for (int i = 0; i < m1->x; ++i)
		m[i] = new int[m2->y];

	for (int ii = 0; ii < n; ii++)
	{
		for (int i = 0; i < m1->x; i++)
			for (int j = 0; j < m2->y; j++)
				m[i][j] = 0;

		tbb::empty_task* parent = new(tbb::task::allocate_root()) tbb::empty_task;
		parent->set_ref_count(count + 1);

		int brojacZadatka = 0;
		int brojac = 0;
		int posljednji = 1;
		bool uslovZaPosljednji = false;
		NTask **t = new NTask*[count];
		task_list tl;
		for (int i = 0; i < m1->x; i++)
		{
			for (int j = 0; j < m2->y; j++)
			{
				
				if (brojac == c && !uslovZaPosljednji)
				{
					brojac = 0;
					posljednji++;
				}
				if (posljednji == count)
					uslovZaPosljednji = true;
				if (brojac == 0)
				{
					t[brojacZadatka] = new(parent->allocate_child()) NTask(i, j,uslovZaPosljednji, c);
					tl.push_back(*t[brojacZadatka++]);
				}
				brojac++;
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
	outputFile.Run(m, m1->x, m2->y);
}

task * NTask::execute()
{ 
	int brojac = 0;
	bool uslov = true;
	int k = 0;
	
	for (int p = i; p < m1->x; ++p)
	{ 		
		k = (uslov) ? j : 0;
		uslov = false;
		m[p][k] = 0;
		for (; k < m2->x; k++)
		{
			for (int h=0; h < m2->y; h++)
			{
				m[p][k] += m1->mat[p][h] * m2->mat[h][k];	
				
			}
			brojac++;
			if (brojac == br && uslovZaPosljednji == false)
			{
				return NULL;
			}
		}		
	}
		
	return NULL;
}
