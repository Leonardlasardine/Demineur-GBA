int control();
int menu();

//Video buffer
#define MODE_3 0x3
#define BG2_ENABLE 0x400

#ifndef DIRECTIONS
#define DIRECTIONS

typedef enum Sens Sens;
enum Sens {
    HAUT, BAS, GAUCHE, DROITE, SUPER_GAUCHE, SUPER_DROITE
};

#endif
