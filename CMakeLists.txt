cmake_minimum_required(VERSION 3.12)

#project(ip_filter VERSION ${PROJECT_VESRION})
project(ip_filter)


add_executable(ip_filter_cli main.cpp)
add_library(ip_filter ip_filter.cpp)

set_target_properties(ip_filter_cli PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

set_target_properties(ip_filter PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(ip_filter PRIVATE "${CMAKE_BINARY_DIR}")
target_link_libraries(ip_filter_cli PRIVATE ip_filter)