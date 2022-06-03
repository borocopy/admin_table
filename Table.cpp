#include "Table.h"

#include <iostream>

Table::Table(Base* parent, int capacity) : Base(parent) {
  this->capacity = capacity;
  std::cout << "Table with capacity: " << capacity << " was created!"
            << std::endl;
}

void Table::signal_fn(Base::Command cid, std::string& payload) {}
void Table::handler_fn(Base::Command cid, std::string payload) {}

Base::Signal Table::get_signal_emitter() { return SIG_M(Table::signal_fn); }

Base::Handler Table::get_signal_handler() { return HDR_M(Table::handler_fn); }
