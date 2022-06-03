#include "../includes/Group.h"

#include <iostream>

Group::Group(Base* parent, int uid, int quantity, int reserved_tick, int time_left)
    : Base(parent),
			uid(uid),
      quantity(quantity),
      reserved_tick(reserved_tick),
      time_left(time_left) {
  std::cout << "Added group of " << quantity << " people"
            << ", that reserved table on tick " << reserved_tick << " and"
            << " they want to occupy it for " << time_left << " ticks."
            << std::endl;
}

int Group::get_quantity() { return quantity; }
int Group::get_reserved_tick() { return reserved_tick; }

void Group::signal_fn(Base::Command cid, std::string& payload) {}
void Group::handler_fn(Base::Command cid, std::string payload) {}

Base::Signal Group::get_signal_emitter() { return SIG_M(Group::signal_fn); }

Base::Handler Group::get_signal_handler() { return HDR_M(Group::handler_fn); }
