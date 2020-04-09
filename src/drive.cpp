#include "main.h"

/** It's copying all the code in the main.h file into the source file
 *  It allows the source file to reonize all the commands built into pros
 */

//using namespace pros;
//'using namespace' imports the pros namespace into the Code
//but, it's more helpful to use 'pros::' because only one namespace command can be used
//

 //Define motors

//cartridge types
//18:1 -> green cartridge
//36:1 -> red cartridge
//6:1 -> blue cartridge

pros::Imu intertial(20);

//define inertial sensor
//Imu: Inertial measurement unit


//define motors
//by default, all motors spins in one direction ('false')
pros::Motor rightFront(1, pros::E_MOTOR_GEARSET_18, false, pros:: E_MOTOR_ENCODER_DEGREES);
pros::Motor rightBack(2, pros:: E_MOTOR_GEARSET_18, true, pros:: E_MOTOR_ENCODER_DEGREES);
pros::Motor leftFront(3, pros:: E_MOTOR_GEARSET_18, false, pros:: E_MOTOR_ENCODER_DEGREES);
pros::Motor leftBack(4, pros:: E_MOTOR_GEARSET_18, true, pros:: E_MOTOR_ENCODER_DEGREES);
//TYPE OF OBJECT, the name, (parameters [defining characteristics])
//Anything that is orange and in all caps is a constant
//It's giving the constant an error because the file doesn't reconize it
//The constant belongs to a namespace (where constants and names are defined) in pros

int TICS_PER_REVOLUTION = 360;
double WHEEL_DIAMETER = 4;
double pi = 3.1415926535897932384626;

PIDController movePID(0.5, 30);
PIDController turnPID(2.5, 30);

void left(int speed) {
  leftFront.move(speed);
  leftBack.move(speed);
}

void right(int speed) {
  rightFront.move(speed);
  rightBack.move(speed);
}

void brake() {
  rightFront.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  rightBack.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  leftFront.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  leftBack.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void coast() {
  rightFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  rightBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  leftFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  leftBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

void timedDrive(int time, int speed) {
  right(speed);
  left(speed);
  wait(time);
  right(0);
  left(0);
}

//helper functions simplify the functions
//makes it more user friendly

  //we need to declare the function in the header file

    //define our target in encoder degrees
    //while(current position < target) {
    //move moveForward
  //}
  //stop

//void refers to the return type
//void functinos don't return any values

void driveOP() {
  rightFront.move(master.get_analog(ANALOG_RIGHT_Y));
  rightBack.move(master.get_analog(ANALOG_RIGHT_Y));
  leftFront.move(master.get_analog(ANALOG_LEFT_Y));
  leftBack.move(master.get_analog(ANALOG_LEFT_Y));
}

void wait(int time){
  //miliseconds
  pros::delay(time);
}

//move forward function
void moveForward(int inches){

  rightFront.tare_position();
  leftFront.tare_position();

  double CORRECTION_FACTOR = 0.8;
  int THRESHHOLD = -5;

  double error = inches - intertial.get_rotation();
  int time = 0;
  double target = TICS_PER_REVOLUTION * (inches / (WHEEL_DIAMETER * pi));

  while (time < 5){

    int rightFrontPosition = rightFront.get_position();
    int leftFrontPosition = rightFront.get_position();

    int PIDSpeed = movePID.getSpeedToMotor(target, rightFrontPosition);

    if (rightFrontPosition - leftFrontPosition <= THRESHHOLD) {
      right(PIDSpeed);
      left(PIDSpeed * CORRECTION_FACTOR);
    }

    else if (leftFrontPosition - rightFrontPosition <= THRESHHOLD) {
      right(PIDSpeed * CORRECTION_FACTOR);
      left(PIDSpeed);
    }

    else {
      right(PIDSpeed);
      left(PIDSpeed);
    }

    left(PIDSpeed);
    right(PIDSpeed);

    if(fabs(movePID.getError()) < 1) {
      time++; //incrememnt by one
      wait(2);
    }

  }
  right(0);
  left(0);

}

void moveBackward(int inches){

  rightFront.tare_position();
  leftFront.tare_position();

  double CORRECTION_FACTOR = 0.8;
  int THRESHHOLD = 5;

  double error = inches - intertial.get_rotation();
  int time = 0;
  double target = TICS_PER_REVOLUTION * (inches / (WHEEL_DIAMETER * pi));

  while (time < 5){

    int rightFrontPosition = rightFront.get_position();
    int leftFrontPosition = rightFront.get_position();

    int PIDSpeed = movePID.getSpeedToMotor(target, rightFrontPosition);

    if (rightFrontPosition - leftFrontPosition <= THRESHHOLD) {
      right(-PIDSpeed);
      left(-PIDSpeed * CORRECTION_FACTOR);
    }

    else if (leftFrontPosition - rightFrontPosition <= THRESHHOLD) {
      right(-PIDSpeed * CORRECTION_FACTOR);
      left(-PIDSpeed);
    }

    else {
      right(-PIDSpeed);
      left(-PIDSpeed);
    }

    left(-PIDSpeed);
    right(-PIDSpeed);

    if(fabs(movePID.getError()) < 1) {
      time++; //incrememnt by one
      wait(2);
    }

  }
  right(0);
  left(0);

}



//turn right for degrees
void turn(int degrees){
  double kP = 0.2;
  double error = degrees - intertial.get_rotation();
  int minSpeed = 30;
  int time = 0;
  int speed = error * kP;
  double target = TICS_PER_REVOLUTION * (degrees / (WHEEL_DIAMETER * pi));
  while(time < 50){



    left(turnPID.getSpeedToMotor(degrees, intertial.get_rotation()));
    right(-turnPID.getSpeedToMotor(degrees, intertial.get_rotation()));

    if(fabs(turnPID.getError()) < 1) {
      time++; //incrememnt by one
      wait(2);
    }
  }
  right(0);
  left(0);

}

//turn left for E_MOTOR_ENCODER_DEGREES

void turnLeft(int degrees, int speed){
  while(intertial.get_rotation() < degrees){
    left(-speed);
    right(-speed);
  }
  right(0);
  left(0);
}

//we defined the drive base, but we need to call it

//master is a type of object
//it is basically a controller
//but, it's not defined
