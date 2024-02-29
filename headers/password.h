unsigned long long concatenate(unsigned long long x, unsigned long long y);
unsigned long long concatenateArray(unsigned char *pseudo);//ne sert plus
unsigned long long power(unsigned long long base, unsigned char exp);

unsigned int getPasswordSeed(unsigned long long base10);
unsigned char getPasswordDifficulty(unsigned long long base10);
unsigned char getPasswordMines(unsigned long long base10);
unsigned short getPasswordFirstCase(unsigned long long base10);

unsigned long long convertToBase10(unsigned char *base39);
unsigned char *convertToBase39(unsigned long long base10, unsigned char *newPseudo);

void writePassword() ;
