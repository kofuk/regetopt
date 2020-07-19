# This file is part of regetopt.
# reGetopt is licensed under GNU GPL v3 or MIT License.

add_custom_target(test_executable)

function(add_boost_test target_name test_name)
  if(NOT Boost_FOUND)
    return()
  endif()

  add_executable(${target_name} EXCLUDE_FROM_ALL ${ARGN})
  target_include_directories(${target_name} PRIVATE SYSTEM ${Boost_INCLUDE_DIRS})
  target_compile_definitions(${target_name} PRIVATE -DBOOST_TEST_DYN_LINK=1)
  target_compile_definitions(${target_name} PRIVATE -DBOOST_TEST_MAIN)
  target_link_libraries(${target_name} PRIVATE ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
  target_link_libraries(${target_name} PRIVATE regetopt_static)

  add_dependencies(test_executable ${target_name})

  add_test(NAME ${test_name} COMMAND ${target_name})
endfunction()

set(TESTS test_case_1;test_case_2;mixed;with_argument;need_reorder;optional_argument)

foreach(TC ${TESTS})
  add_boost_test(${TC} ${TC} ${TC}.cc)
endforeach()
