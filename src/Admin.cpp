#include "../includes/Admin.h"

#include <algorithm>

#include "../lib/helpers.h"

Admin::Admin(Base* app) : Base(app), group_uid(0) {
  add_connection(get_signal_emitter(), app->get_signal_handler(), app);
}

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

void Admin::add_group(int quantity, int reserved_tick, int time_left) {
  Group* group = new Group(this, quantity, reserved_tick, time_left);

  if (group->get_reserved_tick() == 0) {
    groups_livequeue.push_back(group);
  } else {
    groups_reserved.push_back(group);
  }
}

void Admin::make_state_report() {
  std::stringstream report;
  std::string tab = "    ";
  report << "Tables:";
  for (Table* table : tables) {
    report << std::endl
           << tab << "Table with capacity of "
           << table->get_capacity() << " and "
           << table->get_free_places() << " unoccupied seats";
  }

  if (groups_livequeue.size() != 0) {
    report << std::endl << "Livequeue:";
    for (Group* group : groups_livequeue) {
      report << std::endl
             << tab << "Group of " << group->get_quantity()
             << " is waiting for a table";
    }
  }

  if (groups_reserved.size() != 0) {
    report << std::endl << "Reserved:";
    for (Group* group : groups_reserved) {
      report << std::endl
             << tab << "Group of " << group->get_quantity()
             << " has reserved a table on tick " << group->get_reserved_tick();
    }
  }

  if (groups_occupied.size() != 0) {
    report << std::endl << "Occupied:";
    for (Group* group : groups_occupied) {
      report << std::endl
             << tab << "Group of " << group->get_quantity()
             << " will occupy a table for "
             << group->get_time_left() << " more ticks";
    }
  }
  emit(get_signal_emitter(), Base::Command::STATE_REPORT_DONE, report.str());
}

std::vector<Table*> Admin::get_free_tables() {
  std::vector<Table*> filtered;
  for (Table* table : tables) {
    if (table->is_vacant()) {
      filtered.push_back(table);
    }
  }
  std::sort(filtered.begin(), filtered.end(), [](Table* a, Table* b) {
    return a->get_capacity() < b->get_capacity();
  });
  return filtered;
}

bool Admin::occupy_table(Group* group) {
  std::vector<Table*> free_tables = get_free_tables();

  for (Table* table : free_tables) {
    if (table->get_free_places() >= group->get_quantity()) {
      table->occupy(group);
      groups_occupied.push_back(group);
      add_connection(get_signal_emitter(), group->get_signal_handler(), group);

      return true;
    }
  }

  return false;
}

void Admin::remove_group(unsigned int group_uid) {
  for (int i = 0; i < groups_occupied.size(); i++) {
    if (group_uid == groups_occupied[i]->get_uid()) {
      groups_occupied.erase(groups_occupied.begin() + i);
      break;
    }
  }
}

void Admin::move_group_to_livequeue(Group* group) {
  for (int i = 0; i < groups_reserved.size(); i++) {
    if (group->get_uid() == groups_reserved[i]->get_uid()) {
      groups_reserved.erase(groups_reserved.begin() + i);
    }
  }

  groups_livequeue.push_back(group);
}

void Admin::process_next_tick(int current_tick) {
  // Run on each tick
  // Check reservations first
  for (Group* group : groups_reserved) {
    if (group->get_reserved_tick() == current_tick) {
      bool success = occupy_table(group);

      for (int i = 0; i < groups_reserved.size(); i++) {
        if (group->get_uid() == groups_reserved[i]->get_uid()) {
          groups_reserved.erase(groups_reserved.begin() + i);
          break;
        }
      }
      // If cannot occupy => move group from reserved to livequeue
      if (!success) {
        move_group_to_livequeue(group);
      }
    }
  }

  for (Group* group : groups_livequeue) {
    if (occupy_table(group)) {
      for (int i = 0; i < groups_livequeue.size(); i++) {
        if (group->get_uid() == groups_livequeue[i]->get_uid()) {
          groups_livequeue.erase(groups_livequeue.begin() + i);
          break;
        }
      }
    }
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
      int time_left = std::stoi(args[2]);

      add_group(quantity, reserved_tick, time_left);
      break;
    }
    case Base::Command::FREE_TABLE: {
      unsigned int group_uid = stoi(payload);
      remove_group(group_uid);
      break;
    }
    case Base::Command::MAKE_STATE_REPORT: {
      make_state_report();
      break;
    }
    case Base::Command::NEXT_TICK: {
      // Payload = current tick
      process_next_tick(stoi(payload));
      // Groups leave first?
      emit(get_signal_emitter(), Base::Command::NEXT_TICK, "");
      break;
    }
    default:
      break;
  }
}

Base::Signal Admin::get_signal_emitter() { return SIG_M(Admin::signal_fn); }

Base::Handler Admin::get_signal_handler() { return HDR_M(Admin::handler_fn); }
