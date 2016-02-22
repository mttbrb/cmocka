project(NewIpDaemonProject)
cmake_minimum_required (VERSION 2.6)
project(newIpDaemon)

include_directories(include)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(SOURCES
  src/newIpDaemon.c
   )

add_executable(newIpDaemon ${SOURCES})

target_link_libraries(newIpDaemon cmocka)
