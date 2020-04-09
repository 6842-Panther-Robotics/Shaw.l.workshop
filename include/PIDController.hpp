#include "main.h"

class PIDController {
  private:
    //instance fields
    //variables for the object
    double kP; // 2.5
    int minSpeed; // 30
    double error; // constantly getting updated

  public:
    PIDController(double inKP, int inMinspeed);
    int getSpeedToMotor(int target, int current);
    double getError();

};
