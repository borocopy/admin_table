#include "UserInterface.h"

#include <sstream>
#include <string>
#include <vector>

vector<std::string> UserInterface::split_string(string raw_line) {
  std::istringstream iss(raw_line);
  std::string buf;
  std::vector<std::string> args;

  while (iss >> buf) {
    args.push_back(buf);
  }

  return args;
}

void UserInterface::get_initial_state() {
  std::string line;
  std::getline(cin, line);

  std::vector<string> args = split_string(line);
  for (string table_capacity : args) {
    int capacity = std::stoi(table_capacity);
  }
}
