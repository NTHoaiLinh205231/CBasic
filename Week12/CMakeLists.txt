project(songs C)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cgen)
add_executable(prog bai10-1.c menu.c sort.c cgen/all.c)