#ifndef TABLE_H_
#define TABLE_H_

#include <string>

#include "Base.h"

class Table : public Base {
 private:
  int capacity;

 public:
  Table(Base* parent, int capacity);

  void signal_fn(Base::Command cid, std::string& payload);
  void handler_fn(Base::Command cid, std::string payload);

  Signal get_signal_emitter();
  Handler get_signal_handler();
  /* int get_capacity(); */
  /* bool is_occupied(); */
};

#endif  // TABLE_H_
