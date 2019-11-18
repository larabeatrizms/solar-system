//Bibliotecas utilizadas
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>

//Definições dos arrays de dados utilizados
float sol[] = {1,1,0,1};
float nolight[] = {0,0,0,1};
float reflexo = 100;
float dir[] = {0,0,0,1}; 
static float velSol = 0;
static float year[8] = {0};
static float day[8] = {0};
static float dist[8] = {57, 108, 149, 227, 778, 1429, 2870, 4504};
static float rads[9] = {300000, 2440, 6502, 6378, 3398, 71492, 60268, 25559, 24764};

//Funções definidas para as rotações em torno do sol e do próprio planeta
void spinDisplayRight(void);
void spinDisplayLeft(void);
void spinDisplayYearLeft(void);
void spinDisplayYearRight(void);
void spinDisplayDayLeft(void);
void spinDisplayDayRight(void);

//Funções auxiliares
float rest(float year);
float mapFloat(float x, float in_min, float in_max, float out_min, float out_max);
float distance(float dist);
float radius(float rad);

//Funções textura
GLuint LoadTextureImageFile(const char * filename);
void background();

GLuint LoadTextureImageFile(const char * filename)  
{  
    GLuint texture = 0;  
    int width, height;  
    char * data = NULL;  
    FILE * file = NULL;  
  
    // open texture data  
    file = fopen(filename, "r");  
  
    if (&file == NULL) return 0;  
  
    // allocate buffer  
    width = 256;  
    height = 256;  
  
    data = (char*)malloc(width * height * 3);  
  
    // read texture data  
    fread(data, width * height * 3, 1, file);  
    fclose(file);  

    glGenTextures(1, &texture);  
    glPixelStorei(GL_UNPACK_ALIGNMENT, 0);
  
    glBindTexture(GL_TEXTURE_2D, texture);  
  
    //  texture MIP maps  
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);  
  
  
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);  
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
    glTexImage2D (GL_TEXTURE_2D, 0, GL_BGR_EXT, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);  
  
    // free buffer  
    free(data);  
  
    return texture;  
  
}  
  
void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}

