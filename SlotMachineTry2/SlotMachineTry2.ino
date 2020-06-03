#include "wheel.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), wheelInterrupt, CHANGE);
  welcomeMessage();
}

int userInput;

void loop() {
  Serial.println("Enter the number corresponding to your choice.");
  Serial.println("Press: 1 - Manual play.");
  Serial.println("Press: 2 - Spin a certain amount of time.");
  Serial.println("Press: 3 - Show statistics.");
  Serial.println();
  Serial.println();
  userInput = getUserInput();
  //manuelt spil
  if(userInput == 1){
    while(true){
      Serial.println("Press: 1 - Spin");
      Serial.println("Press: 2 - Exit");
      Serial.println();
      Serial.println();
      userInput = getUserInput();
      if(getMySlotMMoney <= 0){
        Serial.println("You have 0 credit left.");
        break;
      }
      if(userInput == 1){
        spinWheels();
      }
      else if(userInput == 2){
        break;
      }
    }
  }
  //vælg antal gange du vil spille
  else if(userInput == 2){
    if(getMySlotMMoney <= 0){
      Serial.println("You have 0 credit left.");
    }
    else{
      Serial.println("Press: the number of times you wanna spin");
      userInput = getUserInput();
      
      for(int i = 0; i < userInput; i++){
        spinWheelsMore();
        if(getMySlotMMoney <= 0){
          Serial.println("You have 0 credit left.");
          break;
        }
      }
    }
  }
  //se din statistik
  else if(userInput == 3){
    stats();
  }
}
