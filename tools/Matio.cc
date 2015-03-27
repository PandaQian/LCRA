/*
 * Matio.cc
 *
 *  Created on: 2015年3月27日
 *      Author: mingpz
 */
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "compcol_double.h"              // Compressed column matrix header
#include "iohb_double.h"                 // Harwell-Boeing matrix I/O header
#include "coord_double.h"
#include "mvblasd.h"                     // MV_Vector level 1 BLAS
#include "diagpre_double.h"              // Diagonal preconditioner

using namespace std;

int main(int argc, char *argv[])
{
    int N, count = 0;
    double **A;
    ifstream myfile;
    string new_name;

    if (argc != 3) {
        cout<<"Please input like ./a.out [-c|-r|-o] [normal matrix name]."<<endl;
        cout<<"normal matrix is organized as ASCII text such as:"<<endl;
        cout<<"2"<<endl;
        cout<<"1.5 4.6" <<endl <<"3.2 2.4"<<endl;
        cout<<"The normal matrix file can be changed to Coord_Mat, CompRow, CompCol format!"<<endl;
        cout<<"The new matrix file will be Harwell-Boeing Format in SparseLib++."<<endl;
        return -1;
    }

    myfile.open (argv[2]);
    if (! myfile.is_open()) {
        cout<<"Open normal matrix file failure!"<<endl;
        return -1;
    }
    myfile >> N;
    fprintf(stderr, "Normal matrix size is %d * %d\n", N, N);
    new_name += argv[2];
    new_name += ".hb";
    cout<<"The new matrix file name is "<<new_name<<endl;

    A = (double **)malloc(N * sizeof(double *));
    if(A == NULL) {
        fprintf(stderr, "Matrix out of memory\n");
        exit(-1);
    }
    for(int i = 0; i < N; i++) {
        A[i] = (double *)malloc(N * sizeof(double));
        if(A[i] == NULL) {
            fprintf(stderr, "Matrix out of memory\n");
            exit(-1);
        }
    }
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            myfile >> A[i][j];
            // cout<< A[i][j] << endl;
            if (A[i][j] != 0.) {
                count++;
            }
        }
    }
    fprintf(stderr, "Normal matrix has non-zero elements %d\n", count);

    double *val = new double[count];
    int *r = new int[count];
    int *c = new int[count];

    int index = 0;
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            if (A[i][j] != 0) {
                val[index] = A[i][j];
                r[index] = i;
                c[index] = j;
                index++;
            }
        }
    }

    if (! strcmp(argv[1], "-o")) {
        cout<<"Change to Coord_Mat format..."<<endl;
        Coord_Mat_double m = Coord_Mat_double(N, N, count, val, r, c);
        writeHB_mat(new_name.c_str(), m);
    } else if (! strcmp(argv[1], "-r")) {
        cout<<"Change to CompRow format..."<<endl;
        Coord_Mat_double m = Coord_Mat_double(N, N, count, val, r, c);
        CompRow_Mat_double rm = CompRow_Mat_double(m);
        writeHB_mat(new_name.c_str(), rm);
    } else if (! strcmp(argv[1], "-c")) {
        cout<<"Change to CompCol format..."<<endl;
        Coord_Mat_double m = Coord_Mat_double(N, N, count, val, r, c);
        CompCol_Mat_double cm = CompCol_Mat_double(m);
        writeHB_mat(new_name.c_str(), cm);
    } else {
        cout<<"Please input like ./a.out [-c|-r|-o] [normal matrix name]."<<endl;
        cout<<"Your option is not supported yet!"<<endl;
    }

    delete []c;
    delete []r;
    delete []val;
    for (int i = 0; i < N; i++) {
        free(A[i]);
    }
    free(A);
    myfile.close();

    return 0;
}



