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
	~Table();

  void signal_fn(Base::Command cid, std::string& payload);
  void handler_fn(Base::Command cid, std::string payload);

	void occupy(Group* group);
	void leave(Group* group);
	int get_capacity();
	int get_free_places();
	bool is_vacant();

  Signal get_signal_emitter();
  Handler get_signal_handler();
};

#endif  // INCLUDES_TABLE_H_
