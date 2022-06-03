#include "Admin.h"

Admin::~Admin() {
  for (Base* table : tables) {
    delete table;
  }
}

void Admin::add_table(int capacity) {
  Table* table = new Table(this, capacity);
}

void Admin::signal_fn(Base::Command cid, std::string& payload) {}
void Admin::handler_fn(Base::Command cid, std::string payload) {
	switch(cid) {
		case Base::Command::ADD_TABLE:
			add_table(stoi(payload));
			break;
		default:
			break;
	}
}

Base::Signal Admin::get_signal_emitter() { return SIG_M(Admin::signal_fn); }

Base::Handler Admin::get_signal_handler() { return HDR_M(Admin::handler_fn); }
