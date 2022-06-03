#ifndef LIB_HELPERS_H_
#define LIB_HELPERS_H_

#include <sstream>
#include <string>
#include <vector>

namespace helpers {

std::vector<std::string> split_string(std::string raw_line);

std::string join_strings(std::vector<std::string> args);

}  // namespace helpers

#endif  // LIB_HELPERS_H_
