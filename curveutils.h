#include <math.h>
#include <stdlib.h>

static double bezierSpine[4][4][3] = {
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
