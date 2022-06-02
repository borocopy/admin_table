#ifndef IOINTERFACE_H_
#define IOINTERFACE_H_
#include <iostream>
#include <string>
#include <vector>

#include "Node.h"

class UserInterface : public Node {
 private:
  std::vector<std::string> split_string(std::string raw_line);

 public:
  explicit UserInterface(Node *app) : Node(app) {}
  void get_initial_state();
  void parse_user_command();
};

#endif  // IOINTERFACE_H_
