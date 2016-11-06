#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>


/* Deklaracije callback funkcija. */
static void on_reshape(int width, int height);
static void on_display(void);
static void on_keyboard(unsigned char key, int x, int y);


/* Metod koji crta model psa */
static void draw_dog(void);

/*Deklaracija promenljive za rotaciju modela*/
static int rotation;


int main(int argc, char **argv) {
    /* Inicijalizuje se GLUT. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    /* Kreira se prozor. */
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(200, 100);
    glutCreateWindow(argv[0]);

    /* Registruju se funkcije za obradu dogadjaja. */
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
    glutKeyboardFunc(on_keyboard);


    /* Obavlja se OpenGL inicijalizacija. */
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    /*Inicijalizuju se globalne promenljive*/
    rotation = 0;

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
    /* Menja se rotacija u odnosu na stisnuto dugme i forsira ponovno crtanje scene. */
    case 'w':
    case 'W':
      rotation = 0;
      glutPostRedisplay();
      break;
    case 'a':
    case 'A':
      rotation = 90;
      glutPostRedisplay();
      break;
    case 's':
    case 'S':
      rotation = 180;
      glutPostRedisplay();
      break;
    case 'd':
    case 'D':
      rotation = 270;
      glutPostRedisplay();
      break;
    }
}

static void on_display(void) {
    /* Postavlja se boja svih piksela na zadatu boju pozadine. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Postavlja se vidna tacka. */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(-20, 10, 0, 0, 0, 0, 1, 0, 0);

    /* Postavljamo sliku psa */
    glPushMatrix();

      glRotatef(rotation, 0, 1, 0);
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
