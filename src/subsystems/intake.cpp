#include "./subsystems/intake.h"
#include "main.h"
#include "devices.h"
#include "globals.h"

namespace Intake{
  int intake_state = OFF;
  int long_goal_state = OFF;
  int center_goal_state = OFF;
  void toggle(){
    if(intake_state == FWD){
      set_intake(OFF);
      set_long_goal(OFF);
      set_center_goal(OFF);
    }else{
      set_intake(FWD);
      set_long_goal(FWD);
      set_center_goal(FWD);
    }
  }

  void set_intake(int state){
    if(state == FWD){
      intake_motor.move_velocity(200);
      intake_state = FWD;
    }else if(state == REV){
      intake_motor.move_velocity(-200);
      intake_state = REV;
    }else{
      intake_motor.move_velocity(0);
      intake_state = OFF;
    }
  }
  void set_long_goal(int state){
    if(state == FWD){
      long_goal_motor.move_velocity(200);
      long_goal_state = FWD;
    }else if(state == REV){
      long_goal_motor.move_velocity(-200);
      long_goal_state = REV;
    }else{
      long_goal_motor.move_velocity(0);
      long_goal_state = OFF;
    }
  }
  void set_center_goal(int state){
    if(state == FWD){
      center_goal_motor.move_velocity(200);
      center_goal_state = FWD;
    }else if(state == REV){
      center_goal_motor.move_velocity(-200);
      center_goal_state = REV;
    }else{
      center_goal_motor.move_velocity(0);
      center_goal_state = OFF;
    }
  }
}