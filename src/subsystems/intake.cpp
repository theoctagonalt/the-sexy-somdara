#include "./subsystems/intake.h"
#include "main.h"
#include "devices.h"
#include "globals.h"

namespace Intake{
  int intake_state = OFF;
  int long_state = OFF;
  int center_state = OFF;
  void toggle(){
    if(intake_state == FWD){
      set_intake(OFF);
      set_long(OFF);
      set_center(OFF);
    }else{
      set_intake(FWD);
      set_long(FWD);
      set_center(FWD);
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
  void set_long(int state){
    if(state == FWD){
      long_motor.move_velocity(200);
      long_state = FWD;
    }else if(state == REV){
      long_motor.move_velocity(-200);
      long_state = REV;
    }else{
      long_motor.move_velocity(0);
      long_state = OFF;
    }
  }
  void set_center(int state){
    if(state == FWD){
      center_motor.move_velocity(200);
      center_state = FWD;
    }else if(state == REV){
      center_motor.move_velocity(-200);
      center_state = REV;
    }else{
      center_motor.move_velocity(0);
      center_state = OFF;
    }
  }
}