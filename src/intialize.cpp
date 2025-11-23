#include "main.h"
#include "globals.h"
#include "devices.h"
#include "initialize.h"

int routine = LEFT_SIDE_QUALS;
int colour = RED;

void initialize(){
	pros::lcd::initialize();
  chassis.calibrate(true);
}
void on_auton_route_cycle(){
  if(routine == SKILLS){
    routine = LEFT_SIDE_QUALS;
  }else{
    routine++;
  }

  pros::lcd::print(1, "Auton Route: %s", (routine == LEFT_SIDE_QUALS) ? "Left Side Quals" : (routine == RIGHT_SIDE_QUALS) ? "Right Side Quals" : (routine == LEFT_SIDE_ELIMS) ? "Left Side Elims" : (routine == RIGHT_SIDE_ELIMS) ? "Right Side Elims" : "SKILLS");
}
void on_colour_cycle(){
  colour = !colour;
  pros::lcd::print(2, "Colour: %s", (colour == RED) ? "Red" : "Blue");
}

void competition_initialize(){
  pros::lcd::register_btn0_cb(on_auton_route_cycle);
  pros::lcd::register_btn1_cb(on_colour_cycle);
  pros::lcd::print(1, "Auton Route: %s", (routine == LEFT_SIDE_QUALS) ? "Left Side Quals" : (routine == RIGHT_SIDE_QUALS) ? "Right Side Quals" : (routine == LEFT_SIDE_ELIMS) ? "Left Side Elims" : "Right Side Elims");
  pros::lcd::print(0, "Autonomous Selector");  
  pros::lcd::print(2, "Colour: %s", (colour == RED) ? "Red" : "Blue");
}
int get_routine(){
  return routine;
}
int get_colour(){
  return colour;
}