void display(void)
{  
   GLuint textSol, textMerc, textVen, textTerra, textMarte, textJup, textSat, textUrano, textNetuno;
   GLUquadric *quadSol, *quadMerc, *quadVen, *quadTerra, *quadMarte, *quadJup, *quadSat, *quadNetuno, *quadUrano;
   GLUquadricObj *disk;

   disk = gluNewQuadric();

   //gluDisk(disk, inDiameter, outDiameter, vertSlices, horizSlices);

   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

   //background();

   glDisable(GL_DEPTH_TEST);
   glPushMatrix(); 

   glEnable(GL_TEXTURE_2D);  
   GLuint texture = LoadTextureImageFile("texturas_2/bmp_stars_milky_way.bmp");   
   glBindTexture(GL_TEXTURE_2D, texture);  
   //even better quality, but this will do for now.
   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
   
   glBegin(GL_QUADS);  
   glTexCoord2f(0.0, 0.0);  
   glVertex3f(-4.0, 4.0, 0.0);  
   glTexCoord2f(0.0, 1.0);  
   glVertex3f(4.0, 4.0, 0.0);  
   glTexCoord2f(1.0, 1.0);  
   glVertex3f(4.0, -4.0, 0.0);  
   glTexCoord2f(1.0, 0.0);  
   glVertex3f(-4.0, -4.0, 0.0);  
   glEnd(); 
   glDeleteTextures(1, &texture);
   glDisable(GL_TEXTURE_2D); 
   glPopMatrix(); 

   glEnable(GL_DEPTH_TEST);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0); 


   //glColor3f (1.0, 1.0, 0.1);

    
   //Desenhando o sol
   glPushMatrix(); 

   glEnable(GL_TEXTURE_2D); 
   textSol = LoadTextureImageFile("texturas_2/bmp_sun.bmp");  
   //printf("textura: %d", textura); 
   glBindTexture(GL_TEXTURE_2D, textSol); 
   quadSol = gluNewQuadric();
   gluQuadricDrawStyle(quadSol, GLU_FILL);
   gluQuadricNormals(quadSol, GLU_SMOOTH);
   gluQuadricTexture(quadSol, GL_TRUE);
   glRotatef ((GLfloat) velSol, 0.0, 1.0, 0.0);
   glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, sol); // Luz solar 
   gluSphere(quadSol, (GLfloat) radius(rads[0]), 10, 8);
   glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, nolight); 
   glDeleteTextures(1, &textSol);
   glDisable(GL_TEXTURE_2D); 
   glLightfv(GL_LIGHT0, GL_POSITION, dir); // Cria a luz do sol em todas as direções 
   glPopMatrix(); 
    

   //Desenhando o planeta 1 - Mércurio
   glPushMatrix();

   glEnable(GL_TEXTURE_2D); 
   textMerc = LoadTextureImageFile("texturas_2/bmp_mercury.bmp"); 
   glBindTexture(GL_TEXTURE_2D, textMerc); 
   quadMerc = gluNewQuadric();
   gluQuadricDrawStyle(quadMerc, GLU_FILL);
   gluQuadricNormals(quadMerc, GLU_SMOOTH);
   gluQuadricTexture(quadMerc, GL_TRUE); 
   glRotatef ((GLfloat) year[0], 0.0, 1.0, 0.0);
   glTranslatef ((GLfloat)distance(dist[0]), 0.0, 0.0);
   glRotatef ((GLfloat) day[0], 0.0, 1.0, 0.0);
   //glColor3f (0.1, 0.35, 0.8);
   gluSphere(quadMerc, (GLfloat)radius(rads[1]), 10, 8);
   glDeleteTextures(1, &textMerc);
   glDisable(GL_TEXTURE_2D); 

   glPopMatrix();

   //Desenhando o planeta 2 - Vênus
   glPushMatrix();

   glEnable(GL_TEXTURE_2D); 
   textVen = LoadTextureImageFile("texturas_2/bmp_venus_surface.bmp"); 
   glBindTexture(GL_TEXTURE_2D, textVen); 
   quadVen = gluNewQuadric();
   gluQuadricDrawStyle(quadVen, GLU_FILL);
   gluQuadricNormals(quadVen, GLU_SMOOTH);
   gluQuadricTexture(quadVen, GL_TRUE); 
   glRotatef ((GLfloat) year[1], 0.0, 1.0, 0.0);
   glTranslatef ((GLfloat)distance(dist[1]), 0.0, 0.0);
   glRotatef ((GLfloat) day[1], 0.0, 1.0, 0.0);
   //glColor3f (0.1, 0.35, 0.8);
   gluSphere(quadVen, (GLfloat)radius(rads[2]), 10, 8);
   glDeleteTextures(1, &textVen);
   glDisable(GL_TEXTURE_2D);
 
   glPopMatrix();
   
   
   //Desenhando o planeta 3 - Terra
   glPushMatrix();

   glEnable(GL_TEXTURE_2D); 
   textTerra = LoadTextureImageFile("texturas_2/bmp_earth_daymap.bmp"); 
   glBindTexture(GL_TEXTURE_2D, textTerra); 
   quadTerra = gluNewQuadric();
   gluQuadricDrawStyle(quadTerra, GLU_FILL);
   gluQuadricNormals(quadTerra, GLU_SMOOTH);
   gluQuadricTexture(quadTerra, GL_TRUE); 
   glRotatef ((GLfloat) year[2], 0.0, 1.0, 0.0);
   glTranslatef ((GLfloat)distance(dist[2]), 0.0, 0.0);
   glRotatef ((GLfloat) day[2], 0.0, 1.0, 0.0);
   //glColor3f (0.1, 0.35, 0.8);
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,reflexo); // Reflexo de luminosidade 
   gluSphere(quadTerra, (GLfloat)radius(rads[3]), 10, 8);
   glDeleteTextures(1, &textTerra);
   glDisable(GL_TEXTURE_2D);

   glPopMatrix();
   
   //Desenhando o planeta 4 - Marte
   glPushMatrix();

   glEnable(GL_TEXTURE_2D); 
   textMarte = LoadTextureImageFile("texturas_2/bmp_mars.bmp"); 
   glBindTexture(GL_TEXTURE_2D, textMarte); 
   quadMarte = gluNewQuadric();
   gluQuadricDrawStyle(quadMarte, GLU_FILL);
   gluQuadricNormals(quadMarte, GLU_SMOOTH);
   gluQuadricTexture(quadMarte, GL_TRUE); 
   glRotatef ((GLfloat) year[3], 0.0, 1.0, 0.0);
   glTranslatef ((GLfloat)distance(dist[3]), 0.0, 0.0);
   glRotatef ((GLfloat) day[3], 0.0, 1.0, 0.0);
   //glColor3f (0.1, 0.35, 0.8);
   gluSphere(quadMarte, (GLfloat)radius(rads[4]), 10, 8);
   glDeleteTextures(1, &textMarte);
   glDisable(GL_TEXTURE_2D);

   glPopMatrix();
   
   //Desenhando o planeta 5 - Júpiter
   glPushMatrix();

   glEnable(GL_TEXTURE_2D); 
   textJup = LoadTextureImageFile("texturas_2/bmp_jupiter.bmp"); 
   glBindTexture(GL_TEXTURE_2D, textJup); 
   quadJup = gluNewQuadric();
   gluQuadricDrawStyle(quadJup, GLU_FILL);
   gluQuadricNormals(quadJup, GLU_SMOOTH);
   gluQuadricTexture(quadJup, GL_TRUE); 
   glRotatef ((GLfloat) year[4], 0.0, 1.0, 0.0);
   glTranslatef ((GLfloat)distance(dist[4]), 0.0, 0.0);
   glRotatef ((GLfloat) day[4], 0.0, 1.0, 0.0);
   //glColor3f (0.1, 0.35, 0.8);
   gluSphere(quadJup, (GLfloat)radius(rads[5]), 10, 8);
   glDeleteTextures(1, &textJup);
   glDisable(GL_TEXTURE_2D);

   glPopMatrix();
   
   //Desenhando o planeta 6 - Saturno
   glPushMatrix();

   glEnable(GL_TEXTURE_2D); 
   textSat = LoadTextureImageFile("texturas_2/bmp_saturn.bmp"); 
   glBindTexture(GL_TEXTURE_2D, textSat); 
   quadSat = gluNewQuadric();
   gluQuadricDrawStyle(quadSat, GLU_FILL);
   gluQuadricNormals(quadSat, GLU_SMOOTH);
   gluQuadricTexture(quadSat, GL_TRUE); 
   glRotatef ((GLfloat) year[5], 0.0, 1.0, 0.0);
   glTranslatef ((GLfloat)distance(dist[5]), 0.0, 0.0);
   glRotatef ((GLfloat) day[5], 0.0, 1.0, 0.0);
   //glColor3f (0.1, 0.35, 0.8);
   gluSphere(quadSat, (GLfloat)radius(rads[6]), 10, 8);
   glDeleteTextures(1, &textSat);
   glDisable(GL_TEXTURE_2D);

   glPopMatrix();
   
   //Desenhando o planeta 7 - Urano
   glPushMatrix();

   glEnable(GL_TEXTURE_2D); 
   textUrano = LoadTextureImageFile("texturas_2/bmp_uranus.bmp"); 
   glBindTexture(GL_TEXTURE_2D, textUrano); 
   quadUrano = gluNewQuadric();
   gluQuadricDrawStyle(quadUrano, GLU_FILL);
   gluQuadricNormals(quadUrano, GLU_SMOOTH);
   gluQuadricTexture(quadUrano, GL_TRUE); 
   glRotatef ((GLfloat) year[6], 0.0, 1.0, 0.0);
   glTranslatef ((GLfloat)distance(dist[6]), 0.0, 0.0);
   glRotatef ((GLfloat) day[6], 0.0, 1.0, 0.0);
   //glColor3f (0.1, 0.35, 0.8);
   gluSphere(quadUrano, (GLfloat)radius(rads[7]), 10, 8);
   glDeleteTextures(1, &textUrano);
   glDisable(GL_TEXTURE_2D);

   glPopMatrix();

   //Desenhando o planeta 8 - Netuno
   glPushMatrix();

   glEnable(GL_TEXTURE_2D); 
   textNetuno = LoadTextureImageFile("texturas_2/bmp_neptune.bmp"); 
   glBindTexture(GL_TEXTURE_2D, textNetuno); 
   quadNetuno = gluNewQuadric();
   gluQuadricDrawStyle(quadNetuno, GLU_FILL);
   gluQuadricNormals(quadNetuno, GLU_SMOOTH);
   gluQuadricTexture(quadNetuno, GL_TRUE); 
   glRotatef ((GLfloat) year[7], 0.0, 1.0, 0.0);
   glTranslatef ((GLfloat)distance(dist[7]), 0.0, 0.0);
   glRotatef ((GLfloat) day[7], 0.0, 1.0, 0.0);
   //glColor3f (0.1, 0.35, 0.8);
   gluSphere(quadNetuno, (GLfloat)radius(rads[8]), 10, 8);
   glDeleteTextures(1, &textNetuno);
   glDisable(GL_TEXTURE_2D);

   glPopMatrix();

   // glPopMatrix();

   
   
   //glutSwapBuffers(); 

   
   glutSwapBuffers(); 

}

