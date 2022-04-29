#include "Lcd.h"

Lcd* Lcd::instance = 0;

Lcd* Lcd::getInstance() {
    if (instance == 0) {
        instance = new Lcd();
    }
    return instance;
}

void Lcd::print(char message[]) {
  printNewMessageAt(1, 0, message);
}

void Lcd::printAt(int n_col, int n_row, char message[]) {
  printNewMessageAt(n_col, n_row, message);
}

void Lcd::clear() {
  lcd.clear();
}

// private - called for internal printing from public methods
void Lcd::printNewMessageAt(int n_col, int n_row, char message[]) {
  lcd.clear();
  lcd.setCursor(n_col, n_row);
  lcd.print(message);
}

// private constructor
Lcd::Lcd() {
  lcd.init();
  lcd.backlight();
}
