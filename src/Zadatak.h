#pragma once
#include<iostream>
#include"tbb/task.h"
#include"LoadMatrix.h"
#include <list>

using namespace tbb;
using namespace std;

class Task :public task
{
public:
	int i,j;
	Task(int i_,int j_) :i(i_),j(j_)
	{}
	Task()
	{}
	task* execute();
};

void EmptyTaskZadatak(Matrix mat1_, Matrix mat2_, int n);