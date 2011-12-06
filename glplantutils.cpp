#include "glplantutils.h"

GLuint createSegList(){
  int ti,tj,tmpi;
  GLuint newList;
  newList = glGenLists(1);
  glNewList(newList, GL_COMPILE);
  glColor3f(0.1,0.6,0.0);
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
          // REVERSE
          glVertex3d(budTip[tmpi][0], budTip[tmpi][1], 0.0);
          glVertex3d(budTip[ti][0], budTip[ti][1], 0.0);
          glVertex3d(budTip[ti][0], budTip[ti][1], 1.0);
          glVertex3d(budTip[tmpi][0], budTip[tmpi][1], 1.0);


          // +Y SIDE
          glNormal3d(budTip[tmpi][0], budTip[tmpi][1] * -1.0, 0.0);
          glVertex3d(budTip[tmpi][0], budTip[tmpi][1] * -1.0, 1.0);

          glNormal3d(budTip[tmpi][0], budTip[tmpi][1] * -1.0, 0.0);
          glVertex3d(budTip[tmpi][0], budTip[tmpi][1] * -1.0, 0.0);

          glNormal3d(budTip[ti][0], budTip[ti][1] * -1.0, 0.0);
          glVertex3d(budTip[ti][0], budTip[ti][1] * -1.0, 0.0);

          glNormal3d(budTip[ti][0], budTip[ti][1] * -1.0, 0.0);
          glVertex3d(budTip[ti][0], budTip[ti][1] * -1.0, 1.0);
          // REVERSE
          glVertex3d(budTip[ti][0], budTip[ti][1] * -1.0, 1.0);
          glVertex3d(budTip[ti][0], budTip[ti][1] * -1.0, 0.0);
          glVertex3d(budTip[tmpi][0], budTip[tmpi][1] * -1.0, 0.0);
          glVertex3d(budTip[tmpi][0], budTip[tmpi][1] * -1.0, 1.0);
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
  glColor3f(0.1,0.6,0.0);
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
        // REVERSE SIDE
        glNormal3d(budTip[tmpi][0], budTip[tmpi][1], 0.0);
        glVertex3d(budTip[tmpi][0], budTip[tmpi][1], budTip[ti][2]);

        glNormal3d(budTip[ti][0], budTip[ti][1], 0.0);
        glVertex3dv(budTip[ti]);

        glNormal3d(budTip[tmpi][0], budTip[tmpi][1], 0.0);
        glVertex3dv(budTip[tmpi]);

        // +Y SIDE
        
        glNormal3d(budTip[tmpi][0], budTip[tmpi][1] * -1.0, 0.0);
        glVertex3d(budTip[tmpi][0], budTip[tmpi][1] * -1.0, budTip[tmpi][2]);

        glNormal3d(budTip[tmpi][0], budTip[tmpi][1] * -1.0, 0.0);
        glVertex3d(budTip[tmpi][0], budTip[tmpi][1] * -1.0, budTip[ti][2]);

        glNormal3d(budTip[ti][0], budTip[ti][1] * -1.0, 0.0);
        glVertex3d(budTip[ti][0], budTip[ti][1] * -1.0, budTip[ti][2]);
        // REVERSE
        glNormal3d(budTip[ti][0], budTip[ti][1] * -1.0, 0.0);
        glVertex3d(budTip[ti][0], budTip[ti][1] * -1.0, budTip[ti][2]);

        glNormal3d(budTip[tmpi][0], budTip[tmpi][1] * -1.0, 0.0);
        glVertex3d(budTip[tmpi][0], budTip[tmpi][1] * -1.0, budTip[ti][2]);

        glNormal3d(budTip[tmpi][0], budTip[tmpi][1] * -1.0, 0.0);
        glVertex3d(budTip[tmpi][0], budTip[tmpi][1] * -1.0, budTip[tmpi][2]);
        
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
          // REVERSE
          glNormal3d(budTip[tmpi][0], budTip[tmpi][1], 0.0);
          glVertex3d(budTip[tmpi][0], budTip[tmpi][1], 0.0);

          glNormal3d(budTip[ti][0], budTip[ti][1], 0.0);
          glVertex3d(budTip[ti][0], budTip[ti][1], 0.0);

          glNormal3d(budTip[ti][0], budTip[ti][1], 0.0);
          glVertex3d(budTip[ti][0], budTip[ti][1], budTip[ti][2]);

          glNormal3d(budTip[tmpi][0], budTip[tmpi][1], 0.0);
          glVertex3d(budTip[tmpi][0], budTip[tmpi][1], budTip[ti][2]);

          // +Y SIDE
          glNormal3d(budTip[tmpi][0], budTip[tmpi][1] * -1.0, 0.0);
          glVertex3d(budTip[tmpi][0], budTip[tmpi][1] * -1.0, budTip[ti][2]);

          glNormal3d(budTip[tmpi][0], budTip[tmpi][1] * -1.0, 0.0);
          glVertex3d(budTip[tmpi][0], budTip[tmpi][1] * -1.0, 0.0);

          glNormal3d(budTip[ti][0], budTip[ti][1] * -1.0, 0.0);
          glVertex3d(budTip[ti][0], budTip[ti][1] * -1.0, 0.0);

          glNormal3d(budTip[ti][0], budTip[ti][1] * -1.0, 0.0);
          glVertex3d(budTip[ti][0], budTip[ti][1] * -1.0, budTip[ti][2]);
          // REVERSE
          glNormal3d(budTip[ti][0], budTip[ti][1] * -1.0, 0.0);
          glVertex3d(budTip[ti][0], budTip[ti][1] * -1.0, budTip[ti][2]);

          glNormal3d(budTip[ti][0], budTip[ti][1] * -1.0, 0.0);
          glVertex3d(budTip[ti][0], budTip[ti][1] * -1.0, 0.0);

          glNormal3d(budTip[tmpi][0], budTip[tmpi][1] * -1.0, 0.0);
          glVertex3d(budTip[tmpi][0], budTip[tmpi][1] * -1.0, 0.0);

          glNormal3d(budTip[tmpi][0], budTip[tmpi][1] * -1.0, 0.0);
          glVertex3d(budTip[tmpi][0], budTip[tmpi][1] * -1.0, budTip[ti][2]);

        glEnd();
      }
    }
  glEndList();
  return newList;
}

