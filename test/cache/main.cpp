#include <gmock/gmock.h>
#include <mysqlcache.h>
#include <iostream>
#include <locale>

int main(int argc, char *argv[]) {
  testing::InitGoogleMock(&argc, argv);
  AtmCache *cache = new MySqlCache();
  cache->initCache();
  delete cache;
  return RUN_ALL_TESTS();
}
