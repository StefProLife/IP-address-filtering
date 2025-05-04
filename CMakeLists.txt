cmake_minimum_required(VERSION 3.12)

#project(ip_filter VERSION ${PROJECT_VESRION})
project(ip_filter)

set(SOURCES_FILE ip_filter.cpp)

add_executable(ip_filter_cli ${SOURCES_FILE})

set_target_properties(ip_filter_cli PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)