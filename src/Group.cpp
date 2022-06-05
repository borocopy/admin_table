#include "../includes/Group.h"

Group::Group(Base* parent, int quantity, int reserved_tick, int time_left)
    : Base(parent),
      quantity(quantity),
      reserved_tick(reserved_tick),
      time_left(time_left),
      occupied_table(nullptr) {}

int Group::get_quantity() { return quantity; }
int Group::get_reserved_tick() { return reserved_tick; }
int Group::get_time_left() { return time_left; }
void Group::decrease_time_span() {
  time_left--;
  if (time_left == 0) {
    emit(get_signal_emitter(), Base::Command::GROUP_LEAVE,
         std::to_string(get_uid()));
		delete this;
  }
}

void Group::occupy_table(Table* table) {
  occupied_table = table;

  add_connection(get_signal_emitter(), table->get_signal_handler(), table);
}

Table* Group::get_occupied_table() { return occupied_table; }

void Group::signal_fn(Base::Command cid, std::string& payload) {}
void Group::handler_fn(Base::Command cid, std::string payload) {
  switch (cid) {
    case Base::Command::NEXT_TICK: {
      decrease_time_span();
    }
    default: {
      break;
    }
  }
}

Base::Signal Group::get_signal_emitter() { return SIG_M(Group::signal_fn); }

Base::Handler Group::get_signal_handler() { return HDR_M(Group::handler_fn); }
