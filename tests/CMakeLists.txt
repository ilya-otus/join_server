cmake_minimum_required(VERSION 3.12)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
add_executable(test_version test_version.cpp)
set_target_properties(test_version PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
    INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/../src/
)
target_link_libraries(test_version
    ${Boost_LIBRARIES}
    join
)

set_target_properties(test_version PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

