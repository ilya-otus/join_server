cmake_minimum_required(VERSION 3.2)
add_library(blk
    brace_handler.cpp
    bulk.cpp
    bulk_proxy.cpp
    command_handler.cpp
    console_output.cpp
    file_output.cpp
    handler.cpp
    handler_fabric.cpp
    output_buffer.cpp
    output_item_abstract.cpp
    lib.cpp
    )

find_package(Threads)
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set_target_properties(blk PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)
target_link_libraries(blk stdc++fs ${CMAKE_THREAD_LIBS_INIT})
