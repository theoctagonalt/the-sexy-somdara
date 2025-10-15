#ifndef INTAKE_H_
#define INTAKE_H_

namespace Intake{
  void toggle();
  void set_intake(int state);
  void set_redirect(int state);
  void set_exit(int state);
  void set_preroller(int state);
  int get_preroller();
}

#endif