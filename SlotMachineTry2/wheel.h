#ifndef WHEEL_H_INCLUDED
#define WHEEL_H_INCLUDED

#define wheelLength 10

typedef struct slotM{
    char left[wheelLength];
    char center[wheelLength];
    char right[wheelLength];
    int money;
    int price;
    int totalSpin;
} slotM;

unsigned int getUserInput();
int getMySlotMMoney();
int rollCheck(char left, char center, char right);
void welcomeMessage();
void spinWheels();
void spinWheelsMore();
void moneyHandler(char left, char center, char right);
void statsHandler(char left, char center, char right);
void stats();
void wheelInterrupt();

#endif // WHEEL_H_INCLUDED
