#include "main.h"

void redFront() {

  //move forward 10 inches
  moveForward(10);
  //turn right 90 degrees
  turnRight(90);
  //move forward 50 inches
  moveForward(50);

}

void blueFront() {
  moveForward(20);
  turnRight(90);

}

void autonomous() {

  switch(autonIndex) {
    case 0:
      redFront();
      break;
    case 1:
      blueFront();
      break;
  }
}
