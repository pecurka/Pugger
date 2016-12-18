#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <time.h>
#include "image.h"
#include "objects.h"

/* Imena fajlova sa teksturama. */
#define GRASSTEXTURE "grass.bmp"

/* Identifikatori tekstura. */
static GLuint grassTexture;

/* Deklaracije callback funkcija. */
static void on_reshape(int width, int height);
static void on_display(void);
static void on_keyboard(unsigned char key, int x, int y);
static void on_timer(int value);

/* Inicijalizacija teksture trave */
static void initializeTexture(void);

/*Deklaracija promenljive za rotaciju i kretanje modela psa*/
static int rotation;
static int movementX;
static int movementY;
static int previousMovementX;
static int previousMovementY;


int main(int argc, char **argv) {
    /* Inicijalizuje se GLUT. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    /* Kreira se prozor. */
    glutInitWindowSize(1300, 800);
    glutInitWindowPosition(200, 100);
    glutCreateWindow(argv[0]);

    /* Registruju se funkcije za obradu dogadjaja. */
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
    glutKeyboardFunc(on_keyboard);

    /* Pali se osvetljenje */
    float diffuse_light[] = {1.0f, 1.0f, 1.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glColorMaterial(GL_FRONT, GL_DIFFUSE);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    /*Inicijalizuju se globalne promenljive*/
    rotation = 0;
    movementX = -15;
    movementY = 0;
    previousMovementX = movementX;
    previousMovementY = movementY;

    /* Obavlja se OpenGL inicijalizacija. */
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_TEXTURE_2D);

    initializeTexture();

    /* Ulazi se u glavnu petlju. */
    glutMainLoop();

    return 0;
}

static void initializeTexture(void)
{
   /* Inicijalizuje se objekat koji ce sadrzati teksture ucitane iz fajla */
    Image *image = image_init(0, 0);

    /* Podesava se rezim iscrtavanja tekstura tako da boje na teksturi potpuno odredjuju boju objekata */
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    /* Kreira se tekstura */
    image_read(image, GRASSTEXTURE);

    /* Generisu se identifikatori teksture i inicijalizuje tekstura*/
    glGenTextures(1, &grassTexture);

    glBindTexture(GL_TEXTURE_2D, grassTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    /* Iskljucujemo aktivnu teksturu */
    glBindTexture(GL_TEXTURE_2D, 0);

    /* Unistava se objekat za citanje tekstura iz fajla. */
    image_done(image);
}

static void on_reshape(int width, int height) {
    /* Postavlja se viewport. */
    glViewport(0, 0, width, height);

    /* Postavljaju se parametri projekcije. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float) width / height, 1, 1500);
}

static void on_keyboard(unsigned char key, int x, int y)
{
  switch (key) {
  case 27:
    /* Zavrsava se program. */
    exit(0);
    break;
  case 'w':
  case 'W':
    /* pamti se prethodna pozicija i poziva se funkcija za iscrtavanje nove */
    previousMovementX = movementX;
    glutTimerFunc(20, on_timer, 0);
    break;
  case 'a':
  case 'A':
    previousMovementY = movementY;
    glutTimerFunc(20, on_timer, 1);
    break;
  case 's':
  case 'S':
    previousMovementX = movementX;
    glutTimerFunc(20, on_timer, 2);
    break;
  case 'd':
  case 'D':
    previousMovementY = movementY;
    glutTimerFunc(20, on_timer, 3);
    break;
  }
}

static void on_timer(int value)
{
  /* Gledamo koje dugme je pritisnuto i pomeramo psa u potrebnom pravcu i rotiramo ga u potreban smer */
  switch (value) {
  case 0:
    rotation = 0;
    movementX += 1;
    glutPostRedisplay();
    if(previousMovementX + 5 != movementX) /* Da bi kretanje izgleda 'glatko' teramo da ponavlja isrtavanje dok se ne pomeri do zeljene lokacije */
      glutTimerFunc(20, on_timer, 0);
    break;
  case 1:
    rotation = 90;
    movementY -= 1;
    glutPostRedisplay();
    if(previousMovementY - 5 != movementY)
      glutTimerFunc(20, on_timer, 1);
    break;
  case 2:
    rotation = 180;
    movementX -= 1;
    glutPostRedisplay();
    if(previousMovementX - 5 != movementX)
      glutTimerFunc(20, on_timer, 2);
    break;
  case 3:
    rotation = 270;
    movementY += 1;
    glutPostRedisplay();
    if(previousMovementY + 5 != movementY)
      glutTimerFunc(20, on_timer, 3);
    break;
  }
}

static void on_display(void) {
    /* Postavlja se boja svih piksela na zadatu boju pozadine. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Postavlja se vidna tacka. */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(-30, 40, 0, 0, 0, 0, 1, 0, 0);

    /*Postavlja se pravac iz koga dolazi svetlost*/
    float l0pos[] = {-30.0f, 60.0f, 0.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, l0pos);

    /*Postavljamo okruzenje*/
    draw_floor(grassTexture);


    /* Postavljamo sliku psa */
    glPushMatrix();
      glTranslatef(movementX, 1.6*1.5, movementY);
      glRotatef(rotation, 0, 1, 0);
      glScalef(1.5, 1.5, 1.5);
      draw_dog();
    glPopMatrix();

    /* Postavlja se nova slika u prozor. */
    glutSwapBuffers();
}
