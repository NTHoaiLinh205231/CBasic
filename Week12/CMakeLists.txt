project(songs C)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cgen)
add_executable(prog bai10-2.c cgen/all.c)