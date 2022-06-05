#include "../includes/Table.h"

Table::Table(Base* parent, int capacity)
    : Base(parent), capacity(capacity), occupied_places(0) {
  add_connection(get_signal_emitter(), parent->get_signal_handler(), parent);
}

void Table::occupy(Group* group) {
  add_child(group);
  group->occupy_table(this);
  occupied_places += group->get_quantity();
}

void Table::leave(Group* group) {
  remove_child(group);
  occupied_places -= group->get_quantity();
  emit(get_signal_emitter(), Base::Command::FREE_TABLE,
       std::to_string(group->get_uid()));
}

int Table::get_free_places() { return capacity - occupied_places; }
int Table::get_capacity() { return capacity; }

void Table::signal_fn(Base::Command cid, std::string& payload) {}
void Table::handler_fn(Base::Command cid, std::string payload) {
  switch (cid) {
    case Base::Command::GROUP_LEAVE: {
      Group* target = (Group*)get_child_by_uid(stoi(payload));
      leave(target);
      break;
    }
    default: {
      break;
    }
  }
}

Base::Signal Table::get_signal_emitter() { return SIG_M(Table::signal_fn); }

Base::Handler Table::get_signal_handler() { return HDR_M(Table::handler_fn); }
