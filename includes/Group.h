#ifndef INCLUDES_GROUP_H_
#define INCLUDES_GROUP_H_
#include <string>

#include "Base.h"
#include "Table.h"

class Table;

class Group : public Base {
 private:
  int quantity;
  int reserved_tick;
  int time_left;
  Table* occupied_table;

 public:
  Group(Base* parent, int quantity, int reserved_tick, int time_left);
	~Group() {}
  int get_quantity();
  int get_reserved_tick();
  int get_time_left();
  void decrease_time_span();

  void occupy_table(Table* table);
  Table* get_occupied_table();

  void signal_fn(Base::Command cid, std::string& payload);
  void handler_fn(Base::Command cid, std::string payload);

  Signal get_signal_emitter();
  Handler get_signal_handler();
};

#endif  // INCLUDES_GROUP_H_
