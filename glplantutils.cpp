#include "glplantutils.h"

GLuint createSegList(){
  int ti,tj,tmpi;
  GLuint newList;
  newList = glGenLists(1);
  glNewList(newList, GL_COMPILE);
  
  for(ti=0;ti<6;ti++){
      tmpi = ti + 1;
      glBegin(GL_QUADS);
          glNormal3d(budTip[tmpi][0], budTip[tmpi][1], 0.0);
          glVertex3d(budTip[tmpi][0], budTip[tmpi][1], 1.0);

          glNormal3d(budTip[ti][0], budTip[ti][1], 0.0);
          glVertex3d(budTip[ti][0], budTip[ti][1], 1.0);

          glNormal3d(budTip[ti][0], budTip[ti][1], 0.0);
          glVertex3d(budTip[ti][0], budTip[ti][1], 0.0);

          glNormal3d(budTip[tmpi][0], budTip[tmpi][1], 0.0);
          glVertex3d(budTip[tmpi][0], budTip[tmpi][1], 0.0);

          // +Y SIDE
          glNormal3d(budTip[tmpi][0], budTip[tmpi][1] * -1.0, 0.0);
          glVertex3d(budTip[tmpi][0], budTip[tmpi][1] * -1.0, 1.0);

          glNormal3d(budTip[tmpi][0], budTip[tmpi][1] * -1.0, 0.0);
          glVertex3d(budTip[tmpi][0], budTip[tmpi][1] * -1.0, 0.0);

          glNormal3d(budTip[ti][0], budTip[ti][1] * -1.0, 0.0);
          glVertex3d(budTip[ti][0], budTip[ti][1] * -1.0, 0.0);

          glNormal3d(budTip[ti][0], budTip[ti][1] * -1.0, 0.0);
          glVertex3d(budTip[ti][0], budTip[ti][1] * -1.0, 1.0);
      glEnd();
  }
  glEndList();
  return newList;
}

GLuint createBudList(){
  int ti,tj,tmpi;
  GLuint newList;
  newList = glGenLists(1);
  glNewList(newList, GL_COMPILE);
    for(ti=0;ti<6;ti++){
      tmpi = ti + 1;
      glBegin(GL_TRIANGLES);
        // -Y SIDE
        glNormal3d(budTip[tmpi][0], budTip[tmpi][1], 0.0);
        glVertex3dv(budTip[tmpi]);

        glNormal3d(budTip[ti][0], budTip[ti][1], 0.0);
        glVertex3dv(budTip[ti]);

        glNormal3d(budTip[tmpi][0], budTip[tmpi][1], 0.0);
        glVertex3d(budTip[tmpi][0], budTip[tmpi][1], budTip[ti][2]);

        // +Y SIDE
        
        glNormal3d(budTip[tmpi][0], budTip[tmpi][1] * -1.0, 0.0);
        glVertex3d(budTip[tmpi][0], budTip[tmpi][1] * -1.0, budTip[tmpi][2]);

        glNormal3d(budTip[tmpi][0], budTip[tmpi][1] * -1.0, 0.0);
        glVertex3d(budTip[tmpi][0], budTip[tmpi][1] * -1.0, budTip[ti][2]);

        glNormal3d(budTip[ti][0], budTip[ti][1] * -1.0, 0.0);
        glVertex3d(budTip[ti][0], budTip[ti][1] * -1.0, budTip[ti][2]);
        
      glEnd();
      if(ti > 0){
        glBegin(GL_QUADS);
          // -Y SIDE
          glNormal3d(budTip[tmpi][0], budTip[tmpi][1], 0.0);
          glVertex3d(budTip[tmpi][0], budTip[tmpi][1], budTip[ti][2]);

          glNormal3d(budTip[ti][0], budTip[ti][1], 0.0);
          glVertex3d(budTip[ti][0], budTip[ti][1], budTip[ti][2]);

          glNormal3d(budTip[ti][0], budTip[ti][1], 0.0);
          glVertex3d(budTip[ti][0], budTip[ti][1], 0.0);

          glNormal3d(budTip[tmpi][0], budTip[tmpi][1], 0.0);
          glVertex3d(budTip[tmpi][0], budTip[tmpi][1], 0.0);

          // +Y SIDE
          glNormal3d(budTip[tmpi][0], budTip[tmpi][1] * -1.0, 0.0);
          glVertex3d(budTip[tmpi][0], budTip[tmpi][1] * -1.0, budTip[ti][2]);

          glNormal3d(budTip[tmpi][0], budTip[tmpi][1] * -1.0, 0.0);
          glVertex3d(budTip[tmpi][0], budTip[tmpi][1] * -1.0, 0.0);

          glNormal3d(budTip[ti][0], budTip[ti][1] * -1.0, 0.0);
          glVertex3d(budTip[ti][0], budTip[ti][1] * -1.0, 0.0);

          glNormal3d(budTip[ti][0], budTip[ti][1] * -1.0, 0.0);
          glVertex3d(budTip[ti][0], budTip[ti][1] * -1.0, budTip[ti][2]);
        glEnd();
      }
    }
  glEndList();
  return newList;
}

