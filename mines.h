unsigned char checkMines(unsigned char x, unsigned char y);
void setGridValue(unsigned char x, unsigned char y, unsigned char value);
unsigned char getGridValue(unsigned char x, unsigned char y);
void reveal();
void drawSave();
void setMinesLeft(unsigned char value);
unsigned char getMinesLeft();
void resetGrid();

void drawCase(unsigned char x, unsigned char y);
void drawGrid();
void drawCaseFromSave(unsigned char x, unsigned char y);
