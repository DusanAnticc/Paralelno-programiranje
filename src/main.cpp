#include<iostream>
#include"LoadMatrix.h"
#include"Serijski.h"
#include"CheckResults.h"
#include"ParallelFor.h"
#include"RedPoRed.h"
#include"Zadatak.h"
#include"NZadataka.h"

using namespace std;

int checkMatrix(Matrix mat1, Matrix mat2);

Matrix *matrica1;
Matrix *matrica2;

int main(int argc, char* argv[])
{
	string inFileName;
	string outFileName;

	/*if (argc != 3)
	{
		cout << "Error. Wrong number of arguments passed." << endl;
		cout << "Execute program like: \"serial.exe <input_file_name> <output_file_name>\"." << endl;
		return -1;
	}
	inFileName = argv[1];
	outFileName = argv[2];*/

	string str1 = "matrica600.txt";
	string str2 = "matrica601.txt";

	Matrix mat1(str1);
	Matrix mat2(str2);
	matrica1 = &mat1;
	matrica2 = &mat2;

	if (checkMatrix(mat1, mat2))
		return 1;

	cout << "Mnozenje matrica velicina: A[" << mat1.x << "][" << mat1.y << "] * B[" << mat2.x << "][" << mat2.y << "]" << endl;

	//Serijski ser(mat1.x, mat2.y);
	//ser.Run(mat1, mat2,1);
	//
	//CheckResults checkResults1("VrijemeSerijski.txt");
	//cout<<"Serijski:"<<checkResults1.Run()<<endl;

	//ParallelFun(&mat1, &mat2, 1);
	//CheckResults checkResults2("VrijemeParallelFor.txt");
	//cout<<"Parallel_for:"<<checkResults2.Run()<<endl;

	//EmptyTask(*matrica1,*matrica2,1);
	//CheckResults checkResults3("VrijemeRedPoRed.txt");
	//cout<<"RedPoRed:"<<checkResults3.Run()<<endl;	

	//EmptyTaskZadatak(*matrica1, *matrica2, 1);
	//CheckResults checkResults4("VrijemeZadatak.txt");
	//cout<<"Zadaci:"<<checkResults4.Run()<<endl;

	EmptyTaskNZadataka(*matrica1, *matrica2,200, 1);
	CheckResults checkResults5("VrijemeNZadataka.txt");
	cout << "NZadataka:" << checkResults5.Run() << endl;

	cout << endl;
	getchar();
	getchar();
}

int checkMatrix(Matrix mat1, Matrix mat2)
{
	if (mat1.y != mat2.x)
	{
		cout << "Wrong matrix formats" << endl;
		return 1;
	}
	return 0;
}
