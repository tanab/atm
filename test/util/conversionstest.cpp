#include <gmock/gmock.h>
#include <util.h>
#include <string>

using namespace std;
using namespace atm::util;

TEST(BoolVectorConversions, ConvertsStringToBitVector) {
    auto temp = "ATM";
    auto bool_vector = to_bool_vector(temp);
    ASSERT_EQ(static_cast<vector<bool>::size_type>(24), bool_vector.size());
    string outcome;
    for(const auto & bool_value : bool_vector) {
        outcome.append(bool_value ? "1" : "0");
    }
    ASSERT_EQ("010000010101010001001101", outcome);
}
