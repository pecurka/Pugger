#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <time.h>

/* Deklaracije callback funkcija. */
static void on_reshape(int width, int height);
static void on_display(void);
static void on_keyboard(unsigned char key, int x, int y);
static void on_timer(int value);

/* Metod koji crta model psa i poda*/
static void draw_dog(void);
static void draw_floor(void);

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

    /* Ulazi se u glavnu petlju. */
    glutMainLoop();

    return 0;
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
    draw_floor();


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

static void draw_dog(void) {
#define glutCube glutSolidCube

  /* Postavljamo boju tela psa */
  glColor3f(.75, .6, .4);

  /* Crtamo telo */
  glPushMatrix();
    glScalef(2, 1, 1);
    glutCube(1);
  glPopMatrix();

  /* Crtamo rep */
  glPushMatrix();
    glColor3f(.3, .2, .1);
    glTranslatef(-1.5, .4, 0);
    glScalef(1, .2, .2);
    glutCube(1);
  glPopMatrix();

  /* Crtamo noge */
  glPushMatrix();
    glColor3f(.75, .6, .4);
    glTranslatef(-.7, -1, -.3);
    glScalef(.3, 1, .3);
    glutCube(1);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(-.7, -1, .3);
    glScalef(.3, 1, .3);
    glutCube(1);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(.7, -1, -.3);
    glScalef(.3, 1, .3);
    glutCube(1);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(.7, -1, .3);
    glScalef(.3, 1, .3);
    glutCube(1);
  glPopMatrix();

  /* Crtamo glavu */
  glPushMatrix();
    glTranslatef(1, .8, 0);
    glScalef(.7, .7, 1);
    glutCube(1);
  glPopMatrix();

  /* Crtamo njusku */
  glPushMatrix();
    glColor3f(.3, .2, .1);
    glTranslatef(1.5, .6, 0);
    glScalef(.4, .4, .4);
    glutCube(1);
  glPopMatrix();

  /* Crtamo usi */
  glPushMatrix();
    glColor3f(.3, .2, .1);
    glTranslatef(1, 1.2, -.3);
    glScalef(.1, .1, .1);
    glBegin( GL_TRIANGLES );
      glVertex3f( 0.0f, 1.f, 0.0f );
      glVertex3f( -1.0f, -1.0f, 1.0f );
      glVertex3f( 1.0f, -1.0f, 1.0f);

      glVertex3f( 0.0f, 1.0f, 0.0f);
      glVertex3f( -1.0f, -1.0f, 1.0f);
      glVertex3f( 0.0f, -1.0f, -1.0f);

      glVertex3f( 0.0f, 1.0f, 0.0f);
      glVertex3f( 0.0f, -1.0f, -1.0f);
      glVertex3f( 1.0f, -1.0f, 1.0f);


      glVertex3f( -1.0f, -1.0f, 1.0f);
      glVertex3f( 0.0f, -1.0f, -1.0f);
      glVertex3f( 1.0f, -1.0f, 1.0f);
    glEnd();
  glPopMatrix();

  glPushMatrix();
    glColor3f(.3, .2, .1);
    glTranslatef(1, 1.2, .3);
    glScalef(.1, .1, .1);
    glBegin( GL_TRIANGLES );
      glVertex3f( 0.0f, 1.f, 0.0f );
      glVertex3f( -1.0f, -1.0f, 1.0f );
      glVertex3f( 1.0f, -1.0f, 1.0f);

      glVertex3f( 0.0f, 1.0f, 0.0f);
      glVertex3f( -1.0f, -1.0f, 1.0f);
      glVertex3f( 0.0f, -1.0f, -1.0f);

      glVertex3f( 0.0f, 1.0f, 0.0f);
      glVertex3f( 0.0f, -1.0f, -1.0f);
      glVertex3f( 1.0f, -1.0f, 1.0f);


      glVertex3f( -1.0f, -1.0f, 1.0f);
      glVertex3f( 0.0f, -1.0f, -1.0f);
      glVertex3f( 1.0f, -1.0f, 1.0f);
    glEnd();
  glPopMatrix();

  /* Crtamo oci */
  glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(1.35, .9, -.3);
    glScalef(.1, .1, .1);
    glutSolidSphere(1, 20, 20);
  glPopMatrix();

  glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(1.35, .9, .3);
    glScalef(.1, .1, .1);
    glutSolidSphere(1, 20, 20);
  glPopMatrix();


#undef glutCube
}

static void draw_floor(void) {

  glPushMatrix();
    /* Trava */
    glColor3f(0,1,0);
    glBegin(GL_QUADS);
      glNormal3f(0, 1, 0);
      glVertex3f(-20,0,-30);
      glVertex3f(-12,0,-30);
      glVertex3f(-12,0,30);
      glVertex3f(-20,0,30);
    glEnd();

    glBegin(GL_QUADS);
      glNormal3f(0, 1, 0);
      glVertex3f(20,0,-30);
      glVertex3f(40,0,-30);
      glVertex3f(40,0,30);
      glVertex3f(20,0,30);
    glEnd();

    /* Autoput */
    glColor3f(0.2,0.2,0.2);
    glBegin(GL_QUADS);
      glNormal3f(0, 1, 0);
      glVertex3f(-12,0,-30);
      glVertex3f(20,0,-30);
      glVertex3f(20,0,30);
      glVertex3f(-12,0,30);
    glEnd();
  glPopMatrix();
}