void drawPlant(plant p, GLuint *lst){
  int currSeg;
  float age,newage,halfwidth;

  glPushMatrix();
  printf("Drawing plant with %d segments\n",p.numOfSegments);
  for(currSeg = 1; currSeg < p.numOfSegments; currSeg++){
    if(p.segments[currSeg].age >= 16.0){ // Draw regular segment
      halfwidth = p.segments[currSeg].width / 2.0;
      glRotatef(p.segments[currSeg].theta,0.0,0.0,1.0);
      glRotatef(p.segments[currSeg].phi,0.0,1.0,0.0);
      glPushMatrix();
      glScalef(halfwidth,
               halfwidth,
               p.segments[currSeg].height);
        glCallList(lst[1]);
      glPopMatrix();
      glTranslatef(0.0,0.0,p.segments[currSeg].height - 0.1);
      // Draw the leaf
      glPushMatrix();
        glScalef(p.segments[currSeg].leafscale, p.segments[currSeg].leafscale,p.segments[currSeg].leafscale);
        glBegin(GL_TRIANGLES);
          glVertex3f(halfwidth,-0.5f,0.0f);
          glVertex3f(0.0f,0.0f,0.0f - p.segments[currSeg].height);
          glVertex3f(halfwidth,0.5f,0.0f);
        glEnd();
        glPushMatrix();
          glTranslatef(halfwidth,0.0,0.0);
          //glScalef(1.0,p.segments[currSeg].width,1.0);
          drawBezierLeaf(p.segments[currSeg].leaf,21,0.1,3);
        glPopMatrix();
      glPopMatrix();
    }
  }else if(p.segments[currSeg].age >= 12.0){ // Draw outter leaf

  }if(p.segments[currSeg].age >= 8.0){ // Draw inner leaf
  }else if(p.segments[currSeg].age >= 4.0){ // draw bud / tassle
  }else{
  }
  glPopMatrix();
}

