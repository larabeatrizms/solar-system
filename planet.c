#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

static int year1 = 0, year2 = 0, year3 = 0, year4 = 0, year5 = 0, year6 = 0, year7 = 0, year8 = 0, year9 = 0, yearLua = 0;
static int day1 = 0, day2 = 0, day3 = 0, day4 = 0, day5 = 0, day6 = 0, day7 = 0, day8 = 0, day9 = 0, dayLua = 0;

void spinDisplayRight(void);
void spinDisplayLeft(void);
void spinDisplayYearLeft(void);
void spinDisplayYearRight(void);
void spinDisplayDayLeft(void);
void spinDisplayDayRight(void);

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
   glRotatef ((GLfloat) year1, 0.0, 1.0, 0.0);
   glTranslatef (2.0, 0.0, 0.0);
   glRotatef ((GLfloat) day1, 0.0, 1.0, 0.0);
   glutWireSphere(0.3, 10, 8);
   glPopMatrix();

   //Desenhando o planeta 2 - Vênus
   glPushMatrix();
   glRotatef ((GLfloat) year2, 0.0, 1.0, 0.0);
   glTranslatef (2.0, 0.0, 0.0);
   glRotatef ((GLfloat) day2, 0.0, 1.0, 0.0);
   glutWireSphere(0.28, 10, 8);
   glPopMatrix();
   glutSwapBuffers();

   //Desenhando o planeta 3 - Terra
   glPushMatrix();
   glRotatef ((GLfloat) year3, 0.0, 1.0, 0.0);
   glTranslatef (2.0, 0.0, 0.0);
   glRotatef ((GLfloat) day3, 0.0, 1.0, 0.0);
   glutWireSphere(0.26, 10, 8);
   glPopMatrix();
   glutSwapBuffers();

   //Desenhando o planeta 4 - Marte
   glPushMatrix();
   glRotatef ((GLfloat) year4, 0.0, 1.0, 0.0);
   glTranslatef (2.0, 0.0, 0.0);
   glRotatef ((GLfloat) day4, 0.0, 1.0, 0.0);
   glutWireSphere(0.20, 10, 8);
   glPopMatrix();
   glutSwapBuffers();

   //Desenhando o planeta 5 - Júpiter
   glPushMatrix();
   glRotatef ((GLfloat) year5, 0.0, 1.0, 0.0);
   glTranslatef (2.0, 0.0, 0.0);
   glRotatef ((GLfloat) day5, 0.0, 1.0, 0.0);
   glutWireSphere(0.17, 10, 8);
   glPopMatrix();
   glutSwapBuffers();

   //Desenhando o planeta 6 - Saturno
   glPushMatrix();
   glRotatef ((GLfloat) year6, 0.0, 1.0, 0.0);
   glTranslatef (2.0, 0.0, 0.0);
   glRotatef ((GLfloat) day6, 0.0, 1.0, 0.0);
   glutWireSphere(0.14, 10, 8);
   glPopMatrix();
   glutSwapBuffers();

   //Desenhando o planeta 7 - Urano
   glPushMatrix();
   glRotatef ((GLfloat) year7, 0.0, 1.0, 0.0);
   glTranslatef (2.0, 0.0, 0.0);
   glRotatef ((GLfloat) day7, 0.0, 1.0, 0.0);
   glutWireSphere(0.10, 10, 8);
   glPopMatrix();
   glutSwapBuffers();

   //Desenhando o planeta 8 - Netuno
   glPushMatrix();
   glRotatef ((GLfloat) year8, 0.0, 1.0, 0.0);
   glTranslatef (2.0, 0.0, 0.0);
   glRotatef ((GLfloat) day8, 0.0, 1.0, 0.0);
   glutWireSphere(0.08, 10, 8);
   glPopMatrix();
   glutSwapBuffers();

   //Desenhando o planeta 9 - Plutão
   glPushMatrix();
   glRotatef ((GLfloat) year9, 0.0, 1.0, 0.0);
   glTranslatef (2.0, 0.0, 0.0);
   glRotatef ((GLfloat) day9, 0.0, 1.0, 0.0);
   glutWireSphere(0.05, 10, 8);
   glPopMatrix();
   glutSwapBuffers();

   //Desenhando a Lua
   glPushMatrix();
   glRotatef ((GLfloat) yearLua, 0.0, 1.0, 0.0);
   glTranslatef (2.0, 0.0, 0.0);
   glRotatef ((GLfloat) dayLua, 0.0, 1.0, 0.0);
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

   day1 = (day1 + 14) % 360;
   day2 = (day2 + 13) % 360;
   day3 = (day3 + 12) % 360;
   day4 = (day4 + 11) % 360;
   day5 = (day5 + 10) % 360;
   day6 = (day6 + 9) % 360;
   day7 = (day7 + 8) % 360;
   day8 = (day8 + 7) % 360;
   day9 = (day9 + 6) % 360;
   dayLua = (dayLua + 15) % 360;

}

void spinDisplayYearLeft(void){

   year1 = (year1 + 14) % 360;
   year2 = (year2 + 13) % 360;
   year3 = (year3 + 12) % 360;
   year4 = (year4 + 11) % 360;
   year5 = (year5 + 10) % 360;
   year6 = (year6 + 9) % 360;
   year7 = (year7 + 8) % 360;
   year8 = (year8 + 7) % 360;
   year9 = (year9 + 6) % 360;
   yearLua = (yearLua + 15) % 360;

}


void spinDisplayLeft(void)
{
   spinDisplayDayLeft();
   spinDisplayYearLeft();
   glutPostRedisplay();
}

void spinDisplayDayRight(void){

   day1 = (day1 - 14) % 360;
   day2 = (day2 - 13) % 360;
   day3 = (day3 - 12) % 360;
   day4 = (day4 - 11) % 360;
   day5 = (day5 - 10) % 360;
   day6 = (day6 - 9) % 360;
   day7 = (day7 - 8) % 360;
   day8 = (day8 - 7) % 360;
   day9 = (day9 - 6) % 360;
   dayLua = (dayLua - 15) % 360;

}

void spinDisplayYearRight(void){

   year1 = (year1 - 14) % 360;
   year2 = (year2 - 13) % 360;
   year3 = (year3 - 12) % 360;
   year4 = (year4 - 11) % 360;
   year5 = (year5 - 10) % 360;
   year6 = (year6 - 9) % 360;
   year7 = (year7 - 8) % 360;
   year8 = (year8 - 7) % 360;
   year9 = (year9 - 6) % 360;
   yearLua = (yearLua - 15) % 360;

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
