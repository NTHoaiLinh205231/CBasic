project(ontap C)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cgen)
add_executable(prog bai12.c cgen/all.c)