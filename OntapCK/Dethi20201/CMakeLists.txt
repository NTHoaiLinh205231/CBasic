project(ontap C)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cgen)
add_executable(prog dethi2020.c cgen/all.c)