#include "../includes/App.h"

#include <sstream>
#include <string>
#include <vector>

#include "../lib/helpers.h"

App::App() : Base(nullptr) {
  IOInterface* io = new IOInterface(this);
  Admin* admin = new Admin(this);
  tick = 1;
  add_connection(get_signal_emitter(), io->get_signal_handler(), io);
  add_connection(get_signal_emitter(), admin->get_signal_handler(), admin);
}

App::~App() {}

void App::set_initial_state(std::string line) {
  std::vector<std::string> args = helpers::split_string(line);
  for (std::string table_capacity : args) {
    emit(get_signal_emitter(), Base::Command::ADD_TABLE, table_capacity);
  }
}

void App::process_user_command(std::string raw_line) {
  std::string display_command = "Display the system status";
  std::string kill_command = "Turn off the system";

  if (raw_line.compare(kill_command) == 0) {
    emit(get_signal_emitter(), Base::Command::PRINT, "System shutdown");
    exit(0);
    return;
  }

  if (raw_line.compare(display_command) == 0) {
    emit(get_signal_emitter(), Base::Command::MAKE_STATE_REPORT, "");
    return;
  }

  std::vector<std::string> args = helpers::split_string(raw_line);
  if (args.size() == 0) return;

  std::string instruction = args[0];

  if (instruction.compare("Reservation") == 0) {
    args.erase(args.begin());
    emit(get_signal_emitter(), Base::Command::ADD_GROUP,
         helpers::join_strings(args));
  } else {
    emit(get_signal_emitter(), Base::Command::PRINT_PAUSE, "Unknown command");
  }
}

void App::signal_fn(Base::Command cid, std::string& payload) {}
void App::handler_fn(Base::Command cid, std::string payload) {
  switch (cid) {
    case Base::Command::PROCESS_USER_INPUT:
      process_user_command(payload);
      break;
    case Base::Command::SET_INIT_STATE:
      set_initial_state(payload);
      break;
    case Base::Command::STATE_REPORT_DONE: {
      emit(get_signal_emitter(), Base::Command::PRINT,
           "System status on tick " + std::to_string(tick) + "\n");
      emit(get_signal_emitter(), Base::Command::PRINT_PAUSE, payload);
      break;
    }
    default:
      break;
  }
}

void App::exec_app() {
  // Get initial tables state
  emit(get_signal_emitter(), Base::Command::GET_INIT_STATE, "");

  // Reading user commands
  while (true) {
    emit(get_signal_emitter(), Base::Command::NEXT_TICK, std::to_string(tick));
    emit(get_signal_emitter(), Base::Command::GET_USER_INPUT, "");
    tick++;
  }
}

Base::Signal App::get_signal_emitter() { return SIG_M(App::signal_fn); }

Base::Handler App::get_signal_handler() { return HDR_M(App::handler_fn); }
