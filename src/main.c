#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>


/* Deklaracije callback funkcija. */
static void on_reshape(int width, int height);
static void on_display(void);
static void on_keyboard(unsigned char key, int x, int y);


/* Metod koji crta model psa i poda*/
static void draw_dog(void);
static void draw_floor(void);

/*Deklaracija promenljive za rotaciju modela*/
static int rotation;


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


    /* Obavlja se OpenGL inicijalizacija. */
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    /* Pali se osvetljenje */
    float diffuse_light[] = {1.0f, 1.0f, 1.0f, 1.0f};
    float specular_light[] = {1.0f, 1.0f, 0.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glColorMaterial(GL_FRONT, GL_DIFFUSE);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

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
    gluLookAt(-20, 30, 0, 0, 0, 0, 1, 0, 0);

    /*Postavlja se pravac iz koga dolazi svetlost*/
    float l0pos[] = {-30.0f, 60.0f, 0.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, l0pos);

    /*Postavljamo okruzenje*/
    draw_floor();


    /* Postavljamo sliku psa */
    glPushMatrix();
      glTranslatef(0, 1.6, 0);
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

static void draw_floor(void) {

  glColor3f(0,1,0);
  glPushMatrix();
  glBegin(GL_QUADS);
    /* Floor */
    glNormal3f(0, 1, 0);
    glVertex3f(-60,0,-30);
    glVertex3f(120,0,-30);
    glVertex3f(120,0,30);
    glVertex3f(-60,0, 30);
  glEnd();

  glPopMatrix();
}
