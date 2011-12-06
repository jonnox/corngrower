#include <stdio.h>
#include <time.h>
#include "glplantutils.h"
#include "textfile.h"
#include <Windows.h>

/**
 * An openGL corn grower
 * This file was created and compiled using MS Visual Studio
 *
 * @author Jon Elliott - 100174454
 */

void reshape(int w, int h);
void reDraw();
void resetAll();
void shaders_cleanup();

POINT ptCursorPos;
int cX,cY;

int prevMouseX, prevMouseY, numOfPlants;

float theta = 0.0;
float thetalr,thetaud;

float *rndTheta;

// FRAGMENT SHADER
GLuint shader_v, shader_f, shader_f2, shaderprogram_p, normal_texture;

GLuint leafList, budList, planeList, trunkList;
GLuint *plantLists;


/**
 * Coordinates of the camera. Default is 10,10,10.
 */
float cameraCoords[3] = {15.0,15.0,0.0};
float lookAt[3] = {0.0,0.0,0.0};

short click = 0;

/**
 * Degree of bezier curve
 */
int n = 3;
int vidStep = 0;

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
   disLists[1] = createLeafLists(0);
   disLists[2] = createLeafLists(1);
   disLists[3] = createLeafLists(2);
   disLists[4] = createSegList();
   //----------------------
}

static void timerCallBack(int value){

  updatePlant(plants[0],0.5f);
        if(value > 200){
          if(theta > 360.0)
            theta = 0.0;
          theta += 4.0;
        }else if(value > 120){
          cameraCoords[1] += 2.0f;
          cameraCoords[0] += 2.0f;
          lookAt[2] -= 0.5f;
          if(theta > 360.0)
            theta = 0.0;
          theta += 2.0;
          value++;
        }else if(value > 40){
          cameraCoords[2] += 1.8f;
          lookAt[2] += 1.7f;
          value++;
          cameraCoords[1] += 0.5f;
          cameraCoords[0] += 0.5f;
        }else if(value > 10){
          cameraCoords[2] += 0.8f;
          lookAt[2] += 0.7f;
          value++;
        }else{
          cameraCoords[2] += 1.0f;
          lookAt[2] += 0.3f;
          value++;
        }
        reDraw();
}

