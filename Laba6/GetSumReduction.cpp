#pragma once
#ifndef ONCE_REDUCTION
#define ONCE_REDUCTION

#include <omp.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "GetSum.h"

using namespace std;

double get_sum_reduction(int n, int **&a, int **&b, int **&c, int threads)
{
	int sum, total = 0, i, j;
	double start = omp_get_wtime();
#pragma omp parallel num_threads(threads) shared(total,a,b,c)
#pragma omp for private (i,j,sum) reduction(+:total)
	for (i = 0;i < n;i++)
	{
		sum = 0;
		for (j = 0; j < n; j++)
		{
			c[i][j] = (a[i][j] > b[i][j]) ? a[i][j] : b[i][j];
			sum += c[i][j];
		}
		fflush(stdout);
		total += sum;
	}
	cout << "total sum = " << total << endl;
	fflush(stdout);
	double end = omp_get_wtime();
	cout << "The time sumReduction: " << end - start << " ms\n";
}

#endif ONCE_REDUCTION