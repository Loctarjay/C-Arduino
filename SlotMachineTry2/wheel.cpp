#include <arduino.h>
#include <stdio.h>
#include "wheel.h"

slotM mySlotM = {
  {111, 010, 001, 110, 000, 000, 011, 100, 101, 100}, //venstre
  {111, 010, 010, 001, 001, 110, 000, 011, 101, 100}, //midten
  {111, 010, 010, 010, 001, 110, 000, 011, 101, 101}, //højre
  20,                                                 //Start Kapital
  1,                                                  //Pris pr spin
  0                                                   //Total mængde spin
};                                                 

unsigned int getUserInput() {
  int input = 0;
  while (input == 0) {
    input = Serial.parseInt();
  }
  return input;
}

//hjulenes position
int leftPosition = 0;
int centerPosition = 0;
int rightPosition = 0;

volatile byte state = LOW;
int wheelUserInput = 0;

void wheelInterrupt() {
  state = !state;
  Serial.println("Wheel is going to stop");
}

//antal millisekunder før næste rotation
int delayTimer = 200;

//the counters on the diffrent win senarios
int c = 0, cc = 0, ccc = 0, bb = 0, bbb = 0, ooo = 0, aaa = 0, ppp = 0, ggg = 0, rrr = 0;


//en pointer til hvert hjul
char *left_ptr = &mySlotM.left[0];
char *center_ptr = &mySlotM.center[0];
char *right_ptr = &mySlotM.right[0];

//getter for at se Kapital-mængde
int getMySlotMMoney() {
  return mySlotM.money;
}

//vundne Kapital pr spil
int rollCheck(char left, char center, char right) {
  if ((left == 111) && (center == 111) && (right == 111)) {
    return 50;
  }
  if ((left == 011) && (center == 011) && (right == 011)) {
    return 24;
  }
  if ((left == 110) && (center == 110) && (right == 110)) {
    return 24;
  }
  if ((left == 000) && (center == 000) && (right == 000)) {
    return 18;
  }
  if ((left == 101) && (center == 101) && (right == 101)) {
    return 10;
  }
  if ((left == 001) && (center == 001) && (right == 001)) {
    return 16;
  }
  if ((center == 001) && (right == 001)) {
    return 8;
  }
  if ((left == 010) && (center == 010) && (right == 010)) {
    return 12;
  }
  if ((center == 010) && (right == 010)) {
    return 8;
  }
  if ((right == 010)) {
    return 2;
  }
  return 0;
}

//visuelt resultat for brugeren
char userVisual(char wheelNumber)
{
  if ( wheelNumber == 000) {
    return 'A';
  }
  else if ( wheelNumber == 001) {
    return 'B';
  }
  else if ( wheelNumber == 010) {
    return 'C';
  }
  else if ( wheelNumber == 011) {
    return 'G';
  }
  else if ( wheelNumber == 100) {
    return 'L';
  }
  else if ( wheelNumber == 101) {
    return 'O';
  }
  else if ( wheelNumber == 110) {
    return 'P';
  }
  else if ( wheelNumber == 111) {
    return 'R';
  }
};

//velkomst besked
void welcomeMessage() {
  Serial.println("Welcome to the one armed bandit!");
  Serial.println((String)"You start with: " + mySlotM.money + " credit.");
  Serial.println((String)"Credit per spin: " + mySlotM.price);
  Serial.println("_________________________________________________\n\n");
}

