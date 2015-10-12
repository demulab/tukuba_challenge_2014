#ifndef _MyMethod_
#define _MyMethod_

#include<iostream>
#include<math.h>

#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

struct pose
{
    double x;
    double y;
    double theta;
};

struct point
{
    double x;
    double y;
};

double changeTheta(double theta);
double gettimeofday_sec() ;
int roundOff(double x);
double randGaussian(double standard, double statndardDeviation);
double gaussian(double x, double y, double statndardDeviation);
bool leastSquaresMethod(point *data, int dataNum, double *a, double *b, double *c);


#endif
