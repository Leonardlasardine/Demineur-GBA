#include "mines.h"

#define TEXT_MODE 0

//Video buffer
#define MODE_3 0x3
#define BG2_ENABLE 0x400

typedef enum Sens Sens;
enum Sens {
    HAUT, BAS, GAUCHE, DROITE
};

void move(Sens sens, unsigned char *x, unsigned char *y);

int grid();
void cursor (unsigned char x, unsigned char y, unsigned short c);
void drawCase(unsigned char x, unsigned char y);
