#include <math.h>
#include <stdlib.h>

static double budTip[7][3] = {
    {-1.000,0.000,0.000000},
    {-0.866,-0.500,0.397940},
    {-0.500,-0.866,0.602060},
    {-0.000,-1.000,0.740363},
    {0.500,-0.866,0.845098},
    {0.866,-0.500,0.929419},
    {1.000,0.000,1.000000}
};

static double leafStepA[6][3] = {
    {-0.866,-0.500,0.0},
    {-0.500,-0.866,0.447},
    {-0.000,-1.000,0.663},
    {0.500,-0.866,0.806},
    {0.866,-0.500,0.913},
    {1.000,0.000,1.000000}
};

static double leafStepB[5][3] = {
    {-0.500,-0.866,0.0},
    {-0.000,-1.000,0.511883},
    {0.500,-0.866,0.740362},
    {0.866,-0.500,0.8893017},
    {1.000,0.000,1.000000}
};

static double leafStepC[3][3] = {
    {0.500,-0.866,0.0},
    {0.866,-0.500,0.74036},
    {1.000,0.000,1.000000}
};

static double bezierSpine[5][5][3] = {
  {{0.0,0.0,0.0},{0.0,0.0,1.0},{0.0,0.0,2.0},{0.5,0.0,4.0}},
  {{0.0,0.0,0.0},{0.5,0.0,2.5},{1.5,0.0,3.75},{3.0,0.0,4.0}},
  {{0.0,0.0,0.0},{1.5,0.0,4.5},{4.0,0.0,6.5},{6.0,0.0,5.5}},
  {{0.0,0.0,0.0},{2.0,0.0,5.5},{8.0,0.0,7.0},{8.0,0.0,3.0}},
  {{0.0,0.0,0.0},{4.0,0.0,5.0},{10.0,0.0,7.0},{10.0,0.0,2.0}}
};

/**
 * Compute the point at time t with 4 given control points and store result in res
 */
void bezier(double* p0, double* p1, double* p2, double* p3, double t, double* res);

void beziersz(double* p0, double* p1, double* p2, double* p3, double t, double* res,
             double scalez);

double bezierU(double p0, double p1, double p2, double p3, double t);

/**
 * Creates 2 bezier curves representing the outter edges of a corn leaf
 */
double*** createLeaf(int segments);

void calcNormal(double* p0, double* p1, double* p2, double* norm);
