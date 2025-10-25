#include "main.h"
#include "globals.h"
#include "devices.h"
#include "initialize.h"

int routine = RIGHT_SIDE;
int colour = RED;

void initialize(){
	pros::lcd::initialize();
  chassis.calibrate(true);
}
void on_auton_route_cycle(){
  routine = !routine;
  pros::lcd::print(1, "Auton Route: %s", (routine == LEFT_SIDE) ? "Left Side" : "Right Side");
}
void on_colour_cycle(){
  colour = !colour;
  pros::lcd::print(2, "Colour: %s", (colour == RED) ? "Red" : "Blue");
}

void competition_initialize(){
  pros::lcd::register_btn0_cb(on_auton_route_cycle);
  pros::lcd::register_btn1_cb(on_colour_cycle);
  pros::lcd::print(1, "Auton Route: %s", (routine == LEFT_SIDE) ? "Left Side" : "Right Side");
  pros::lcd::print(0, "Autonomous Selector");  
  pros::lcd::print(2, "Colour: %s", (colour == RED) ? "Red" : "Blue");
}
int get_routine(){
  return routine;
}
int get_colour(){
  return colour;
}