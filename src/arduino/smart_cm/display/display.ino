#include <LiquidCrystal_I2C.h>
#include <EnableInterrupt.h>

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,20,4); 

//Sezione BTN
int btn_up = 4;
int btn_down = 5;
int btn_selection = 6;

//Sezione LCD
const int colIndent = 0;
unsigned int rowIndent;

//Sezione beverage
unsigned int n_coffee;
unsigned int n_thea;
unsigned int n_chocolate;

boolean isCoffeeActive;
boolean isTheaActive;
boolean isChocolateActive;

void setup() {
  Serial.begin(9600);
  rowIndent = 0; 

  isCoffeeActive = true;
  isTheaActive = true;
  isChocolateActive = true;

  n_thea = 5;
  n_coffee = 5;
  n_chocolate = 5;
  
  lcd.init();
  lcd.backlight();

  lcd.setCursor(colIndent, rowIndent); // Set the cursor on the third column and first row.
  lcd.print("-");
  lcd.setCursor(2, 0); // Set the cursor on the third column and first row.
  lcd.print("making a coffee");
  lcd.setCursor(2, 1); // Set the cursor on the third column and first row.
  lcd.print("making a tea");
  lcd.setCursor(2, 2); // Set the cursor on the third column and first row.
  lcd.print("making a chocolate");

  pinMode(btn_up, INPUT);
  pinMode(btn_down, INPUT);
  pinMode(btn_selection, INPUT);

  //enableInterrupt(5, pushDown, CHANGE);
  //enableInterrupt(4, pushUP, CHANGE);
}

void loop() {

  if (n_thea > 0 && n_chocolate > 0 && n_coffee > 0) {
    if (isCoffeeActive) {
      lcd.setCursor(2, 0);
      lcd.print("making a coffee");
    }

    if (isTheaActive) {
      lcd.setCursor(2, 1);
      lcd.print("making a tea");
    }

    if (isChocolateActive) {
      lcd.setCursor(2, 2);
      lcd.print("making a chocolate");
    }
  
    delay(150);
    int buttonStateDown = digitalRead(btn_down);
    int buttonStateUP = digitalRead(btn_up);
    int buttonSelection = digitalRead(btn_selection);
  
    if (buttonStateUP == HIGH) {
      Serial.println("pushUp");
      pushUP();
    } 
  
    if (buttonStateDown == HIGH) {
      Serial.println("pushDown");
      pushDown();
    }

    if (buttonSelection == HIGH) {
      selectBeverage();
      lcd.clear();
    } 
  
  } else if (n_thea == 0 || n_chocolate == 0 || n_coffee == 0) {
    printAssistanceRequired();
  }
}

void pushDown() {
  if (rowIndent < 2) {      
      rowIndent++;

      lcd.clear();
      lcd.setCursor(colIndent, rowIndent); // Set the cursor on the third column and first row.
      lcd.print("-");
  }
}

void pushUP() {  
  if (rowIndent > 0) {      
      rowIndent--;

      lcd.clear();
      lcd.setCursor(colIndent, rowIndent); // Set the cursor on the third column and first row.
      lcd.print("-");
  }
}

void selectBeverage() {
  Serial.print(n_coffee);
  Serial.print(n_thea);
  Serial.println(n_chocolate);
  
  switch(rowIndent) {
    case 0:
      n_coffee--;
    break;
    
    case 1:
      n_thea--;
    break;

    case 2:
      n_chocolate--;
    break;
  }
}

void printAssistanceRequired() {
  lcd.setCursor(1,2);
  lcd.print("Assistance Required");
}
