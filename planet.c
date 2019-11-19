//Bibliotecas utilizadas
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

//Definições dos arrays de dados utilizados
float sol[] = {1, 1, 0, 1};
float nolight[] = {0, 0, 0, 1};
float reflexo = 100;
float dir[] = {0, 0, 0, 1};
static float velSol = 0;
static float year[8] = {0};
static float day[8] = {0};
static float dist[8] = {57, 108, 149, 227, 778, 1429, 2870, 4504};
static float rads[9] = {300000, 2440, 6502, 6378, 3398, 71492, 60268, 25559, 24764};
float _Angle = 0.0;
float _moveLeftRight = 0.0;
float X = 0.0, Z = 3.0;
float X_2 = 0.0, Z_2 = -1.0;
float Y = 0.0;
int _moveForeBack = 0;
int moveUp = 0;
int _width, _height;
float fb = 0.2;

//Funções definidas para as rotações em torno do sol e do próprio planeta
void spinDisplayRight(void);
void spinDisplay(void);
void spinDisplayYear(void);
void spinDisplayYearRight(void);
void spinDisplayDay(void);
void spinDisplayDayRight(void);

//Funções auxiliares
float rest(float year);
float mapFloat(float x, float in_min, float in_max, float out_min, float out_max);
float distance(float dist);
float radius(float rad);
void DesenhaOrbita(float cx, float cy, float rx, float ry, int num_segments);

//Funções textura
GLuint LoadTextureImageFile(const char *filename);
void background();

