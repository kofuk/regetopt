# This file is part of regetopt.
# reGetopt is licensed under GNU GPL v3 or MIT License.

project(regetopt C CXX)
cmake_minimum_required(VERSION 3.15)

enable_testing()
find_package(Boost COMPONENTS unit_test_framework)

add_library(regetopt_static STATIC regetopt.c)
add_library(regetopt SHARED regetopt.c)
target_compile_definitions(regetopt PUBLIC -DREGETOPT_DLL)
set_target_properties(regetopt regetopt_static PROPERTIES
  PUBLIC_HEADER include/regetopt.h)

add_executable(sample EXCLUDE_FROM_ALL sample.c)
target_link_libraries(sample PRIVATE regetopt_static)

configure_file(regetopt.pc.in regetopt.pc @ONLY)
configure_file(regetopt_static.pc.in regetopt_static.pc @ONLY)

install(TARGETS regetopt_static regetopt
  EXPORT regetopt
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
  PUBLIC_HEADER DESTINATION include/regetopt)
install(EXPORT regetopt
  FILE regetopt-config.cmake
  DESTINATION lib/regetopt)
install(FILES ${CMAKE_BINARY_DIR}/regetopt.pc ${CMAKE_BINARY_DIR}/regetopt_static.pc DESTINATION lib/pkgconfig)

add_subdirectory(tests)
