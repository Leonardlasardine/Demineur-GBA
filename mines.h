unsigned char checkMines(unsigned char x, unsigned char y);

void setGridValue(unsigned char x, unsigned char y, unsigned char value);
unsigned char getGridValue(unsigned char x, unsigned char y);

void grid(unsigned int seed, unsigned char x, unsigned char y);
void resetGrid();

void reveal();
void drawSave();
unsigned short countCases(unsigned char value);
unsigned short countUnrevealed();
unsigned char checkWon();

void setMinesLeft(unsigned char value);
unsigned char getMinesLeft();
signed short getFlagsLeft();
void countRevealedCase();
void setUnrevealedCase(unsigned short value);
void setWrongFlags(unsigned short value);
unsigned short getWrongFlags();
