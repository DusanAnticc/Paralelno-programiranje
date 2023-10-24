#include"CheckResults.h"

CheckResults::CheckResults(string fn)
{
	FileName = fn;
	File.open(FileName);
	if (!File.is_open())
	{
		cout << "File with results could not be opened." << endl;
		cout << endl;
	}

}

double CheckResults::Run()
{
	double time,suma=0,counter=0;
	while (File >> time)
	{
		suma += time;
		counter++;
	}
	suma = suma / counter;
	return suma;
}