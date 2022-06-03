#include "../includes/Admin.h"

#include <algorithm>
#include <iostream>

#include "../lib/helpers.h"

Admin::~Admin() {
  // @TODO: add other dynamic variables cleanups
  for (Base* table : tables) {
    delete table;
  }
}
void Admin::add_table(int capacity) {
  Table* table = new Table(this, capacity);
  tables.push_back(table);
}

void Admin::add_group(int quantity, int reserved_tick, int duration) {
  Group* group = new Group(this, get_new_group_id(), quantity, reserved_tick, duration);
  if (group->get_reserved_tick() == 0) {
    groups_livequeue.push(group);
  } else {
    groups_reserved.push_back(group);
  }
}

int Admin::get_new_group_id() {
	return group_uid++;
}

std::vector<Table*> Admin::get_free_tables() {
  std::vector<Table*> filtered;
  for (Table* table : tables) {
    if (table->get_free_places() != 0) {
      filtered.push_back(table);
    }
  }
  std::sort(filtered.begin(), filtered.end(), [](Table* a, Table* b) {
    return a->get_free_places() < b->get_free_places();
  });
  return filtered;
}

bool Admin::occupy_table(Group* group) {
  std::vector<Table*> free_tables = get_free_tables();

  for (Table* table : free_tables) {
    if (table->get_free_places() >= group->get_quantity()) {
      table->occupy(group);
      groups_occupied.push_back(group);
      return true;
    }
  }

  return false;
}

void Admin::move_group_to_livequeue(Group* group) {
  std::vector<Group*>::iterator group_iter =
      std::find(groups_reserved.begin(), groups_reserved.end(), group);
  if (group_iter != groups_reserved.cend()) {
    int pos = std::distance(groups_reserved.begin(), group_iter);
    std::cout << "Element found on index " << pos << std::endl;
    groups_reserved.erase(groups_reserved.begin() + pos);
  }

  groups_livequeue.push(group);
}

void Admin::process_next_tick(int current_tick) {
  // Run on each tick
  // Check reservations first
  for (Group* group : groups_reserved) {
    if (group->get_reserved_tick() == current_tick) {
      bool success = occupy_table(group);

      // If cannot occupy => move group from reserved to livequeue
      if (!success) {
        move_group_to_livequeue(group);
      }
    }
  }

  // Then process livequeue
  Group* first_in_queue = groups_livequeue.front();
  // If first in queue can be placed then place it and pop it from queue
  if (occupy_table(first_in_queue)) {
    groups_livequeue.pop();
  }
}

void Admin::signal_fn(Base::Command cid, std::string& payload) {}
void Admin::handler_fn(Base::Command cid, std::string payload) {
  switch (cid) {
    case Base::Command::ADD_TABLE: {
      add_table(stoi(payload));
      break;
    }
    case Base::Command::ADD_GROUP: {
      std::vector<std::string> args = helpers::split_string(payload);
      int quantity = std::stoi(args[0]);
      int reserved_tick = std::stoi(args[1]);
      int duration = std::stoi(args[2]);

      add_group(quantity, reserved_tick, duration);
      break;
    }
    case Base::Command::NEXT_TICK: {
      // Payload = current tick
      process_next_tick(stoi(payload));
      break;
    }
    default:
      break;
  }
}

Base::Signal Admin::get_signal_emitter() { return SIG_M(Admin::signal_fn); }

Base::Handler Admin::get_signal_handler() { return HDR_M(Admin::handler_fn); }
