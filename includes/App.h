#ifndef INCLUDES_APP_H_
#define INCLUDES_APP_H_
#include <string>
#include <vector>

#include "Admin.h"
#include "Base.h"
#include "IOInterface.h"

class App : public Base {
 private:
  int tick;
  IOInterface* io;
  Admin* admin;

  void set_initial_state(std::string args);
  void process_user_command(std::string raw_line);

 public:
  App();
	~App();
  void exec_app();
  void signal_fn(Base::Command cid, std::string& payload);
  void handler_fn(Base::Command cid, std::string payload);

  Signal get_signal_emitter();
  Handler get_signal_handler();
};

#endif  // INCLUDES_APP_H_
