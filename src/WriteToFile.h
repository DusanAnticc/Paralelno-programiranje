#pragma once

#include <iostream>
#include <fstream>

using namespace std;

class WriteToFile
{
private:
	string outFileName;  
	ofstream outFile;   
	ofstream outFileTime;
public:
	WriteToFile(string outputFileName, string outputFileNameTime);
	~WriteToFile();
	virtual int Run(int **matrica,int x, int y);
	void Time(double time);
};
