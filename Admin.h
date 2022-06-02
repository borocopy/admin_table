#ifndef ADMIN_H_
#define ADMIN_H_
#include <queue>
#include <vector>

#include "Base.h"
#include "Group.h"
#include "Table.h"

class Admin: public Base {
 private:
  std::vector<Table*> tables;
  std::queue<Group*> live_queue;
  std::vector<Group*> reservations;

  void enqueue_group(Group* group);
  void dequeue_group();
  void add_reservation(Group* group);

 public:
  explicit Admin(Base* app) : Base(app) {}
  ~Admin();

  void assign_table(Group* group);
};

#endif  // ADMIN_H_
