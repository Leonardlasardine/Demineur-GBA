//Timer 0 = Nombre aléatoire
#define TIMER_FREQUENCY_SYSTEM 0x0
void startTimer0();
void Timer0Function(void);
unsigned int getTimerCount();

//Timer 3 = Temps d'un niveau
void startTimer3();
void Timer3Function(void);
void stopTimer3();
void restartTimer3();

//Temps
unsigned char getHours();
unsigned char getMinutes();
unsigned char getSeconds();
void setTime(unsigned char hours, unsigned char minutes, unsigned char seconds);
