#include "main.h"
#include "globals.h"
#include "devices.h"

int routine = -1;

void initialize(){
	pros::lcd::initialize();
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