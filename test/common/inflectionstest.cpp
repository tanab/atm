#include <gmock/gmock.h>

#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>

using namespace std;
using namespace boost;

TEST(ApplyingInflections, ApplyingInflectionsOnASpacesOnlyStringShouldNotChangeIt) {
    std::wstring input = L"     ";
    ASSERT_EQ(true, input.find_first_not_of(L' ') == std::wstring::npos);
}