void drawPlant(plant p, GLuint *lst){
  bool variance;
  int currSeg,tmpi,i,j,sp;
  float age,newage,halfwidth;
  double **icp, curt,stepage,agescale,tmpscale;

  icp = (double **)malloc(sizeof(double *) * 4);
  for(tmpi=0;tmpi<4;tmpi++){
    icp[tmpi] = (double *)malloc(sizeof(double) * 3);
  }

  glPushMatrix();
  //printf("Drawing plant with %d segments\n",p.numOfSegments);
  for(currSeg = 1; currSeg < p.numOfSegments; currSeg++){
    halfwidth = p.segments[currSeg].width / 2.0;

    //++++++++++++++++++++++++++
    //   DRAW REGULAR SEGMENT
    //++++++++++++++++++++++++++
    if(p.segments[currSeg].age >= 16.0){
      glRotatef(p.segments[currSeg].theta,0.0,0.0,1.0);
      //agescale = (p.segments[currSeg].age //
      glRotatef(p.segments[currSeg].phi,0.0,1.0,0.0);
      glPushMatrix();
        glScalef(halfwidth,
               halfwidth,
               p.segments[currSeg].height);
        glCallList(lst[4]);
      glPopMatrix();
      glTranslatef(0.0,0.0,p.segments[currSeg].height - 0.1f);
      // Draw the leaf
      glPushMatrix();
        glTranslatef(halfwidth,0.0,0.0);
        tmpscale = -1.0 / p.segments[currSeg].leafscale;
        glScalef(p.segments[currSeg].leafscale, p.segments[currSeg].leafscale,p.segments[currSeg].leafscale);
        glBegin(GL_QUADS);
          glVertex3f(0.0,0.5f,0.0f);
          glVertex3f(0.0,-0.5f,0.0f);
          glVertex3f(halfwidth * tmpscale,-0.5f,
              (0.0f - (p.segments[currSeg].height * 0.2) / p.segments[currSeg].leafscale));
          glVertex3f(halfwidth * tmpscale,0.5f,
              (0.0f - (p.segments[currSeg].height * 0.2) / p.segments[currSeg].leafscale));

          glVertex3f(halfwidth * tmpscale,0.5f,
              (0.0f - (p.segments[currSeg].height * 0.2) / p.segments[currSeg].leafscale));
          glVertex3f(halfwidth * tmpscale,-0.5f,
              (0.0f - (p.segments[currSeg].height * 0.2) / p.segments[currSeg].leafscale));
          glVertex3f(0.0,-0.5f,0.0f);
          glVertex3f(0.0,0.5f,0.0f);


        glEnd();
        glPushMatrix();
          
          //glScalef(1.0,p.segments[currSeg].width,1.0);
          //drawBezierLeaf(p.segments[currSeg].leaf,21,0.1,3);
          for(i=0;i<4;i++){
            for(j=0;j<3;j++){
              icp[i][j] = (bezierSpine[4][i][j]);
            }
          }
          drawBezierLeafWithSpine(p.segments[currSeg].leaf,21,0.1,true,icp);
        glPopMatrix();
      glPopMatrix();
    }
    //++++++++++++++++++++++++++
    //    DRAW OUTTER LEAF
    //++++++++++++++++++++++++++
    else if(p.segments[currSeg].age >= 12.0){
      glRotatef(p.segments[currSeg].theta,0.0,0.0,1.0);
      stepage = p.segments[currSeg].age - 12.0;
      curt = stepage * 0.25;
      glRotatef(curt * p.segments[currSeg].phi,0.0,1.0,0.0);
      //glTranslated(0.0,0.0,(-1.0 + curt)*p.segments[currSeg].height); // shift down
      glPushMatrix();
      glScalef(halfwidth,
               halfwidth,
               (curt)*p.segments[currSeg].height);
       glCallList(lst[4]);
       glPopMatrix();
      if(stepage < 1.0){
        sp = 1;
        variance = false;
      }else if(stepage < 2.0){
        sp = 2;
        variance = false;
      }else if(stepage < 3.0){
        sp = 3;
        variance = true;
      }else{
        sp = 4;
        variance = true;
      }
      for(i=0;i<4;i++){
        for(j=0;j<3;j++){
          icp[i][j] = curt*(bezierSpine[sp][i][j] - bezierSpine[sp-1][i][j]) 
                            + bezierSpine[sp-1][i][j];
        }
      }
      glTranslatef(0.0,0.0,(curt)*p.segments[currSeg].height - 0.1f);
      glPushMatrix();
        glTranslatef(halfwidth,0.0,0.0);
        glScalef(p.segments[currSeg].leafscale, p.segments[currSeg].leafscale,p.segments[currSeg].leafscale);
        drawBezierLeafWithSpine(p.segments[currSeg].leaf,21,0.1,variance,icp);
      glPopMatrix();
      
    }
    //+++++++++++++++++++++++++++++
    //      DRAW MIDDLE LEAF
    //+++++++++++++++++++++++++++++
    else if(p.segments[currSeg].age >= 8.0){// Draw inner leaf
      stepage = p.segments[currSeg].age - 8.0;
      curt = stepage * 0.25;
      glRotatef(curt * p.segments[currSeg].theta,0.0,0.0,1.0);
      glPushMatrix();
      glScalef(halfwidth,halfwidth,(p.segments[currSeg].leafscale + 2.0f));
      switch( (int) stepage ) {
        case 0:
          glScalef(1.0,1.0,stepage / 2.0);
          glCallList(lst[0]);
          break;
        case 1:
          glScalef(1.0,1.0,stepage / 2.0);
          glCallList(lst[1]);
          break;
        case 2:
          glScalef(1.0,1.0,stepage / 2.0);
          glCallList(lst[2]);
          break;
        case 3:
          glScalef(1.0,1.0,stepage / 2.0);
          glCallList(lst[3]);
          break;
      }
      glPopMatrix();
    }
    //+++++++++++++++++++++++++++++
    //      DRAW INNER LEAF
    //+++++++++++++++++++++++++++++
    else if(p.segments[currSeg].age >= 4.0){ // draw bud / tassle
      stepage = p.segments[currSeg].age - 8.0;
      curt = stepage * 0.25;
      glRotatef(curt * p.segments[currSeg].theta,0.0,0.0,1.0);
      glPushMatrix();
        glScalef(halfwidth,halfwidth,p.segments[currSeg].leafscale);
        glCallList(lst[0]);
      glPopMatrix();
    }
    //+++++++++++++++++++++++++++++
    //           DRAW BUD
    //+++++++++++++++++++++++++++++
    else{
      stepage = p.segments[currSeg].age - 8.0;
      curt = stepage * 0.25;
      glRotatef(curt * p.segments[currSeg].theta,0.0,0.0,1.0);
      glPushMatrix();
        glScalef(halfwidth,halfwidth,p.segments[currSeg].leafscale * 0.5);
        glCallList(lst[0]);
        glRotatef(180.0,0.0,0.0,1.0);
        glScalef(0.5,0.5,0.5);
        glCallList(lst[0]);
        glRotatef(180.0,0.0,0.0,1.0);
        glScalef(0.5,0.5,0.5);
        glCallList(lst[0]);
      glPopMatrix();
    }
  }
  glPopMatrix();

  for(tmpi=0;tmpi<4;tmpi++){
    free(icp[tmpi]);
  }
  free(icp);
}

