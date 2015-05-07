#include <util.h>
#include <iostream>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

using namespace std;
using namespace boost;

namespace atm {
namespace util {

vector<bool> to_bool_vector(const string &data) {
    vector<bool> ret_val;
    for (const auto &letter : data) {
        unsigned char value = letter;
        unsigned char bitmask = 0x80;
        for (int i = 0; i < 8; i++) {
            ret_val.push_back((value & bitmask) > 0);
            bitmask = bitmask >> 1;
        }
    }
    return ret_val;
}

vector<wstring> split(const wstring &input, const wstring &delimiter) {
    vector<wstring> output;
    boost::split(output, input, is_any_of(delimiter), token_compress_on);
    return output;
}

vector<string> split(const string &input, const string &delimiter) {
    vector<string> output;
    boost::split(output, input, is_any_of(delimiter), token_compress_on);
    return output;
}
}
}
