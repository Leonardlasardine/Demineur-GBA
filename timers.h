//Timer 2 utilisé pour les nombres aléatoires
//dans le menu principal puis pour attendre
//des délais courts le reste du jeu.

//Timer 2 = Nombre aléatoire
#define TIMER_FREQUENCY_SYSTEM 0x0

void startTimer2();
void stopTimer2();
void restartTimer2();
void Timer2Function(void);

unsigned int getTimerCount();
void setTimerCount(unsigned int v);
unsigned int getSeed();
void setSeed(unsigned int newSeed);

//Delais courts
unsigned short getDelay();
void waitTime(unsigned short time);


//Timer 3 = Compte me temps pendant un niveau
void initTimer3();
void Timer3Function(void);
void stopTimer3();
void startTimer3();

//Temps
unsigned char getHours();
unsigned char getMinutes();
unsigned char getSeconds();
void setTime(unsigned char hours, unsigned char minutes, unsigned char seconds);
