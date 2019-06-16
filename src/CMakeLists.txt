cmake_minimum_required(VERSION 3.2)
add_compile_definitions($<$<CONFIG:DEBUG>:DEBUG>)
add_library(join # SHARED
    handler.cpp
    insert_handler.cpp
    intersection_handler.cpp
    lib.cpp
    parser.cpp
    server.cpp
    session.cpp
    storage.cpp
    symmetric_difference_handler.cpp
    truncate_handler.cpp
    )

find_package(Threads)
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set_target_properties(join PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${MAJOR_VERSION}
    PUBLIC_HEADER lib.h
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)
target_link_libraries(join stdc++fs ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(join PUBLIC .)
include(GNUInstallDirs)
install(TARGETS join
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
