#include <stdio.h>
#include <time.h>
#include "glplantutils.h"

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

GLUquadric *qobj;

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

void init(void) 
{
   int i = 0;
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
   glEnable(GL_DEPTH_TEST);

   //----------------------
   // CREATE DISPLAY LISTS
   //----------------------
   disLists = (GLuint *)malloc(sizeof(GLuint) * 8);
   disLists[0] = createBudList();
   disLists[1] = createSegList();
   //----------------------
}

void display(void)
{
  int i = 0;
  float *ptr;
  glClear (GL_COLOR_BUFFER_BIT);
  glLoadIdentity ();
  gluLookAt(80.0, 80.0, 20.0, 0.0, 0.0, 20.0, 0.0, 0.0, 1.0);
  
  glRotatef(theta,0.0,0.0,1.0);


  
  glColor3f(0.9,0.3,0.3);
  //glScaled(10.0,10.0,20.0);
  //glCallList(budList);
  //glCallList(segList);
  //drawBezierLeaf(cornleaf, 21, 0.1, 0);
  

  drawPlant(plants[0],disLists);

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
   gluPerspective(fov, (GLfloat)w / (GLfloat)h, 1.0, 180.0);
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
      case 46: //.
        updatePlant(plants[0],1.0f);
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
   // Set up openGL objects
   qobj = gluNewQuadric();

   srand( time(NULL) );
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMouseFunc(mouseClick);

   seg = newSegment(1.0f, 1.0f, 0.0f, 0.0f, 1.0f);
   plants = (plant *)malloc(sizeof(plant));
   plants[0] = newPlant(2.0,1.0,7.0,0.15,0.15,20);
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

/*
static double budTip[7][3] = {
    {-1.000,0.000,0.000000},
    {-0.866,-0.500,0.397940},
    {-0.500,-0.866,0.602060},
    {-0.000,-1.000,0.740363},
    {0.500,-0.866,0.845098},
    {0.866,-0.500,0.929419},
    {1.000,0.000,1.000000}
};*/


