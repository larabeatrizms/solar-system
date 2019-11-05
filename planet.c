#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>

static float year[10] = {0};
static float day[10] = {0};
static float dist[10] = {57, 108, 149, 227, 778, 1429, 2870, 4504, 5922, 152};
static float diam[10] = {2440, 6502, 6378, 3398, 71492, 60268, 25559, 24764, 1153, 1737};

void spinDisplayRight(void);
void spinDisplayLeft(void);
void spinDisplayYearLeft(void);
void spinDisplayYearRight(void);
void spinDisplayDayLeft(void);
void spinDisplayDayRight(void);
float rest(float year);
long map(float x, long in_min, long in_max, long out_min, long out_max);
float mapFloat(float x, float in_min, float in_max, float out_min, float out_max);
float distance(float dist);

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}

void display(void)
{  
   glClear (GL_COLOR_BUFFER_BIT);
   glColor3f (1.0, 1.0, 1.0);

   //Desenhando o sol
   glPushMatrix();
   glutWireSphere(1.5, 20, 16);
   glPopMatrix();

   //Desenhando o planeta 1 - Mércurio
   glPushMatrix();
   glRotatef ((GLfloat) year[0], 0.0, 1.0, 0.0);
   glTranslatef ((GLfloat)distance(dist[0]), 0.0, 0.0);
   glRotatef ((GLfloat) day[0], 0.0, 1.0, 0.0);
   glutWireSphere(0.3, 10, 8);
   glPopMatrix();

   //Desenhando o planeta 2 - Vênus
   glPushMatrix();
   glRotatef ((GLfloat) year[1], 0.0, 1.0, 0.0);
   glTranslatef ((GLfloat)distance(dist[1]), 0.0, 0.0);
   glRotatef ((GLfloat) day[1], 0.0, 1.0, 0.0);
   glutWireSphere(0.28, 10, 8);
   glPopMatrix();
   glutSwapBuffers();

   //Desenhando o planeta 3 - Terra
   glPushMatrix();
   glRotatef ((GLfloat) year[2], 0.0, 1.0, 0.0);
   glTranslatef ((GLfloat)distance(dist[2]), 0.0, 0.0);
   glRotatef ((GLfloat) day[2], 0.0, 1.0, 0.0);
   glutWireSphere(0.26, 10, 8);
   glPopMatrix();
   glutSwapBuffers();

   //Desenhando o planeta 4 - Marte
   glPushMatrix();
   glRotatef ((GLfloat) year[3], 0.0, 1.0, 0.0);
   glTranslatef ((GLfloat)distance(dist[3]), 0.0, 0.0);
   glRotatef ((GLfloat) day[3], 0.0, 1.0, 0.0);
   glutWireSphere(0.20, 10, 8);
   glPopMatrix();
   glutSwapBuffers();

   //Desenhando o planeta 5 - Júpiter
   glPushMatrix();
   glRotatef ((GLfloat) year[4], 0.0, 1.0, 0.0);
   glTranslatef ((GLfloat)distance(dist[4]), 0.0, 0.0);
   glRotatef ((GLfloat) day[4], 0.0, 1.0, 0.0);
   glutWireSphere(0.17, 10, 8);
   glPopMatrix();
   glutSwapBuffers();

   //Desenhando o planeta 6 - Saturno
   glPushMatrix();
   glRotatef ((GLfloat) year[5], 0.0, 1.0, 0.0);
   glTranslatef ((GLfloat)distance(dist[5]), 0.0, 0.0);
   glRotatef ((GLfloat) day[5], 0.0, 1.0, 0.0);
   glutWireSphere(0.14, 10, 8);
   glPopMatrix();
   glutSwapBuffers();

   //Desenhando o planeta 7 - Urano
   glPushMatrix();
   glRotatef ((GLfloat) year[6], 0.0, 1.0, 0.0);
   glTranslatef ((GLfloat)distance(dist[6]), 0.0, 0.0);
   glRotatef ((GLfloat) day[6], 0.0, 1.0, 0.0);
   glutWireSphere(0.10, 10, 8);
   glPopMatrix();
   glutSwapBuffers();

   //Desenhando o planeta 8 - Netuno
   glPushMatrix();
   glRotatef ((GLfloat) year[7], 0.0, 1.0, 0.0);
   glTranslatef ((GLfloat)distance(dist[7]), 0.0, 0.0);
   glRotatef ((GLfloat) day[7], 0.0, 1.0, 0.0);
   glutWireSphere(0.08, 10, 8);
   glPopMatrix();
   glutSwapBuffers();

   //Desenhando o planeta 9 - Plutão
   glPushMatrix();
   glRotatef ((GLfloat) year[8], 0.0, 1.0, 0.0);
   glTranslatef ((GLfloat)distance(dist[8]), 0.0, 0.0);
   glRotatef ((GLfloat) day[8], 0.0, 1.0, 0.0);
   glutWireSphere(0.05, 10, 8);
   glPopMatrix();
   glutSwapBuffers();

   //Desenhando a Lua
   glPushMatrix();
   glRotatef ((GLfloat) year[9], 0.0, 1.0, 0.0);
   glTranslatef ((GLfloat)distance(dist[9]), 0.0, 0.0);
   glRotatef ((GLfloat) day[9], 0.0, 1.0, 0.0);
   glutWireSphere(0.32, 10, 8);
   glPopMatrix();
   glutSwapBuffers();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(100.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void spinDisplayDayLeft(void){

   float velDay1[10] = {0.003, 0.002, 0.46, 0.12, 12.57, 10.28, 2.58, 2.69, 0.802, 1.022};
   float velDay2[10];

   for(int i=0; i<10; i++){
      velDay2[i] = mapFloat(velDay1[i],0.002,12.57,1,10);
   }

   printf("velvenus %f", velDay2[2]);

   for(int i=0; i<10; i++){
      day[i] = rest(day[i] + velDay2[i]);
   }

}

void spinDisplayYearLeft(void){

   float velYear1[10] = {48, 35, 29, 24, 13, 9, 6, 5, 4, 1};
   float velYear2[10];

   for(int i=0; i<10; i++){
      velYear2[i] = map(velYear1[i],1,48,2,10);
   }

   printf("vel1 %f", velYear2[1]);

   for(int i=0; i<10; i++){
      year[i] = rest(year[i] + velYear2[i]);
   }

}

float rest(float year) {
   float r;

   if(year / 360 == 1){

      return 0;
   }else{

      r = year - 360*((int)(year/360));
      return r;
   }

}

long map(float x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float distance(float dist){

   return mapFloat(dist,57,5922,2,10);
   
}

float diameter(float diam){

   return mapFloat(diam,1153,71492,2,10);
   
}


void spinDisplayLeft(void)
{
   spinDisplayDayLeft();
   spinDisplayYearLeft();
   glutPostRedisplay();
}

void spinDisplayDayRight(void){

   float velYear1[10] = {48, 35, 29, 24, 13, 9, 6, 5, 4, 1};
   float velYear2[10];

   for(int i=0; i<10; i++){
      velYear2[i] = map(velYear1[i],1,48,1,10);
   }

   printf("vel1 %f", velYear2[1]);

   for(int i=0; i<10; i++){
      year[i] = rest(year[i] - velYear2[i]);
   }

}

void spinDisplayYearRight(void){

   float velYear1[10] = {48, 35, 29, 24, 13, 9, 6, 5, 4, 1};
   float velYear2[10];

   for(int i=0; i<10; i++){
      velYear2[i] = map(velYear1[i],1,48,1,10);
   }

   printf("vel1 %f", velYear2[1]);

   for(int i=0; i<10; i++){
      year[i] = rest(year[i] - velYear2[i]);
   }

}

void spinDisplayRight(void)
{
   spinDisplayDayRight();
   spinDisplayYearRight();
   glutPostRedisplay();
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case 'y':
         glutIdleFunc(spinDisplayLeft);
         break;
      case 'Y':
         glutIdleFunc(spinDisplayRight);
         break;
      default:
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
