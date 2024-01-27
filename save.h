unsigned char initSave();
void saveGrid();
void save();
unsigned char load();
void saveMenu();
void saveSettings(unsigned char volume, unsigned short color);
void deleteSave();

//Obtenir le score
unsigned char *getScorePseudo(unsigned char difficulty, unsigned char line, unsigned char *pseudo);
unsigned char getScoreH(unsigned char difficulty, unsigned char line);
unsigned char getScoreM(unsigned char difficulty, unsigned char line);
unsigned char getScoreS(unsigned char difficulty, unsigned char line);

//Ecrire le score
void setScorePseudo(unsigned char difficulty, unsigned char line, unsigned char *pseudo);
void setScoreH(unsigned char difficulty, unsigned char line, unsigned char value);
void setScoreM(unsigned char difficulty, unsigned char line, unsigned char value);
void setScoreS(unsigned char difficulty, unsigned char line, unsigned char value);
