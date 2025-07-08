#include "main.h"
#include "globals.h"
#include "devices.h"
#include "./subsystems/intake.h"


void opcontrol(){
  int game_time = 0;
  Intake::set_intake(OFF);
  Intake::set_center(OFF);
  Intake::set_long(OFF);

  while(true){
    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)){
      Intake::toggle();
    }

    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)){
      // if(Intake::get_hooks() == REV){
      //   Intake::set_hooks(OFF);
      //   Intake::set_preroller(OFF);
      // }else{
      //   Intake::set_hooks(REV);
      //   Intake::set_preroller(REV);
      // }
    }

    //game
    if(pros::competition::is_connected() && !pros::competition::is_autonomous()){
      game_time++;
    } 
    if(game_time == 15000){ //CHANGE TIME
      master.rumble("--");
    }
    pros::delay(5);
  }
}