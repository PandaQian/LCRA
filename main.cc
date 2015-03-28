/*
 * main.cc
 *
 *  Created on: 2015年3月26日
 *      Author: mingpz
 */
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>
#include <limits>
#include <unistd.h>
#include "ExternSolver.h"
#include "Solver.h"

using namespace std;

int main(int argc, char *argv[])
{
    IML_CG_testing();

    IML_Benchmark1();
    IML_Benchmark2();
    IML_Benchmark3();
    IML_Benchmark4();

    return 0;
}