void drawBezierLeafWithSpine(double*** leaf, int segments, double dt, bool highVariance, double** spine){
  int i,j,k,seg3i,i3,i9;
  double scale;
  double t, seg3;
  double* prev,* res,* tmp, * prevspine, * resspine, *normal, *p1, *p2, *p3;
  double* prevB,* resB;
  prev = (double *)malloc(sizeof(double) * 3);
  res = (double *)malloc(sizeof(double) * 3);
  prevB = (double *)malloc(sizeof(double) * 3);
  resB = (double *)malloc(sizeof(double) * 3);
  prevspine = (double *)malloc(sizeof(double) * 3);
  resspine = (double *)malloc(sizeof(double) * 3);
  normal = (double *)malloc(sizeof(double) * 3);
  p1 = (double *)malloc(sizeof(double) * 3);
  p2 = (double *)malloc(sizeof(double) * 3);
  p3 = (double *)malloc(sizeof(double) * 3);


  scale = 0.5;

  if(highVariance){
    glBegin(GL_QUADS); 
    for(i=0;i<segments;i++){
      i3 = i*3;
      t = dt;
      bezier(leaf[0][i3],leaf[0][i3 + 1],leaf[0][i3 + 2],leaf[0][i3 + 3], 0.0, prev);
      bezier(leaf[1][i3],leaf[1][i3 + 1],leaf[1][i3 + 2],leaf[1][i3 + 3], 0.0, prevB);
  
      // Calculate spine
      //bezier(bezierSpine[age][0],bezierSpine[age][1],bezierSpine[age][2],bezierSpine[age][3], i/(segments*1.0), prevspine);
      bezier(spine[0],spine[1],spine[2],spine[3], (i)/(segments*1.0), prevspine);

      while(t <= 1.0){
        // far edge
        bezier(leaf[0][i3],leaf[0][i3 + 1],leaf[0][i3 + 2],leaf[0][i3 + 3], t, res);
        // near edge
        bezier(leaf[1][i3],leaf[1][i3 + 1],leaf[1][i3 + 2],leaf[1][i3 + 3], t, resB);
        //spine
        //bezier(bezierSpine[age][0],bezierSpine[age][1],bezierSpine[age][2],bezierSpine[age][3], (i + t)/(segments*1.0), resspine);
        bezier(spine[0],spine[1],spine[2],spine[3], (i + t)/(segments*1.0), resspine);

        glColor3f(0.1,0.6,0.0);

        // draw line far
        p1[0] = resspine[0];
        p1[1] = res[1];
        p1[2] = res[2] + resspine[2];

        p2[0] = prevspine[0];
        p2[1] = prev[1];
        p2[2] = prev[2] + prevspine[2];

        p3[0] = prevspine[0];
        p3[1] = 0.0;
        p3[2] = prevspine[2];

        calcNormal(p1,p2,p3,normal);

        glNormal3dv(normal);
        //glVertex3dv(resspine[0],res[1],res[2] + resspine[2]);
        //glVertex3dv(prevspine[0],prev[1],prev[2] + prevspine[2]);
        //glVertex3dv(prevspine[0],0.0,prevspine[2]);
        glVertex3dv(p1);
        glVertex3dv(p2);
        glVertex3dv(p3);
        glVertex3d(resspine[0],0.0,resspine[2]);
        
        calcNormal(p1,p3,p2,normal);
        glNormal3dv(normal);
        glVertex3d(resspine[0],0.0,resspine[2]);
        glVertex3dv(p3);
        glVertex3dv(p2);
        glVertex3dv(p1);
        
        // draw line near
        p1[0] = resspine[0];
        p1[1] = 0.0;
        p1[2] = resspine[2];

        p2[0] = prevspine[0];
        p2[1] = 0.0;
        p2[2] = prevspine[2];

        p3[0] = prevspine[0];
        p3[1] = prevB[1];
        p3[2] = prevB[2] + prevspine[2];

        calcNormal(p1,p2,p3,normal);
        glNormal3dv(normal);
        //glVertex3d(resspine[0],0.0,resspine[2]);
        //glVertex3d(prevspine[0],0.0,prevspine[2]);
        //glVertex3d(prevspine[0],prevB[1],prevB[2] + prevspine[2]);
        glVertex3dv(p1);
        glVertex3dv(p2);
        glVertex3dv(p3);
        glVertex3d(resspine[0],resB[1],resB[2] + resspine[2]);

        calcNormal(p1,p3,p2,normal);
        glNormal3dv(normal);
        glVertex3d(resspine[0],resB[1],resB[2] + resspine[2]);
        glVertex3dv(p3);
        glVertex3dv(p2);
        glVertex3dv(p1);


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
    glBegin(GL_QUADS); 
    seg3i = segments / 3;
    seg3 = segments / 3.0;
    for(i=0;i< seg3i ;i++){
      i9 = i*9;
      t = dt;
      
      beziersz(leaf[0][i9],leaf[0][i9 + 3],leaf[0][i9 + 6],leaf[0][i9 + 9], 0.0, prev
        ,scale);
      beziersz(leaf[1][i9],leaf[1][i9 + 3],leaf[1][i9 + 6],leaf[1][i9 + 9], 0.0, prevB
        ,scale);
      
  
      // Calculate spine
      //bezier(bezierSpine[age][0],bezierSpine[age][1],bezierSpine[age][2],bezierSpine[age][3], i/(seg3), prevspine);
      bezier(spine[0],spine[1],spine[2],spine[3], (i)/(seg3), prevspine);

      while(t <= 1.0){
        // far edge
        beziersz(leaf[0][i9],leaf[0][i9 + 3],leaf[0][i9 + 6],leaf[0][i9 + 9], t, res
          ,scale);
        // near edge
        beziersz(leaf[1][i9],leaf[1][i9 + 3],leaf[1][i9 + 6],leaf[1][i9 + 9], t, resB
          ,scale);
        //spine
        //bezier(bezierSpine[age][0],bezierSpine[age][1],bezierSpine[age][2],bezierSpine[age][3], (i + t)/(seg3), resspine);
        bezier(spine[0],spine[1],spine[2],spine[3], (i + t)/(seg3), resspine);


        //glColor3f(0.3,0.8,0.0);

        
        glColor3f(0.1,0.6,0.0);

        // draw line far
        p1[0] = resspine[0];
        p1[1] = res[1];
        p1[2] = res[2] + resspine[2];

        p2[0] = prevspine[0];
        p2[1] = prev[1];
        p2[2] = prev[2] + prevspine[2];

        p3[0] = prevspine[0];
        p3[1] = 0.0;
        p3[2] = prevspine[2];

        calcNormal(p1,p2,p3,normal);

        glNormal3dv(normal);
        //glVertex3dv(resspine[0],res[1],res[2] + resspine[2]);
        //glVertex3dv(prevspine[0],prev[1],prev[2] + prevspine[2]);
        //glVertex3dv(prevspine[0],0.0,prevspine[2]);
        glVertex3dv(p1);
        glVertex3dv(p2);
        glVertex3dv(p3);
        glVertex3d(resspine[0],0.0,resspine[2]);
        
        calcNormal(p1,p3,p2,normal);
        glNormal3dv(normal);
        glVertex3d(resspine[0],0.0,resspine[2]);
        glVertex3dv(p3);
        glVertex3dv(p2);
        glVertex3dv(p1);
        
        // draw line near
        p1[0] = resspine[0];
        p1[1] = 0.0;
        p1[2] = resspine[2];

        p2[0] = prevspine[0];
        p2[1] = 0.0;
        p2[2] = prevspine[2];

        p3[0] = prevspine[0];
        p3[1] = prevB[1];
        p3[2] = prevB[2] + prevspine[2];

        calcNormal(p1,p2,p3,normal);
        glNormal3dv(normal);
        //glVertex3d(resspine[0],0.0,resspine[2]);
        //glVertex3d(prevspine[0],0.0,prevspine[2]);
        //glVertex3d(prevspine[0],prevB[1],prevB[2] + prevspine[2]);
        glVertex3dv(p1);
        glVertex3dv(p2);
        glVertex3dv(p3);
        glVertex3d(resspine[0],resB[1],resB[2] + resspine[2]);

        calcNormal(p1,p3,p2,normal);
        glNormal3dv(normal);
        glVertex3d(resspine[0],resB[1],resB[2] + resspine[2]);
        glVertex3dv(p3);
        glVertex3dv(p2);
        glVertex3dv(p1);
        

        /*
        glVertex3d(prevspine[0],prevspine[1],prevspine[2]);
        glVertex3d(resspine[0],resspine[1],resspine[2]);

        glColor3f(0.1,0.6,0.0);
        */

        /*
        glVertex3d(resspine[0],res[1],res[2] + resspine[2]);
        glVertex3d(prevspine[0],prev[1],prev[2] + prevspine[2]);
        glVertex3d(prevspine[0],0.0,prevspine[2]);
        glVertex3d(resspine[0],0.0,resspine[2]);
        
        // draw line near
        glVertex3d(resspine[0],0.0,resspine[2]);
        glVertex3d(prevspine[0],0.0,prevspine[2]);
        glVertex3d(prevspine[0],prevB[1],prevB[2] + prevspine[2]);
        glVertex3d(resspine[0],resB[1],resB[2] + resspine[2]);
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
  }
  free(prev);// = (double *)malloc(sizeof(double) * 3);
  free(res);// = (double *)malloc(sizeof(double) * 3);
  free(prevB);// = (double *)malloc(sizeof(double) * 3);
  free(resB);// = (double *)malloc(sizeof(double) * 3);
  free(prevspine);// = (double *)malloc(sizeof(double) * 3);
  free(resspine);// = (double *)malloc(sizeof(double) * 3);
  free(p1);
  free(p2);
  free(p3);
}




/*


};
*/

GLuint createLeafLists(int step){
  int ti,tj,tmpi,i,j;
  double leafStep[6][3] = {
    {-0.866,-0.500,0.0},
    {-0.500,-0.866,0.447},
    {-0.000,-1.000,0.663},
    {0.500,-0.866,0.806},
    {0.866,-0.500,0.913},
    {1.000,0.000,1.000000}
  };

  switch(step){
    case 0:
      i = 5;
      break;
    case 1:
      for(i=0;i<5;i++){
        for(j=0;j<3;j++){
          leafStep[i][j] = leafStepB[i][j];
        }
      }
      i = 4;
      break;
    case 2:
      for(i=0;i<3;i++){
        for(j=0;j<3;j++){
          leafStep[i][j] = leafStepC[i][j];
        }
      }
      i = 2;
      break;
  }
  GLuint newList;
  newList = glGenLists(1);
  glNewList(newList, GL_COMPILE);
    for(ti=0;ti<i;ti++){
      tmpi = ti + 1;
      glBegin(GL_TRIANGLES);
        // -Y SIDE
        glNormal3d(leafStep[tmpi][0], leafStep[tmpi][1], 0.0);
        glVertex3dv(leafStep[tmpi]);

        glNormal3d(leafStep[ti][0], leafStep[ti][1], 0.0);
        glVertex3dv(leafStep[ti]);

        glNormal3d(leafStep[tmpi][0], leafStep[tmpi][1], 0.0);
        glVertex3d(leafStep[tmpi][0], leafStep[tmpi][1], leafStep[ti][2]);
        // REVERSE
        glNormal3d(leafStep[tmpi][0], leafStep[tmpi][1], 0.0);
        glVertex3d(leafStep[tmpi][0], leafStep[tmpi][1], leafStep[ti][2]);

        glNormal3d(leafStep[ti][0], leafStep[ti][1], 0.0);
        glVertex3dv(leafStep[ti]);

        glNormal3d(leafStep[tmpi][0], leafStep[tmpi][1], 0.0);
        glVertex3dv(leafStep[tmpi]);

        // +Y SIDE
        
        glNormal3d(leafStep[tmpi][0], leafStep[tmpi][1] * -1.0, 0.0);
        glVertex3d(leafStep[tmpi][0], leafStep[tmpi][1] * -1.0, leafStep[tmpi][2]);

        glNormal3d(leafStep[tmpi][0], leafStep[tmpi][1] * -1.0, 0.0);
        glVertex3d(leafStep[tmpi][0], leafStep[tmpi][1] * -1.0, leafStep[ti][2]);

        glNormal3d(leafStep[ti][0], leafStep[ti][1] * -1.0, 0.0);
        glVertex3d(leafStep[ti][0], leafStep[ti][1] * -1.0, leafStep[ti][2]);
        // REVERSE
        glNormal3d(leafStep[ti][0], leafStep[ti][1] * -1.0, 0.0);
        glVertex3d(leafStep[ti][0], leafStep[ti][1] * -1.0, leafStep[ti][2]);

        glNormal3d(leafStep[tmpi][0], leafStep[tmpi][1] * -1.0, 0.0);
        glVertex3d(leafStep[tmpi][0], leafStep[tmpi][1] * -1.0, leafStep[ti][2]);

        glNormal3d(leafStep[tmpi][0], leafStep[tmpi][1] * -1.0, 0.0);
        glVertex3d(leafStep[tmpi][0], leafStep[tmpi][1] * -1.0, leafStep[tmpi][2]);
        
      glEnd();
      if(ti > 0){
        glBegin(GL_QUADS);
          // -Y SIDE
          glNormal3d(leafStep[tmpi][0], leafStep[tmpi][1], 0.0);
          glVertex3d(leafStep[tmpi][0], leafStep[tmpi][1], leafStep[ti][2]);

          glNormal3d(leafStep[ti][0], leafStep[ti][1], 0.0);
          glVertex3d(leafStep[ti][0], leafStep[ti][1], leafStep[ti][2]);

          glNormal3d(leafStep[ti][0], leafStep[ti][1], 0.0);
          glVertex3d(leafStep[ti][0], leafStep[ti][1], 0.0);

          glNormal3d(leafStep[tmpi][0], leafStep[tmpi][1], 0.0);
          glVertex3d(leafStep[tmpi][0], leafStep[tmpi][1], 0.0);
          // REVERSE SIDE
          glNormal3d(leafStep[tmpi][0], leafStep[tmpi][1], 0.0);
          glVertex3d(leafStep[tmpi][0], leafStep[tmpi][1], 0.0);

          glNormal3d(leafStep[ti][0], leafStep[ti][1], 0.0);
          glVertex3d(leafStep[ti][0], leafStep[ti][1], 0.0);

          glNormal3d(leafStep[ti][0], leafStep[ti][1], 0.0);
          glVertex3d(leafStep[ti][0], leafStep[ti][1], leafStep[ti][2]);

          glNormal3d(leafStep[tmpi][0], leafStep[tmpi][1], 0.0);
          glVertex3d(leafStep[tmpi][0], leafStep[tmpi][1], leafStep[ti][2]);


          // +Y SIDE
          glNormal3d(leafStep[tmpi][0], leafStep[tmpi][1] * -1.0, 0.0);
          glVertex3d(leafStep[tmpi][0], leafStep[tmpi][1] * -1.0, leafStep[ti][2]);

          glNormal3d(leafStep[tmpi][0], leafStep[tmpi][1] * -1.0, 0.0);
          glVertex3d(leafStep[tmpi][0], leafStep[tmpi][1] * -1.0, 0.0);

          glNormal3d(leafStep[ti][0], leafStep[ti][1] * -1.0, 0.0);
          glVertex3d(leafStep[ti][0], leafStep[ti][1] * -1.0, 0.0);

          glNormal3d(leafStep[ti][0], leafStep[ti][1] * -1.0, 0.0);
          glVertex3d(leafStep[ti][0], leafStep[ti][1] * -1.0, leafStep[ti][2]);

          // REVERSE SIDE
          glNormal3d(leafStep[ti][0], leafStep[ti][1] * -1.0, 0.0);
          glVertex3d(leafStep[ti][0], leafStep[ti][1] * -1.0, leafStep[ti][2]);

          glNormal3d(leafStep[ti][0], leafStep[ti][1] * -1.0, 0.0);
          glVertex3d(leafStep[ti][0], leafStep[ti][1] * -1.0, 0.0);

          glNormal3d(leafStep[tmpi][0], leafStep[tmpi][1] * -1.0, 0.0);
          glVertex3d(leafStep[tmpi][0], leafStep[tmpi][1] * -1.0, 0.0);

          glNormal3d(leafStep[tmpi][0], leafStep[tmpi][1] * -1.0, 0.0);
          glVertex3d(leafStep[tmpi][0], leafStep[tmpi][1] * -1.0, leafStep[ti][2]);
        glEnd();
      }
    }
  glEndList();
  return newList;
}





/****************************************
 *             DEPRECATED               *
 ****************************************/
void drawBezierLeaf(double*** leaf, int segments, double dt, int age){
  int i,j,k,seg3i;
  double scale;
  double t, seg3;
  double* prev,* res,* tmp, * prevspine, * resspine, *normal, *p1, *p2, *p3;
  double* prevB,* resB;
  prev = (double *)malloc(sizeof(double) * 3);
  res = (double *)malloc(sizeof(double) * 3);
  prevB = (double *)malloc(sizeof(double) * 3);
  resB = (double *)malloc(sizeof(double) * 3);
  prevspine = (double *)malloc(sizeof(double) * 3);
  resspine = (double *)malloc(sizeof(double) * 3);
  normal = (double *)malloc(sizeof(double) * 3);
  p1 = (double *)malloc(sizeof(double) * 3);
  p2 = (double *)malloc(sizeof(double) * 3);
  p3 = (double *)malloc(sizeof(double) * 3);


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
        p1[0] = resspine[0];
        p1[1] = res[1];
        p1[2] = res[2] + resspine[2];

        p2[0] = prevspine[0];
        p2[1] = prev[1];
        p2[2] = prev[2] + prevspine[2];

        p3[0] = prevspine[0];
        p3[1] = 0.0;
        p3[2] = prevspine[2];

        calcNormal(p1,p2,p3,normal);

        glNormal3dv(normal);
        //glVertex3dv(resspine[0],res[1],res[2] + resspine[2]);
        //glVertex3dv(prevspine[0],prev[1],prev[2] + prevspine[2]);
        //glVertex3dv(prevspine[0],0.0,prevspine[2]);
        glVertex3dv(p1);
        calcNormal(p2,p3,p1,normal);
        glNormal3dv(normal);
        glVertex3dv(p2);
        calcNormal(p3,p1,p2,normal);
        glNormal3dv(normal);
        glVertex3dv(p3);
        glVertex3d(resspine[0],0.0,resspine[2]);
        
        
        calcNormal(p3,p2,p1,normal);
        glNormal3dv(normal);
        glVertex3d(resspine[0],0.0,resspine[2]);
        glVertex3dv(p3);
        glVertex3dv(p2);
        calcNormal(p1,p3,p2,normal);
        glNormal3dv(normal);
        glVertex3dv(p1);
        
        // draw line near
        p1[0] = resspine[0];
        p1[1] = 0.0;
        p1[2] = resspine[2];

        p2[0] = prevspine[0];
        p2[1] = 0.0;
        p2[2] = prevspine[2];

        p3[0] = prevspine[0];
        p3[1] = prevB[1];
        p3[2] = prevB[2] + prevspine[2];

        calcNormal(p1,p2,p3,normal);
        glNormal3dv(normal);
        //glVertex3d(resspine[0],0.0,resspine[2]);
        //glVertex3d(prevspine[0],0.0,prevspine[2]);
        //glVertex3d(prevspine[0],prevB[1],prevB[2] + prevspine[2]);
        glVertex3dv(p1);
        glVertex3dv(p2);
        glVertex3dv(p3);
        glVertex3d(resspine[0],resB[1],resB[2] + resspine[2]);

        calcNormal(p1,p3,p2,normal);
        glNormal3dv(normal);
        glVertex3d(resspine[0],resB[1],resB[2] + resspine[2]);
        glVertex3dv(p3);
        glVertex3dv(p2);
        glVertex3dv(p1);

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
