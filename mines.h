unsigned char checkMines(unsigned char x, unsigned char y);

void setGridValue(unsigned char x, unsigned char y, unsigned char value);
unsigned char getGridValue(unsigned char x, unsigned char y);

void grid(unsigned int seed, unsigned char x, unsigned char y);
void resetGrid();

void reveal();
void drawSave();

void setMinesLeft(unsigned char value);
unsigned char getMinesLeft();
