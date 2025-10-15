#include "./subsystems/colourSort.h"
#include "main.h"
#include "devices.h"
#include "globals.h"

namespace ColourSort{
  bool colour_sort_state = false;

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
    if(colour_sensor.get_hue() < RED_HUE_MAX && colour_sensor.get_hue() > RED_HUE_MIN){ //if we see red
      set(EXTENDED); //extend the colour sorter
    }else if(colour_sensor.get_hue() < BLUE_HUE_MAX && colour_sensor.get_hue() > BLUE_HUE_MIN){ //if we see blue
      set(RETRACTED); //retract the colour sorter
    }
  }
}