void display(void)
{
  int i = 0,j,k;
  float *ptr;
  double ** icp;
  icp = (double **)malloc(sizeof(double *) * 4);

  glClear (GL_COLOR_BUFFER_BIT);
  glLoadIdentity ();
  gluLookAt(cameraCoords[0],cameraCoords[1],cameraCoords[2],
    lookAt[0], lookAt[1], lookAt[2], 0.0, 0.0, 1.0);
  //gluLookAt(10.0,10.0,4.0, 0.0, 0.0, 2.0, 0.0, 0.0, 1.0);
  
  glRotatef(theta,0.0,0.0,1.0);

  drawPlant(plants[0],disLists);
  
  //++++++++++++++++++++++++
  // CORN FIELD EXAMPLE
  //++++++++++++++++++++++++
  /*
  glScalef(0.1,0.1,0.1);
  for(i=0;i < (numOfPlants / 20);i++){
    glTranslatef(rndTheta[i + 1],-80.0 + rndTheta[i],0.0);
    glPushMatrix();
    glTranslatef(-400.0,0.0,0.0);
    for(j=0;j<10;j++){
          glTranslatef(80.0 + rndTheta[i+j],0.0,0.0);
          glPushMatrix();
            glRotatef(rndTheta[i+j],0.0,0.0,1.0);
            glCallList(plantLists[i + j]);
          glPopMatrix();
    }
    glPopMatrix();
  }
  */

  /*
  //++++++++++++++++++++++++
  // LEAF EXAMPLE
  //++++++++++++++++++++++++
  icp = (double **)malloc(sizeof(double *) * 4);
  for(i=0;i<4;i++){
        icp[i] = (double *)malloc(sizeof(double) * 3);
  }

  glPushMatrix();
  glTranslatef(-15.0,-15.0,-5.0);
  for(k=0;k<5;k++){
    glTranslatef(5.0,5.0,0.0);
      for(i=0;i<4;i++){
        for(j=0;j<3;j++){
          icp[i][j] = bezierSpine[k][i][j];
        }
      }
      drawBezierLeafWithSpine(plants[0].segments[0].leaf, 21, 0.1, false, icp);
  }
  glPopMatrix();

  glRotatef(180,0.0,0.0,1.0);

  glPushMatrix();
  glTranslatef(-15.0,-15.0,5.0);
  for(k=0;k<5;k++){
    glTranslatef(5.0,5.0,0.0);
      for(i=0;i<4;i++){
        for(j=0;j<3;j++){
          icp[i][j] = bezierSpine[k][i][j];
        }
      }
      drawBezierLeafWithSpine(plants[0].segments[0].leaf, 21, 0.1, false, icp);
  }
  glPopMatrix();
  */

  glutSwapBuffers();
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

void MouseUpdate(){
  GetCursorPos(&ptCursorPos);
  (ptCursorPos.x - cX);
  SetCursorPos(cX,cY);
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
   gluPerspective(fov, (GLfloat)w / (GLfloat)h, 1.0, 380.0);
   //gluOrtho2D(-30.0,30.0,-30.0,30.0);
   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity();
   _w = w;
   _h = h;
}

void keyboard(unsigned char key, int x, int y)
{
  int i;
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
        updatePlant(plants[0],0.5f);
        if(vidStep > 200){
          if(theta > 360.0)
            theta = 0.0;
          theta += 4.0;
          vidStep++;
        }else if(vidStep > 120){
          //cameraCoords[2] -= 1.8f;
          cameraCoords[1] += 2.0f;
          cameraCoords[0] += 2.0f;
          //lookAt[2] -= 0.3f;
          if(theta > 360.0)
            theta = 0.0;
          theta += 2.0;
          vidStep++;
        }else if(vidStep > 40){
          cameraCoords[2] += 1.8f;
          lookAt[2] += 1.7f;
          //printf("%d\n",vidStep);
          vidStep++;
          cameraCoords[1] += 0.5f;
          cameraCoords[0] += 0.5f;
        }else if(vidStep > 10){
          cameraCoords[2] += 0.8f;
          lookAt[2] += 0.7f;
          //printf("%d\n",vidStep);
          vidStep++;
        }else{
          cameraCoords[2] += 1.0f;
          lookAt[2] += 0.3f;
          vidStep++;
        }
        reDraw();
        break;
      case 44:
        for(i=0;i< numOfPlants ; i++){
          updatePlant(plants[i],0.5f);
        }
        break;
      case 119: //w
        cameraCoords[1] -= 2.0f;
        //cameraCoords[0] -= 2.0f;
        reDraw();
        break;
      case 115: //s
        cameraCoords[1] += 2.0f;
        //cameraCoords[0] += 2.0f;
        reDraw();
        break;
      case 101: //e
        lookAt[2] += 2.0f;
        reDraw();
        break;
      case 100: //d
        lookAt[2] -= 2.0f;
        reDraw();
        break;
      case 114: //r
        cameraCoords[2] += 2.0f;
        reDraw();
        break;
      case 102://f
        cameraCoords[2] -= 2.0f;
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

void mouse(int button, int state, int x, int y){
  //printf("button:%d state:%d x:%d y:%d\n",button,state,x,y);
  if(state == GLUT_DOWN){
    prevMouseX = x;
    prevMouseY = y;
  }
}

/**
 * Activates when mouse is clicked and dragged
 */
void mousemove(int x, int y){
  //printf("(Drag x:%d y:%d)",x,y);
  thetalr = (float)(x - prevMouseX);
  thetaud = (float)(x - prevMouseY);
  reDraw();
}

void shaders_cleanup()
{
	glDetachShader(shaderprogram_p, shader_v);
	glDetachShader(shaderprogram_p, shader_f);
	glDetachShader(shaderprogram_p, shader_f2);
}


void shaders_setup() 
{
	shader_v = glCreateShader(GL_VERTEX_SHADER);
	shader_f = glCreateShader(GL_FRAGMENT_SHADER);
	shader_f2 = glCreateShader(GL_FRAGMENT_SHADER);

	//char *shadersource_v=NULL, *shadersource_f=NULL, *shadersource_f2=NULL;
	const char * shadersource_v = (const char*) textFileRead("toon.vert");
	const char * shadersource_f = (const char*) textFileRead("toon.frag");
	//const char * shadersource_f2 = (const char*) textFileRead("toon2.frag");
	glShaderSource(shader_v, 1, &shadersource_v, NULL);
	glShaderSource(shader_f, 1, &shadersource_f, NULL);
	//glShaderSource(shader_f2, 1, &shadersource_f2, NULL);

	free((void*) shadersource_v);
	free((void*) shadersource_f);
	//free((void*) shadersource_f2);

	glCompileShader(shader_v);
	glCompileShader(shader_f);
	//glCompileShader(shader_f2);

	shaderprogram_p = glCreateProgram();
	glAttachShader(shaderprogram_p,shader_f);
	//glAttachShader(shaderprogram_p,shader_f2);
	glAttachShader(shaderprogram_p,shader_v);

	glLinkProgram(shaderprogram_p);
	glUseProgram(shaderprogram_p);
}

int main(int argc, char** argv)
{
  float *** test;
  int i,j,k;
  segment seg;
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_ACCUM);
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

   glutMouseFunc(mouse);
   glutMotionFunc(mousemove);

   glEnable(GL_DEPTH_TEST);
   glEnable(GL_CULL_FACE);

   glewInit();
   shaders_setup();

   /*
   //++++++++++++++++++++++++
  // CORN FIELD EXAMPLE
  //++++++++++++++++++++++++
   numOfPlants = 200;
   plantLists = (GLuint *)malloc(sizeof(GLuint) * numOfPlants);
   rndTheta = (float *)malloc(sizeof(float) * numOfPlants);
   plants = (plant *)malloc(sizeof(plant) * numOfPlants);
   for(i=0;i<numOfPlants;i++){
      plants[i] = newPlant(2.0,1.0,7.0,0.1,0.1,20);
      while(updatePlant(plants[i],0.1f)){
      }
      plantLists[i] = createPlantList(plants[i],disLists);
      rndTheta[i] = (rand() % 100) * 0.1f - 5.0f;
   }
   */

   //++++++++++++++++++++++++
  // SINGLE GORWING EXAMPLE
  //++++++++++++++++++++++++
  plants = (plant *)malloc(sizeof(plant));
  plants[0] = newPlant(2.0,1.0,7.0,0.1,0.1,20);
  cameraCoords[2] = 30.0;



   int cX = GetSystemMetrics(SM_CXSCREEN);
   int cY = GetSystemMetrics(SM_CYSCREEN);

   /*
    * Print welcome message
    */
     printf("Welcome to Corn Grower\n");
     printf(" By: Jon Elliott\n");
     //glutTimerFunc(1000, timerCallback,0);
   glutMainLoop();
   return 0;
}
