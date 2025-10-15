#include "./subsystems/blocker.h"
#include "main.h"
#include "devices.h"
#include "globals.h"

namespace Blocker{
  bool blocker_state = false;

  void toggle(){
    blocker_state = !blocker_state;
    blocker.set_value(blocker_state);
  }
  void set(bool state){
    blocker_state = state;
    blocker.set_value(blocker_state);
  }
  bool get(){
    return blocker_state;
  }
}