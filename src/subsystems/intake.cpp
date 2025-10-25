#include "./subsystems/intake.h"
#include "main.h"
#include "devices.h"
#include "globals.h"

namespace Intake{
  int preroller_state = OFF;
  int redirect_state = OFF;
  int exit_state = OFF;
  int anti_redirect_stall_counter = 0;
  int anti_exit_stall_counter = 0;
  void toggle(){
    if(preroller_state == FWD){
      set_intake(OFF);
    }else{
      set_intake(FWD);
    }
  }

  void update_intake(){
    if(redirect_motor.get_actual_velocity() < 50 && redirect_state == FWD){ //if we are intaking and the motor is stalled
      anti_redirect_stall_counter++;
      if(anti_redirect_stall_counter > 50){
        set_redirect(OFF); //stop the redirect
        redirect_state = 2; //set the state to stalled
        master.rumble(".");
        anti_redirect_stall_counter = 0;
      }
    }else if(redirect_motor.get_actual_velocity() > 50 && redirect_state == FWD){ //if we are intaking and the motor is not stalled
      anti_redirect_stall_counter = 0; //reset the counter
    }

    if(exit_motor.get_actual_velocity() < 50 && exit_state == FWD){ //if we are intaking and the motor is stalled
      anti_exit_stall_counter++;
      if(anti_exit_stall_counter > 50){
        set_exit(OFF); //stop the exit
        exit_state = 2; //set the state to stalled
        master.rumble(".");
        anti_exit_stall_counter = 0;
      }
    }else if(exit_motor.get_actual_velocity() > 50 && exit_state == FWD){ //if we are intaking and the motor is not stalled
      anti_exit_stall_counter = 0; //reset the counter
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