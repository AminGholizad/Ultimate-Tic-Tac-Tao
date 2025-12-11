cmake_minimum_required(VERSION 3.15)
project(Ultimate-Tic-Tac-Tao LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

add_executable(Ultimate-Tic-Tac-Tao
    src/main.cpp
    src/mcts.cpp
    src/negamax.cpp
    src/ttt.cpp
    src/uttt.cpp
    # Add all other .cpp files here
)

set_target_properties(Ultimate-Tic-Tac-Tao PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

target_include_directories(Ultimate-Tic-Tac-Tao PRIVATE
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

target_compile_options(Ultimate-Tic-Tac-Tao PRIVATE
    -Wall -Wextra -Werror
    -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align
    -Wunused -Wpedantic -Wconversion -Wsign-conversion
    -Wnull-dereference -Wdouble-promotion -Wformat=2
    -Wimplicit-fallthrough
)
target_compile_options(Ultimate-Tic-Tac-Tao PRIVATE
    \$<$<CONFIG:Debug>:-O0>
    \$<$<CONFIG:Release>:-O3 -DNDEBUG>
    \$<$<CONFIG:MinSizeRel>:-Os -DNDEBUG>
    \$<$<CONFIG:RelWithDebInfo>:-O2 -DNDEBUG>
)
target_link_options(Ultimate-Tic-Tac-Tao PRIVATE
    \$<$<CONFIG:Debug>:-g>
    \$<$<CONFIG:RelWithDebInfo>:-g>
)

option(Ultimate-Tic-Tac-Tao_BUILD_TESTS "Build tests" ON)
if (Ultimate-Tic-Tac-Tao_BUILD_TESTS)
    enable_testing()
    add_executable(Ultimate-Tic-Tac-TaoTests
        tests/test_main.cpp
        # Add all other .cpp files here
    )
    target_include_directories(Ultimate-Tic-Tac-TaoTests PRIVATE ${PROJECT_SOURCE_DIR}/include)
    add_test(NAME Ultimate-Tic-Tac-TaoTests COMMAND Ultimate-Tic-Tac-TaoTests)
endif()