void background()
{

    GLuint text_cosmo = LoadTextureImageFile("texturas_2/bmp_stars_milky_way.bmp");  
    int width = 256;
    int height = 256;
    int length = 256;

    //start in this coordinates
    int x = 0;
    int y = 0;
    int z = 0;

    //center the square
    x = x - width / 2;
    y = y - height / 2;
    z = z - length / 2;

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, text_cosmo);
    glBegin(GL_QUADS);      
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y,  z);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z); 
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
    glEnd();

    //FRONT
    glBindTexture(GL_TEXTURE_2D, text_cosmo);
    glBegin(GL_QUADS);  
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y,  z + length);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length); 
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,  z + length);
    glEnd();

    //BOTTOM
    glBindTexture(GL_TEXTURE_2D, text_cosmo);
    glBegin(GL_QUADS);      
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y,  z);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y,  z + length);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y,  z + length); 
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,  z);
    glEnd();

    //TOP
    glBindTexture(GL_TEXTURE_2D, text_cosmo);
    glBegin(GL_QUADS);      
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y + height, z + length); 
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
    glEnd();

    //LEFT
    glBindTexture(GL_TEXTURE_2D, text_cosmo);
    glBegin(GL_QUADS);      
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z); 
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length); 
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y,  z + length);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y,  z);     

    glEnd();

    //RIGHT
    glBindTexture(GL_TEXTURE_2D, text_cosmo);
    glBegin(GL_QUADS);  
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,  z);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y,  z + length);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length); 
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt (0.0, 1.5, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void spinDisplayDayLeft(void){

   float velDay1[10] = {0.003, 0.002, 0.46, 0.12, 12.57, 10.28, 2.58, 2.69, 0.802, 1.022};
   float velDay2[10];

   for(int i=0; i<10; i++){
      velDay2[i] = mapFloat(velDay1[i],0.002,12.57,0.2,1);
   }

   for(int i=0; i<10; i++){
      if(i == 2)
         day[i] = rest(day[i] - velDay2[i]);
      else
         day[i] = rest(day[i] + velDay2[i]);
      
   }
   velSol = rest(velSol + 0.1);
   

}

void spinDisplayYearLeft(void){

   float velYear1[10] = {48, 35, 29, 24, 13, 9, 6, 5, 4, 1};
   float velYear2[10];

   for(int i=0; i<10; i++){
      velYear2[i] = mapFloat(velYear1[i],1,48,0.2,1);
   }

   for(int i=0; i<10; i++){
      year[i] = rest(year[i] + velYear2[i]);
   }

   velSol = rest(velSol + 0.1);

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

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max){

  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float distance(float dist){

   return mapFloat(dist,57,4504,1.5,10);
   
}

float radius(float rad){

   return mapFloat(rad,2440,300000,0.1,0.4);
   
}

void spinDisplayLeft(void) {

   spinDisplayDayLeft();
   spinDisplayYearLeft();
   glutPostRedisplay();
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case 'y':
         glutIdleFunc(spinDisplayLeft);
         break;
      default:
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (1000, 1000); 
   glutInitWindowPosition (800, 800);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
