#include "main.h"
#include "lemlib/api.hpp"

#define LONG_MOTOR -1
#define CENTER_MOTOR 2
#define INTAKE_MOTOR 3

#define LEFT_FRONT_MOTOR 4
#define LEFT_BACK_MOTOR 5
#define LEFT_MIDDLE_MOTOR 6

#define RIGHT_FRONT_MOTOR 7
#define RIGHT_BACK_MOTOR 8
#define RIGHT_MIDDLE_MOTOR 9

#define INERTIAL 10

//sensors: colour sensor, inertial sensor, auton selector?

pros::Controller master (pros::E_CONTROLLER_MASTER);

//motors

pros::MotorGroup left_motors ({LEFT_FRONT_MOTOR, LEFT_BACK_MOTOR, LEFT_MIDDLE_MOTOR}, pros::MotorGear::blue);
pros::MotorGroup right_motors ({RIGHT_FRONT_MOTOR, RIGHT_BACK_MOTOR, RIGHT_MIDDLE_MOTOR}, pros::MotorGear::blue);

pros::Motor long_motor (LONG_MOTOR, pros::MotorGear::green);
pros::Motor center_motor (CENTER_MOTOR, pros::MotorGear::green);
pros::Motor intake_motor (INTAKE_MOTOR, pros::MotorGear::green);

//pistons

//sensors
pros::Imu inertial (INERTIAL);

//lemlib objects
lemlib::Drivetrain drivetrain (&left_motors, &right_motors, 10.428, lemlib::Omniwheel::NEW_325, 450, 2);

//rotational
lemlib::ControllerSettings angular_controller(1.64, //kP
                                              0, //kIx
                                              0.7, //kD
                                              7, //anti-windup
                                              0.1, //small error range (in)
                                              1000, //small error timeout (ms)
                                              0, //large error range (in)
                                              500, //large error timeout(ms)
                                              0  //maximum accel
                                              ); 

//front-back
lemlib::ControllerSettings lateral_controller(3.5,
                                             0.1, 
                                             0.1, 
                                             5, 
                                             1, 
                                             100, 
                                             0, 
                                             500, 
                                             0 //TODO: TUNE SLEW
                                             );

lemlib::TrackingWheel left_side_imes (&left_motors, lemlib::Omniwheel::NEW_325, -5.8525, 400);
lemlib::TrackingWheel right_side_imes (&right_motors, lemlib::Omniwheel::NEW_325, 5.8525, 400);

lemlib::OdomSensors sensors (&left_side_imes, &right_side_imes, nullptr, nullptr, &inertial);

lemlib::Chassis chassis (drivetrain, lateral_controller, angular_controller, sensors);