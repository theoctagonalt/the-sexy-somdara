#ifndef PISTONS_H_
#define PISTONS_H_

namespace Pistons{  
  void toggle_matchloader();
  void toggle_blocker();
  void toggle_colour_sort();
  void set_colour_sort(bool state);
  bool get_colour_sort();
  void set_matchloader(bool state);
  bool get_matchloader();
  void set_blocker(bool state);
  bool get_blocker();
}

#endif