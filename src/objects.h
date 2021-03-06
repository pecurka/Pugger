#ifndef _H_OBJECTS_H_
#define _H_OBJECTS_H_

/* Struktura koja pamti tip vozila (auto ili kamion), u kojoj je traci i
   trenutnu poziciju */
typedef struct Vehicle {
  unsigned int typeOfVehicle;
  unsigned int lane;
  int position;
} Vehicle;


/* Metod koji crta model  psa */
void draw_dog(void);

/* Metod koji crta model poda */
void draw_floor(GLuint grassTexture);

/* Metod koji crta model kamiona */
void draw_truck(void);

/* Metod koji crta model automobila */
void draw_car(void);

/* Metod koja iscrtava broj smrti */
void draw_death_counter(const unsigned char* string);

/* Metod koja iscrtava tekst za pobedu */
void draw_victory_announcement(const unsigned char* string);

#endif
