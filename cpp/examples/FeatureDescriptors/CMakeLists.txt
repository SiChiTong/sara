cmake_minimum_required(VERSION 2.6)

project(DO_FeatureDescriptors_Examples)

message(STATUS "  - DO_FeatureDescriptors_Examples")

find_package(DO_Sara COMPONENTS
  Core Graphics ImageIO
  Features FeatureDetectors FeatureDescriptors REQUIRED)

macro (sara_add_example example)
  add_executable(${example} ${example}.cpp)
  set_target_properties(${example} PROPERTIES
                        COMPILE_FLAGS ${SARA_DEFINITIONS})
  target_link_libraries(${example} ${DO_Sara_LIBRARIES})
  set_property(TARGET ${example}
    PROPERTY
    FOLDER "DO Sara Examples/FeatureDescriptors")
endmacro ()

sara_add_example(sift_example)
