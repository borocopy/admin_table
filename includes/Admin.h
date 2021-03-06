#ifndef INCLUDES_ADMIN_H_
#define INCLUDES_ADMIN_H_
#include <deque>
#include <string>
#include <vector>

#include "Base.h"
#include "Group.h"
#include "Table.h"

class Admin : public Base {
 private:
  std::vector<Table*> tables;
  std::vector<Group*> groups_reserved;
  std::deque<Group*> groups_livequeue;
  std::vector<Group*> groups_occupied;

  void add_table(int capacity);
  void add_group(int quantity, int reserved_tick, int time_left);
  std::vector<Table*> get_free_tables();
  bool occupy_table(Group* group);
	void remove_group(unsigned int group_uid);
  void process_next_tick(int current_tick);
  void move_group_to_livequeue(Group* group);

	void make_state_report();

 public:
	explicit Admin(Base* parent);
  ~Admin();

  void signal_fn(Base::Command cid, std::string& payload);
  void handler_fn(Base::Command cid, std::string payload);

  Signal get_signal_emitter();
  Handler get_signal_handler();
};

#endif  // INCLUDES_ADMIN_H_
