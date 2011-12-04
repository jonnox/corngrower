#include "curveutils.h"

/**
 * Compute the point at time t with 4 given control points and store result in res
 */
void bezier(double* p0, double* p1, double* p2, double* p3, double t, double* res){
  int i;
  for(i=0;i<3;i++)
    res[i] = bezierU(p0[i],p1[i],p2[i],p3[i],t);
}

/**
 * Compute the point at time t with 4 given control points and store result in res
 * scaling the control points for the z component
 */
void beziersz(double* p0, double* p1, double* p2, double* p3, double t, double* res,
             double scalez){
  int i;
  res[2] = bezierU(p0[2] * scalez,p1[2] * scalez,p2[2] * scalez,p3[2] * scalez,t);
  for(i=0;i<2;i++)
    res[i] = bezierU(p0[i],p1[i],p2[i],p3[i],t);
}

/**
 * Compute the bezier point in 1-D
 */
double bezierU(double p0, double p1, double p2, double p3, double t){
  double nt = 1.0 - t;
  return ( pow(nt,3)*p0 + 3.0*pow(nt,2)*t*p1 +
                               3.0*(nt) * pow(t,2) * p2 +
                                pow(t,3) * p3);
}

/**
 * Creates a bezier spline with segments*3 + 1 control points.
 * Minimum size is 3 segments. Each leaf is from 0.0x -> 10.0x
 -0.5y -> 0.5y
 */
double*** createLeaf(int segments){
	int n,i,j; // number of segments
	double rndA,rndB,rndC,tmpd;
	double x; // current x location
	double dx; // delta x
	double*** leaf = (double ***)malloc(sizeof(double **) * 2);
	if(segments < 3)
		n = 10;
	else
		n = (segments * 3) + 1;

	for(i=0;i<3;i++)
		leaf[i] = (double **)malloc(sizeof(double *) * n);
	for(i=0;i<3;i++)
		for(j=0;j<n;j++)
			leaf[i][j] = (double *)malloc(sizeof(double) * 3);

	dx = (double)(15.0 / (n * 1.0));
	x = 0.0;

	for(i=0;i<3;i++){
		leaf[0][i][0] = x;
		leaf[0][i][1] = -0.5;
		leaf[0][i][2] = 0.0;
		leaf[1][i][0] = x;
		leaf[1][i][1] = 0.5;
		leaf[1][i][2] = 0.0;
		x = x + dx;
	}

	for(i=3;i<n;i++){
		leaf[0][i][0] = x;
		leaf[1][i][0] = x;
		leaf[0][i][1] = -0.5;
		leaf[1][i][1] = 0.5;
		rndA = (rand() * 1.0) / RAND_MAX;
		rndB = ((rand() * 1.0) / RAND_MAX) * 0.4;
		rndC = ((rand() * 1.0) / RAND_MAX) * -0.4;
		if(rndA < 0.5){
			leaf[0][i][2] = rndB;
			leaf[1][i][2] = rndC;
		}else{
			leaf[0][i][2] = rndC;
			leaf[1][i][2] = rndB;
		}
    x += dx;
	}

	leaf[0][n - 5][1] = -15.0/32.0;
	leaf[0][n - 4][1] = -13.0/32.0;
	leaf[0][n - 3][1] = -10.0/32.0;
	leaf[0][n - 2][1] = -6.0/32.0;
	leaf[0][n - 1][1] = 0.0;

	leaf[1][n - 5][1] = 15.0/32.0;
	leaf[1][n - 4][1] = 13.0/32.0;
	leaf[1][n - 3][1] = 10.0/32.0;
	leaf[1][n - 2][1] = 6.0/32.0;
	leaf[1][n - 1][1] = 0.0;

	return leaf;
}

void calcNormal(double* p0, double* p1, double* p2, double* norm){
  
}
