#ifndef INCLUDES_TABLE_H_
#define INCLUDES_TABLE_H_

#include <string>

#include "Base.h"
#include "Group.h"

class Group;

class Table : public Base {
 private:
  int capacity;
	int occupied_places;

 public:
  Table(Base* parent, int capacity);

  void signal_fn(Base::Command cid, std::string& payload);
  void handler_fn(Base::Command cid, std::string payload);

	void occupy(Group* group);
	void leave(Group* group);
	int get_free_places();

  Signal get_signal_emitter();
  Handler get_signal_handler();
  /* int get_capacity(); */
  /* bool is_occupied(); */
};

#endif  // INCLUDES_TABLE_H_
