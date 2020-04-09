#include "main.h"

double kP = 0;

int minSpeed = 0;

//constructor:
PIDController::PIDController(double inKP, int inMinSpeed){
  kP = inKP;
  minSpeed = inMinSpeed;
}

int PIDController::getSpeedToMotor(int target, int current) {

  error = target - current;
  int speed = error * kP;

  if(speed <= minSpeed && speed >=0){
    speed = minSpeed;
  }

  else if(speed >= -minSpeed && speed <= 0) {
    speed = -minSpeed;
  }
  return speed;
}

double PIDController::getError() {
  return error;
}

// PIDController::getOutput(int target, int current){
//   kP = inKP;
//   minSpeed = inMinSpeed;
// }
// int PIDController::getOutput(int target, int current){
// }
