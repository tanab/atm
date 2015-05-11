#pragma once

#include <string>
#include <vector>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

namespace atm {
namespace util {
std::vector<bool> to_bool_vector(const std::string &data);

template <class STRING_TYPE>
std::vector<STRING_TYPE> split(const STRING_TYPE &input, const STRING_TYPE &delimiter) {
    std::vector<STRING_TYPE> output;
    boost::split(output, input, boost::is_any_of(delimiter), boost::token_compress_on);
    return output;


}
}
}
