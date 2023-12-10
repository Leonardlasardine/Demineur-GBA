#include "libham.h"
#include <mygba.h>

void control(unsigned char newGame);
unsigned char menu();
unsigned char selectionMenu();
unsigned char *keyboard(unsigned char *pseudo);
void loadMenu();

void wait();

//Video buffer
#define MODE_3 0x3
#define BG2_ENABLE 0x400

#ifndef DIRECTIONS
#define DIRECTIONS

typedef enum Sens Sens;
enum Sens {
    HAUT, BAS, GAUCHE, DROITE, SUPER_GAUCHE, SUPER_DROITE, NUL
};

#endif
