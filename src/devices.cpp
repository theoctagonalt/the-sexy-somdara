#include "main.h"
#include "lemlib/api.hpp"

// #define LONG_MOTOR -17 //TO CHANGE
// #define CENTER_MOTOR 5
#define INTAKE_MOTOR -11
#define REDIRECT_MOTOR -12
#define EXIT_MOTOR 13

#define LEFT_FRONT_MOTOR 8
#define LEFT_BACK_MOTOR -15
#define LEFT_MIDDLE_MOTOR -20

#define RIGHT_FRONT_MOTOR -9
#define RIGHT_BACK_MOTOR 17
#define RIGHT_MIDDLE_MOTOR 16

#define COLOUR_SORT 1
#define MATCHLOADER 2
#define BLOCKER 3

#define INERTIAL 10
#define COLOUR_SENSOR 4

//sensors: colour sensor, inertial sensor, auton selector?

pros::Controller master (pros::E_CONTROLLER_MASTER);

//motors

pros::MotorGroup left_motors ({LEFT_FRONT_MOTOR, LEFT_BACK_MOTOR, LEFT_MIDDLE_MOTOR}, pros::MotorGear::blue);
pros::MotorGroup right_motors ({RIGHT_FRONT_MOTOR, RIGHT_BACK_MOTOR, RIGHT_MIDDLE_MOTOR}, pros::MotorGear::blue);

pros::Motor intake_motor (INTAKE_MOTOR, pros::MotorGear::green);
pros::Motor redirect_motor (REDIRECT_MOTOR, pros::MotorGear::green);
pros::Motor exit_motor (EXIT_MOTOR, pros::MotorGear::green);


//pistons
pros::adi::DigitalOut colour_sort (COLOUR_SORT);
pros::adi::DigitalOut matchloader (MATCHLOADER);
pros::adi::DigitalOut blocker (BLOCKER);

//sensors
pros::Imu inertial (INERTIAL);
pros::Optical colour_sensor (COLOUR_SENSOR);

//lemlib objects
lemlib::Drivetrain drivetrain (&left_motors, &right_motors, 10.428, lemlib::Omniwheel::NEW_325, 450, 2);

//drive curve
lemlib::ExpoDriveCurve throttle_curve(10, // joystick deadband out of 127
                                     15, // minimum output where drivetrain will move out of 127
                                     1 // expo curve gain
);
lemlib::ExpoDriveCurve turn_curve(10, // joystick deadband out of 127
                                     15, // minimum output where drivetrain will move out of 127
                                     1.029 // expo curve gain
);

//rotational
lemlib::ControllerSettings angular_controller(4, //kP
                                              0, //kIx
                                              15, //kD
                                              7, //anti-windup
                                              0.1, //small error range (in)
                                              1000, //small error timeout (ms)
                                              0, //large error range (in)
                                              500, //large error timeout(ms)
                                              0  //maximum accel
                                              ); 

//front-back
lemlib::ControllerSettings lateral_controller(6.5,
                                             0, 
                                             5.5, 
                                             5, 
                                             1, 
                                             100, 
                                             0, 
                                             500, 
                                             0 //TODO: TUNE SLEW
                                             );

lemlib::TrackingWheel left_side_imes (&left_motors, lemlib::Omniwheel::NEW_325, -5.8525, 450);
lemlib::TrackingWheel right_side_imes (&right_motors, lemlib::Omniwheel::NEW_325, 5.8525, 450);
lemlib::OdomSensors sensors (&left_side_imes, &right_side_imes, nullptr, nullptr, &inertial);

lemlib::Chassis chassis (drivetrain, lateral_controller, angular_controller, sensors, &throttle_curve, &turn_curve);