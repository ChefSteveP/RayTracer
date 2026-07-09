cmake_minimum_required(VERSION 3.0.0...3.7.0)
project(renderer VERSION 0.1.0 LANGUAGES C CXX)

add_executable(renderer 
        src/main.cc)

target_include_directories(renderer PRIVATE include) # private means only renderer uses them