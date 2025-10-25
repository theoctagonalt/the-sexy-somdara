#include "main.h"
#include "globals.h"
#include "devices.h"
#include "initialize.h"
#include "./subsystems/intake.h"
#include "./subsystems/blocker.h"
#include "./subsystems/matchloader.h"
#include "./subsystems/colourSort.h"
#include "lemlib/api.hpp"

void opcontrol(){
  int game_time = 0;
  ColourSort::set_colour(get_colour());
  Intake::set_intake(OFF);
  bool toggle_intake_next = false;
  while(true){
    int throttle = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    ColourSort::update_colour_sort();
    Intake::update_intake();
    // if(master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)){
    //   if (throttle > 100){
    //     throttle *= 0.8;
    //   }
    // }
    chassis.arcade(throttle, turn, false, 0.5f);

    if(toggle_intake_next){
      Intake::toggle();
      toggle_intake_next = false;
    }
    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)){ //if we detect a new press of R1
      Blocker::set(RETRACTED); //always retract the blocker when intaking
      toggle_intake_next = true;
    }else if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)){ //if we detect a new press of R2
      Blocker::set(RETRACTED); //always retract the blocker when outtaking
      if(Intake::get_preroller() == REV){ //if the intake is already outtaking
        Intake::set_intake(OFF); //turn the intake off
      }else{ //if the intake is not outtaking
        Intake::set_intake(REV); //set the intake to outtake
      }
    }

    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)){ //if we detect a new press of L1
      Blocker::set(EXTENDED); //extend the blocker
      Intake::set_intake(FWD); //set the intake to cycle blocks foward
    }else if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)){ //if we detect a new press of L2
      Blocker::set(EXTENDED); //retract the blocker
      Intake::set_intake(FWD); //set the intake to cycle blocks foward
      Intake::set_exit(REV); //set the exit to outtake
    }

    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)){ //if we detect a new press of the right button
      Matchloader::toggle(); //toggle the matchloader
    }
    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)){ //if we detect a new press of the Y button
      Blocker::toggle(); //toggle the blocker
    }
    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)){ //if we detect a new press of the X button
      ColourSort::toggle(); //toggle the colour sorter
    }

    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)){ //if we detect a new press of the B button
      ColourSort::set_colour(!ColourSort::get_colour()); //toggle the target colour
      master.rumble("-"); //rumble to confirm the change
    }
    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)){ //turn off colour sort
      ColourSort::set_colour(-1); 
      master.rumble("--");
    }
    //game
    if(pros::competition::is_connected() && !pros::competition::is_autonomous()){
      game_time++;
    } 
    if(game_time == 19000){ //rumble ts at 10 seconds left
      master.rumble("--");
    }
    pros::delay(5);
  }
}