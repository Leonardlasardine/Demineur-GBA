unsigned char initSave();
void saveGrid();
void save();
unsigned char load();
void saveMenu();
void saveSettings(unsigned char volume);
void deleteSave();

//SCORES D'UN NIVEAU
typedef struct SRAM_SCORE {
	char pseudo[20]; //Changer taille
	unsigned char s_H, s_M, s_S;;
}SRAM_SCORE;
