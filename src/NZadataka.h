#pragma once
#include<iostream>
#include"tbb/task.h"
#include"LoadMatrix.h"
#include <list>

using namespace tbb;
using namespace std;

class NTask :public task
{
public:
	int i, j;
	int brojZadataka;
	bool uslovZaPosljednji;
	NTask(int i_, int j_,bool uslov,int c) :i(i_), j(j_),uslovZaPosljednji(uslov),brojZadataka(c)
	{}
	NTask()
	{}
	task* execute();
};

void EmptyTaskNZadataka(Matrix mat1_, Matrix mat2_,int count, int n);