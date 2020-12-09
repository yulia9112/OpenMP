#include <omp.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "GetSum.h"
using namespace std;

const void print_mas(int n,int **&mas)
{
	for (int i = 0;i < n;i++)
	{
		for (int j = 0; j < n; j++)
			cout << mas[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}


void main()
{
	int **A=NULL,**B=NULL,**C=NULL,sum=0,n,threads;
	cout << "Enter n: ";
	cin >> n;
	cout << endl;
	A = new int*[n];
	B = new int*[n];
	C = new int*[n];
	for (int i = 0;i < n;i++)
	{
		A[i] = new int[n];
		B[i] = new int[n];
		C[i] = new int[n];
	}
	
	srand(time(0));
	for (int i = 0;i < n;i++)
		for (int j = 0; j < n; j++)
		{
			A[i][j] = rand() % 10;
			B[i][j] = rand() % 10;
		}


	cout <<"max threads: " << omp_get_max_threads() << endl
		<< "number of processing elements: " << omp_get_num_procs() << endl;
	cout << "Enter quantity threads:" << endl<<"threads = ";
	cin >> threads;
	
	get_sum_reduction(n, A, B, C, threads);
	get_sum_reduction(n, A, B, C, 1);
	get_sum_atomic(n, A, B, C, threads);
	get_sum_semaphores(n, A, B, C, threads);
	get_sum_barrier(n, A, B, C, threads);

	for (int i = 0;i < n;i++)
	{
		delete[] A[i];
		delete[] B[i];
		delete[] C[i];
	}
	delete[] A;
	delete[] B;
	delete[] C;
}