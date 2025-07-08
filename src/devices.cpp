#include "main.h"
// #include "lemlib/api.hpp"

#define LONG_GOAL_MOTOR -1
#define CENTER_GOAL_MOTOR 2
#define INTAKE_MOTOR 3

//sensors: colour sensor, inertial sensor, auton selector?

pros::Controller master (pros::E_CONTROLLER_MASTER);

//motors

// pros::MotorGroup left_motors ({LEFT_FRONT_MOTOR, LEFT_BACK_MOTOR, LEFT_BACK_MOTOR_TOP}, pros::MotorGear::blue);
// pros::MotorGroup right_motors ({RIGHT_FRONT_MOTOR, RIGHT_BACK_MOTOR, RIGHT_BACK_MOTOR_TOP}, pros::MotorGear::blue);

pros::Motor long_goal_motor (LONG_GOAL_MOTOR, pros::MotorGear::green);
pros::Motor center_goal_motor (CENTER_GOAL_MOTOR, pros::MotorGear::green);
pros::Motor intake_motor (INTAKE_MOTOR, pros::MotorGear::green);

//pistons

//sensors