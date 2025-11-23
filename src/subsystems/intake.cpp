#include "./subsystems/intake.h"
#include "main.h"
#include "devices.h"
#include "globals.h"

namespace Intake{
  int preroller_state = OFF;
  int redirect_state = OFF;
  int exit_state = OFF;
  int preroller_antistall_counter = 0;
  int redirect_antistall_counter = 0;
  int exit_antistall_counter = 0;
  
  void toggle(){
    if(preroller_state == FWD){
      set_intake(OFF);
    }else{
      set_intake(FWD);
    }
  }

  void update_intake(){
    if((redirect_motor.get_actual_velocity() < 50 && redirect_state == FWD)){ // if we are intaking forwards and the motor is stalled 
      redirect_antistall_counter++;
      // give the motor 50 frames to start moving again; account for time taken to accelerate to 50 rpm
      if(redirect_antistall_counter > 50){
        set_redirect(OFF); // stop the redirect
        redirect_state = 0; // set the state to stalled
        master.rumble("."); // give physical signal
        redirect_antistall_counter = 0; // reset the counter for future use
      }
    } else if(redirect_motor.get_actual_velocity() > 50 && redirect_state == FWD){ //if we are intaking and the motor is not stalled
      redirect_antistall_counter = 0; //reset the counter
    }

    if((exit_motor.get_actual_velocity() < 50 && exit_state == FWD)){ // if we are intaking forwards and the motor is stalled 
      exit_antistall_counter++;
      // give the motor 50 frames to start moving again; account for time taken to accelerate to 50 rpm
      if(exit_antistall_counter > 50){
        set_exit(OFF); // stop the exit
        exit_state = 0; //s et the state to stopped
        master.rumble("."); // give physical signal
        exit_antistall_counter = 0; // reset the counter for future use
      }
    } else if(exit_motor.get_actual_velocity() > 50 && exit_state == FWD){ // if we are intaking and the motor is not stalled
      exit_antistall_counter = 0; // reset the counter
    }

    if((intake_motor.get_actual_velocity() < 50 && preroller_state == FWD) || preroller_state == STALLED){ //if we are intaking and the motor is stalled
      preroller_antistall_counter++;
      if(preroller_antistall_counter > 50){
        set_preroller(OFF); //stop the preroller
        preroller_state = STALLED; //set the state to stalled
        if(!pros::competition::is_autonomous()){
          master.rumble("."); // stronger rumble in auton to make sure we feel it
        }
          if(preroller_antistall_counter > 100){ // cooldown after it has been stopped
          set_preroller(FWD); //try to start the preroller again after a longer period
          preroller_antistall_counter = 0;
        }
      }
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
      set_exit(FWD);
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