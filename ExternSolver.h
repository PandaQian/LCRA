/*
 * ExternSolver.h
 *
 *  Created on: 2015年3月26日
 *      Author: mingpz
 */

#ifndef EXTERNSOLVER_H_
#define EXTERNSOLVER_H_


void IML_CG_testing();
void IML_CG_Solver(int N, const char *name, double *x, double *b,
        double *b_solve, double epsilon);
void IML_BiCG_Solver(int N, const char *name, double *x, double *b,
        double *b_solve, double epsilon);
void IML_GMRES_Solver(int N, const char *name, double *x, double *b,
        double *b_solve, double epsilon);

void IML_Benchmark1();
void IML_Benchmark2();
void IML_Benchmark3();
void IML_Benchmark4();
void IML_Benchmark5();
void IML_Benchmark6();

#endif /* EXTERNSOLVER_H_ */
