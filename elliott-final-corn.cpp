#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>
#include "cornplant.h"

/**
 * An openGL corn grower
 * This file was created and compiled using MS Visual Studio
 *
 * @author Jon Elliott - 100174454
 */

void reshape(int w, int h);
void reDraw();
void resetAll();

float theta = 0.0;

/**
 * Coordinates of the camera. Default is 10,10,10.
 */
float cameraCoords[3] = {10.0,10.0,10.0};

short click = 0;

/**
 * Degree of bezier curve
 */
int n = 3;

double*** cornleaf;
double*** cornleafB;

plant* plants;

/**
 * Step for curve rendering
 */
float t = 0.1;

/**
 * Field of view (in degrees)
 */
int fov = 45;

// window width and height
int _w=0,_h=0;

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

void init(void) 
{
   int i = 0;
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
   glEnable(GL_DEPTH_TEST);
}

void display(void)
{
  int i = 0;
  float *ptr;
  glClear (GL_COLOR_BUFFER_BIT);
  glLoadIdentity ();
  gluLookAt(20.0, 20.0, 10.0, 0.0, 0.0, 5.0, 0.0, 0.0, 1.0);

  glRotatef(theta,0.0,0.0,1.0);

  glColor3f(0.9,0.3,0.3); 

  drawBezierLeaf(cornleaf, 21, 0.1, 0);

  glRotatef(90.0,0.0,0.0,1.0);
  drawBezierLeaf(cornleaf, 21, 0.1, 1);

  glRotatef(90.0,0.0,0.0,1.0);
  drawBezierLeaf(cornleaf, 21, 0.1, 2);

  glRotatef(90.0,0.0,0.0,1.0);
  drawBezierLeaf(cornleaf, 21, 0.1, 3);

  glTranslatef(0.0,0.0,5.0);
  glRotatef(90.0,0.0,0.0,1.0);

  drawBezierLeaf(cornleafB, 21, 0.1, 0);

  glRotatef(90.0,0.0,0.0,1.0);
  drawBezierLeaf(cornleafB, 21, 0.1, 1);

  glRotatef(90.0,0.0,0.0,1.0);
  drawBezierLeaf(cornleafB, 21, 0.1, 2);

  glRotatef(90.0,0.0,0.0,1.0);
  drawBezierLeaf(cornleafB, 21, 0.1, 3);

  glFlush();
}

/**
 * Increases the field of view by 5 degress with a
 * maximum of 120 degrees
 */
void incFOV(){
  if (fov < 120){
    fov = fov + 5;
    reDraw(); // Redraw the objects in the window
  }
}

/**
 * Decreases the field of view by 5 degress with a
 * minimum of 10 degrees
 */
void decFOV(){
  if (fov > 10){
    fov = fov - 5;
    reDraw(); // Redraw the objects in the window
  }
}

/**
 * Clears the contents of the screen, positions the viewing
 * matricies and redraws the objects
 */
void reDraw(){
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   reshape(_w,_h);
   display();
}

/**
 * Positiones the camera at (10,10,10), sets the camera's apperature to 0.0,
 * sets the field of view to 45 degrees and redraws the scene
 */
void resetAll(){
  cameraCoords[0] = 0.0;
  cameraCoords[1] = 0.0;
  cameraCoords[2] = 10.0;
  fov = 45;
  reDraw();
}

/**
 * Maintains the correct aspect ratio of the elements on a changed window size
 */
void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(fov, (GLfloat)w / (GLfloat)h, 1.0, 80.0);
   //gluOrtho2D(-30.0,30.0,-30.0,30.0);
   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity();
   _w = w;
   _h = h;
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27: //Esc
         exit(0);
         break;
      case 122: //z
        incFOV();
        break;
      case 120: //x
        decFOV();
        break;
      case 113: //q
        exit(0);
        break;
      case 108: //l
        if(theta > 360.0)
          theta = 0.0;
        theta += 1.0;
        reDraw();
        break;
      default:
        printf("%c-%d\n",key,key);
        break;
   }
   //printf("%c-%d\n",key,key);
}

/**
 * When mouse is clicked
 *
 * button: GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON
 * state: GLUT_UP, GLUT_DOWN
 */
void mouseClick(int button, int state, int x, int y){
  if(button == GLUT_LEFT_BUTTON){
    if(n<6 && click == 0){
      n++;
      reDraw();
      click += 1;
    }else{
      click = 0;
    }
  }
}


int main(int argc, char** argv)
{
  float *** test;
  segment seg;
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_ACCUM);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMouseFunc(mouseClick);

   seg = newSegment(1.0f, 1.0f, 0.0f, 0.0f, 1.0f);
   plants = (plant *)malloc(sizeof(plant));
   plants[0] = newPlant(2.0,2.0,3.0,1.0,1.0,20);
   cornleaf = plants[0].segments[0].leaf;

   cornleafB = createLeaf(21);


   /*
    * Print welcome message
    */
     printf("Welcome to Corn Grower\n");
     printf(" By: Jon Elliott\n");
   glutMainLoop();
   return 0;
}