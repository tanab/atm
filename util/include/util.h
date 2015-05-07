#pragma once

#include <string>
#include <vector>

namespace atm {
namespace util {
std::vector<bool> to_bool_vector(const std::string &data);
std::vector<std::wstring> split(const std::wstring &input, const std::wstring &delimiter);
std::vector<std::string> split(const std::string &input, const std::string &delimiter);
}
}
