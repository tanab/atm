#include <gmock/gmock.h>
#include <diacritics.hpp>
#include <mysqlcache.h>
#include <tree.h>

int main(int argc, char *argv[]) {
  testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
