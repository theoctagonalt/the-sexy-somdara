#include "main.h"
#include "lemlib/api.hpp"

#ifndef DEVICES_H_
#define DEVICES_H_

extern pros::Controller master;

extern pros::Motor intake_motor;
extern pros::Motor redirect_motor;
extern pros::Motor exit_motor;

extern pros::adi::DigitalOut colour_sort;
extern pros::adi::DigitalOut matchloader;
extern pros::adi::DigitalOut blocker;

extern pros::Optical colour_sensor;
extern pros::Imu inertial;  

extern lemlib::Chassis chassis;
#endif