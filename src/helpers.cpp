#include "../lib/helpers.h"

std::vector<std::string> helpers::split_string(std::string raw_line) {
  std::istringstream iss(raw_line);
  std::string buf;
  std::vector<std::string> args;

  while (iss >> buf) {
    args.push_back(buf);
  }

  return args;
}

std::string helpers::join_strings(std::vector<std::string> args) {
  std::string query = "";
  for (int i = 0; i < args.size(); i++) {
    query += args[i];
    if (i+1 != args.size()) query += " ";
  }

  return query;
}
