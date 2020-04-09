#include "main.h"

//define lift motor
pros::Motor liftMotor(1, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);

pros::ADIPotentiometer liftPOT ('C');
pros::ADILineSensor line('G');

PIDController liftPID(0.46, 5);

void test() {
  if(line.get_value() < 2000 && line.get_value() > 100) {
    //do x
  }
  else{

  }
}



//auton
void moveLift(int position){
  int time = 0;
  while (time < 50){
    int PIDSpeed = -liftPID.getSpeedToMotor(target, pot.get_value());

    if(fabs(liftPID.getError()) < 30) {
      time++;
      wait(2);
    }
    lift(PIDSpeed);
  }
  lift(0);
  liftBrake();
}


void liftOP(){
  liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
      liftMotor.move_velocity(100);
    }

    else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
      liftMotor.move_velocity(-100);
    }
    else {
      liftMotor.move_velocity(0);
    }
}



//helper functions
