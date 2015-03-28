/*
 * IML_Solver.cc
 *
 *  Created on: 2015年3月26日
 *      Author: mingpz
 */
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "compcol_double.h"              // Compressed column matrix header
#include "iohb_double.h"                 // Harwell-Boeing matrix I/O header
#include "mvblasd.h"                     // MV_Vector level 1 BLAS
#include "mvmd.h"
#include "diagpre_double.h"              // Diagonal preconditioner
#include "cg.h"
#include "bicg.h"
#include "ilupre_double.h"
#include "gmres.h"
#include "ExternSolver.h"
#include "Utils.h"

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

void IML_CG_Solver(int N, const char *name, double *x, double *b,
        double *b_solve, double epsilon)
{
    double tol = epsilon;                    // Convergence tolerance
    int result, maxit = MAX_OF_ITR;               // Maximum iterations
    double start, end;

    CompCol_Mat_double A;                  // Create a matrix
    readHB_mat(name, &A);               // Read matrix data
    VECTOR_double gb(N), gx(A.dim(1), 0.0);     // Create rhs, solution vectors

    for (int i=0; i<N; i++) {
        gb(i) = b[i];
    }
    DiagPreconditioner_double D(A);        // Create diagonal preconditioner

    start = Now();
    result = CG(A, gx, gb, D, maxit, tol);   // Solve system
    end = Now();

#ifdef MY_DEBUG
    fprintf(stderr, "IML CG solve time is %.8lf sec!\n", end - start);
    cout << "CG flag = " << result << endl;
    cout << "iterations performed: " << maxit << endl;
    cout << "tolerance achieved  : " << tol << endl;
#endif

    gb = A * gx;  // For the error analysis later...
    for (int i=0; i<N; i++) {
        x[i] = gx(i);
        b_solve[i] = gb(i);
    }
}

void IML_BiCG_Solver(int N, const char *name, double *x, double *b,
        double *b_solve, double epsilon)
{
    double tol = epsilon;                    // Convergence tolerance
    int result, maxit = MAX_OF_ITR;               // Maximum iterations
    double start, end;

    CompCol_Mat_double A;                  // Create a matrix
    readHB_mat(name, &A);               // Read matrix data
    VECTOR_double gb(N), gx(A.dim(1), 0.0);     // Create rhs, solution vectors

    for (int i=0; i<N; i++) {
        gb(i) = b[i];
    }
    DiagPreconditioner_double D(A);        // Create diagonal preconditioner

    start = Now();
    result = BiCG(A, gx, gb, D, maxit, tol);   // Solve system
    end = Now();

#ifdef MY_DEBUG
    fprintf(stderr, "IML BiCG solve time is %.8lf sec!\n", end - start);
    cout << "BiCG flag = " << result << endl;
    cout << "iterations performed: " << maxit << endl;
    cout << "tolerance achieved  : " << tol << endl;
#endif

    gb = A * gx;  // For the error analysis later...
    for (int i=0; i<N; i++) {
        x[i] = gx(i);
        b_solve[i] = gb(i);
    }
}

void IML_GMRES_Solver(int N, const char *name, double *x, double *b,
        double *b_solve, double epsilon)
{
    double tol = epsilon;                    // Convergence tolerance
    int result, maxit = MAX_OF_ITR, restart = 32;               // Maximum iterations
    double start, end;

    CompCol_Mat_double A;                  // Create a matrix
    readHB_mat(name, &A);               // Read matrix data
    VECTOR_double gb(N), gx(A.dim(1), 0.0);     // Create rhs, solution vectors

    for (int i=0; i<N; i++) {
        gb(i) = b[i];
    }
    MATRIX_double H(restart+1, restart, 0.);

    CompCol_ILUPreconditioner_double M(A);        // Create diagonal preconditioner

    start = Now();
    result = GMRES(A, gx, gb, M, H, restart, maxit, tol);   // Solve system
    end = Now();

#ifdef MY_DEBUG
    fprintf(stderr, "IML GMRES solve time is %.8lf sec!\n", end - start);
    cout << "GMRES flag = " << result << endl;
    cout << "iterations performed: " << maxit << endl;
    cout << "tolerance achieved  : " << tol << endl;
#endif

    gb = A * gx;  // For the error analysis later...
    for (int i=0; i<N; i++) {
        x[i] = gx(i);
        b_solve[i] = gb(i);
    }
}

void IML_Benchmark1()
{
    double x[4];
    double b[4];
    double b_solve[4];
    double ans;

    b[0] = 6; b[1] = 25; b[2] = -11; b[3] = 15;
    IML_CG_Solver(4, "./data/mat1.hb", x, b, b_solve, 1e-8);
    ans = Vector_cmp(4, b, b_solve);

    fprintf(stderr, "IML Benchmark1 maximum error is %.6le\n", ans);
}

void IML_Benchmark2()
{
    int n;
    ifstream myfile;

    myfile.open ("./data/mat2_b");
    myfile >> n;

    double *x = new double[n];
    double *b = new double[n];
    double *b_solve = new double[n];
    double ans;
    for (int i=0; i<n; i++) {
        myfile >> b[i];
    }
    myfile.close();

    IML_CG_Solver(n, "./data/mat2.hb", x, b, b_solve, 1e-8);
    ans = Vector_cmp(n, b, b_solve);

    fprintf(stderr, "IML Benchmark2 maximum error is %.6le\n", ans);
}

void IML_Benchmark3()
{
    int n;
    ifstream myfile;

    myfile.open ("./data/mat2_b");
    myfile >> n;

    double *x = new double[n];
    double *b = new double[n];
    double *b_solve = new double[n];
    double ans;
    for (int i=0; i<n; i++) {
        myfile >> b[i];
    }
    myfile.close();

    IML_BiCG_Solver(n, "./data/mat2.hb", x, b, b_solve, 1e-8);
    ans = Vector_cmp(n, b, b_solve);

    fprintf(stderr, "IML Benchmark3 maximum error is %.6le\n", ans);
}

void IML_Benchmark4()
{
    int n;
    ifstream myfile;

    myfile.open ("./data/mat2_b");
    myfile >> n;

    double *x = new double[n];
    double *b = new double[n];
    double *b_solve = new double[n];
    double ans;
    for (int i=0; i<n; i++) {
        myfile >> b[i];
    }
    myfile.close();

    IML_GMRES_Solver(n, "./data/mat2.hb", x, b, b_solve, 1e-8);
    ans = Vector_cmp(n, b, b_solve);

    fprintf(stderr, "IML Benchmark4 maximum error is %.6le\n", ans);
}

void IML_Benchmark5()
{

}

void IML_Benchmark6()
{

}




