/*
 * Solver.cc
 *
 *  Created on: 2015年3月26日
 *      Author: mingpz
 */
#include <cstdio>
#include "Solver.h"

void GaussSeidel_iterate(int N, CompCol_Mat_double &A, double *x,
        double *b, double epsilon)
{
    int i, j, itr = 0;
    double residual = 1;
    double factor, left_sum, right_sum;
    double *x_tmp = new double[N + 1];

    do {
        itr++;

        for (i=1; i<=N; i++) {
            factor = 1/A(i, i);
            left_sum = right_sum = 0.0;
            for (j=1; j<i; j++) {
                left_sum += A(i,j)*x[j];
            }
            for (j=i; j<=N; j++) {
                right_sum += A(i,j)*x[j];
            }
            x[i] = x[i] + factor * (b[i]-left_sum-right_sum);
        } // 计算出本轮迭代的数值，存放于x向量中

        for (i=1; i<=N; i++) {
            x_tmp[i] = x[i];
        } // 拷贝本次迭代的数值

        // Vector_mul(N, A, x_tmp);
        // Vector_mul(N, x_tmp, -1);
        // Vector_add(N, x_tmp, b);

        // residual = Vector_max_norm(N, x_tmp); // 本次的迭代收敛误差

        if (residual < epsilon) {
            printf("ITR = %d convergence!!!\n", itr-1);
            break;
        }

#ifdef DEBUG
        printf("ITR = %d : residual = %.8le\n", itr-1, residual);
#endif

    } while (1);

    delete[] x_tmp;
}


