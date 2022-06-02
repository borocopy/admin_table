#include "App.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

App::App() : Base(nullptr) {
  IOInterface* io = new IOInterface(this);

  tick = 0;
  add_connection(get_signal_emitter(), io->get_signal_handler(), io);
}

std::vector<std::string> App::split_string(std::string raw_line) {
  std::istringstream iss(raw_line);
  std::string buf;
  std::vector<std::string> args;

  while (iss >> buf) {
    args.push_back(buf);
  }

  return args;
}

void App::set_initial_state(std::string line) {
  std::vector<std::string> args = split_string(line);
  for (std::string table_capacity : args) {
    emit(get_signal_emitter(), Base::Command::ADD_TABLE, table_capacity);
  }
}

void App::signal_fn(Base::Command cid, std::string& payload) {}
void App::handler_fn(Base::Command cid, std::string payload) {
  switch (cid) {
    case Base::Command::PROCESS_USER_INPUT:
      std::cout << payload << std::endl;
      break;
    default:
      break;
  }
}

void App::exec_app() {
  // Get initial tables state
  while (true) {
    emit(get_signal_emitter(), Base::Command::GET_USER_INPUT, "");
  }
}

Base::Signal App::get_signal_emitter() { return SIG_M(App::signal_fn); }

Base::Handler App::get_signal_handler() { return HDR_M(App::handler_fn); }
