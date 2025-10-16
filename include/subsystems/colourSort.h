#ifndef __COLOUR_SORT_H__
#define __COLOUR_SORT_H__

namespace ColourSort {
  void set(bool state);
  void toggle();
  bool get();
  void update_colour_sort();
  void set_colour(int colour);
  int get_colour();
}

#endif