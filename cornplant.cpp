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
    newplant.numOfSegments = 2;
    newplant.scale = scale;
    if(maturity == 0){
      newplant.maturity = (rand() % 4) + 19;
    }else{
      newplant.maturity = maturity;
    }
    newplant.segments = (segment *)malloc(sizeof(segment) * (newplant.maturity + 1));
    newplant.segments[0] = newSegment(iwidth, iheight, 0.0f, 0.0f, 1.0);
    newplant.segments[1] = newSegment(iwidth, iheight, 0.0f, 0.0f, 1.0);

    return newplant;
}

/**
 * Perform a growth time step for a given plant, dt max is 1 day.
 */
void updatePlant(plant &p, float dt){
  int currSeg;
  float age,newage,dtdh,dtdw,tdt;
  if(dt > 1.0f)
    dt = 1.0f;
  dtdh = dt * p.dh;
  dtdw = dt * p.dw;
  tdt = (dt / 10.0f) + 1.0f;

  if(p.numOfSegments == p.maturity)
    return;

  for(currSeg = 1; currSeg < p.numOfSegments; currSeg++){
    age = p.segments[currSeg].age;
    p.segments[currSeg].age += dt;
    newage = p.segments[currSeg].age;

    // Increase width and height of node
    p.segments[currSeg].height += dtdh;
    p.segments[currSeg].width += dtdh;
    
    if(age >= 16.0){ // Collared leaf - internode
      //p.segments[currSeg].leafscale *= tdt;

    }else if(age >= 12.0){ // Outter leaf
    }else if(age >= 8.0){ // Middle leaf
    }else if(age >= 4.0){ // Inner leaf
    }else{ // Bud
      if(newage >= 4.0){
        if(p.numOfSegments < p.maturity){
          p.segments[currSeg + 1] = newSegment(
            p.segments[currSeg].width - (4.0 * p.dw),
            p.segments[currSeg].height,
            180.0f + ((rand() % 200) - 100) * 0.1f,
            (rand() % 75) * 0.1f + p.segments[currSeg].phi / 2.0 ,
            p.segments[currSeg].leafscale * 1.1f
            );
          p.numOfSegments++;
          printf("Created new bud: %d\n",p.numOfSegments);
        }
      }
    }
  }
}
