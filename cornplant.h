#include "curveutils.h"
#include <stdio.h>

typedef struct {
  float age;
  float width;
  float height;
  float theta;
  float phi;
  float leafscale;
  double ***leaf;
} segment;

typedef struct{
  float scale;
  float iwidth;
  float iheight;
  float dw; // delta width per day
  float dh; // delta height per day
  int numOfSegments; // Number of segments currently in system - 1
  int maturity; // Number of segments once fully grown
  segment *segments; // composition of segments from bottom up
} plant;

segment newSegment(float width, float height, float theta, float phi, float leafscale);

plant newPlant(float scale,
  float iwidth,
  float iheight,
  float dw, // delta width per day
  float dh, // delta height per day
  int maturity); // Number of segments once fully grown

void updatePlant(plant &p, float dt);
