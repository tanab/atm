#include <gmock/gmock.h>
#include <mysqlcache.h>
#include <iostream>
#include <locale>

int main(int argc, char *argv[]) {
  testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
