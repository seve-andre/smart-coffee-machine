#include <LiquidCrystal_I2C.h>
#include <EnableInterrupt.h>

#include "Beverage.h"
#include "BootMain.h"
#include "Boot.h"
#include "Ready.h"
#include "Indent.h"
#include "Assistance.h"
#include "ServoMotor.h"

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,20,4);

Boot* bootMachine;
Ready* readyMachine;
Assistance* ast;
Beverage* drink;
ServoMotor* myservo;

int btn_up = 5;
int btn_down = 4;
int btn_selection = 6;

unsigned int readyState;

//State-2
//Sezione LCD
const int colIndent = 0;
Indent* rowIndent;

//Sezione beverage
unsigned int n_coffee;
unsigned int n_thea;
unsigned int n_chocolate;
unsigned long timerIdle;
unsigned int menuOption;

boolean isCoffeeActive;
boolean isTheaActive;
boolean isChocolateActive;
boolean isPrint;
boolean isAssistanceRequired;
boolean isAssistanceRequiredPrint;
boolean isMenuInitialize;

void setup() {
  Serial.begin(9600);
  //lcd initialization
  lcd.init();
  lcd.backlight();
  
  bootMachine = new Boot();
  readyMachine = new Ready();
  rowIndent = new Indent();
  ast = new Assistance();
  drink = new Beverage();
  myservo = new ServoMotor(9);

  readyState = 0;
  isMenuInitialize = false;
}

void loop() {  
  returnToReadyState();

  switch(readyState) {
    case 0:
      bootButtonIntialization();
      bootMachine->initialization();
    break;

    case 1:
      bootButtonIntialization();
      readyMachine->showReadyMessage();
      isMenuInitialize = false;
    break;

    case 2:
      menuInitialization();
      loopMenu();
    break;

    case 3:
      isAssistanceRequired = true;
      ast->assistanceRequired();
    break;

    //Stato->MakingDrink
    case 4:
      timerIdle = millis();
      myservo->prepareDrink(rowIndent->getPositionIndent());
    break;

    //Stato->ProductReady
    case 5:
    //...
    break;
  }
}

void bootButtonIntialization() {
  enableInterrupt(btn_selection, goToMenuState, RISING);
  enableInterrupt(btn_down, goToMenuState, RISING);
  enableInterrupt(btn_up, goToMenuState, RISING);  
}

void goToMenuState() {
  if (bootMachine->isInitializationComplete()) {
    readyState = 2;
  }
}

//State-2
//-------------------------------

void loopMenu() {  
  if (drink->getNThea() == 0 || drink->getNChocolate() == 0 || drink->getNCoffee() == 0) {
    readyState = 3;
  }

  if (!isAssistanceRequired) {
    menuOption = rowIndent->getPositionIndent();
    delay(30);
    
    switch(menuOption) {
      case 0:
        if (isPrint) {
          isPrint = false;
          lcd.clear();
          drink->printCoffeeMessage();
        }
      break;

      case 1:
        if (isPrint) {
          isPrint = false;
          lcd.clear();
          drink->printTheaMessage();
        }
      break;

      case 2:
        if (isPrint) {
          isPrint = false;
          lcd.clear();
          drink->printChocolateMessage();
        }
      break;
    }
  }
}

void menuInitialization() {
  if (!isMenuInitialize) {
    enableInterrupt(btn_selection, selectBeverage, FALLING);
    enableInterrupt(btn_down, movePrev, RISING);
    enableInterrupt(btn_up, moveNext, RISING);

    //Da inserire in altro metodo separato
    isPrint = true;
    isAssistanceRequired = false;
    isAssistanceRequiredPrint = false;

    //TO-DO
    //Da inserire in altro metodo perchè altrimenti scatta allo stato Ready dopo 10s
    //timerIdle = millis();
    isMenuInitialize = true;
  }
}

void moveNext() {
  timerIdle = millis();
  rowIndent->moveNext();
  isPrint = true;
  delay(50);
}

void movePrev() {
  timerIdle = millis();  
  rowIndent->movePrev();
  isPrint = true;
  delay(50);
}

void selectBeverage() {
  timerIdle = millis();
  menuOption = rowIndent->getPositionIndent();
  int buttonSelection = digitalRead(btn_selection);
  //Serial.println(drink->getNCoffee());

  delay(50);
  if (buttonSelection == LOW) {
    switch(menuOption) {
      case 0:
        drink->takeACoffee();
        readyState = 4;
      break;
    
      case 1:
        drink->takeAThea();
        readyState = 4; 
      break;

      case 2:
        drink->takeAChocolate();
        readyState = 4;
      break;
    }
  }
}

void returnToReadyState() {  
  //Interrupt
  if ((millis() - timerIdle) >= 5000 && !isAssistanceRequired) {
      timerIdle = millis();
      lcd.clear();
      readyMachine->resetIsFirstReady();
      readyState = 1;
      Serial.println("Ready");
  }
}