void drawBezierLeaf(double*** leaf, int segments, double dt, int age){
  int i,j,k,seg3i;
  double scale;
  double t, seg3;
  double* prev,* res,* tmp, * prevspine, * resspine;
  double* prevB,* resB;
  prev = (double *)malloc(sizeof(double) * 3);
  res = (double *)malloc(sizeof(double) * 3);
  prevB = (double *)malloc(sizeof(double) * 3);
  resB = (double *)malloc(sizeof(double) * 3);
  prevspine = (double *)malloc(sizeof(double) * 3);
  resspine = (double *)malloc(sizeof(double) * 3);

  glBegin(GL_QUADS); 
  glLineWidth(6);

  scale = (age + 1.0) / 4.0;

  if(age > 1){
    for(i=0;i<segments;i++){
      t = dt;
      beziersz(leaf[0][i*3],leaf[0][i*3 + 1],leaf[0][i*3 + 2],leaf[0][i*3 + 3], 0.0, prev
        ,scale);
      beziersz(leaf[1][i*3],leaf[1][i*3 + 1],leaf[1][i*3 + 2],leaf[1][i*3 + 3], 0.0, prevB
        ,scale);
  
      // Calculate spine
      bezier(bezierSpine[age][0],bezierSpine[age][1],bezierSpine[age][2],bezierSpine[age][3], i/(segments*1.0), prevspine);

      while(t <= 1.0){
        // far edge
        beziersz(leaf[0][i*3],leaf[0][i*3 + 1],leaf[0][i*3 + 2],leaf[0][i*3 + 3], t, res
          ,scale);
        // near edge
        beziersz(leaf[1][i*3],leaf[1][i*3 + 1],leaf[1][i*3 + 2],leaf[1][i*3 + 3], t, resB
          ,scale);
        //spine
        bezier(bezierSpine[age][0],bezierSpine[age][1],bezierSpine[age][2],bezierSpine[age][3], (i + t)/(segments*1.0), resspine);

        /*
        glColor3f(0.3,0.8,0.0);
        glVertex3d(prevspine[0],prevspine[1],prevspine[2]);
        glVertex3d(resspine[0],resspine[1],resspine[2]);
        */

        glColor3f(0.1,0.6,0.0);

        // draw line far
        
        glVertex3d(resspine[0],res[1],res[2] + resspine[2]);
        glVertex3d(prevspine[0],prev[1],prev[2] + prevspine[2]);
        glVertex3d(prevspine[0],0.0,prevspine[2]);
        glVertex3d(resspine[0],0.0,resspine[2]);
        
        // draw line near
        glVertex3d(resspine[0],0.0,resspine[2]);
        glVertex3d(prevspine[0],0.0,prevspine[2]);
        glVertex3d(prevspine[0],prevB[1],prevB[2] + prevspine[2]);
        glVertex3d(resspine[0],resB[1],resB[2] + resspine[2]);

        // edge to center
        /*
        glVertex3d(resspine[0],res[1],res[2] + resspine[2]);
        glVertex3d(resspine[0],resB[1],resB[2] + resspine[2]);
        glVertex3d(resspine[0],0.0,resspine[2]);
        */

        tmp = res;
        res = prev;
        prev = tmp;

        tmp = resB;
        resB = prevB;
        prevB = tmp;

        tmp = resspine;
        resspine = prevspine;
        prevspine = tmp;

        t += dt;
      }
    }
    glEnd();
  }else{
    seg3i = segments / 3;
    seg3 = segments / 3.0;
    for(i=0;i< seg3i ;i++){
      t = dt;
      beziersz(leaf[0][i*9],leaf[0][i*9 + 3],leaf[0][i*9 + 6],leaf[0][i*9 + 9], 0.0, prev
        ,scale);
      beziersz(leaf[1][i*9],leaf[1][i*9 + 3],leaf[1][i*9 + 6],leaf[1][i*9 + 9], 0.0, prevB
        ,scale);
  
      // Calculate spine
      bezier(bezierSpine[age][0],bezierSpine[age][1],bezierSpine[age][2],bezierSpine[age][3], i/(seg3), prevspine);

      while(t <= 1.0){
        // far edge
        beziersz(leaf[0][i*9],leaf[0][i*9 + 3],leaf[0][i*9 + 6],leaf[0][i*9 + 9], t, res
          ,scale);
        // near edge
        beziersz(leaf[1][i*9],leaf[1][i*9 + 3],leaf[1][i*9 + 6],leaf[1][i*9 + 9], t, resB
          ,scale);
        //spine
        bezier(bezierSpine[age][0],bezierSpine[age][1],bezierSpine[age][2],bezierSpine[age][3], (i + t)/(seg3), resspine);


        glColor3f(0.3,0.8,0.0);

        /*
        glVertex3d(prevspine[0],prevspine[1],prevspine[2]);
        glVertex3d(resspine[0],resspine[1],resspine[2]);

        glColor3f(0.1,0.6,0.0);
        */

        glVertex3d(resspine[0],res[1],res[2] + resspine[2]);
        glVertex3d(prevspine[0],prev[1],prev[2] + prevspine[2]);
        glVertex3d(prevspine[0],0.0,prevspine[2]);
        glVertex3d(resspine[0],0.0,resspine[2]);
        
        // draw line near
        glVertex3d(resspine[0],0.0,resspine[2]);
        glVertex3d(prevspine[0],0.0,prevspine[2]);
        glVertex3d(prevspine[0],prevB[1],prevB[2] + prevspine[2]);
        glVertex3d(resspine[0],resB[1],resB[2] + resspine[2]);

        tmp = res;
        res = prev;
        prev = tmp;

        tmp = resB;
        resB = prevB;
        prevB = tmp;

        tmp = resspine;
        resspine = prevspine;
        prevspine = tmp;

        t += dt;
      }
    }
    glEnd();
  }
}
