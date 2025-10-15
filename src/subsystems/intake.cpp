#include "./subsystems/intake.h"
#include "main.h"
#include "devices.h"
#include "globals.h"

namespace Intake{
  int preroller_state = OFF;
  int redirect_state = OFF;
  int exit_state = OFF;
  void toggle(){
    if(preroller_state == FWD){
      set_intake(OFF);
    }else{
      set_intake(FWD);
    }
  }

  void set_intake(int state){
    if(state == FWD){
      set_preroller(FWD);
      set_redirect(FWD);
      set_exit(FWD);
    }else if(state == REV){
      set_preroller(REV);
      set_redirect(REV);
      set_exit(REV);
    }else{
      set_preroller(OFF);
      set_redirect(OFF);
      set_exit(OFF);
    }
  }

  void set_redirect(int state){
    if(state == FWD){
      redirect_motor.move_velocity(200);
    }else if(state == REV){
      redirect_motor.move_velocity(-200);
    }else{
      redirect_motor.move_velocity(0);
    }
    redirect_state = state;
  }
  void set_exit(int state){
    if(state == FWD){
      exit_motor.move_velocity(200);
    }else if(state == REV){
      exit_motor.move_velocity(-200);
    }else{
      exit_motor.move_velocity(0);
    }
    exit_state = state;
  }
  void set_preroller(int state){
    if(state == FWD){
      intake_motor.move_velocity(200);
    }else if(state == REV){
      intake_motor.move_velocity(-200);
    }else{
      intake_motor.move_velocity(0);
    }
    preroller_state = state;
  }
  int get_preroller(){
    return preroller_state;
  }
}