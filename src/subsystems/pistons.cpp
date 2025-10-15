#include "./subsystems/pistons.h"
#include "main.h"
#include "devices.h"
#include "globals.h"

namespace Pistons{
  bool colour_sort_state = false;
  bool matchloader_state = false;
  bool blocker_state = false;

  void toggle_matchloader(){
    matchloader_state = !matchloader_state; //set the state to the opposite of what it is
    matchloader.set_value(matchloader_state); //set the piston to that state
  }
  void toggle_blocker(){
    blocker_state = !blocker_state;
    blocker.set_value(blocker_state);
  }
  void toggle_colour_sort(){
    colour_sort_state = !colour_sort_state;
    colour_sort.set_value(colour_sort_state);
  }
  void set_colour_sort(bool state){
    colour_sort_state = state;
    colour_sort.set_value(colour_sort_state);
  }
  bool get_colour_sort(){
    return colour_sort_state;
  }
  void set_matchloader(bool state){
    matchloader_state = state; //set the state to the new state
    matchloader.set_value(matchloader_state); //set the piston to that state
  }
  bool get_matchloader(){
    return matchloader_state; //return the state
  }
  void set_blocker(bool state){
    blocker_state = state;
    blocker.set_value(blocker_state);
  }
  bool get_blocker(){
    return blocker_state;
  }
}