/*
 * Utils.h
 *
 *  Created on: 2015年3月27日
 *      Author: mingpz
 */

#ifndef UTILS_H_
#define UTILS_H_

#define MAX_OF_ITR  100000

double Now();

// 二维数组矩阵的动态分配
int Alloc_2D_array(int N, double ***A);
void Free_2D_array(int N, double **A);

// 增加的关于向量运算的接口函数
double Vector_max_norm(int N, double *x);
double Vector_cmp(int N, double *x, double *y);
double Vector_inner_product(int N, double *x, double *y);
void Vector_mul(int N, double *x, double num);
void Vector_add(int N, double *x, double *y);
void Vector_sub(int N, double *x, double *y);

#endif /* UTILS_H_ */
