#include "main.h"
#include "globals.h"
#include "devices.h"
#include "initialize.h"

int routine = -1;
int colour = RED;

void initialize(){
	pros::lcd::initialize();
  colour_sort.set_value(0);
}

void competition_initialize(){
	while(true){
		pros::lcd::set_text(0, "Autonomous selector");
    chassis.calibrate(true);
  }
}
int get_routine(){
  return routine;
}
int get_colour(){
  return colour;
}