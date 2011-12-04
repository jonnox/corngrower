#include "cornplant.h"

segment newSegment(float width, float height, float theta, float phi, float leafscale){
  segment seg;
  seg.age = 0.0;
  seg.width = width;
  seg.height = height;
  seg.theta = theta;
  seg.phi = phi;
  seg.leafscale = leafscale;
  seg.leaf = createLeaf(21);
  return seg;
}

/**
 * set maturity to 0 if you want random maturity [19,22]
 */
plant newPlant(float scale,
  float iwidth,
  float iheight,
  float dw, // delta width per day
  float dh, // delta height per day
  int maturity){
    plant newplant;
    newplant.dh = dh;
    newplant.dw = dw;
    newplant.numOfSegments = 1;
    newplant.scale = scale;
    if(maturity == 0){
      newplant.maturity = (rand() % 4) + 19;
    }else{
      newplant.maturity = maturity;
    }
    newplant.segments = (segment *)malloc(sizeof(segment) * (newplant.maturity + 1));
    newplant.segments[0] = newSegment(iwidth, iheight, 0.0f, 0.0f, 1.0);

    return newplant;
}

/**
 * Perform a growth time step for a given plant, dt max is 1 day.
 */
void updatePlant(plant p, float dt){
  if(dt > 1.0f)
    dt = 1.0f;
  int currSeg;
  float segage,newage;
  for(currSeg = 1; currSeg < p.numOfSegments; currSeg++){
    segage = p.segments[currSeg].age;
    p.segments[currSeg].age += dt;
    newage = p.segments[currSeg].age;
  }
}
