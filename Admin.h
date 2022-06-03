#ifndef ADMIN_H_
#define ADMIN_H_
#include <queue>
#include <string>
#include <vector>

#include "Base.h"
/* #include "Group.h" */
#include "Table.h"

class Admin : public Base {
 private:
  std::vector<Table*> tables;
  /* std::queue<Group*> live_queue; */
  /* std::vector<Group*> reservations; */

  /* void enqueue_group(Group* group); */
  void add_table(int capacity);
  /* void dequeue_group(); */
  /* void add_reservation(Group* group); */

 public:
  explicit Admin(Base* app) : Base(app) {}
  ~Admin();

  void signal_fn(Base::Command cid, std::string& payload);
  void handler_fn(Base::Command cid, std::string payload);

  Signal get_signal_emitter();
  Handler get_signal_handler();

  /* void assign_table(Group* group); */
};

#endif  // ADMIN_H_
