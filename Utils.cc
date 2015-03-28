/*
 * Utils.cc
 *
 *  Created on: 2015年3月27日
 *      Author: mingpz
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>
#include <limits>
#include <unistd.h>
#include "Utils.h"

double Now()
{
    struct timespec timer;
    double tm;

    clock_gettime(CLOCK_REALTIME, &timer);
    tm = timer.tv_sec + timer.tv_nsec*0.000000001;

    return tm;
}

int Alloc_2D_array(int N, double ***A)
{
    double **B;
    B = (double **)malloc(N * sizeof(double *));

    if(B == NULL) {
        fprintf(stderr, "Alloc 2D array out of memory\n");
        return -1;
    }

    for(int i = 0; i < N; i++) {
        B[i] = (double *)malloc(N * sizeof(double));
        if(B[i] == NULL) {
            fprintf(stderr, "Alloc 2D array out of memory\n");
            return -1;
        }
    }
    *A = B;

    return 0;
}

void Free_2D_array(int N, double **A)
{
    for (int i = 0; i < N; i++) {
        free(A[i]);
    }

    if (A != NULL) {
        free(A);
    }
}

double Vector_max_norm(int N, double *x)
{
    int i;
    double tmp;
    double ans = fabs(x[0]);

    for (i=1; i<N; i++) {
        tmp = fabs(x[i]);
        if (tmp > ans) {
            ans = tmp;
        } // 获取向量的最大范数
    }

    return ans;
}

double Vector_cmp(int N, double *x, double *y)
{
    int i;
    double tmp;
    double ans = fabs(x[0]-y[0]);

    for (i=1; i<N; i++) {
        tmp = fabs(x[i]-y[i]);
        if (tmp > ans) {
            ans = tmp;
        }
    }

    return ans;
}

double Vector_inner_product(int N, double *x, double *y)
{
    double ans = 0;
    int i;

    for (i=0; i<N; i++) {
        ans += x[i]*y[i];
    }

    return ans;
}

void Vector_mul(int N, double *x, double num)
{
    int i;

    for (i=0; i<N; i++) {
        x[i] *= num;
    }
}

void Vector_add(int N, double *x, double *y)
{
    int i;

    for (i=0; i<N; i++) {
        x[i] += y[i];
    }
}

void Vector_sub(int N, double *x, double *y)
{
    int i;

    for (i=0; i<N; i++) {
        x[i] -= y[i];
    }
}



