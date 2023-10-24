#pragma once
#include<iostream>
#include"tbb/task.h"
#include"LoadMatrix.h"
#include <list>

using namespace tbb;
using namespace std;

class DagTask :public task
{
public:
	int n;
	DagTask(int n_) :n(n_)
	{}
	DagTask()
	{}
	task* execute();
};

void EmptyTask(Matrix mat1_, Matrix mat2_,int n);