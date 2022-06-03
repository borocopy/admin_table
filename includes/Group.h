#ifndef INCLUDES_GROUP_H_
#define INCLUDES_GROUP_H_
#include <string>

#include "Base.h"

class Group : public Base {
 private:
	int uid;
  int quantity;
  int reserved_tick;
  int time_left;

 public:
  Group(Base* parent, int uid, int quantity, int reserved_tick, int duration);

  int get_quantity();
  int get_reserved_tick();
	int get_uid();

	void decrease_time_span();

  void signal_fn(Base::Command cid, std::string& payload);
  void handler_fn(Base::Command cid, std::string payload);

  Signal get_signal_emitter();
  Handler get_signal_handler();
};

#endif  // INCLUDES_GROUP_H_