GLuint LoadTextureImageFile(const char *filename)
{
    GLuint texture = 0;
    int width, height;
    char *data = NULL;
    FILE *file = NULL;

    // open texture data
    file = fopen(filename, "r");

    if (&file == NULL)
        return 0;

    // allocate buffer
    width = 256;
    height = 256;

    data = (char *)malloc(width * height * 3);

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
    glTexImage2D(GL_TEXTURE_2D, 0, GL_BGR_EXT, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);

    // free buffer
    free(data);

    return texture;
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void Moving_Foreword_Backword_Direction(int loc)
{
    X = X + loc * (X_2)*fb;
    //Y = Y + loc*0.5*fb;
    Z = Z + loc * (Z_2)*fb;
    glLoadIdentity();
    gluLookAt(X, Y, Z, X + X_2, Y, Z + Z_2, 0.0f, 1.0f, 0.0f);
}

void Moving_Left_Right_Direction(float angle)
{
    X_2 = sin(angle);
    Z_2 = -cos(angle);
    glLoadIdentity();
    gluLookAt(X, Y, Z, X + X_2, Y, Z + Z_2, 0.0f, 1.0f, 0.0f);
}

void display(void)
{
    GLuint textSol, textMerc, textVen, textTerra, textLua, textMarte, textJup, textSat, textUrano, textNetuno;
    GLUquadric *quadSol, *quadMerc, *quadVen, *quadTerra, *quadLua, *quadMarte, *quadJup, *quadSat, *quadNetuno, *quadUrano;

    if (_moveForeBack)
    {
        Moving_Foreword_Backword_Direction(_moveForeBack);
    }

    if (_moveLeftRight)
    {
        _Angle += _moveLeftRight;
        Moving_Left_Right_Direction(_Angle);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_DEPTH_TEST);
    glPushMatrix();

    glEnable(GL_TEXTURE_2D);
    GLuint texture = LoadTextureImageFile("texturas_2/bmp_stars_milky_way.bmp");
    glBindTexture(GL_TEXTURE_2D, texture);
    // Melhora a qualidade da textura
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-8.0, 8.0, 0.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(8.0, 8.0, 0.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(8.0, -8.0, 0.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-8.0, -8.0, 0.0);
    glEnd();
    glDeleteTextures(1, &texture);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glPushMatrix();
    for (int i = 0; i < 8; i++)
    {
        DesenhaOrbita(0, 0, (GLfloat)distance(dist[i]), (GLfloat)distance(dist[i]), 100);
    }

    //Desenhando o sol
    glPushMatrix();

    glEnable(GL_TEXTURE_2D);
    textSol = LoadTextureImageFile("texturas_2/bmp_sun.bmp");
    glBindTexture(GL_TEXTURE_2D, textSol);
    quadSol = gluNewQuadric();
    gluQuadricDrawStyle(quadSol, GLU_FILL);
    gluQuadricNormals(quadSol, GLU_SMOOTH);
    gluQuadricTexture(quadSol, GL_TRUE);
    glRotatef((GLfloat)velSol, 0.0, 1.0, 0.0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, sol); // Luz solar
    gluSphere(quadSol, (GLfloat)radius(rads[0]), 10, 8);
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
    glRotatef((GLfloat)year[0], 0.0, 1.0, 0.0);
    glTranslatef((GLfloat)distance(dist[0]), 0.0, 0.0);
    glRotatef((GLfloat)day[0], 0.0, 1.0, 0.0);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, reflexo);
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
    glRotatef((GLfloat)year[1], 0.0, 1.0, 0.0);
    glTranslatef((GLfloat)distance(dist[1]), 0.0, 0.0);
    glRotatef((GLfloat)day[1], 0.0, 1.0, 0.0);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, reflexo);
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
    glRotatef((GLfloat)year[2], 0.0, 1.0, 0.0);
    glTranslatef((GLfloat)distance(dist[2]), 0.0, 0.0);
    glRotatef((GLfloat)day[2], 0.0, 1.0, 0.0);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, reflexo); // Reflexo de luminosidade
    gluSphere(quadTerra, (GLfloat)radius(rads[3]), 10, 8);
    glDeleteTextures(1, &textTerra);
    glDisable(GL_TEXTURE_2D);

    //Desenhando a lua
    glPushMatrix();

    glEnable(GL_TEXTURE_2D);
    textLua = LoadTextureImageFile("texturas_2/bmp_moon.bmp");
    glBindTexture(GL_TEXTURE_2D, textLua);
    quadLua = gluNewQuadric();
    gluQuadricDrawStyle(quadLua, GLU_FILL);
    gluQuadricNormals(quadLua, GLU_SMOOTH);
    gluQuadricTexture(quadLua, GL_TRUE);
    glRotatef((GLfloat)year[2], 0.0, 0.2, 0.0);
    glTranslatef((GLfloat)distance(dist[2]) / 10.0, 0.0, 0.0);
    glRotatef((GLfloat)day[2], 0.0, 1.0, 0.0);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, reflexo); // Reflexo de luminosidade
    gluSphere(quadLua, (GLfloat)radius(rads[3]) / 3.0, 10, 8);
    glDeleteTextures(1, &textLua);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();

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
    glRotatef((GLfloat)year[3], 0.0, 1.0, 0.0);
    glTranslatef((GLfloat)distance(dist[3]), 0.0, 0.0);
    glRotatef((GLfloat)day[3], 0.0, 1.0, 0.0);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, reflexo);
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
    glRotatef((GLfloat)year[4], 0.0, 1.0, 0.0);
    glTranslatef((GLfloat)distance(dist[4]), 0.0, 0.0);
    glRotatef((GLfloat)day[4], 0.0, 1.0, 0.0);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, reflexo);
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
    glRotatef((GLfloat)year[5], 0.0, 1.0, 0.0);
    glTranslatef((GLfloat)distance(dist[5]), 0.0, 0.0);
    glRotatef((GLfloat)day[5], 0.0, 1.0, 0.0);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, reflexo);
    gluSphere(quadSat, (GLfloat)radius(rads[6]), 10, 8);
    glDeleteTextures(1, &textSat);
    glDisable(GL_TEXTURE_2D);

    glLineWidth(3.0f);
    glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
    //aneis de saturno
    for (int j = 1; j <= 3; j++)
    {
        for (int i = 1; i <= 100; i++)
        {
            glVertex3f(0, (0.20 + 0.015 * j) * cos(2.0 * 3.14 * i / 100), (0.20 + 0.015 * j) * sin(2.0 * 3.14 * i / 100));
            glVertex3f(0, (0.20 + 0.015 * j) * cos(2.0 * 3.14 * i / 100), (0.20 + 0.015 * j) * sin(2.0 * 3.14 * i / 100));
            glVertex3f(0, (0.20 + 0.015 * j) * cos(2.0 * 3.14 * i / 100), (0.20 + 0.015 * j) * sin(2.0 * 3.14 * i / 100));
        }
    }
    glEnd();

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
    glRotatef((GLfloat)year[6], 0.0, 1.0, 0.0);
    glTranslatef((GLfloat)distance(dist[6]), 0.0, 0.0);
    glRotatef((GLfloat)day[6], 0.0, 1.0, 0.0);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, reflexo);
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
    glRotatef((GLfloat)year[7], 0.0, 1.0, 0.0);
    glTranslatef((GLfloat)distance(dist[7]), 0.0, 0.0);
    glRotatef((GLfloat)day[7], 0.0, 1.0, 0.0);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, reflexo);
    gluSphere(quadNetuno, (GLfloat)radius(rads[8]), 10, 8);
    glDeleteTextures(1, &textNetuno);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();

    glutSwapBuffers();
}

