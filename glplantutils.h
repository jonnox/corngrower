#include <GL/glew.h>
#include <GL/glut.h>
#include "cornplant.h"

static GLuint *disLists;
//leafList, budList, planeList, clDispList, segList;

GLuint createBudList();
GLuint createSegList();
void drawPlant(plant p, GLuint *lst);
void drawBezierLeaf(double*** leaf, int segments, double dt, int age);
void drawBezierLeafWithSpine(double*** leaf, int segments, double dt, bool highVariance, double** spine);

