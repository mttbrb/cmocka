project(SampleCmockaCmakeProject)
cmake_minimum_required (VERSION 2.6)
project(example)

include_directories(include)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(SOURCES
  src/example.c
  src/example2.c)

add_executable(example ${SOURCES})

target_link_libraries(example cmocka)


