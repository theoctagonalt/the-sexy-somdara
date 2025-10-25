#include "./subsystems/colourSort.h"
#include "main.h"
#include "devices.h"
#include "globals.h"
#include "./subsystems/intake.h"

namespace ColourSort{
  bool colour_sort_state = false;
  int target_colour = -1;
  int timer = 0;

  void toggle(){
    colour_sort_state = !colour_sort_state;
    colour_sort.set_value(colour_sort_state);
  }
  void set(bool state){
    colour_sort_state = state;
    colour_sort.set_value(colour_sort_state);
  }
  bool get(){
    return colour_sort_state;
  }

  void update_colour_sort(){
    int current_colour = -1;
    if(colour_sensor.get_hue() < RED_HUE_MAX && colour_sensor.get_hue() > RED_HUE_MIN){ //if we see red
      current_colour = RED;
    }else if(colour_sensor.get_hue() < BLUE_HUE_MAX && colour_sensor.get_hue() > BLUE_HUE_MIN){ //if we see blue
      current_colour = BLUE;
    }

    if(current_colour != target_colour && current_colour != -1 && target_colour !=-1 && Intake::get_preroller() == FWD){
      set(EXTENDED);
    }else if(current_colour == target_colour && colour_sort_state == EXTENDED){
      set(RETRACTED);
    }

    if(current_colour == -1 && colour_sort_state == EXTENDED){
      if(timer > 75){
        set(RETRACTED);
        timer = 0;
      }
      timer++;
    }

    if(target_colour == -1){
      set(RETRACTED);
    }


  }

  void set_colour(int colour){
    target_colour = colour;
  }
  int get_colour(){
    return target_colour;
  }
}