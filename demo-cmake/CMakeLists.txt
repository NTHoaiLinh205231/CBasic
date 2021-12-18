project(demo C)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cgen)
add_executable(prog main.c cgen/all.c)