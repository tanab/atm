#include <gmock/gmock.h>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <string>
#include <vector>
#include <tree.h>
#include <mysqlcache.h>
#include <letters.hpp>

using namespace std;
using namespace boost;

class AffixTreeTests : public ::testing::Test {
  protected:
    virtual void SetUp() {
        cache = new atm::cache::MySqlCache();
        cache->initCache();
    }

    virtual void TearDown() { delete cache; }

    atm::cache::MySqlCache *cache;
};

TEST(ApplyingInflections, ApplyingInflectionsOnASpacesOnlyStringShouldNotChangeIt) {
    std::wstring input = L"     ";
    ASSERT_EQ(true, input.find_first_not_of(L' ') == std::wstring::npos);
}

TEST_F(AffixTreeTests, PrefixTreeGenerationShouldNotFail) {
    atm::common::Tree tree(cache);
    ASSERT_TRUE(tree.buildAffixTree(ItemTypes::PREFIX));
    tree.printTree();
}

TEST_F(AffixTreeTests, SuffixTreeGenerationShouldNotFail) {
    atm::common::Tree tree(cache);
    ASSERT_TRUE(tree.buildAffixTree(ItemTypes::SUFFIX));
    tree.printTree();
}

TEST_F(AffixTreeTests, StemTreeGenerationShouldNotFail) {
    atm::common::Tree tree(cache);
    ASSERT_TRUE(tree.buildAffixTree(ItemTypes::STEM));
    tree.printTree();
}
