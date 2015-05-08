#include <gmock/gmock.h>
#include <util.h>
#include <string>

using namespace std;
using namespace atm::util;

TEST(StringSplitting, SplitsWideStrings) {
    const wstring temp = L"A T M";
    const wstring delimiter = L" ";
    auto output = split(temp, delimiter);
    ASSERT_EQ(static_cast<vector<wstring>::size_type>(3), output.size());
    ASSERT_EQ(L"A", output.at(0));
    ASSERT_EQ(L"T", output.at(1));
    ASSERT_EQ(L"M", output.at(2));
}

TEST(StringSplitting, SplitsStrings) {
    string temp = "A T M";
    string delimiter = " ";
    auto output = split(temp, delimiter);
    ASSERT_EQ(static_cast<vector<wstring>::size_type>(3), output.size());
    ASSERT_EQ("A", output.at(0));
    ASSERT_EQ("T", output.at(1));
    ASSERT_EQ("M", output.at(2));
}
