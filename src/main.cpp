#include "main.h"
#include "globals.h"
#include "devices.h"
#include "./subsystems/intake.h"
#include "lemlib/api.hpp"

void opcontrol(){
  int game_time = 0;
  Intake::set_intake(OFF);
  // Intake::set_center(OFF);
  // Intake::set_long(OFF);

  while(true){
    int throttle = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    chassis.arcade(throttle, turn, false, 0.6f);

    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)){
      Intake::toggle();
    }else if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)){
      Intake::set_intake(REV);
    }

    //game
    if(pros::competition::is_connected() && !pros::competition::is_autonomous()){
      game_time++;
    } 
    if(game_time == 20000){
      master.rumble("--");
    }
    pros::delay(5);
  }
}