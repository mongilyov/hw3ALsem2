cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BOOST_COMPONENTS
        program_options)

project(hw3 VERSION 0.1.0)

find_package(Boost CONFIG REQUIRED ${BOOST_COMPONENTS})

add_library(Cipher
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/Cipher.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/HandleFunctions.cpp)

add_executable(demo
        ${CMAKE_CURRENT_SOURCE_DIR}/demo/main.cpp
        )

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(demo ${Boost_LIBRARIES} Cipher)
