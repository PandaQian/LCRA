/*
 * IML_Solver.cc
 *
 *  Created on: 2015年3月26日
 *      Author: mingpz
 */
#include <cstdlib>
#include <iostream>
#include "compcol_double.h"              // Compressed column matrix header
#include "iohb_double.h"                 // Harwell-Boeing matrix I/O header
#include "mvblasd.h"                     // MV_Vector level 1 BLAS
#include "diagpre_double.h"              // Diagonal preconditioner
#include "cg.h"
#include "ExternSolver.h"

using namespace std;

void IML_CG_testing()
{
    double tol = 1.e-16;                    // Convergence tolerance
    int result, maxit = 10000;               // Maximum iterations

    CompCol_Mat_double A;                  // Create a matrix
    readHB_mat("data/la2d8.hb", &A);               // Read matrix data
    VECTOR_double b, x(A.dim(1), 0.0);     // Create rhs, solution vectors
    readHB_rhs("data/la2d8.hb", &b);               // Read rhs data

    DiagPreconditioner_double D(A);        // Create diagonal preconditioner

    result = CG(A, x, b, D, maxit, tol);   // Solve system

    cout << "CG flag = " << result << endl;
    cout << "iterations performed: " << maxit << endl;
    cout << "tolerance achieved  : " << tol << endl;
}

