cmake_minimum_required(VERSION 2.6)

project(DO_Core_tests)

message(STATUS "  - DO_Core_Tests")

find_package(DO_Sara COMPONENTS Core REQUIRED)

set(TestGroupName "Core")

file(GLOB test_core_SOURCE_FILES FILES *.cpp)

foreach (file ${test_core_SOURCE_FILES})
  get_filename_component(filename "${file}" NAME_WE)
  sara_add_test(${filename} ${file} "${DO_Sara_LIBRARIES}" ${TestGroupName})
endforeach ()
