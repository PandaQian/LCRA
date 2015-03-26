/*
 * Solver.h
 *
 *  Created on: 2015年3月26日
 *      Author: mingpz
 */

#ifndef SOLVER_H_
#define SOLVER_H_

#include <iostream>
#include "compcol_double.h"

void GaussSeidel_iterate(int N, CompCol_Mat_double &A, double x, double *b, double epsilon);

#endif /* SOLVER_H_ */
