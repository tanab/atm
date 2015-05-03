# This is an ugly hack!!!
# Untill mysql people provide reasonable cmake module we have to hardcode this.

if(CMAKE_SYSTEM_NAME STREQUAL Darwin)
  set(MYSQLCPPCONN_INCLUDE_DIRS /opt/local/include/mysql55-connector-cpp)
  set(MYSQLCPPCONN_LIBRARY_DIRS /opt/local/lib/mysql55-connector-cpp)
  set(MYSQLCPPCONN_LIBRARIES mysqlcppconn)
endif(CMAKE_SYSTEM_NAME STREQUAL Darwin)