void spinWheels() {
  Serial.println("Press a number and the wheel will stop after a few spins");

  //angiv ny mængde ved hjælp af "seed"-funktion
  randomSeed(millis());

  //hjulene kører fra 2 - 11
  int leftSpinRandom = random(10) + 2;
  int leftCounter = 0;
  int centerSpinRandom = random(10) + 2;
  int centerCounter = 0;
  int rightSpinRandom = random(10) + 2;
  int rightCounter = 0;

  //hjulene kører indtil "interrupt" er sat igang hvorefter højre hjulet stopper
  while (rightCounter < rightSpinRandom) {
    Serial.println("\t\t_____________");
    Serial.println((String)"\t\t| " + userVisual(*(left_ptr + leftPosition)) + " | " + userVisual(*(center_ptr + centerPosition)) + " | " + userVisual(*(right_ptr + rightPosition)) + " |");
    Serial.println("\t\t‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾");
    delay(delayTimer);

    //start "interrupt" her
    wheelUserInput = Serial.parseInt();
    if (wheelUserInput != 0) {
      wheelInterrupt();
    }
    wheelUserInput = 0;
    if (state != LOW) {
      rightCounter++;
    }
    else {
      rightCounter = 0;
    }

    leftPosition++;
    centerPosition++;
    rightPosition++;
    if (leftPosition == (wheelLength)) {
      leftPosition = 0;
    }
    if (centerPosition == (wheelLength)) {
      centerPosition = 0;
    }
    if (rightPosition == (wheelLength)) {
      rightPosition = 0;
    }
  }
  Serial.println("Right wheel has stopped.");

  //nulstil "state"
  state = LOW;

  //hjulene kører indtil "interrupt" er sat igang hvorefter center hjulet stopper
  while (centerCounter < centerSpinRandom) {
    Serial.println("\t\t_____________");
    Serial.println((String)"\t\t| " + userVisual(*(left_ptr + leftPosition)) + " | " + userVisual(*(center_ptr + centerPosition)) + " | " + userVisual(*(right_ptr + rightPosition)) + " |");
    Serial.println("\t\t‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾");
    delay(delayTimer);

    //start "interrupt" her
    wheelUserInput = Serial.parseInt();
    if (wheelUserInput != 0) {
      wheelInterrupt();
    }
    wheelUserInput = 0;
    if (state != LOW) {
      centerCounter++;
    }
    else {
      centerCounter = 0;
    }

    leftPosition++;
    centerPosition++;
    if (leftPosition == (wheelLength)) {
      leftPosition = 0;
    }
    if (centerPosition == (wheelLength)) {
      centerPosition = 0;
    }
  }
  Serial.println("Center wheel has stopped.");

  //nulstil "state"
  state = LOW;

  //sidste hjul kører indtil "interrupt" bliver kaldt
  while (leftCounter < leftSpinRandom) {
    Serial.println("\t\t_____________");
    Serial.println((String)"\t\t| " + userVisual(*(left_ptr + leftPosition)) + " | " + userVisual(*(center_ptr + centerPosition)) + " | " + userVisual(*(right_ptr + rightPosition)) + " |");
    Serial.println("\t\t‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾");
    delay(delayTimer);

    //Start "interrupt" her
    wheelUserInput = Serial.parseInt();
    if (wheelUserInput != 0) {
      wheelInterrupt();
    }
    wheelUserInput = 0;
    if (state != LOW) {
      leftCounter++;
    }
    else {
      leftCounter = 0;
    }

    leftPosition++;
    if (leftPosition == (wheelLength)) {
      leftPosition = 0;
    }
  }
  Serial.println("Left wheel has stopped.");

  //print the final wheel result
  Serial.println("Your final result is: ");
  Serial.println("\t\t_____________");
  Serial.println((String)"\t\t| " + userVisual(*(left_ptr + leftPosition)) + " | " + userVisual(*(center_ptr + centerPosition)) + " | " + userVisual(*(right_ptr + rightPosition)) + " |");
  Serial.println("\t\t‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾");

  //update the money amound
  moneyHandler((*(left_ptr + leftPosition)), (*(center_ptr + centerPosition)), (*(right_ptr + rightPosition)));

  //add the result to the statistiks
  statsHandler((*(left_ptr + leftPosition)), (*(center_ptr + centerPosition)), (*(right_ptr + rightPosition)));

  //nulstil state og klar til næste spil
  state = LOW;
}

