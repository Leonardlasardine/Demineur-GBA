#include "menu.h"
#include "mines.h"
#include "pause.h"

char *numbersStr[600];

//Emplacement de la sauvegarde
#define IDENTIFIER_STRING	"Difficultee"

typedef struct TSRAMDataBlock {
	unsigned char difficulty;
	unsigned char mines;
	unsigned char minesLeft;
	//cursor ?
}TSRAMDataBlock;

void save();
unsigned char load();
