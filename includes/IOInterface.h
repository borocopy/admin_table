#ifndef INCLUDES_IOINTERFACE_H_
#define INCLUDES_IOINTERFACE_H_
#include <iostream>
#include <string>
#include <vector>

#include "Base.h"

class IOInterface : public Base {
 private:
  void read_line(Base::Command cid);

 public:
  explicit IOInterface(Base *app);
	~IOInterface();

  void signal_fn(Base::Command cid, std::string &payload);
  void handler_fn(Base::Command cid, std::string payload);

  Signal get_signal_emitter();
  Handler get_signal_handler();
};

#endif  // INCLUDES_IOINTERFACE_H_
