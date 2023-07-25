#include "mines.h"

//Video buffer
#define MODE_3 0x3
#define BG2_ENABLE 0x400

typedef enum Sens Sens;
enum Sens {
    HAUT, BAS, GAUCHE, DROITE
};

void move(Sens sens, unsigned char *x, unsigned char *y);

void grid(unsigned int seed);
void cursor (unsigned char x, unsigned char y, unsigned short c);
void drawCase(unsigned char x, unsigned char y);

//Timer
#define TIMER_FREQUENCY_SYSTEM 0x0
#define TIMER_ENABLE 0x80
#define REG_TM0CNT *(volatile u16*)0x4000102
#define REG_TM0D *(volatile u16*)0x4000100
