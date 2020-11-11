#include <omp.h>
#include <iostream>
#include <random>

using namespace std;

#define __PARALLEL 1
int main() {
    int N, num;
    cout << "input N" << endl;
    cin >> N;
    cout << "input num_threads" << endl;
    cin >> num;
    uint32_t* arr1 = new uint32_t[N];
    for (int i = 0; i < N; i++)
        arr1[i] = 1;
    uint32_t* arr2 = new uint32_t[N];
    for (int i = 0; i < N; i++)
        arr2[i] = 1;
    double total = 1;
    int sum = 0, i = 0;

    double start2 = omp_get_wtime();
#pragma omp parallel num_threads(num) shared(arr1,arr2)
    {
#pragma omp sections reduction(*:total)
        {
#pragma omp section
            {
                for (i = 0; i < N / 8; i++)
                {
                    sum = arr1[i] + arr2[i];
                    sum != 0 ? total *= sum : sum = 0;
                }
            }
#pragma omp section
            {
                for (i = N / 8; i < 2 * N / 8; i++)
                {
                    sum = arr1[i] + arr2[i];
                    sum != 0 ? total *= sum : sum = 0;
                }
            }
#pragma omp section
            {
                for (i = 2 * N / 8; i < 3 * N / 8; i++)
                {
                    sum = arr1[i] + arr2[i];
                    sum != 0 ? total *= sum : sum = 0;
                }
            }
#pragma omp section
            {
                for (i = 3 * N / 8; i < 4 * N / 8; i++)
                {
                    sum = arr1[i] + arr2[i];
                    sum != 0 ? total *= sum : sum = 0;
                }
            }
#pragma omp section
            {
                for (i = 4 * N / 8; i < 5 * N / 8; i++)
                {
                    sum = arr1[i] + arr2[i];
                    sum != 0 ? total *= sum : sum = 0;
                }
            }

#pragma omp section
            {
                for (i = 5 * N / 8; i < 6 * N / 8; i++)
                {
                    sum = arr1[i] + arr2[i];
                    sum != 0 ? total *= sum : sum = 0;
                }
            }
#pragma omp section
            {
                for (i = 6 * N / 4; i < 7 * N / 8; i++)
                {
                    sum = arr1[i] + arr2[i];
                    sum != 0 ? total *= sum : sum = 0;
                }
            }
#pragma omp section
            {
                for (i = 7 * N / 4; i < N; i++)
                {
                    sum = arr1[i] + arr2[i];
                    sum != 0 ? total *= sum : sum = 0;
                }
            }
        }
    }
    printf("sum elem mass %lf\n", total);
    double end2 = omp_get_wtime();
    cout << "The time for 8 sections: " << end2 - start2 << " ms\n";

    double start = omp_get_wtime();
#pragma omp parallel num_threads(num) shared(arr1,arr2)
    {
#pragma omp sections reduction(*:total)
        {
#pragma omp section
            {
                for (i = 0; i < N / 4; i++)
                {
                    sum = arr1[i] + arr2[i];
                    sum != 0 ? total *= sum : sum = 0;
                }
            }

#pragma omp section
            {
                for (i = N / 4; i < 2 * N / 4; i++)
                {
                    sum = arr1[i] + arr2[i];
                    sum != 0 ? total *= sum : sum = 0;
                }
            }
#pragma omp section
            {
                for (i = 2 * N / 4; i < 3 * N / 4; i++)
                {
                    sum = arr1[i] + arr2[i];
                    sum != 0 ? total *= sum : sum = 0;
                }
            }
#pragma omp section
            {
                for (i = 3 * N / 4; i < N; i++)
                {
                    sum = arr1[i] + arr2[i];
                    sum != 0 ? total *= sum : sum = 0;
                }
            }
        }
    }
    printf("sum elem mass %lf\n", total);
    double end = omp_get_wtime();
    cout << "The time for 4 sections: " << end - start << " ms\n";
    total = 1;
    
    double start1 = omp_get_wtime();
#pragma omp parallel num_threads(num) shared(arr1,arr2)
    {
#pragma omp sections reduction(*:total)
        {
#pragma omp section
            {
                for (i = 0; i < N; i += 2)
                {
                    sum = arr1[i] + arr2[i];
                    sum != 0 ? total *= sum : sum = 0;
                }
            }

#pragma omp section
            {
                for (i = 1; i < N; i += 2)
                {
                    sum = arr1[i] + arr2[i];
                    sum != 0 ? total *= sum : sum = 0;
                }
            }
        }
    }

    printf("sum elem mass: %lf\n", total);
    double end1 = omp_get_wtime();
    cout << "The time for 2 sections: " << end1 - start1 << " ms\n";
}
