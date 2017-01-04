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

/* Iicijalizuju se vozila */
static void initializeVehicles(void);

/*Deklaracija promenljive za rotaciju i kretanje modela psa, kretanje vozila
  kao i ostale bitne podatke */
static int rotation;
static int movementX;
static int movementY;
static int previousMovementX;
static int previousMovementY;
static int isMoving;
static int numberOfVehicles = 12; /* Promeniti ovaj broj da bi se promenio broj vozila */
static Vehicle *vehicles;
static int deaths;
static char deathCount[10];
static int isVictory;


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
    isMoving = 0;
    deaths = 0;
    isVictory = 0;
    vehicles = malloc(numberOfVehicles * sizeof(Vehicle));
    initializeVehicles();

    /*Pokrecemo animaciju kamiona i automobila*/
    glutTimerFunc(60, on_timer, 4);

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

static void initializeVehicles(void) {
  /* Inicijalizuje se niz vozila */
  int i;

  for(i = 0; i < numberOfVehicles; i++) {
    if(i % 4 == 0 || i % 4 == 2) {
      vehicles[i].typeOfVehicle = 0;
      vehicles[i].position = -50 + (i/4) * 30;
    } else {
      vehicles[i].typeOfVehicle = 1;
      vehicles[i].position = 50 + (i/4) * 30;
    }

    vehicles[i].lane = i % 4;
  }
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
    /* Pamti se prethodna pozicija i poziva se funkcija za iscrtavanje nove
      Ne dopusta pomeranje unapred ako je pas stigao do kraja scene */
    if(movementX < 30 && isVictory == 0 && isMoving == 0) {
      isMoving = 1; /* Sprecava Pugger da pobegne sa ekrana ako se vec krece */
      previousMovementX = movementX;
      glutTimerFunc(20, on_timer, 0);
    }
    break;
  case 'a':
  case 'A':
    if(movementY > -30 && isVictory == 0 && isMoving == 0) {
      isMoving = 1;
      previousMovementY = movementY;
      glutTimerFunc(20, on_timer, 1);
    }
    break;
  case 's':
  case 'S':
    if(movementX > -20 && isVictory == 0 && isMoving == 0) {
      isMoving = 1;
      previousMovementX = movementX;
      glutTimerFunc(20, on_timer, 2);
    }
    break;
  case 'd':
  case 'D':
    if(movementY < 30 && isVictory == 0 && isMoving == 0) {
      isMoving = 1;
      previousMovementY = movementY;
      glutTimerFunc(20, on_timer, 3);
    }
    break;
  case 'r':
  case 'R':
    /* Resetuje se igrica */
    rotation = 0;
    movementX = -15;
    movementY = 0;
    previousMovementX = movementX;
    previousMovementY = movementY;
    isMoving = 0;
    deaths = 0;
    isVictory = 0;
    initializeVehicles();
    break;
  }
}

static void on_timer(int value) {
  int i;

  /* Ako je pas stigao do kraja postavlja promenljivu na tacno i time je igrac pobedio */
  if(movementX == 25) {
    isVictory = 1;
  }

  /* Gledamo koje dugme je pritisnuto i pomeramo psa u potrebnom pravcu i rotiramo ga u potreban smer */
  switch (value) {
  case 0:
    rotation = 0;
    movementX += 1;
    glutPostRedisplay();
    if(previousMovementX + 5 != movementX) /* Da bi kretanje izgleda 'glatko' teramo da ponavlja isrtavanje dok se ne pomeri do zeljene lokacije */
      glutTimerFunc(20, on_timer, 0);
    else
      isMoving = 0;
    break;
  case 1:
    rotation = 90;
    movementY -= 1;
    glutPostRedisplay();
    if(previousMovementY - 5 != movementY)
      glutTimerFunc(20, on_timer, 1);
    else
      isMoving = 0;
    break;
  case 2:
    rotation = 180;
    movementX -= 1;
    glutPostRedisplay();
    if(previousMovementX - 5 != movementX)
      glutTimerFunc(20, on_timer, 2);
    else
      isMoving = 0;
    break;
  case 3:
    rotation = 270;
    movementY += 1;
    glutPostRedisplay();
    if(previousMovementY + 5 != movementY)
      glutTimerFunc(20, on_timer, 3);
    else
      isMoving = 0;
    break;
  /* Postavlja se kretanje vozila */
  case 4:
    /* Prolazimo kroz svako vozilo i proveravamo da li je pas udaren */
    for(i = 0; i < numberOfVehicles; i++) {
      int isHit = 0;

      switch (vehicles[i].lane) {
      case 0:
        if((movementX == -10 || movementX == -5) && vehicles[i].position >  movementY - 10 && vehicles[i].position < movementY + 6)
          isHit = 1;
        break;
      case 1:
        if(movementX == 0 && vehicles[i].position >  movementY - 6 && vehicles[i].position < movementY + 6)
          isHit = 1;
        break;
      case 2:
        if((movementX == 5 || movementX == 10) && vehicles[i].position >  movementY - 10 && vehicles[i].position < movementY + 6)
          isHit = 1;
        break;
      case 3:
        if(movementX == 15 && vehicles[i].position >  movementY - 6 && vehicles[i].position < movementY + 6)
          isHit = 1;
        break;
      }

      /* Ako je pas udaren vracamo ga na pocetak igre i registrujemo smrt */
      if(isHit) {
        movementX = -15;
        movementY = 0;
        deaths++;
      }

      /* Pomeramo vozilo */
      if(vehicles[i].typeOfVehicle == 0) {
        if(vehicles[i].position < 50)
          vehicles[i].position += 1;
        else
          vehicles[i].position = -50;
      } else {
        if(vehicles[i].position > -50)
          vehicles[i].position -= 1;
        else
          vehicles[i].position = 50;
      }
    }

    glutPostRedisplay();
    glutTimerFunc(60, on_timer, 4);
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

    /* Postavljamo brojac smrti */
    sprintf(deathCount, "DEATHS: %d", deaths);
    draw_death_counter(deathCount);

    /* Postavljamo sliku psa */
    glPushMatrix();
      glTranslatef(movementX, 1.6*1.5, movementY);
      glRotatef(rotation, 0, 1, 0);
      glScalef(1.5, 1.5, 1.5);
      draw_dog();
    glPopMatrix();

    /* Postavljamo sliku vozila */
    int i;

    for(i = 0; i < numberOfVehicles; i++) {
      int lane;
      float heightOfVehicle;

      /* Gledamo u kojoj je traci vozilo i postavljamo vrednost x za translaciju */
      switch (vehicles[i].lane) {
        case 0:
          lane = -8;
          break;
        case 1:
          lane = 0;
          break;
        case 2:
          lane = 8;
          break;
        case 3:
          lane = 15;
          break;
      }

      /* Gledamo koje je vrste vozilo i postavljamo vrednost y za translaciju */
      if(vehicles[i].typeOfVehicle == 0)
        heightOfVehicle = 4.5;
      else
        heightOfVehicle = 3.5;

      glPushMatrix();
        glTranslatef(lane, heightOfVehicle, vehicles[i].position);
        if(vehicles[i].typeOfVehicle == 0)
          draw_truck();
        else
          draw_car();
      glPopMatrix();
    }

    /* Ako je korisnik pobedio iscrtava se tekst pobede */
    if(isVictory == 1) {
      draw_victory_announcement("VICTORY!\nTO REPLAY PRESS R.\nTO EXIT PRESS ESC.");
    }

    /* Postavlja se nova slika u prozor. */
    glutSwapBuffers();
}
