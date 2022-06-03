#include "../includes/Table.h"

#include <iostream>

Table::Table(Base* parent, int capacity)
    : Base(parent), capacity(capacity), occupied_places(0) {
  std::cout << "Table with capacity: " << capacity << " was created!"
            << std::endl;
}

void Table::occupy(Group* group) {
  add_child(group);
  occupied_places += group->get_quantity();
}

int Table::get_free_places() { return capacity - occupied_places; }

void Table::signal_fn(Base::Command cid, std::string& payload) {}
void Table::handler_fn(Base::Command cid, std::string payload) {}

Base::Signal Table::get_signal_emitter() { return SIG_M(Table::signal_fn); }

Base::Handler Table::get_signal_handler() { return HDR_M(Table::handler_fn); }
