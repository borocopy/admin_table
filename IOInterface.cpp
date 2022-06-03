#include "IOInterface.h"

#include <string>
#include <vector>

IOInterface::IOInterface(Base* app) : Base(app) {
  add_connection(get_signal_emitter(), app->get_signal_handler(), app);
}

void IOInterface::read_line(Base::Command cid) {
  std::string line;
  std::getline(std::cin, line);

  emit(get_signal_emitter(), cid, line);
}

void IOInterface::signal_fn(Base::Command cid, std::string& payload) {}
void IOInterface::handler_fn(Base::Command cid, std::string payload) {
  switch (cid) {
    case Base::Command::GET_USER_INPUT:
      read_line(Base::Command::PROCESS_USER_INPUT);
      break;
		case Base::Command::GET_INIT_STATE:
			read_line(Base::Command::SET_INIT_STATE);
			break;
    default:
      break;
  }
}

Base::Signal IOInterface::get_signal_emitter() {
	return SIG_M(IOInterface::signal_fn);
}

Base::Handler IOInterface::get_signal_handler() {
	return HDR_M(IOInterface::handler_fn);
}
