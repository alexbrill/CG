#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include <cmath>
#include <iostream>
#include <omp.h>

int factorial(int);
double*** getSurfaceBezier(double***, int, int, int, int); //desired N, M
void applyPerspective(double***, int, int, double, double, double);
void rotateX(double***, int, int, double);
void rotateY(double***, int, int, double);
void moveM(double***, int, int, double, double, double);
void memFree(double***, int, int);
double*** dataCopy(double***, int, int);

extern double ***surface;
extern double ***surfacePersp;
extern const int DESIRED_N, DESIRED_M;

#endif // CALCULATIONS_H
