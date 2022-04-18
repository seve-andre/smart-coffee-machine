#include "Indent.h"
#include "Arduino.h"

Indent::Indent() {
  this->positionIndent = 0;
}

void Indent::moveNext() {
  if (positionIndent < maxRow) {   
    positionIndent++;
  }
}

void Indent::movePrev() {
  if (positionIndent > 0) {
      positionIndent--;
  }
}

int Indent::getPositionIndent() {
  return this->positionIndent;
}
