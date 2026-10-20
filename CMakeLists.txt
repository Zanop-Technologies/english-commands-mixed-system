cmake_minimum_required(VERSION 3.16)
project(ecmxs LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(ecmxs
    src/main.cpp
    src/parser.cpp
    src/dispatcher.cpp
    src/frt.cpp
)
target_include_directories(ecmxs PRIVATE src)
