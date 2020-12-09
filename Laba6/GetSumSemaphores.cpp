#pragma once
#ifndef ONCE_SEMAPHORES
#define ONCE_SEMAPHORES

#include <omp.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "GetSum.h"

using namespace std;

double get_sum_semaphores(int n, int**& a, int**& b, int**& c, int threads)
{
	int sum, total = 0, i, j;
	double start = omp_get_wtime();
	omp_lock_t lock; //инициализация замка
	omp_init_lock(&lock); //устаовка замка
#pragma omp parallel num_threads(threads) shared(total,a,b,c) private(i,j,sum)
#pragma omp for 
	for (i = 0; i < n; i++)
	{
		sum = 0;
		for (j = 0; j < n; j++)
		{
			c[i][j] = (a[i][j] > b[i][j]) ? a[i][j] : b[i][j];
			sum += c[i][j];
		}

		//fflush(stdout);
		omp_set_lock(&lock); //поток блокируется
		total += sum;
		omp_unset_lock(&lock); //освобождение замка
	}
	cout << "total sum = " << total << endl;
	fflush(stdout);
	omp_destroy_lock(&lock); // перевод замка в неинециализированное состояние
	double end = omp_get_wtime();
	cout << "The time sumSenaphores: " << end - start << " ms\n";
}
#endif ONCE_SEMAPHORES