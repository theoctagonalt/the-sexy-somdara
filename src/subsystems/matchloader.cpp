#include "./subsystems/blocker.h"
#include "main.h"
#include "devices.h"
#include "globals.h"

namespace Matchloader{
  bool matchloader_state = false;

  void toggle(){
    matchloader_state = !matchloader_state;
    matchloader.set_value(matchloader_state);
  }
  void set(bool state){
    matchloader_state = state;
    matchloader.set_value(matchloader_state);
  }
  bool get(){
    return matchloader_state;
  }
}