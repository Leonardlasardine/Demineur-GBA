#include "menu.h"
#include "mines.h"
#include "pause.h"

char *numbersStr[600];

//Emplacement de la sauvegarde
#define IDENTIFIER_STRING	"Partie"

typedef struct TSRAMDataBlock {
	unsigned char gameExist;
	unsigned char difficulty;
	unsigned char mines;
	unsigned char minesLeft;
	//cursor ?
	//temps
}TSRAMDataBlock;

unsigned char initSave();
void saveGrid(unsigned char textX, unsigned char textY);
void save();
unsigned char load();
