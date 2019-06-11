cmake_minimum_required(VERSION 3.2)
set(MAJOR_VERSION 0)
set(MINOR_VERSION 0)
set(PATCH_VERSION 999)
if($ENV{MAJOR_VERSION})
    set(MAJOR_VERSION $ENV{MAJOR_VERSION})
endif()
if($ENV{MINOR_VERSION})
    set(MINOR_VERSION $ENV{MINOR_VERSION})
endif()
if($ENV{CIRCLE_BUILD_NUM})
    set(PATCH_VERSION $ENV{CIRCLE_BUILD_NUM})
endif()

project(bulk_server VERSION ${MAJOR_VERSION}.${MAJOR_VERSION}.${PATCH_VERSION})
configure_file(version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/version.h)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)

add_executable(bulk_server
    main.cpp
    server.cpp
    session.cpp
    )
find_package(Boost REQUIRED system)
include_directories(${Boost_INCLUDE_DIRS})

set_target_properties(bulk_server PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)
 
target_link_libraries(bulk_server
    async
)

install(TARGETS bulk_server RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT podshivalov.ilya@yandex.ru)
include(CPack)
add_test(bulk_test_version ${CMAKE_CURRENT_BINARY_DIR}/tests/test_version)
add_test(bulk_test_multithreading ${CMAKE_CURRENT_BINARY_DIR}/tests/test_multithreading)
enable_testing()
