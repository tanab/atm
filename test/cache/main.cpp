#include <gmock/gmock.h>
#include <mysqlcache.h>
#include <iostream>
#include <locale>

int main(int argc, char *argv[]) {
  testing::InitGoogleMock(&argc, argv);
  atm::cache::AtmCache *cache = new atm::cache::MySqlCache();
  cache->initCache();
  auto tmp = cache->findAffixCategories(3);
  auto tmp2 = cache->findAffixName(ItemTypes::PREFIX, 3);
  delete cache;
  return RUN_ALL_TESTS();
}
