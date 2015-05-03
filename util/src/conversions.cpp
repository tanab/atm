#include <conversions.h>
#include <iostream>

using namespace std;

namespace atm {
namespace conversions {
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
}
}
