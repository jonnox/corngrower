#include <stdio.h>
#include <time.h>
#include "glplantutils.h"
#include "textfile.h"

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

int prevMouseX, prevMouseY;

float theta = 0.0;
float thetalr,thetaud;

// FRAGMENT SHADER
GLuint shader_v, shader_f, shader_f2, shaderprogram_p, normal_texture;

GLuint leafList, budList, planeList, trunkList;


/**
 * Coordinates of the camera. Default is 10,10,10.
 */
float cameraCoords[3] = {40.0,40.0,40.0};

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
  gluLookAt(cameraCoords[0],cameraCoords[1],cameraCoords[2], 0.0, 0.0, 40.0, 0.0, 0.0, 1.0);
  
  glRotatef(theta,0.0,0.0,1.0);


  
  glColor3f(0.9,0.3,0.3);
  //glScaled(10.0,10.0,20.0);
  //glCallList(budList);
  //glCallList(segList);
  //drawBezierLeaf(cornleaf, 21, 0.1, 0);
  

  //glTranslatef(-15.0f,0.0f,0.0f);
  drawPlant(plants[0],disLists);
  /*
  glTranslatef(0.0f,-15.0f,0.0f);
  drawPlant(plants[1],disLists);
  glTranslatef(15.0f,0.0,0.0);
  drawPlant(plants[2],disLists);
  glTranslatef(0.0f,15.0f,0.0f);
  drawPlant(plants[3],disLists);
  */

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
   gluPerspective(fov, (GLfloat)w / (GLfloat)h, 1.0, 280.0);
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
        updatePlant(plants[0],0.5f);
        //updatePlant(plants[1],1.0f);
        //updatePlant(plants[2],1.0f);
        //updatePlant(plants[3],1.0f);
        reDraw();
        break;
      case 119: //w
        cameraCoords[2] += 5.0f;
        cameraCoords[1] += 2.0f;
        cameraCoords[0] += 2.0f;
        reDraw();
        break;
      case 115: //s
        cameraCoords[2] -= 5.0f;
        cameraCoords[1] -= 2.0f;
        cameraCoords[0] -= 2.0f;
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

   glutMouseFunc(mouse);
   glutMotionFunc(mousemove);

   glEnable(GL_DEPTH_TEST);
   glEnable(GL_CULL_FACE);

   glewInit();
   shaders_setup();


   plants = (plant *)malloc(sizeof(plant) * 4);
   plants[0] = newPlant(1.0,1.0,7.0,0.15,0.15,20);
   plants[1] = newPlant(1.0,1.0,7.0,0.15,0.15,20);
   plants[2] = newPlant(1.0,1.0,7.0,0.15,0.15,20);
   plants[3] = newPlant(1.0,1.0,7.0,0.15,0.15,20);


   /*
    * Print welcome message
    */
     printf("Welcome to Corn Grower\n");
     printf(" By: Jon Elliott\n");
   glutMainLoop();
   return 0;
}
