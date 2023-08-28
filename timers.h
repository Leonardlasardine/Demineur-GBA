//Timer 0
#define TIMER_FREQUENCY_SYSTEM 0x0
#define TIMER_ENABLE 0x80
#define REG_TM0CNT *(volatile u16*)0x4000102
#define REG_TM0D *(volatile u16*)0x4000100

//Timer 3
void startTimer3();
void Timer3Function(void);
void stopTimer3();
void restartTimer3();
