cmake_minimum_required(VERSION 3.2)
add_compile_definitions($<$<CONFIG:DEBUG>:DEBUG>)
add_library(async SHARED
    async.cpp
    async_impl.cpp
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

set_target_properties(async PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${MAJOR_VERSION}
    PUBLIC_HEADER async.h
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)
target_link_libraries(async stdc++fs ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(async PUBLIC .)
include(GNUInstallDirs)
install(TARGETS async
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
