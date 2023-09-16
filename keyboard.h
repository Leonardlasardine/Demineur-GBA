void drawScreen(const unsigned short screen[38400]);
void drawLine(unsigned char x, unsigned char y, unsigned char l, unsigned char h, unsigned short c);

unsigned char *keyboard(unsigned char *pseudo);
void drawKeyboard();
void moveKey(Sens sens, unsigned char *x, unsigned char *y);
void keyCursor(unsigned char x, unsigned char y, unsigned short c);
void writePseudo(unsigned char *pseudo, unsigned char *pos);
