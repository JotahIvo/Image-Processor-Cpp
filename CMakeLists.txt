cmake_minimum_required(VERSION 3.10)

project(ImageProcessor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(processor
    src/main.cpp
    src/Image.cpp
)

target_include_directories(processor PUBLIC include)