void spinWheelsMore() {
  //angiv ny mængde ved hjælp af "seed"-funktion
  randomSeed(millis());

  //tilfældig mængde spin pr hjul
  int leftSpinRandom = random(1, 11);
  int centerSpinRandom = random(1, 11);
  int rightSpinRandom = random(1, 11);

  //find hjulenes position
  for (int i = 0; i < leftSpinRandom; i++) {
    leftPosition++;
    if (leftPosition == (wheelLength)) {
      leftPosition = 0;
    }
  }
  for (int i = 0; i < centerSpinRandom; i++) {
    centerPosition++;
    if (centerPosition == (wheelLength)) {
      centerPosition = 0;
    }
  }
  for (int i = 0; i < rightSpinRandom; i++) {
    rightPosition++;
    if (rightPosition == (wheelLength)) {
      rightPosition = 0;
    }
  }

  //print spillets resultat
  Serial.println("Your final result is: ");
  Serial.println("\t\t_____________");
  Serial.println((String)"\t\t| " + userVisual(*(left_ptr + leftPosition)) + " | " + userVisual(*(center_ptr + centerPosition)) + " | " + userVisual(*(right_ptr + rightPosition)) + " |");
  Serial.println("\t\t‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾");

  //opdater den totale Kapital
  moneyHandler((*(left_ptr + leftPosition)), (*(center_ptr + centerPosition)), (*(right_ptr + rightPosition)));

  //tilføj til statistikken
  statsHandler((*(left_ptr + leftPosition)), (*(center_ptr + centerPosition)), (*(right_ptr + rightPosition)));
}

//opdater den totale Kapital
void moneyHandler(char left, char center, char right) {
  mySlotM.money = mySlotM.money - mySlotM.price + rollCheck(left, center, right);
  Serial.println((String)"You now have " + mySlotM.money + "credits left");
}

//add the 1 to the win counters and the total of spins
void statsHandler(char left, char center, char right) {
  if ((left == 111) && (center == 111) && (right == 111)) {
    rrr++;
  }
  else if ((left == 011) && (center == 011) && (right == 011)) {
    ggg++;
  }
  else if ((left == 110) && (center == 110) && (right == 110)) {
    ppp++;
  }
  else if ((left == 000) && (center == 000) && (right == 000)) {
    aaa++;
  }
  else if ((left == 101) && (center == 101) && (right == 101)) {
    ooo++;
  }
  else if ((left == 001) && (center == 001) && (right == 001)) {
    bbb++;
  }
  else if ((center == 001) && (right == 001)) {
    bb++;
  }
  else if ((left == 010) && (center == 010) && (right == 010)) {
    ccc++;
  }
  else if ((center == 010) && (right == 010)) {
    cc++;
  }
  else if ((right == 010)) {
    c++;
  }
  mySlotM.totalSpin++;
}

// print the % of the diffrent wins and the % of now wins
void stats() {
  Serial.println((String)"You spinned: " + mySlotM.totalSpin + " times");
  Serial.println((String)"RRR: " + (double)rrr / mySlotM.totalSpin * 100 + "%");
  Serial.println((String)"GGG: " + (double)ggg / mySlotM.totalSpin * 100 + "%");
  Serial.println((String)"PPP: " + (double)ppp / mySlotM.totalSpin * 100 + "%");
  Serial.println((String)"AAA: " + (double)aaa / mySlotM.totalSpin * 100 + "%");
  Serial.println((String)"OOO: " + (double)ooo / mySlotM.totalSpin * 100 + "%");
  Serial.println((String)"BBB: " + (double)bbb / mySlotM.totalSpin * 100 + "%");
  Serial.println((String)"BB: " + (double)bb / mySlotM.totalSpin * 100 + "%");
  Serial.println((String)"CCC: " + (double)ccc / mySlotM.totalSpin * 100 + "%");
  Serial.println((String)"CC: " + (double)cc / mySlotM.totalSpin * 100 + "%");
  Serial.println((String)"C: " + (double)c / mySlotM.totalSpin * 100 + "%");
  Serial.println((String)"no win: " + (double)(mySlotM.totalSpin - (rrr + ggg + ppp + aaa + ooo + bbb + bb + ccc + cc + c)) / mySlotM.totalSpin * 100 + "%");
}
