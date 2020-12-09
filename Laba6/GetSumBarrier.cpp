#pragma once
#ifndef ONCE_BARRIER
#define ONCE_BARRIER

#include <omp.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "GetSum.h"

using namespace std;

double get_sum_barrier(int n, int **&a, int **&b, int **&c, int threads)
{
	int *sum = new int[n], sum2 = 0, total = 0, i, j,t;
	double start = omp_get_wtime();
	for (int i = 0;i < n;i++)
		sum[i] = 0;
#pragma omp parallel num_threads(2) private(i,j,t)
	{
	/*	t = omp_get_thread_num();
		if(t==0)
			for (i = 0;i < n / 2;i++)
				for (j = 0; j < n; j++)
				{
					c[i][j] = (a[i][j] > b[i][j]) ? a[i][j] : b[i][j];
					sum[i] += c[i][j];
				}
		else
			for (i = n/2; i < n; i++)
				for (j = 0; j < n; j++)
				{
					c[i][j] = (a[i][j] > b[i][j]) ? a[i][j] : b[i][j];
					sum[i] += c[i][j];
				}
				*/
#pragma omp for
		for (i = 0;i < n;i++)
		{
			for (j = 0; j < n; j++)
			{
				c[i][j] = (a[i][j] > b[i][j]) ? a[i][j] : b[i][j];
				sum[i] += c[i][j];
			}
		}
#pragma omp barrier
#pragma omp master //определяет фрагмент кода, который должен быть выполнен только основным потоком; все остальные потоки пропускают данный фрагмент кода
		{
			for (int i = 0; i < n;i++)
				total += sum[i];
		}

//#pragma omp barrier
//#pragma omp single //определяет блок параллельного фрагмента, который должен быть выполнен только одним потоком; все остальные потоки ожидают завершения выполнения данного блока
//	{
//		for (int i = 0; i < n; i++)
//			total += sum[i];
//	}
}
    cout << "total sum = " << total << endl;
	fflush(stdout);
	delete[] sum;
	double end1 = omp_get_wtime();
	cout << "The time sumBarrier master: " << end1 - start << " ms\n";
	/*double end = omp_get_wtime();
	cout << "The time sumBarrier single: " << end - start << " ms\n";*/
}

#endif ONCE_BARRIER