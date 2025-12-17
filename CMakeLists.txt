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
    #src/mcts.cpp
    #src/negamax.cpp
    src/Tic_Tac_Toe.cpp
    src/Ultimate_Tic_Tac_Toe.cpp
    # Add all other .cpp files here
)

add_subdirectory(lib/Random-Helper)
add_subdirectory(lib/Timer)

target_link_libraries(Ultimate-Tic-Tac-Tao PRIVATE Random-Helper::Random-Helper Timer::Timer)

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

option(Ultimate-Tic-Tac-Tao_BUILD_TESTS "Build tests" ${PROJECT_IS_TOP_LEVEL})
if (Ultimate-Tic-Tac-Tao_BUILD_TESTS)
    include(FetchContent)

    FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.11.0
    )

    FetchContent_MakeAvailable(Catch2)

    enable_testing()
    add_executable(Ultimate-Tic-Tac-TaoTests
        tests/test_main.cpp
        src/Tic_Tac_Toe.cpp
        src/Ultimate_Tic_Tac_Toe.cpp
        # Add all other .cpp files here
    )
    target_link_libraries(Ultimate-Tic-Tac-TaoTests PRIVATE Catch2::Catch2WithMain Random-Helper::Random-Helper Timer::Timer)
    target_include_directories(Ultimate-Tic-Tac-TaoTests PRIVATE ${PROJECT_SOURCE_DIR}/include)
    include(Catch)
    catch_discover_tests(Ultimate-Tic-Tac-TaoTests)
endif()
