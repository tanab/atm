#include <gmock/gmock.h>
#include <iostream>
#include <mysqlcache.h>
#include <enums.hpp>

using namespace std;

class MySqlCacheTests : public ::testing::Test {
  protected:
    virtual void SetUp() {
        cache = new atm::cache::MySqlCache();
        cache->initCache();
    }

    virtual void TearDown() { delete cache; }

    atm::cache::MySqlCache *cache;
};

TEST_F(MySqlCacheTests, CheckPrefixCategorySearch) {
    auto prefix_categories = cache->findPrefixCategories(14);
    int j = 0;
    for (auto it = prefix_categories.first; it != prefix_categories.second; it++) {
        std::cout << "prefix_id: " << it->second.affix_id
                  << " category_id: " << it->second.category_id << std::endl;
        j++;
    }
    ASSERT_EQ(2, j);
}

TEST_F(MySqlCacheTests, CheckPrefixCompatibilityRulesSearch) {
    auto type = ItemTypes::PREFIX;
    auto compatibility_rules =
        cache->findCompatibilityRules((type == ItemTypes::PREFIX ? Rules::AA : Rules::CC), 3);
    int j = 0;
    for (auto it_comp_rules = compatibility_rules.first;
         it_comp_rules != compatibility_rules.second; it_comp_rules++) {
        std::cout << "category_id1: " << it_comp_rules->second.category_id_1 << " ";
        std::cout << "category_id2: " << it_comp_rules->second.category_id_2 << " ";
        std::cout << "resulting cateogry: " << it_comp_rules->second.resulting_category << std::endl;
        j++;
    }

    ASSERT_EQ(32, j);
}