void DesenhaOrbita(float cx, float cy, float rx, float ry, int num_segments)
{
    glPushMatrix();
    float theta = 2 * 3.1415926 / (float)num_segments;
    float c = cosf(theta); //precalculate the sine and cosine
    float s = sinf(theta);
    float t;

    float x = 1; //we start at angle = 0
    float y = 0;
    glRotatef(180.0f, 0.0f, 1.0f, 1.0f); // roda 45 graus no eixo z
    //glRotatef((GLfloat)year[0], 0.0, 1.0, 0.0);
    glBegin(GL_LINE_LOOP);

    for (int ii = 0; ii < num_segments; ii++)
    {
        //apply radius and offset

        glVertex2f(x * rx + cx, y * ry + cy); //output vertex

        //apply the rotation matrix
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }
    glEnd();
    glPopMatrix();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 1.5, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void spinDisplayDay(void)
{

    float velDay1[10] = {0.003, 0.002, 0.46, 0.12, 12.57, 10.28, 2.58, 2.69, 0.802, 1.022};
    float velDay2[10];

    for (int i = 0; i < 10; i++)
    {
        velDay2[i] = mapFloat(velDay1[i], 0.002, 12.57, 0.2, 1);
    }

    for (int i = 0; i < 10; i++)
    {
        if (i == 2)
            day[i] = rest(day[i] - velDay2[i]);
        else
            day[i] = rest(day[i] + velDay2[i]);
    }
    velSol = rest(velSol + 0.1);
}

void spinDisplayYear(void)
{

    float velYear1[10] = {48, 35, 29, 24, 13, 9, 6, 5, 4, 1};
    float velYear2[10];

    for (int i = 0; i < 10; i++)
    {
        velYear2[i] = mapFloat(velYear1[i], 1, 48, 0.2, 1);
    }

    for (int i = 0; i < 10; i++)
    {
        year[i] = rest(year[i] + velYear2[i]);
    }

    velSol = rest(velSol + 0.1);
}

float rest(float year)
{
    float r;

    if (year / 360 == 1)
    {

        return 0;
    }
    else
    {

        r = year - 360 * ((int)(year / 360));
        return r;
    }
}

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max)
{

    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float distance(float dist)
{

    return mapFloat(dist, 57, 4504, 1.3, 10);
}

float radius(float rad)
{

    return mapFloat(rad, 2440, 300000, 0.08, 0.3);
}

void spinDisplay(void)
{

    spinDisplayDay();
    spinDisplayYear();
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        glutIdleFunc(spinDisplay);
        break;
    case GLUT_MIDDLE_BUTTON:
        glutIdleFunc(NULL);
        break;
    default:
        break;
    }
}

void Key_Pressed(int key, int x, int y)
{
    if (key == GLUT_KEY_UP)
    {
        _moveForeBack = 8;
    }
    else if (key == GLUT_KEY_DOWN)
    {
        _moveForeBack = -8;
    }
    else if (key == GLUT_KEY_LEFT)
    {
        _moveLeftRight = -0.09;
    }
    else if (key == GLUT_KEY_RIGHT)
    {
        _moveLeftRight = 0.09;
    }
    else if (key == GLUT_KEY_PAGE_UP)
    {
        Y += 0.5;
        glLoadIdentity();
        gluLookAt(X, Y, Z, X + X_2, Y, Z + Z_2, 0.0f, 1.0f, 0.0f);
        glutPostRedisplay();
    }
    else if (key == GLUT_KEY_PAGE_DOWN)
    {
        Y -= 0.5;
        glLoadIdentity();
        gluLookAt(X, Y, Z, X + X_2, Y, Z + Z_2, 0.0f, 1.0f, 0.0f);
        glutPostRedisplay();
    }
}

void Key_Released(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        if (_moveForeBack > 0)
            _moveForeBack = 0;

        break;

    case GLUT_KEY_DOWN:
        if (_moveForeBack < 0)
            _moveForeBack = 0;
        break;
    case GLUT_KEY_LEFT:
        if (_moveLeftRight < 0.0f)
            _moveLeftRight = 0.0f;
        break;

    case GLUT_KEY_RIGHT:
        if (_moveLeftRight > 0.0f)
            _moveLeftRight = 0.0f;
        break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(800, 800);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutSpecialFunc(Key_Pressed);
    glutSpecialUpFunc(Key_Released);
    glutMainLoop();
    return 0;
}
