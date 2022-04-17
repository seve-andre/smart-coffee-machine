#include "Indent.h"

Indent::Indent() {
  this->positionIndent = 0;
}

void Indent::moveUp() {
  if (positionIndent > 0) {   
    positionIndent--;
  }
}

void Indent::moveDown() {
  if (positionIndent < maxRow) {      
      positionIndent++;
  }
}

int Indent::getPositionIndent() {
  return this->positionIndent;
}
