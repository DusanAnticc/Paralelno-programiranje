#pragma once
#include<iostream>
#include<fstream>

using namespace std;

class CheckResults
{
	string FileName;
	fstream File;
public:
	CheckResults(string FileName);
	double Run();
};