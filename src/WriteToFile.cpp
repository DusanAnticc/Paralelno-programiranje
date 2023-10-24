#include "WriteToFile.h"

WriteToFile::WriteToFile(string outFileName,string outFileNameTime)
{
	this->outFileName = outFileName;
	outFile.open(outFileName);
	outFileTime.open(outFileNameTime);
	if (!outFile.is_open()||!outFileTime.is_open())
	{
		cout << "Output file could not be opened." << endl;
		cout << endl;
	}
}

WriteToFile::~WriteToFile()
{
	outFile.close();
}

int WriteToFile::Run(int **matrica,int x,int y)
{
	outFile << x << " " << y << endl;
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
			outFile << matrica[i][j] << " ";
		outFile << endl;
	}
	return 0;
}

void WriteToFile::Time(double time)
{
	outFileTime << time << endl;
}