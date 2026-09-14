cmake_minimum_required(VERSION 3.16)
project(LW1 LANGUAGES CXX)

add_executable(LW1 "LW1.cpp")

target_compile_features(LW1 PRIVATE cxx_std_20)

if(MSVC)
    target_compile_options(LW1 PRIVATE /utf-8)
endif()