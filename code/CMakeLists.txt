cmake_minimum_required(VERSION "3.20.0")

project(RPIOpenES VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(
            "-Wall" "-Wextra" "-Werror"
            "-Wnon-virtual-dtor" "-Wcast-align" "-Wunused"
            "-Woverloaded-virtual"
            "-fexceptions" "-pedantic"
            "-O2" "-no-pie"
    )
endif()

find_package(Threads REQUIRED)

# Source files
set(SOURCES
    main.cpp
    timer.cpp
)

# Libraries to link against
set(LIBS Threads::Threads)

# Add the executable
add_executable(main.out ${SOURCES})

# Link libraries
target_link_libraries(main.out ${LIBS})