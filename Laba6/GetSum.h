#pragma once
double get_sum_reduction(int n, int **&a, int **&b, int **&c, int threads);
double get_sum_atomic(int n, int **&a, int **&b, int **&c, int threads);
double get_sum_semaphores(int n, int **&a, int **&b, int **&c, int threads);
double get_sum_barrier(int n, int **&a, int **&b, int **&c, int threads);
