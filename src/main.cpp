#include "main.h"
#include "globals.h"
#include "devices.h"
#include "./subsystems/intake.h"
#include "./subsystems/pistons.h"
#include "lemlib/api.hpp"

void opcontrol(){
  int game_time = 0;
  Intake::set_intake(OFF);

  while(true){
    int throttle = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    chassis.arcade(throttle, turn, false, 0.5f);

    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)){ //if we detect a new press of R1
      Intake::toggle(); //toggle the intake
      Pistons::set_blocker(RETRACTED); //always retract the blocker when intaking
    }else if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)){ //if we detect a new press of R2
      Pistons::set_blocker(RETRACTED); //always retract the blocker when outtaking
      if(Intake::get_preroller() == REV){ //if the intake is already outtaking
        Intake::set_intake(OFF); //turn the intake off
      }else{ //if the intake is not outtaking
        Intake::set_intake(REV); //set the intake to outtake
      }
    }

    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)){ //if we detect a new press of L1
      Pistons::set_blocker(EXTENDED); //extend the blocker
      Intake::set_intake(FWD); //set the intake to cycle blocks foward
    }else if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)){ //if we detect a new press of L2
      Pistons::set_blocker(RETRACTED); //retract the blocker
      Intake::set_intake(FWD); //set the intake to cycle blocks foward
      Intake::set_exit(REV); //set the exit to outtake
    }

    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)){ //if we detect a new press of the right button
      Pistons::toggle_matchloader(); //toggle the matchloader
    }
    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)){ //if we detect a new press of the left button
      Pistons::toggle_blocker(); //toggle the blocker
    }
    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)){ //if we detect a new press of the B button
      Pistons::toggle_colour_sort(); //toggle the matchloader
    }

    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)){
      Pistons::toggle_colour_sort();
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