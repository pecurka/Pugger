#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "objects.h"

#define PI 3.14

static void draw_tire(void);

void draw_dog(void) {
#define glutCube glutSolidCube

  /* Postavljamo boju tela psa */
  glColor3f(.75, .6, .4);

  /* Crtamo telo */
  glPushMatrix();
    glScalef(2, 1, 1);
    glutCube(1);
  glPopMatrix();

  /* Crtamo noge */
  glPushMatrix();
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

  /* Postavljamo boju njuske, repa i usiju */
  glColor3f(.3, .2, .1);

  /* Crtamo rep */
  glPushMatrix();
    glTranslatef(-1.5, .4, 0);
    glScalef(1, .2, .2);
    glutCube(1);
  glPopMatrix();

  /* Crtamo njusku */
  glPushMatrix();
    glTranslatef(1.5, .6, 0);
    glScalef(.4, .4, .4);
    glutCube(1);
  glPopMatrix();

  /* Crtamo usi */
  glPushMatrix();
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
  glColor3f(0, 0, 0);
  glPushMatrix();
    glTranslatef(1.35, .9, -.3);
    glScalef(.1, .1, .1);
    glutSolidSphere(1, 20, 20);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(1.35, .9, .3);
    glScalef(.1, .1, .1);
    glutSolidSphere(1, 20, 20);
  glPopMatrix();


#undef glutCube
}

void draw_floor(GLuint grassTexture) {

  /* Trava */
  /* Gasi se osvetljenje i pali se tekstura trave */
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glBindTexture(GL_TEXTURE_2D, grassTexture);

  glPushMatrix();
    glBegin(GL_QUADS);
      glNormal3f(0, 1, 0);
      glTexCoord2f(0, 0); glVertex3f(-20,0,-30);
      glTexCoord2f(10, 0); glVertex3f(-12,0,-30);
      glTexCoord2f(10, 10); glVertex3f(-12,0,30);
      glTexCoord2f(0, 10); glVertex3f(-20,0,30);
    glEnd();

    glBegin(GL_QUADS);
      glNormal3f(0, 1, 0);
      glTexCoord2f(0, 0); glVertex3f(20,0,-30);
      glTexCoord2f(10, 0); glVertex3f(40,0,-30);
      glTexCoord2f(10, 10);glVertex3f(40,0,30);
      glTexCoord2f(0, 10); glVertex3f(20,0,30);
    glEnd();

    /* Gasi se tekstura i ponovo se pokrece osvetljenje*/
    glBindTexture(GL_TEXTURE_2D, 0);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

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

static void draw_tire(void) {
  glRotatef(90, 0, 1, 0);


  glBegin(GL_POLYGON);
    GLUquadricObj *obj = gluNewQuadric();
    gluCylinder(obj, 1.0, 1, 1, 30, 30);
  glEnd();
}

void draw_truck(void) {
#define glutCube glutSolidCube

  /* Crtamo glavni deo tela kamiona*/
  glColor3f(1, 0, 0);

  glPushMatrix();
    glScalef(0.5, 0.7, 1);
    glutCube(8);
  glPopMatrix();

  /* Crtamo kabinu kamiona*/
  glColor3f(1, 1, 1);

  glPushMatrix();
    glTranslatef(0, -0.75, 6);
    glScalef(0.5, 0.5, 0.5);
    glutCube(8);
  glPopMatrix();

  /* Crtamo tockove */
  glColor3f(0.05, 0.05, 0.05);

  glPushMatrix();
    glTranslatef(0.5, -3.5, 6);
    draw_tire();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(-1.5, -3.5, 6);
    draw_tire();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.5, -3.5, -2);
    draw_tire();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(-1.5, -3.5, -2);
    draw_tire();
  glPopMatrix();

#undef glutCube
}
